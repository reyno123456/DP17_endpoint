#include "frmparameterssetting.h"
#include "ui_frmparameterssetting.h"

frmParametersSetting::frmParametersSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmParametersSetting)
{
    ui->setupUi(this);
    pEquipment=NULL;
    connect(ui->btnNewConfig,SIGNAL(clicked(bool)),this,SLOT(btn_click_new_config(bool)));
    connect(ui->btnEquipment,SIGNAL(clicked(bool)),this,SLOT(btn_click_equipment(bool)));
    connect(ui->btnDevice,SIGNAL(clicked(bool)),this,SLOT(btn_click_device(bool)));
    connect(ui->btnStart,SIGNAL(clicked(bool)),this,SLOT(btn_click_start(bool)));

    connect(ui->btnLeftMenu1,SIGNAL(clicked(bool)),this,SLOT(btn_click_left_menu1(bool)));
    connect(ui->btnLeftMenu2,SIGNAL(clicked(bool)),this,SLOT(btn_click_left_menu2(bool)));
    connect(ui->btnLeftMenu3,SIGNAL(clicked(bool)),this,SLOT(btn_click_left_menu3(bool)));
    connect(ui->btnLeftMenu4,SIGNAL(clicked(bool)),this,SLOT(btn_click_left_menu4(bool)));


    ui->leftMenuWidget->setStyleSheet(".QWidget{background-image: url(:/images/bg1.png);}");
    ActivatedStateTopMenu(1);
    InActivatedStateLeftMenu();
    //ActivatedStateLeftMenu(1);

}

void frmParametersSetting::InActivatedStateTopMenu()
{
    ui->btnNewConfig->setStyleSheet("QPushButton{border-image: url(:/images/btn_newConfig2.png);}"
                                    "QPushButton{backgroud-image: url(:/images/btn_newConfig2.png);}");
    ui->btnEquipment->setStyleSheet("QPushButton{border-image: url(:/images/btn_equipment2.png);}"
                                    "QPushButton:{border-image: url(:/images/btn_equipment2.png);}");
    ui->btnDevice->setStyleSheet("QPushButton{border-image: url(:/images/btn_device2.png);}"
                                 "QPushButton:{border-image: url(:/images/btn_device2.png);}");
    ui->btnStart->setStyleSheet("QPushButton{border-image: url(:/images/btn_start2.png);}"
                                "QPushButton:{border-image: url(:/images/btn_start2.png);}");
}

void frmParametersSetting::ActivatedStateTopMenu(int which)
{
    InActivatedStateTopMenu();
    switch (which) {
    case 1:
        ui->btnNewConfig->setStyleSheet("QPushButton{border-image: url(:/images/btn_newConfig.png);}"
                                        "QPushButton{backgroud-image: url(:/images/btn_newConfig.png);}");
        break;case 2:
        ui->btnEquipment->setStyleSheet("QPushButton{border-image: url(:/images/btn_equipment.png);}"
                                        "QPushButton:{border-image: url(:/images/btn_equipment.png);}");
        break;
    case 3:
        ui->btnDevice->setStyleSheet("QPushButton{border-image: url(:/images/btn_device.png);}"
                                     "QPushButton:{border-image: url(:/images/btn_device.png);}");
        break;
    case 4:
        ui->btnStart->setStyleSheet("QPushButton{border-image: url(:/images/btn_start.png);}"
                                    "QPushButton:{border-image: url(:/images/btn_start.png);}");
        break;
    default:
        break;
    }
}

void frmParametersSetting::InActivatedStateLeftMenu()
{
    ui->btnLeftMenu1->setStyleSheet("QPushButton{border-image: url(:/images/btn_left_menu12.png);}"
                                    "QPushButton{backgroud-image: url(:/images/btn_left_menu12.png);}");
    ui->btnLeftMenu2->setStyleSheet("QPushButton{border-image: url(:/images/btn_left_menu22.png);}"
                                    "QPushButton:{border-image: url(:/images/btn_left_menu22.png);}");
    ui->btnLeftMenu3->setStyleSheet("QPushButton{border-image: url(:/images/btn_left_menu32.png);}"
                                    "QPushButton:{border-image: url(:/images/btn_left_menu32.png);}");
    ui->btnLeftMenu4->setStyleSheet("QPushButton{border-image: url(:/images/btn_left_menu42.png);}"
                                    "QPushButton:{border-image: url(:/images/btn_left_menu42.png);}");
}

void frmParametersSetting::ActivatedStateLeftMenu(int which)
{
    InActivatedStateLeftMenu();
    switch (which) {
    case 1:
        ui->btnLeftMenu1->setStyleSheet("QPushButton{border-image: url(:/images/btn_left_menu1.png);}"
                                        "QPushButton{backgroud-image: url(:/images/btn_left_menu1.png);}");
        break;
    case 2:
        ui->btnLeftMenu2->setStyleSheet("QPushButton{border-image: url(:/images/btn_left_menu2.png);}"
                                        "QPushButton:{border-image: url(:/images/btn_left_menu2.png);}");
        break;
    case 3:
        ui->btnLeftMenu3->setStyleSheet("QPushButton{border-image: url(:/images/btn_left_menu3.png);}"
                                        "QPushButton:{border-image: url(:/images/btn_left_menu3.png);}");
        break;
    case 4:
        ui->btnLeftMenu4->setStyleSheet("QPushButton{border-image: url(:/images/btn_left_menu4.png);}"
                                        "QPushButton:{border-image: url(:/images/btn_left_menu4.png);}");
        break;
    default:
        break;
    }
}

frmParametersSetting::~frmParametersSetting()
{
    delete ui;
    if(pEquipment!=NULL)
    {
        delete pEquipment;
        pEquipment=NULL;
    }
}


void frmParametersSetting::btn_click_new_config(bool)
{
    ActivatedStateTopMenu(1);

}
void frmParametersSetting::btn_click_equipment(bool)
{
    ActivatedStateTopMenu(2);

}
void frmParametersSetting::btn_click_device(bool)
{
    ActivatedStateTopMenu(3);

}
void frmParametersSetting::btn_click_start(bool)
{
    ActivatedStateTopMenu(4);

}

void frmParametersSetting::btn_click_left_menu1(bool)
{
    ActivatedStateLeftMenu(1);

    if(pEquipment==NULL)
    {
        pEquipment=new frmEquipment();
        pEquipment->setParent(this);
        connect(pEquipment,SIGNAL(sig_close()),this,SLOT(frmEquipmentClose()));
    }
    ui->frameMain->hide();
    pEquipment->show();
}
void frmParametersSetting::btn_click_left_menu2(bool)
{
    ActivatedStateLeftMenu(2);
}
void frmParametersSetting::btn_click_left_menu3(bool)
{
    ActivatedStateLeftMenu(3);
}
void frmParametersSetting::btn_click_left_menu4(bool)
{
    ActivatedStateLeftMenu(4);
}

void frmParametersSetting::frmEquipmentClose()
{
    if(pEquipment!=NULL)
    {
        delete pEquipment;
        pEquipment=NULL;
    }
    InActivatedStateLeftMenu();
    ui->frameMain->show();
}
