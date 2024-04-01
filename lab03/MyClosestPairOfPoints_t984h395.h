#ifndef _MY_CLOSEST_PAIR_POINTS_H_
#define _MY_CLOSEST_PAIR_POINTS_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
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
float Distance(const PointType &a, const PointType &b)
{
    return std::hypot(a.x - b.x, a.y - b.y);
}

float ClosestPairRecursive(const std::vector<PointType> &pointsSortedX, std::vector<PointType> &pointsSortedY, size_t start, size_t end)
{
    size_t n = end - start;
    if (n <= 3)
    {
        float minDist = std::numeric_limits<float>::max();
        for (size_t i = start; i < end; ++i)
        {
            for (size_t j = i + 1; j < end; ++j)
            {
                minDist = std::min(minDist, Distance(pointsSortedX[i], pointsSortedX[j]));
            }
        }
        return minDist;
    }

    size_t mid = start + n / 2;
    PointType midPoint = pointsSortedX[mid];

    float distLeft = ClosestPairRecursive(pointsSortedX, pointsSortedY, start, mid);
    float distRight = ClosestPairRecursive(pointsSortedX, pointsSortedY, mid, end);

    float d = std::min(distLeft, distRight);

    std::vector<PointType> strip;
    for (const auto &point : pointsSortedY)
    {
        if (std::abs(point.x - midPoint.x) < d)
        {
            strip.push_back(point);
        }
    }

    for (size_t i = 0; i < strip.size(); ++i)
    {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; ++j)
        {
            d = std::min(d, Distance(strip[i], strip[j]));
        }
    }

    return d;
}

float ClosestPairOfPoints(
    const std::vector<PointType> &points,
    PointType &p1,
    PointType &p2)
{
    /*------ CODE BEGINS ------*/
    if (points.size() < 2)
    {
        return 0.0f;
    }

    std::vector<PointType> pointsSortedX = points, pointsSortedY = points;
    std::sort(pointsSortedX.begin(), pointsSortedX.end(), [](const PointType &a, const PointType &b)
              { return a.x < b.x; });
    std::sort(pointsSortedY.begin(), pointsSortedY.end(), [](const PointType &a, const PointType &b)
              { return a.y < b.y; });

    float minDist = ClosestPairRecursive(pointsSortedX, pointsSortedY, 0, points.size());

    // Avoid recalculating the distance by storing them
    for (size_t i = 0; i < points.size(); ++i)
    {
        for (size_t j = i + 1; j < points.size(); ++j)
        {
            float dist = Distance(points[i], points[j]);
            if (dist == minDist)
            {
                p1 = points[i].ID < points[j].ID ? points[i] : points[j];
                p2 = points[i].ID < points[j].ID ? points[j] : points[i];
                break;
            }
        }
    }

    return std::round(minDist * 1000.0f) / 1000.0f;
    /*------ CODE ENDS ------*/
}

#endif
