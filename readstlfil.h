#ifndef READSTLFIL_H
#define READSTLFIL_H

#include <fstream>
#include <sstream>
#include <string>
#include <QVector>
#include <triangle.h>


using namespace std;

class readstlfil
{
public:
    readstlfil();
    bool ReadFile(const char *cfilename);
    int NumTri();
    QVector<Triangle> GetTriangleList();
private:
    bool ReadASCII(const char *cfilename);
    bool ReadBinary(const char *cfilename);

    QVector<Triangle> triangleList;
    int unTriangles;
    char* memwriter;
    int cpyint(const char*& p);
    float cpyfloat(const char*& p);
};


#endif // READSTLFIL_H
