#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point3D
{
    double x;
    double y;
    double z;
    double w = 1.0;
};

struct Matrix4x4
{
    double m[4][4];
};

double degreesToRadians(double degrees)
{
    return degrees * (acos(-1.0) / 180.0);
}

Matrix4x4 multiply(const Matrix4x4 &left, const Matrix4x4 &right)
{
    Matrix4x4 result = {};

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            double sum = 0.0;
            for (int k = 0; k < 4; k++)
            {
                sum += left.m[row][k] * right.m[k][col];
            }
            result.m[row][col] = sum;
        }
    }

    return result;
}

Point3D apply(const Matrix4x4 &transform, const Point3D &point)
{
    double newX = transform.m[0][0] * point.x +
                  transform.m[0][1] * point.y +
                  transform.m[0][2] * point.z +
                  transform.m[0][3] * point.w;

    double newY = transform.m[1][0] * point.x +
                  transform.m[1][1] * point.y +
                  transform.m[1][2] * point.z +
                  transform.m[1][3] * point.w;

    double newZ = transform.m[2][0] * point.x +
                  transform.m[2][1] * point.y +
                  transform.m[2][2] * point.z +
                  transform.m[2][3] * point.w;

    double newW = transform.m[3][0] * point.x +
                  transform.m[3][1] * point.y +
                  transform.m[3][2] * point.z +
                  transform.m[3][3] * point.w;

    if (newW != 0.0)
    {
        newX /= newW;
        newY /= newW;
        newZ /= newW;
    }

    return {newX, newY, newZ, 1.0};
}

Matrix4x4 translationMatrix(double u, double v, double w)
{
    return Matrix4x4{{{1.0, 0.0, 0.0, u},
                      {0.0, 1.0, 0.0, v},
                      {0.0, 0.0, 1.0, w},
                      {0.0, 0.0, 0.0, 1.0}}};
}

Matrix4x4 scalingMatrix(double sx, double sy, double sz)
{
    return Matrix4x4{{{sx, 0.0, 0.0, 0.0},
                      {0.0, sy, 0.0, 0.0},
                      {0.0, 0.0, sz, 0.0},
                      {0.0, 0.0, 0.0, 1.0}}};
}

Matrix4x4 rotationMatrixX(double degrees)
{
    double theta = degreesToRadians(degrees);
    double c = cos(theta);
    double s = sin(theta);

    return Matrix4x4{{{1.0, 0.0, 0.0, 0.0},
                      {0.0, c, -s, 0.0},
                      {0.0, s, c, 0.0},
                      {0.0, 0.0, 0.0, 1.0}}};
}

Matrix4x4 rotationMatrixY(double degrees)
{
    double theta = degreesToRadians(degrees);
    double c = cos(theta);
    double s = sin(theta);

    return Matrix4x4{{{c, 0.0, s, 0.0},
                      {0.0, 1.0, 0.0, 0.0},
                      {-s, 0.0, c, 0.0},
                      {0.0, 0.0, 0.0, 1.0}}};
}

Matrix4x4 rotationMatrixZ(double degrees)
{
    double theta = degreesToRadians(degrees);
    double c = cos(theta);
    double s = sin(theta);

    return Matrix4x4{{{c, -s, 0.0, 0.0},
                      {s, c, 0.0, 0.0},
                      {0.0, 0.0, 1.0, 0.0},
                      {0.0, 0.0, 0.0, 1.0}}};
}

Matrix4x4 aroundPoint(const Matrix4x4 &baseTransform, double cx, double cy, double cz)
{
    Matrix4x4 moveToOrigin = translationMatrix(-cx, -cy, -cz);
    Matrix4x4 moveBack = translationMatrix(cx, cy, cz);

    return multiply(moveBack, multiply(baseTransform, moveToOrigin));
}

void transformObjFile(const string &inputPath, const string &outputPath, const Matrix4x4 &transform)
{
    ifstream inFile(inputPath);
    ofstream outFile(outputPath);

    outFile << setprecision(15);

    string line;
    while (getline(inFile, line))
    {
        istringstream iss(line);
        string token;
        iss >> token;

        if (token == "v")
        {
            double x = 0.0, y = 0.0, z = 0.0;
            if (iss >> x >> y >> z)
            {
                Point3D p = {x, y, z, 1.0};
                Point3D q = apply(transform, p);
                outFile << "v " << q.x << " " << q.y << " " << q.z << "\n";
            }
            else
            {
                outFile << line << "\n";
            }
        }
        else
        {
            outFile << line << "\n";
        }
    }
}

int main()
{
    string inputPath, outputPath;
    cin >> inputPath >> outputPath;

    double u, v, w;
    cin >> u >> v >> w;

    double degreesX, degreesY, degreesZ;
    cin >> degreesX >> degreesY >> degreesZ;

    double sx, sy, sz;
    cin >> sx >> sy >> sz;

    double rotationCenterX, rotationCenterY, rotationCenterZ;
    cin >> rotationCenterX >> rotationCenterY >> rotationCenterZ;

    double scalingCenterX, scalingCenterY, scalingCenterZ;
    cin >> scalingCenterX >> scalingCenterY >> scalingCenterZ;

    Matrix4x4 t = translationMatrix(u, v, w);

    Matrix4x4 rx = rotationMatrixX(degreesX);
    Matrix4x4 ry = rotationMatrixY(degreesY);
    Matrix4x4 rz = rotationMatrixZ(degreesZ);

    Matrix4x4 rotationBase = multiply(rz, multiply(ry, rx));
    Matrix4x4 r = aroundPoint(rotationBase,
                              rotationCenterX, rotationCenterY, rotationCenterZ);

    Matrix4x4 scalingBase = scalingMatrix(sx, sy, sz);
    Matrix4x4 s = aroundPoint(scalingBase,
                              scalingCenterX, scalingCenterY, scalingCenterZ);

    Matrix4x4 combined = multiply(s, multiply(r, t));

    transformObjFile(inputPath, outputPath, combined);

    return 0;
}