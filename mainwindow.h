#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtGui>
#include "graphic.h"
#include <QDebug>

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    Graphic *view;
public:
    MainWindow();
private slots:
    void setXvar(int i);
    void setYvar(int i);
    void setZvar(int i);
    void setnumber(int i);
    void setX(int state);
    void setAngleB(int state);
    void setPerspective(int state);
    void setI(int state);
    void setP(int state);
    void setL1x(int state);
    void setL1y(int state);
    void setL1z(int state);
    void setL2x(int state);
    void setL2y(int state);
    void setL2z(int state);
};

#endif // MAINWINDOW_H
