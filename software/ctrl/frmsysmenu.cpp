#include "frmsysmenu.h"
#include "ui_frmsysmenu.h"
#include <QPainter>
#include <QMainWindow>
#include <QTime>

frmSysMenu::frmSysMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmSysMenu)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    connect(ui->labTime,SIGNAL(clicked(bool)),this,SLOT(btn_shutdown(bool)));

    this->setStyleSheet("QWidget{background:#030c25;}");

   ui->labTime->setText(QTime::currentTime().toString("HH:mm:ss"));

    timer.setInterval(500);
    timer.setSingleShot(false);

    connect(&timer, SIGNAL(timeout()), this, SLOT(timer_update()));
     timer.start(1000);

}

frmSysMenu::~frmSysMenu()
{
    delete ui;
}

void frmSysMenu::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this );
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

 void frmSysMenu::btn_shutdown(bool)
 {
    //QMainWindow* p=(QMainWindow*) this->parent();
    //p->close();
    //QApplication::exit(0);

 }
 void frmSysMenu::btn_sysmenu(bool)
 {


 }
 void frmSysMenu::setProcess(int process)
 {
   ui->widget_process->setStyleSheet("QWidget{border-image: url(:/images/process50.png);}");

 }

 void frmSysMenu::timer_update()
 {

ui->labTime->setText(QTime::currentTime().toString("HH:mm:ss"));
 }



