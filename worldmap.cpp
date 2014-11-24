#include "worldmap.h"

WorldMap::WorldMap()
{
    clearmatrix();  //очистить матрицу трансформирования
}

void WorldMap::addDot(qreal xPos, qreal yPos, qreal zPos)   //добавление точки в мировую систему координат
{
    QVector<qreal> dot;                 //создание переменной для точки
    dot << xPos << yPos << zPos << 1;   //установка координат точки
    dots << dot;                        //занесение точки в массив точек мировой системы координат
}

void WorldMap::addRebro(int a, int b, int c)     //добавление ребра в мировую систему координат
{
    QVector<int> rebro;        //создание ребра
    rebro << a << b << c;
    rebra << rebro;                         //занесение ребра в массив ребер мировой системы координат
}

void WorldMap::clearmatrix()                //очистка матрицы трансформирования
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            i == j? matrix[i][j] = 1 : matrix[i][j] = 0;
}

void WorldMap::setAngleX(qreal cos, qreal sin)      //поворот по Х
{
    matrix[1][1] = cos;         //установка нужных параметров в матрице
    matrix[1][2] = sin;
    matrix[2][1] = -sin;
    matrix[2][2] = cos;
    Transform();                //трансформирование мировой системы координат
}

void WorldMap::setAngleY(qreal cos, qreal sin)      //поворот по У
{
    matrix[0][0] = sin;
    matrix[0][2] = cos;
    matrix[2][0] = -cos;
    matrix[2][2] = sin;
    Transform();
}

void WorldMap::setAngleZ(qreal cos, qreal sin)      //поворот по Z
{
    matrix[0][0] = cos;
    matrix[0][1] = -sin;
    matrix[1][0] = sin;
    matrix[1][1] = cos;
    Transform();
}

void WorldMap::setPos(qreal xPos, qreal yPos, qreal zPos)   //перенос точки
{
    matrix[3][0] = xPos;
    matrix[3][1] = yPos;
    matrix[3][2] = zPos;
    Transform();
}

void WorldMap::Transform()                      //трансформация мировой системы координат
{
    QVector<QVector<qreal> >::iterator p;       //указатель на массив координат
    /*перебираем каждую точку в массиве точек мировой сис-мы координат*/
    for (p = dots.begin(); p!=dots.end(); p++)
    {
        qreal x = (*p)[0];
        qreal y = (*p)[1];
        qreal z = (*p)[2];
        qreal mas = (*p)[3];

        (*p)[0] = matrix[0][0]*x + matrix[1][0]*y + matrix[2][0]*z + matrix[3][0]*mas;
        (*p)[1] = matrix[0][1]*x + matrix[1][1]*y + matrix[2][1]*z + matrix[3][1]*mas;
        (*p)[2] = matrix[0][2]*x + matrix[1][2]*y + matrix[2][2]*z + matrix[3][2]*mas;
        (*p)[3] = matrix[0][3]*x + matrix[1][3]*y + matrix[2][3]*z + matrix[3][3]*mas;
    }
    clearmatrix();              //после трансформации очищаем матрицу
}

void WorldMap::changeOSI()      //функция замены осей координат
{
   matrix[0][0] = 0;
   matrix[1][1] = 0;
   matrix[2][2] = 0;
   matrix[0][2] = -1;
   matrix[1][0] = 1;
   matrix[2][1] = 1;
  Transform();
}
