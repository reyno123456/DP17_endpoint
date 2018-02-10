#include "frmhome.h"
#include "ui_frmhome.h"

frmHome::frmHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmHome)
{
    ui->setupUi(this);

    connect(ui->btnBox,SIGNAL(clicked(bool)),this,SLOT(btn_click_box(bool)));
    connect(ui->btnDev,SIGNAL(clicked(bool)),this,SLOT(btn_click_dev(bool)));
    connect(ui->btnPara,SIGNAL(clicked(bool)),this,SLOT(btn_click_para(bool)));
    connect(ui->btnHistory,SIGNAL(clicked(bool)),this,SLOT(btn_click_his(bool)));


    ui->btnBox->setStyleSheet("QPushButton{border-image: url(:/images/btn_box.png);}"
                                      "QPushButton:hover{border-image: url(:/images/btn_box2.png);}"
                                      "QPushButton:pressed{border-image: url(:/images/btn_box2.png);}");
    ui->btnDev->setStyleSheet("QPushButton{border-image: url(:/images/btn_dev.png);}"
                                      "QPushButton:hover{border-image: url(:/images/btn_dev2.png);}"
                                      "QPushButton:pressed{border-image: url(:/images/btn_dev2.png);}");
    ui->btnPara->setStyleSheet("QPushButton{border-image: url(:/images/btn_para.png);}"
                                      "QPushButton:hover{border-image: url(:/images/btn_para2.png);}"
                                      "QPushButton:pressed{border-image: url(:/images/btn_para2.png);}");
    ui->btnHistory->setStyleSheet("QPushButton{border-image: url(:/images/btn_his.png);}"
                                      "QPushButton:hover{border-image: url(:/images/btn_his2.png);}"
                                      "QPushButton:pressed{border-image: url(:/images/btn_his2.png);}");





}

void frmHome::btn_click_box(bool)
{
emit this->sig_button_click(1);

}
void frmHome::btn_click_dev(bool)
{

emit this->sig_button_click(2);
}
void frmHome::btn_click_para(bool)
{

emit this->sig_button_click(3);
}
void frmHome::btn_click_his(bool)
{

emit this->sig_button_click(4);
}

void frmHome::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this );
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


frmHome::~frmHome()
{
    delete ui;
}
