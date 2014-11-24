#include "graphic.h"


Graphic::Graphic(QWidget *wgt, int x, int y, int z, int edge) : QWidget(wgt)
{
    dot << x << y << z << 1;        //установка координат точки обзора
    edges = edge;                   //установка кол-ва граней, 12
    B = 20;                         //установка угла по заданию
    X = 1;                         //установка длины основания
    persp = false;
    I = 45;
    P = 200;

    ligdot1 << 90 << 3 << 230;
    ligdot2 << 6 << 120 << 150;
}

void Graphic::Init()                //преднастройка перед рисованием
{
    map.dots.clear();               //очистка точек мировой сис-мы координат (МСК)
    map.rebra.clear();              //очистка ребер МСК
    for (int i = 0; i < height(); i++)
        for(int j = 0; j < width(); j++)
            Zbufer[i][j] = 0;
    qreal R = 2*X/tan(M_PI/edges);    //расчет радиуса конуса
    qreal H = R*1/tan(B*M_PI/180);    //расчет высоты конуса

    /*нахождение точек на основании конуса*/
    qreal grad= qreal(360)/edges;         //шаг по углу
    for(int i = 0; i < edges; i++)
        map.addDot(R*cos(i*grad*M_PI/180),R*sin(i*grad*M_PI/180),0);   //добавление точек МСК
    map.addDot(0,0,H);             //добавление точки вершины
    map.addDot(0,0,0);             //добавление точки центра конуса
    for(int i = 0; i < edges-1; i++)
    {
        map.addRebro(i,i+1,edges);                                     //добавление боковых граней
        map.addRebro(i,i+1,edges+1);                                   //добавление граней основания
    }
    map.addRebro(0,edges-1,edges);
    map.addRebro(0,edges-1,edges+1);
    map.addDot(ligdot1[0],ligdot1[1],ligdot1[2]);
    map.addDot(ligdot2[0],ligdot2[1],ligdot2[2]);
    /*расчет необходимых данных для нахождения cos и sin*/
    qreal a = sqrt(pow(dot[0],2) + pow(dot[1],2));
    qreal e = sqrt(pow(dot[0],2) + pow(dot[1],2) + pow(dot[2],2));
    if (a == 0) a = 1;
    /*преобразования систем координат по методике*/
    map.setAngleZ(dot[0]/a,dot[1]/a);           //поворот оси по Z
    map.setAngleY(dot[2]/e,a/e);                //поворот оси по У
    map.setPos(-e,0,0);                         //перенос начала координат
    map.changeOSI();                            //изменение осей
    /*перспективное трансформирование МСК по необходимости*/
    if (persp)
    {
        QVector<QVector<qreal> >::iterator p;
        for (p = map.dots.begin(); p!=map.dots.end(); p++)
        {
            if ((*p)[2] == 0) continue;
           (*p)[0] = e*((*p)[0]/(*p)[2]);
           (*p)[1] = e*((*p)[1]/(*p)[2]);
        }
    }
    Xpos = width()/2;       //расчет центра...
    Ypos = height()/2;      //...экрана

    //qDebug() << (map.dots[edges+2])[0] << (map.dots[edges+2])[1] << (map.dots[edges+2])[2];
    //qDebug() << grad;
}

void Graphic::paintEvent(QPaintEvent *pe) //функция прорисовки
{
    Init();                 //подготовка к рисованию
    painter.begin(this);
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));  //кисть
    painter.drawRect(QRect(0,0,width(),height()));          //закраска всей облисти белым цветом
    /*рисование конуса по ребрам*/
    QVector<QVector<int> >::iterator p; //указатель на массив ребер
    for( p = map.rebra.begin(); p != map.rebra.end() ; p++)
        drawPoli((*p)[0],(*p)[1],(*p)[2]);
    /*int i;
    QVector<QVector<qreal> >::iterator p1;
        for (i = 0, p1 = map.dots.begin(); p1!=map.dots.end(); p1++, i++)
        {
            painter.drawText(Xpos+(*p1)[0],Ypos-(*p1)[1],QString::QString("%1").arg(i));
        }*/
    painter.end();
}

void Graphic::drawLine(int x1,int y1,int x2,int y2, QVector<int> &st)                 //алгоритм рисования по Брезенхему
{
    int dx;
    int dy;
    int x;
    int y;
    int d = 0;
    int count = st.count();

    if (x2 < x1)        //сортируем точки слева направо
    {
        qSwap(x1,x2);
        qSwap(y1,y2);
    }                   //отсортированны
    dx = x2 - x1;
    dy = y2 - y1;
    x = x1;
    y = y1;

    st << x1;
    if (dy > 0)         //сверху вниз
    {
        if ( dx < dy )  //прирост по y
        {
            do
             {
             y++;
             d = d + 2*dx;
             if(d > dy)
                {
                   x++;
                   d = d - 2*dy;
                }
             st << x;
             }
             while(y < y2);
        }
        else    //прирост по x
        {
            do
             {
             x++;
             d = d + 2*dy;
             if(d > dx)
                {
                   y++;
                   st << x;
                   d = d - 2*dx;
                }
             }
             while(x < x2);
        }
    }
    else        //снизу вверх
    {
        if ( dx < dy*(-1) ) //прирост по y
        {
            do
             {
             y--;
             d = d + 2*dx;
             if(d > dy*(-1))
                {
                   x++;
                   d = d + 2*dy;
                }
            st.insert(count,x);
             }
             while(y > y2);
        }
        else    //прирост по x
        {
            do
             {
             x++;
             d = d - 2*dy;
             if(d > dx)
                {
                   y--;
                 st.insert(count,x);
                 d = d - 2*dx;
                }

             }
             while(x < x2);
        }
    }
}

void Graphic::drawPoli(int A, int B, int C)
{
    QVector<int> st1;
    QVector<int> st2;
    qreal z;

    if ((map.dots[C])[1] < (map.dots[B])[1]) qSwap(C,B);
    if ((map.dots[B])[1] < (map.dots[A])[1]) qSwap(A,B);
    if ((map.dots[B])[1] > (map.dots[C])[1]) qSwap(C,B);

    drawLine((map.dots[C])[0],(map.dots[C])[1],(map.dots[A])[0],(map.dots[A])[1],st1);
    drawLine((map.dots[B])[0],(map.dots[B])[1],(map.dots[A])[0],(map.dots[A])[1],st2);
    drawLine((map.dots[C])[0],(map.dots[C])[1],(map.dots[B])[0],(map.dots[B])[1],st2);

    //color -=1;
    //if (color < 175) color = 255;
    //painter.setPen(QPen(QColor(255,color,0)));
    color = 0;
    for (int y = (map.dots[A])[1], i = 0; y < (map.dots[C])[1]; y++,i++)
    {
        for(int x = st1[i]; x != st2[i]; )
        {
         if ( st1[i] >= st2[i]) x--;
         else x++;
         z = getZ(x,y,(map.dots[A])[0],(map.dots[A])[1],(map.dots[A])[2],(map.dots[B])[0],(map.dots[B])[1],(map.dots[B])[2],(map.dots[C])[0],(map.dots[C])[1],(map.dots[C])[2]);
         if (compareZ(Xpos+x,Ypos-y,z))
         {
             if (c > 0)
             {
                 a = -a;
                 b = -b;
                 c = -c;
             }
             int zcolor = color;
             qreal col1 = light1(x,y,z);
             qreal col2 = light2(x,y,z);
             if (col1 || col2)
             {
                 color = color + col1 +col2;
                 if (color <= 255) painter.setPen(QPen(QColor(0,color,0)));
                 if ( (color > 255) && (color <= 510) ) painter.setPen(QPen(QColor(color-255,255,color-255)));
                 if (color > 510) painter.setPen(QPen(QColor(255,255,255)));
             }
             painter.drawPoint(Xpos+x,Ypos-y);
             color = zcolor;
             painter.setPen(QPen(QColor(0,color,0)));
         }
        }
    }

}

qreal Graphic::getZ(qreal x, qreal y, qreal x1, qreal y1, qreal z1, qreal x2, qreal y2, qreal z2, qreal x3, qreal y3, qreal z3)
{
    a = (y1*z2)+(y2*z3)+(z1*y3)-(z2*y3)-(z1*y2)-(y1*z3);
    b = (x1*z2)+(x2*z3)+(z1*x3)-(z2*x3)-(x1*z3)-(z1*x2);
    c = (x1*y2)+(x2*y3)+(y1*x3)-(y2*x3)-(y1*x2)-(x1*y3);
    d = (x1*y2*z3)+(x2*y3*z1)+(y1*z2*x3)-(x3*y2*z1)-(y1*x2*z3)-(y3*z2*x1);
    return (b*y-a*x+d)/c;
}

bool Graphic::compareZ(int x, int y, qreal z)
{
    if (z == 0) return false;
    if (x < 0 || x >= 800 || y < 0 || y >= 825) return false;
    if (1/z < Zbufer[x][y])  return false;
    else
    {
        Zbufer[x][y] = 1/z;
        return true;
    }
}


qreal Graphic::light1(qreal x, qreal y, qreal z)
{
    qreal mod1 = sqrt(pow(((map.dots[edges+2])[0]-x),2)+pow(((map.dots[edges+2])[1]-y),2)+pow(((map.dots[edges+2])[2]-z),2));
    qreal mod2 = sqrt(a*a+b*b+c*c);
    qreal cosinys = (((map.dots[edges+2])[0]-x)*a-((map.dots[edges+2])[1]-y)*b+((map.dots[edges+2])[2]-z)*c)/(mod1*mod2);
    if (cosinys < 0) return 0;
    else return P/qreal(100)*I*cosinys/(mod1*0.01);
}

qreal Graphic::light2(qreal x, qreal y, qreal z)
{
    qreal mod1 = sqrt(pow(((map.dots[edges+3])[0]-x),2)+pow(((map.dots[edges+3])[1]-y),2)+pow(((map.dots[edges+3])[2]-z),2));
    qreal mod2 = sqrt(a*a+b*b+c*c);
    qreal cosinys = (((map.dots[edges+3])[0]-x)*a-((map.dots[edges+3])[1]-y)*b+((map.dots[edges+3])[2]-z)*c)/(mod1*mod2);
    if (cosinys < 0) return 0;
    else return P/qreal(100)*I*cosinys/(mod1*0.01);
}
