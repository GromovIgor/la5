#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QtGui>
#include <math.h>
#include <QVector>
#include <QDebug>
#include "worldmap.h"
#include <QWidget>

class Graphic : public QWidget
{
public:
    Graphic(QWidget *wgt, int x, int y, int z, int edge);
    QVector<int> dot;
    QVector<int> ligdot1;
    QVector<int> ligdot2;
    int edges;
    int B;
    int X;
    bool persp;
    qreal I;
    int P;
private:
    qreal Xpos;
    qreal Ypos;
    QWidget *wgt;
    QPainter painter;
    void paintEvent(QPaintEvent *pe);
    void Init();
    WorldMap map;
    int color;
    qreal Zbufer[800][825];
    void drawLine(int x1,int y1,int x2,int y2, QVector<int> &st);
    void drawPoli(int A, int B, int C);
    qreal getZ(qreal x, qreal y, qreal x1, qreal y1, qreal z1, qreal x2, qreal y2, qreal z2, qreal x3, qreal y3, qreal z3);
    bool compareZ(int x, int y, qreal z);

    qreal light1(qreal x, qreal y, qreal z);
    qreal light2(qreal x, qreal y, qreal z);
    qreal a;
    qreal b;
    qreal c;
    qreal d;

};

#endif // GRAPHIC_H
