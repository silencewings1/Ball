#ifndef TRIANGLE_H
#define TRIANGLE_H

struct Point3f
{
    float x;
    float y;
    float z;
};

struct Triangle
{
    Point3f N;
    Point3f V[3];
};

#endif // TRIANGLE_H
