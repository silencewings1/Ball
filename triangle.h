#ifndef TRIANGLE_H
#define TRIANGLE_H

struct Point3f
{
    float x;
    float y;
    float z;

    Point3f(){}
    Point3f(float px, float py, float pz){
        x = px; y = py; z = pz;
    }
};

struct Triangle
{
    Point3f N;
    Point3f V[3];
};

#endif // TRIANGLE_H
