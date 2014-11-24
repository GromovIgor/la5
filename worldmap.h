#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <QList>
#include <QVector>
#include <QPair>
#include <math.h>

class WorldMap
{
    qreal matrix[4][4];
    void clearmatrix();
    void Transform();
public:
    QVector< QVector<qreal> > dots;
    QVector< QVector<int> > rebra;
    void addDot(qreal xPos, qreal yPos, qreal zPos);
    void addRebro(int a, int b, int c);
    /*функции поворота точки*/
    void setAngleX(qreal cos, qreal sin);
    void setAngleY(qreal cos, qreal sin);
    void setAngleZ(qreal cos, qreal sin);
    /*функции смена осей и переноса точки*/
    void changeOSI();
    void setPos(qreal xPos, qreal yPos, qreal zPos);
    /*конструктор класса*/
    WorldMap();
};

#endif // WORLDMAP_H
