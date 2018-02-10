#include "frmbottommenu.h"
#include "ui_frmbottommenu.h"
#include <QPainter>
#include <QMainWindow>

frmBottomMenu::frmBottomMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmBottomMenu)
{
    ui->setupUi(this);

    this->setStyleSheet("QWidget{background-image: url(:/images/bg_bottom.png);}");

    connect(ui->btnHome,SIGNAL(clicked(bool)),this,SLOT(btn_click_home(bool)));
    connect(ui->btnWarning,SIGNAL(clicked(bool)),this,SLOT(btn_click_warning(bool)));
    connect(ui->btnProcess,SIGNAL(clicked(bool)),this,SLOT(btn_click_process(bool)));
    connect(ui->btnStatus,SIGNAL(clicked(bool)),this,SLOT(btn_click_status(bool)));
    connect(ui->btnPause,SIGNAL(clicked(bool)),this,SLOT(btn_click_pause(bool)));
    connect(ui->btnVideo,SIGNAL(clicked(bool)),this,SLOT(btn_click_video(bool)));
    connect(ui->btnBack,SIGNAL(clicked(bool)),this,SLOT(btn_click_back(bool)));


    ui->btnHome->setStyleSheet("QWidget{border-image: url(:/images/bottom_menu_home.png);background-image: url(:/images/bottom_menu_home.png);}");
    ui->btnWarning->setStyleSheet("QWidget{border-image: url(:/images/bottom_menu_warning.png);background-image: url(:/images/bottom_menu_warning.png); }");
    ui->btnProcess->setStyleSheet("QWidget{border-image: url(:/images/bottom_menu_process.png);background-image: url(:/images/bottom_menu_process.png);}");
    ui->btnStatus->setStyleSheet("QWidget{border-image: url(:/images/bottom_menu_status.png);background-image: url(:/images/bottom_menu_status.png);}");
    ui->btnPause->setStyleSheet("QWidget{border-image: url(:/images/bottom_menu_pause.png);background-image: url(:/images/bottom_menu_pause.png);}");
    ui->btnVideo->setStyleSheet("QWidget{border-image: url(:/images/bottom_menu_video.png);background-image: url(:/images/bottom_menu_video.png);}");
    ui->btnBack->setStyleSheet("QWidget{border-image: url(:/images/bottom_menu_back.png);background-image: url(:/images/bottom_menu_back.png);}");

    ui->widget_title->hide();


/*
ui->widget_title->setParent((QWidget*)ui->widget_title->parent());
ui->widget_title->show();
ui->widget_title->move(0,this->pos().y()-10);
ui->widget_title->raise();
*/
}

frmBottomMenu::~frmBottomMenu()
{
    delete ui;
}
void frmBottomMenu::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this );
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void frmBottomMenu::btn_click_home(bool)
{

    emit this->sig_button_click(1);
}
void frmBottomMenu::btn_click_warning(bool)
{

    emit this->sig_button_click(2);
}
void frmBottomMenu::btn_click_process(bool)
{
    emit this->sig_button_click(3);

}
void frmBottomMenu::btn_click_status(bool)
{
    emit this->sig_button_click(4);

}
void frmBottomMenu::btn_click_pause(bool)
{
    emit this->sig_button_click(5);

}
void frmBottomMenu::btn_click_video(bool)
{

    emit this->sig_button_click(6);
}
void frmBottomMenu::btn_click_back(bool)
{
    emit this->sig_button_click(7);

}
