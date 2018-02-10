#include "frmconfigdevice.h"
#include "ui_frmconfigdevice.h"
#include <QColor>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QMouseEvent>



QGraphicsLineItem *line;
QGraphicsRectItem *pRect;
frmConfigDevice::frmConfigDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmConfigDevice)
{
    ui->setupUi(this);
    connect(ui->btnTest1,SIGNAL(clicked()),this,SLOT(test1()));
    connect(ui->btnTest2,SIGNAL(clicked()),this,SLOT(test2()));
    this->setMouseTracking(true);
    //this->setWindowFlags(Qt::SplashScreen);
    this->resize(1024,600);
    this->move(0,0);


    pDevGraphicsView=new DevGraphicsView(this);
    //pDevGraphicsView->setParent(this);
    pDevGraphicsView->move(100,10);
    pDevGraphicsView->resize(400,400);
    pDevGraphicsView->setMouseTracking(true);
    pDevGraphicsView->show();

    this->pScene=new QGraphicsScene(this);
    pScene->setSceneRect(0,0,pDevGraphicsView->width(),pDevGraphicsView->height());
    pDevGraphicsView->setScene(this->pScene);
    QBrush brush( QColor::fromRgb(0,150,0) ,   Qt::SolidPattern);
    pRect=pScene->addRect(0,0,200,200,QPen(QColor::fromRgb(150,0,0)),brush);

    //pDevGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //pDevGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(pDevGraphicsView,SIGNAL(sig_mouseMoveEvent(QMouseEvent*)),this,SLOT(graphics_mouse_move(QMouseEvent*)));




}

frmConfigDevice::~frmConfigDevice()
{
    delete ui;
    pScene->removeItem((QGraphicsItem *)line);
}

void frmConfigDevice::test1()
{
    line=pScene->addLine(-100,-100,100,100);//,QPen(QColor::fromRgb(0,0,0))

}


void frmConfigDevice::test2()
{


}

void frmConfigDevice::graphics_mouse_move(QMouseEvent*event)
{
    QString str="x=%1,y=%2";

//QPoint pos=  event->pos();
  QPoint pos=  this->mapFromParent(  event->pos());

    //QPointF pos=   event->scenePos();

    ui->labTip->setText(  str.arg(pos.x()).arg(pos.y()) );


}


void frmConfigDevice::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent( event);
}
