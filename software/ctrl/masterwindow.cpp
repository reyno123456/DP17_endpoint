#include "masterwindow.h"
#include "ui_masterwindow.h"

MasterWindow::MasterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MasterWindow)
{
    ui->setupUi(this);
    //QMainWindow::K

    this->resize(1024,600);
    this->setWindowFlags(Qt::SplashScreen);

    pConfigDevice=NULL;
    height_top=63;
    height_bottom=89;
    height_center=SCREEN_HEIGHT-height_top-height_bottom;


    pSysMenu=new frmSysMenu();
    pSysMenu->setParent(this);
    pSysMenu->move(0,0);
    pSysMenu->resize(SCREEN_WIDTH,height_top);
    pSysMenu->show();

    pBottomMenu=new frmBottomMenu();
    pBottomMenu->setParent(this);
    pBottomMenu->move(0,height_top+height_center);
    pBottomMenu->resize(SCREEN_WIDTH,height_bottom);
    pBottomMenu->show();

    pHome=new frmHome();
    pHome->setParent(this);
    pHome->show();
    pHome->move(0,height_top);

    pParametersSetting=NULL;

    this->setStyleSheet("QMainWindow{background-image: url(:/images/bg.png);}");
    //connect(ui->btnSystem,SIGNAL(clicked()),this,SLOT(btn_system_click()));
    connect(pHome,SIGNAL(sig_button_click(int)),this,SLOT(btn_home_click(int)));
    connect(pBottomMenu,SIGNAL(sig_button_click(int)),this,SLOT(btn_bottom_menu_click(int)));


    pSysMenu->setProcess(0);


    pBottomTitle=new QWidget(this);
    pBottomTitle->resize(133,15);
    pBottomTitle->setStyleSheet("background-image: url(:/images/bottom_menu_title.png);");
    setBottomMenuTitlePos(1);
}

MasterWindow::~MasterWindow()
{
    delete ui;
    delete pSysMenu;
    delete pBottomMenu;
    if(pConfigDevice!=NULL)
    {
        delete pConfigDevice;
        pConfigDevice=NULL;
    }
    if(pBottomTitle!=NULL)
    {
        delete pBottomTitle;
        pBottomTitle=NULL;
    }
    if(pParametersSetting!=NULL)
    {
        delete pParametersSetting;
        pParametersSetting=NULL;
    }


}
void MasterWindow::keyReleaseEvent(QKeyEvent *event)
{
    QWidget::keyReleaseEvent(event);
    if(Qt::Key_Escape== event->key())
    {
        this->close();
        QApplication::exit(0);
    }
}
void MasterWindow::btn_system_click()
{
    if(pConfigDevice==NULL)
    {
        pConfigDevice=new frmConfigDevice();
        pConfigDevice->show();
    }
}

void MasterWindow::setBottomMenuTitlePos(int which)
{
    int offset=8;

    pBottomTitle->move((which-1)*150,pBottomMenu->pos().y()-offset);
    pBottomTitle->show();
}
void MasterWindow::btn_home_click(int which)
{
    pHome->hide();

    if(which==3)
    {
        if(pParametersSetting==NULL)
        {
            pParametersSetting=new frmParametersSetting();
            pParametersSetting->setParent(this);
        }
        pParametersSetting->show();
        pParametersSetting->move(0,height_top);


    }
    btn_bottom_menu_click(0);//隐藏绿色导航条

}
void MasterWindow::btn_bottom_menu_click(int which)
{
    setBottomMenuTitlePos(which);
    if(which==1)
    {
        if(pParametersSetting!=NULL)
        {
            pParametersSetting->hide();
        }
        pHome->show();
    }
}
