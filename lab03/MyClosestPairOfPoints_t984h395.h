#ifndef _MY_CLOSEST_PAIR_POINTS_H_
#define _MY_CLOSEST_PAIR_POINTS_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <fstream>

typedef struct
{
    unsigned int ID; // the ID of the point
    float x;         // the x-coordinate of the point
    float y;         // the y-coordinate of the point
} PointType;

/*------------------------------------------------------------------------------
    ClosestPairOfPoints: find the closest pair of points from a set of points in a 2D plane

        points: the set of points
        p1: the first point of the closest pair of points; should have a smaller ID
        p2: the second point of the closest pair of points; should have a larger ID

        returns the distance between the two points (round to 3-digit precision)
------------------------------------------------------------------------------*/

// Helper functions
bool compareX(const PointType &a, const PointType &b)
{
    return a.x < b.x;
}

bool compareY(const PointType &a, const PointType &b)
{
    return a.y < b.y;
}

float dist(const PointType &p1, const PointType &p2)
{
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

float bruteForce(const std::vector<PointType> &points, int left, int right, PointType &p1, PointType &p2)
{
    float minDistance = std::numeric_limits<float>::infinity();
    for (int i = left; i < right; ++i)
    {
        for (int j = i + 1; j <= right; ++j)
        {
            float d = dist(points[i], points[j]);
            if (d < minDistance)
            {
                minDistance = d;
                p1 = points[i];
                p2 = points[j];
            }
        }
    }
    return minDistance;
}

float stripClosest(std::vector<PointType> &strip, float d, PointType &p1, PointType &p2)
{
    float minDistance = d;
    std::sort(strip.begin(), strip.end(), compareY);

    for (size_t i = 0; i < strip.size(); ++i)
    {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDistance; ++j)
        {
            float d = dist(strip[i], strip[j]);
            if (d < minDistance)
            {
                minDistance = d;
                p1 = strip[i];
                p2 = strip[j];
            }
        }
    }

    return minDistance;
}

float closestUtil(std::vector<PointType> &points, int left, int right, PointType &p1, PointType &p2)
{
    if (right - left <= 2)
    {
        return bruteForce(points, left, right, p1, p2);
    }

    int mid = left + (right - left) / 2;
    PointType midPoint = points[mid];

    PointType pl1, pl2, pr1, pr2;
    float dl = closestUtil(points, left, mid, pl1, pl2);
    float dr = closestUtil(points, mid + 1, right, pr1, pr2);
    if (dl < dr)
    {
        p1 = pl1;
        p2 = pl2;
    }
    else
    {
        p1 = pr1;
        p2 = pr2;
    }

    if (p1.ID > p2.ID)
    {
        std::swap(p1, p2);
    }

    float d = std::min(dl, dr);
    std::vector<PointType> strip;
    for (int i = left; i <= right; i++)
    {
        if (std::abs(points[i].x - midPoint.x) < d)
        {
            strip.push_back(points[i]);
        }
    }
    PointType strip_p1, strip_p2;
    float strip_d = stripClosest(strip, d, strip_p1, strip_p2);

    if (strip_d < d)
    {
        p1 = strip_p1;
        p2 = strip_p2;
    }

    if (p1.ID > p2.ID)
    {
        std::swap(p1, p2);
    }

    return std::min(d, strip_d);
}

float ClosestPairOfPoints(
    const std::vector<PointType> &points,
    PointType &p1,
    PointType &p2)
{
    /*------ CODE BEGINS ------*/
    if (points.size() < 2)
    {
        std::cerr << "Error: At least two points are required.\n";
        return std::numeric_limits<float>::infinity();
    }

    std::vector<PointType> pointsCopy = points;
    std::sort(pointsCopy.begin(), pointsCopy.end(), compareX);

    float minDistance = closestUtil(pointsCopy, 0, pointsCopy.size() - 1, p1, p2);
    minDistance = std::round(minDistance * 1000.0) / 1000.0;

    return minDistance;
    /*------ CODE ENDS ------*/
}

#endif
