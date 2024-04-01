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
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float Min(float a, float b)
{
    return (a < b) ? a : b;
}

float ClosestPairRecursive(const std::vector<PointType> &pointsSortedX, const std::vector<PointType> &pointsSortedY)
{
    size_t n = pointsSortedX.size();
    if (n <= 3)
    {
        float minDist = std::numeric_limits<float>::max();
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = i + 1; j < n; ++j)
            {
                minDist = std::min(minDist, Distance(pointsSortedX[i], pointsSortedX[j]));
            }
        }
        return minDist;
    }

    size_t mid = n / 2;
    PointType midPoint = pointsSortedX[mid];

    std::vector<PointType> leftY, rightY;
    for (const auto &point : pointsSortedY)
    {
        if (point.x <= midPoint.x)
        {
            leftY.push_back(point);
        }
        else
        {
            rightY.push_back(point);
        }
    }

    float distLeft = ClosestPairRecursive(std::vector<PointType>(pointsSortedX.begin(), pointsSortedX.begin() + mid), leftY);
    float distRight = ClosestPairRecursive(std::vector<PointType>(pointsSortedX.begin() + mid, pointsSortedX.end()), rightY);

    float d = std::min(distLeft, distRight);

    // Construct the strip
    std::vector<PointType> strip;
    for (const auto &point : pointsSortedY)
    {
        if (fabs(point.x - midPoint.x) < d)
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

    std::vector<PointType> pointsSortedX = points;
    std::vector<PointType> pointsSortedY = points;
    std::sort(pointsSortedX.begin(), pointsSortedX.end(), [](const PointType &a, const PointType &b)
              { return a.x < b.x; });
    std::sort(pointsSortedY.begin(), pointsSortedY.end(), [](const PointType &a, const PointType &b)
              { return a.y < b.y; });

    float minDist = ClosestPairRecursive(pointsSortedX, pointsSortedY);

    for (size_t i = 0; i < points.size(); ++i)
    {
        for (size_t j = i + 1; j < points.size(); ++j)
        {
            float dist = Distance(points[i], points[j]);
            if (dist == minDist)
            {
                if (points[i].ID < points[j].ID)
                {
                    p1 = points[i];
                    p2 = points[j];
                }
                else
                {
                    p1 = points[j];
                    p2 = points[i];
                }
                break;
            }
        }
    }

    return std::round(minDist * 1000.0f) / 1000.0f;
    /*------ CODE ENDS ------*/
}

#endif
