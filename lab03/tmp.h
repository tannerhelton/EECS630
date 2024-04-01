#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

#ifndef _MY_CLOSEST_PAIR_POINTS_H_
#define _MY_CLOSEST_PAIR_POINTS_H_

typedef struct
{
    unsigned int ID; // the ID of the point
    float x;         // the x-coordinate of the point
    float y;         // the y-coordinate of the point
} PointType;

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
    float minDistance = d; // Initialize the minimum distance as d

    // Sort the points according to y-coordinate
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
    // If there are 2 or 3 points, then use brute force
    if (right - left <= 2)
    {
        return bruteForce(points, left, right, p1, p2);
    }

    // Find the middle point
    int mid = left + (right - left) / 2;
    PointType midPoint = points[mid];

    PointType pl1, pl2, pr1, pr2;
    float dl = closestUtil(points, left, mid, pl1, pl2);
    float dr = closestUtil(points, mid + 1, right, pr1, pr2);

    // Update the closest pair from the left and right halves
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

    // Ensure that p1 has the smaller ID
    if (p1.ID > p2.ID)
    {
        std::swap(p1, p2);
    }

    float d = std::min(dl, dr);

    // Build an array strip[] that contains points close (closer than d)
    // to the line passing through the middle point
    std::vector<PointType> strip;
    for (int i = left; i <= right; i++)
    {
        if (std::abs(points[i].x - midPoint.x) < d)
        {
            strip.push_back(points[i]);
        }
    }

    // Find the closest points in strip
    PointType strip_p1, strip_p2;
    float strip_d = stripClosest(strip, d, strip_p1, strip_p2);

    // Check if the closest pair is in the strip
    if (strip_d < d)
    {
        p1 = strip_p1;
        p2 = strip_p2;
    }

    // Ensure that p1 has the smaller ID
    if (p1.ID > p2.ID)
    {
        std::swap(p1, p2);
    }

    return std::min(d, strip_d);
}

float ClosestPairOfPoints(std::vector<PointType> &points, PointType &p1, PointType &p2)
{
    // Check if there are at least two points
    if (points.size() < 2)
    {
        std::cerr << "Error: At least two points are required.\n";
        return std::numeric_limits<float>::infinity();
    }

    // Sort the points by X-coordinate
    std::sort(points.begin(), points.end(), compareX);

    // Use recursive function closestUtil() to find the smallest distance
    float minDistance = closestUtil(points, 0, points.size() - 1, p1, p2);

    // Round the distance to 3 digits
    minDistance = std::round(minDistance * 1000.0) / 1000.0;
    return minDistance;
}

#endif // _MY_CLOSEST_PAIR_POINTS_H_