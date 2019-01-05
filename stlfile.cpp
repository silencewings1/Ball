#include "stlfile.h"


#include <QDebug>
#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"

stlFile::stlFile()
{

}


bool stlFile::ReadFile(const char *cfilename)
{
    FILE * pFile;
    size_t lSize;
    char* buffer;
    size_t result;

    // 若要一个byte不漏地读入整个文件，只能采用二进制方式打开
    fopen_s(&pFile,cfilename, "rb");    //将文件放入pFile
    if (pFile == NULL)                  //文件为空
    {
        fputs("File error", stderr);
        exit(1);
    }

    /* 获取文件大小 */
    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);

    /* 分配内存存储整个文件 */
    buffer = (char*)malloc(sizeof(char)*lSize);
    if (buffer == NULL)               //内存获取失败
    {
        fputs("Memory error", stderr);
        exit(2);
    }

    /* 将文件拷贝到buffer中 */
    result = fread(buffer, 1, lSize, pFile);
    if (result != lSize)             //内存读取失败
    {
        fputs("Reading error", stderr);
        exit(3);
    }


    /* 结束演示，关闭文件并释放内存 */
    fclose(pFile);

    if (buffer[79]!='\0')//判断格式
    {
        ReadASCII(buffer);
    }
    else
    {
        ReadBinary(buffer);
    }

    free(buffer);   //释放内存
    return true;
}

bool stlFile::ReadASCII(const char *buffer)
{
    unTriangles = 0;   //三角面片数量
    triangleList.clear();
    float x, y, z;
    int i;
    string name, useless;
    stringstream ss(buffer);    //字符串流
    ss >> name >> name;
    ss.get();
    do {
        Triangle triangle;
        ss >> useless;
        if (useless != "facet")
            break;
        ss >> useless >> x >> y >> z;
        ss.get();
        Point3f N;
        N.x = x;
        N.y = y;
        N.z = z;
        triangle.N = N;
        getline(ss, useless);
        getline(ss, useless);
        for (i = 0; i < 3; i++)
        {
            ss >> useless >> x >> y >> z;
            Point3f point;
            point.x = x;
            point.y = y;
            point.z = z;
            triangle.V[i] = point;
        }
        unTriangles++;
        getline(ss, useless);
        getline(ss, useless);
        getline(ss, useless);
        triangleList.push_back(triangle);
    } while(1);
    return true;
}

bool stlFile::ReadBinary(const char *buffer)
{
    const char* p = buffer;
    char name[80];
    int i, j;
    triangleList.clear();
    memcpy(name, p, 80);    //将内存p的内容拷贝到name中
    p += 80;
    unTriangles= cpyint(p);
    cout<<unTriangles;
    triangleList.reserve(unTriangles);
    for (i = 0; i < unTriangles; i++)
    {
        Triangle triangle;  //一个三角面片
//        p += 12;//跳过头部法向量
        Point3f point;    //法向量
        point.x = cpyfloat(p);
        point.y = cpyfloat(p);
        point.z = cpyfloat(p);
        triangle.N = point;
        for (j = 0; j < 3; j++)//读取三顶点
        {
            point.x = cpyfloat(p);
            point.y = cpyfloat(p);
            point.z = cpyfloat(p);
            triangle.V[j] = point;
        }
        p += 2;//跳过尾部标志
        triangleList.push_back(triangle);
    }
    return true;
}

int stlFile::NumTri()
{
    return unTriangles;
}

QVector<Triangle> stlFile::GetTriangleList()
{
    QVector<Triangle> zhuanhuan;
    zhuanhuan = triangleList;
    float x_max;
    float x_min;


    float max1 = zhuanhuan[0].V[0].x;
    float min1 = zhuanhuan[0].V[0].x;
    for(int i = 0;i<zhuanhuan.size();i++)
    {
        for(int j = 0;j < 3;j++)
        {
            if(max1<zhuanhuan[i].V[j].x)
            {
                max1 = zhuanhuan[i].V[j].x;
            }
            if(min1>zhuanhuan[i].V[j].x)
            {
                min1 = zhuanhuan[i].V[j].x;
            }
        }
    }
    x_max = max1;
    x_min = min1;//得到最大的x 的值和最小的x的值


    for(int i = 0;i<zhuanhuan.size();i++)
    {
        for(int j =0;j<3;j++)
        {
            zhuanhuan[i].V[j].x = zhuanhuan[i].V[j].x/(x_max-x_min);
            zhuanhuan[i].V[j].y = zhuanhuan[i].V[j].y/(x_max-x_min);
            zhuanhuan[i].V[j].z = zhuanhuan[i].V[j].z/(x_max-x_min);
        }
    }

    triangleList = zhuanhuan;

    return triangleList;
}

int stlFile::cpyint(const char*& p)
{
    int cpy;
    memwriter = (char*)&cpy;    //memwriter是cpy的镜像
    memcpy(memwriter, p, 4);
    p += 4;
    return cpy;
}
float stlFile::cpyfloat(const char*& p)
{
    float cpy;
    memwriter = (char*)&cpy;
    memcpy(memwriter, p, 4);
    p += 4;
    return cpy;
}
