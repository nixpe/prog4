#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct Point2D
{
    double x;
    double y;
    double w = 1.0;
};

struct Object2D
{
    vector<Point2D> points;

    Object2D(int numberOfPoints) : points(numberOfPoints) {}
};

struct Matrix3x3
{
    double m[3][3];
};

double degreesToRadians(double degrees)
{
    return degrees * (acos(-1.0) / 180.0);
}

Matrix3x3 multiply(const Matrix3x3 &left, const Matrix3x3 &right)
{
    Matrix3x3 result = {};

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            double sum = 0.0;
            for (int k = 0; k < 3; k++)
            {
                sum += left.m[row][k] * right.m[k][col];
            }
            result.m[row][col] = sum;
        }
    }

    return result;
}

Point2D apply(const Matrix3x3 &transform, const Point2D &point)
{
    double newX = transform.m[0][0] * point.x +
                  transform.m[0][1] * point.y +
                  transform.m[0][2] * point.w;

    double newY = transform.m[1][0] * point.x +
                  transform.m[1][1] * point.y +
                  transform.m[1][2] * point.w;

    double newW = transform.m[2][0] * point.x +
                  transform.m[2][1] * point.y +
                  transform.m[2][2] * point.w;

    if (newW != 0.0)
    {
        newX /= newW;
        newY /= newW;
    }

    return {newX, newY, 1.0};
}

Object2D apply(const Matrix3x3 &transform, const Object2D &object, const int numberOfPoints)
{
    Object2D result(numberOfPoints);

    for (int i = 0; i < numberOfPoints; i++)
    {
        result.points[i] = apply(transform, object.points[i]);
    }

    return result;
}

Matrix3x3 translationMatrix(double u, double v)
{
    return Matrix3x3{{{1.0, 0.0, u},
                      {0.0, 1.0, v},
                      {0.0, 0.0, 1.0}}};
}

Matrix3x3 scalingMatrix(double sx, double sy)
{
    return Matrix3x3{{{sx, 0.0, 0.0},
                      {0.0, sy, 0.0},
                      {0.0, 0.0, 1.0}}};
}

Matrix3x3 rotationMatrix(double degrees)
{
    double theta = degreesToRadians(degrees);
    double c = cos(theta);
    double s = sin(theta);

    return Matrix3x3{{{c, -s, 0.0},
                      {s, c, 0.0},
                      {0.0, 0.0, 1.0}}};
}

Matrix3x3 aroundPoint(const Matrix3x3 &baseTransform, double cx, double cy)
{
    Matrix3x3 moveToOrigin = translationMatrix(-cx, -cy);
    Matrix3x3 moveBack = translationMatrix(cx, cy);

    return multiply(moveBack, multiply(baseTransform, moveToOrigin));
}

Matrix3x3 rotationAroundPoint(double degrees, double cx, double cy)
{
    return aroundPoint(rotationMatrix(degrees), cx, cy);
}

Matrix3x3 scalingAroundPoint(double sx, double sy, double cx, double cy)
{
    return aroundPoint(scalingMatrix(sx, sy), cx, cy);
}

int main()
{
    int numberOfPoints;
    cin >> numberOfPoints;

    Object2D object(numberOfPoints);

    for (int i = 0; i < numberOfPoints; i++)
    {
        cin >> object.points[i].x >> object.points[i].y;
    }

    double u, v;
    cin >> u >> v;

    double degrees;
    cin >> degrees;

    double sx, sy;
    cin >> sx >> sy;

    double rotationCenterX, rotationCenterY;
    cin >> rotationCenterX >> rotationCenterY;

    double scalingCenterX, scalingCenterY;
    cin >> scalingCenterX >> scalingCenterY;

    Matrix3x3 t = translationMatrix(u, v);
    Matrix3x3 r = rotationAroundPoint(degrees, rotationCenterX, rotationCenterY);
    Matrix3x3 s = scalingAroundPoint(sx, sy, scalingCenterX, scalingCenterY);

    Matrix3x3 combined = multiply(s, multiply(r, t));

    Object2D result = apply(combined, object, numberOfPoints);

    for (int i = 0; i < numberOfPoints; i++)
    {
        cout << result.points[i].x << " " << result.points[i].y << endl;
    }

    return 0;
}