#include <iostream>
#include <vector>

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

vector<Point> jarvisMarch(const vector<Point> &points)
{
    int numberOfPoints = points.size();
    vector<Point> hull;

    if (numberOfPoints < 3)
    {
        return hull;
    }

    int leftmostIndex = 0;
    for (int index = 1; index < numberOfPoints; index++)
    {
        if (points[index].x < points[leftmostIndex].x ||
            (points[index].x == points[leftmostIndex].x &&
             points[index].y < points[leftmostIndex].y))
        {
            leftmostIndex = index;
        }
    }

    int currentIndex = leftmostIndex;

    do
    {
        hull.push_back(points[currentIndex]);

        int nextIndex = (currentIndex + 1) % numberOfPoints;

        for (int index = 0; index < numberOfPoints; index++)
        {
            int turn = orientation(points[currentIndex], points[nextIndex], points[index]);

            if (turn == 1)
            {
                nextIndex = index;
            }

            else if (turn == 0 &&
                     squaredDistance(points[currentIndex], points[index]) >
                         squaredDistance(points[currentIndex], points[nextIndex]))
            {
                nextIndex = index;
            }
        }

        currentIndex = nextIndex;

    } while (currentIndex != leftmostIndex);

    return hull;
}

int main()
{
    vector<Point> points = {
        {0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};

    vector<Point> convexHull = jarvisMarch(points);

    for (int index = 0; index < (int)convexHull.size(); index++)
    {
        cout << "(" << convexHull[index].x << ", " << convexHull[index].y << ")\n";
    }

    return 0;
}