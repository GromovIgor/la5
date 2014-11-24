/*самое главное окно, реализованы функции, связывающие переключатели и поля слева с основным
виджетом отрисовки конуса. При любом изменении значения поля - перерисовка конуса*/
#include "mainwindow.h"
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>

//конструктор всего окна и связывание переключателей с виждетом рисования конуса
MainWindow::MainWindow()
{
    setFixedSize(1000,800);

    view              = new Graphic(this,200,200,-200,200);
    QGroupBox *gbox   = new QGroupBox(this);
    QLabel *lbl       = new QLabel(gbox);
    QCheckBox *chbox  = new QCheckBox(gbox);

    view->setGeometry(175,0,this->width()-175,this->height());

    gbox->setTitle(tr("Point of view"));
    gbox->setGeometry(10,10,145,100);
    lbl->setText(tr("Observation point"));
    lbl->setGeometry(30,10,100,40);
    QSpinBox *xVar = new QSpinBox(gbox);
    QSpinBox *yVar = new QSpinBox(gbox);
    QSpinBox *zVar = new QSpinBox(gbox);
    xVar->setRange(-50000,50000);
    yVar->setRange(-50000,50000);
    zVar->setRange(-50000,50000);
    xVar->setValue(200);
    yVar->setValue(200);
    zVar->setValue(300);
    xVar->setGeometry(5,45,45,20);
    yVar->setGeometry(50,45,45,20);
    zVar->setGeometry(95,45,45,20);
    connect(xVar,SIGNAL(valueChanged(int)),this,SLOT(setXvar(int)));
    connect(yVar,SIGNAL(valueChanged(int)),this,SLOT(setYvar(int)));
    connect(zVar,SIGNAL(valueChanged(int)),this,SLOT(setZvar(int)));
    chbox->setText(tr("Perspective"));
    chbox->setGeometry(5,65,100,40);
    connect(chbox,SIGNAL(stateChanged(int)),this,SLOT(setPerspective(int)));

    gbox = new QGroupBox(this);
    gbox->setGeometry(10,120,145,170);
    gbox->setTitle(tr("Parameters of Conus"));

    lbl = new QLabel(gbox);
    lbl->setText(tr("Number grane"));
    lbl->setGeometry(5,10,100,40);
    QSpinBox *spbox = new QSpinBox(gbox);
    spbox->setValue(200);
    spbox->setRange(3,1000);
    spbox->setGeometry(5,45,35,20);
    connect(spbox,SIGNAL(valueChanged(int)),this,SLOT(setnumber(int)));

    lbl = new QLabel(gbox);
    lbl->setText(tr("Side size"));
    lbl->setGeometry(5,55,100,40);
    spbox = new QSpinBox(gbox);
    spbox->setRange(1,1000);
    spbox->setValue(1);
    spbox->setGeometry(5,90,35,20);
    connect(spbox,SIGNAL(valueChanged(int)),this,SLOT(setX(int)));

    lbl = new QLabel(gbox);
    lbl->setText(tr("AngleB"));
    lbl->setGeometry(5,100,100,40);
    spbox = new QSpinBox(gbox);
    spbox->setRange(15,80);
    spbox->setValue(20);
    spbox->setGeometry(5,135,35,20);
    connect(spbox,SIGNAL(valueChanged(int)),this,SLOT(setAngleB(int)));

    gbox = new QGroupBox(this);
    gbox->setTitle(tr("Point of lights"));
    gbox->setGeometry(10,300,145,70);
    xVar = new QSpinBox(gbox);
    yVar = new QSpinBox(gbox);
    zVar = new QSpinBox(gbox);
    xVar->setRange(-50000,50000);
    yVar->setRange(-50000,50000);
    zVar->setRange(-50000,50000);
    xVar->setValue(90);
    yVar->setValue(3);
    zVar->setValue(230);
    xVar->setGeometry(5,18,45,20);
    yVar->setGeometry(50,18,45,20);
    zVar->setGeometry(95,18,45,20);
    connect(xVar,SIGNAL(valueChanged(int)),this,SLOT(setL1x(int)));
    connect(yVar,SIGNAL(valueChanged(int)),this,SLOT(setL1y(int)));
    connect(zVar,SIGNAL(valueChanged(int)),this,SLOT(setL1z(int)));
    xVar = new QSpinBox(gbox);
    yVar = new QSpinBox(gbox);
    zVar = new QSpinBox(gbox);
    xVar->setRange(-50000,50000);
    yVar->setRange(-50000,50000);
    zVar->setRange(-50000,50000);
    xVar->setValue(6);
    yVar->setValue(120);
    zVar->setValue(150);
    xVar->setGeometry(5,45,45,20);
    yVar->setGeometry(50,45,45,20);
    zVar->setGeometry(95,45,45,20);
    connect(xVar,SIGNAL(valueChanged(int)),this,SLOT(setL2x(int)));
    connect(yVar,SIGNAL(valueChanged(int)),this,SLOT(setL2y(int)));
    connect(zVar,SIGNAL(valueChanged(int)),this,SLOT(setL2z(int)));


    gbox = new QGroupBox(this);
    gbox->setGeometry(10,380,145,170);
    gbox->setTitle(tr("Light"));

    lbl = new QLabel(gbox);
    lbl->setText(tr("Intensivity"));
    lbl->setGeometry(5,10,100,40);
    spbox = new QSpinBox(gbox);
    spbox->setValue(45);
    spbox->setRange(0,100);
    spbox->setGeometry(5,45,35,20);
    connect(spbox,SIGNAL(valueChanged(int)),this,SLOT(setI(int)));

   lbl = new QLabel(gbox);
    lbl->setText(tr("Reflection"));
    lbl->setGeometry(5,55,100,40);
    spbox = new QSpinBox(gbox);
    spbox->setRange(0,10000);
    spbox->setValue(200);
    spbox->setGeometry(5,90,35,20);
    connect(spbox,SIGNAL(valueChanged(int)),this,SLOT(setP(int)));



}

void MainWindow::setXvar(int i)
{
    view->dot[0] = i;
    view->repaint();
}

void MainWindow::setYvar(int i)
{
    view->dot[1] = i;
    view->repaint();
}

void MainWindow::setZvar(int i)
{
    view->dot[2] = -i;
    view->repaint();
}

void MainWindow::setnumber(int i)
{
   view->edges = i;
   view->repaint();
}

void MainWindow::setAngleB(int state)
{
    view->B = state;
    view->repaint();
}

void MainWindow::setX(int state)
{
    view->X = state;
    view->repaint();
}

void MainWindow::setPerspective(int state)
{
    view->persp = state;
    view->repaint();
}

void MainWindow::setI(int state)
{
    view->I = state;
    view->repaint();
}

void MainWindow::setP(int state)
{
    view->P = state;
    view->repaint();
}

void MainWindow::setL1x(int state)
{
    view->ligdot1[0] = state;
    view->repaint();
}

void MainWindow::setL1y(int state)
{
    view->ligdot1[1] = state;
    view->repaint();
}

void MainWindow::setL1z(int state)
{
    view->ligdot1[2] = state;
    view->repaint();
}

void MainWindow::setL2x(int state)
{
    view->ligdot2[0] = state;
    view->repaint();
}

void MainWindow::setL2y(int state)
{
    view->ligdot2[1] = state;
    view->repaint();
}

void MainWindow::setL2z(int state)
{
    view->ligdot2[2] = state;
    view->repaint();
}

