#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point
{
    int x;
    int y;
};

int orientation(const Point &first, const Point &second, const Point &third)
{
    int value = (second.y - first.y) * (third.x - second.x) - (second.x - first.x) * (third.y - second.y);

    if (value == 0)
    {
        return 0;
    }

    return (value > 0) ? 1 : -1;
}

int squaredDistance(const Point &first, const Point &second)
{
    int deltaX = first.x - second.x;
    int deltaY = first.y - second.y;

    return deltaX * deltaX + deltaY * deltaY;
}

vector<Point> grahamScan(vector<Point> points)
{
    int numberOfPoints = points.size();
    vector<Point> hull;

    if (numberOfPoints < 3)
    {
        return points;
    }

    int lowestIndex = 0;
    for (int index = 1; index < numberOfPoints; index++)
    {
        if (points[index].y < points[lowestIndex].y ||
            (points[index].y == points[lowestIndex].y &&
             points[index].x < points[lowestIndex].x))
        {
            lowestIndex = index;
        }
    }

    swap(points[0], points[lowestIndex]);
    Point referencePoint = points[0];

    sort(points.begin() + 1, points.end(), [&referencePoint](const Point &first, const Point &second)
         {
        int turn = orientation(referencePoint, first, second);
        
        if (turn == 0)
        {
            return squaredDistance(referencePoint, first) < squaredDistance(referencePoint, second);
        }
        
        return (turn == -1); });

    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for (int index = 2; index < numberOfPoints; index++)
    {
        while (hull.size() > 1)
        {
            Point top = hull.back();
            Point secondToTop = hull[hull.size() - 2];

            if (orientation(secondToTop, top, points[index]) != -1)
            {
                hull.pop_back();
            }
            else
            {
                break;
            }
        }

        hull.push_back(points[index]);
    }

    return hull;
}

int main()
{
    vector<Point> points = {
        {0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};

    vector<Point> convexHull = grahamScan(points);

    for (int index = 0; index < (int)convexHull.size(); index++)
    {
        cout << "(" << convexHull[index].x << ", " << convexHull[index].y << ")\n";
    }

    return 0;
}