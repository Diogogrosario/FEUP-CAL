/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

const double MAX_DOUBLE = std::numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
	this->dmin = dmin;
	this->p1 = p1;
	this->p2 = p2;
}

Result::Result() {
	this->dmin = MAX_DOUBLE;
	this->p1 = Point(0,0);
	this->p2 = Point(0,0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {

    Result res;

	for(int i = 0;i < vp.size();i++){
	    for(int j = i+1;j<vp.size();j++){
	        double dist = vp.at(i).distance(vp.at(j));
	        if(dist < res.dmin){
	            res.dmin = dist;
	            res.p1 = vp.at(i);
	            res.p2 = vp.at(j);
	        }
	    }

	}
	return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	Result res;
	sortByX(vp, 0, vp.size()-1);
    for(int i = 0;i < vp.size();i++){
        for(int j = i+1;j<vp.size();j++){
            double dist = vp.at(i).distance(vp.at(j));
            if(dist < res.dmin){
                res.dmin = dist;
                res.p1 = vp.at(i);
                res.p2 = vp.at(j);
            }
        }

    }
	return res;
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res)
{
    double curr;
    for (int i = left; i < right - 1; ++i) {
        for (int j = i + 1; j < right; ++j) {
            if (vp.at(j).y - vp.at(i).y > res.dmin)
                break;

            if ((curr = vp.at(i).distance(vp.at(j))) < res.dmin) {
                res.dmin = curr;
                res.p1 = vp.at(i);
                res.p2 = vp.at(j);
            }
        }
    }
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {
    Result res;
	// Base case of two points
	if( (right-left) == 1){
	    res.p1 = vp[0];
	    res.p2 = vp[1];
	    res.dmin = vp[0].distance(vp[1]);
	    return res;
	}

	// Base case of a single point: no solution, so distance is MAX_DOUBLE
	else if(right -left == 0){
	    return res;
	}


	int middle = (right+left)/2;
	// Divide in halves (left and right) and solve them recursively,
	// possibly in parallel (in case numThreads > 1)
	Result resLeft;
	Result resRight;
	if(numThreads<=1) {
	    resLeft = np_DC(vp, left, middle, numThreads);
        resRight = np_DC(vp, middle + 1, right, numThreads);
    }
	else{
        std::thread t([&vp, &resLeft, left, middle, numThreads] {
            vector<Point> vv(vp); // copy array -> multiple threads might sort part of it at the same time
            resLeft = np_DC(vv, left, middle, numThreads / 2);
        });
        resRight = np_DC(vp, middle + 1, right, numThreads / 2);
        t.join(); // wait for the other thread
    }

	// Select the best solution from left and right
	if(resLeft.dmin < resRight.dmin){
	    res = resLeft;
	}
	else{
	    res = resRight;
	}

	// Determine the strip area around middle point
    int strip_l, strip_r;
    for (strip_l = middle; strip_l >= left; --strip_l) {
        if (vp.at(middle).x - vp.at(strip_l).x > res.dmin)
            break;
    }
    ++strip_l;
    for (strip_r = middle + 1; strip_r <= right; ++strip_r) {
        if (vp.at(strip_l).x - vp.at(middle).x > res.dmin)
            break;
    }
    --strip_r;

	// Order points in strip area by Y coordinate
	sortByY(vp,left,right);

	// Calculate nearest points in strip area (using npByY function)
    npByY(vp,left,right,res);

	// Reorder points in strip area back by X coordinate
	sortByX(vp,left,right);

	return res;
}


/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num)
{
	numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, 1);
}


/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, numThreads);
}
