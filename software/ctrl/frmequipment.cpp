#include "frmequipment.h"
#include "ui_frmequipment.h"
#include <QLayoutItem>
#include <QVBoxLayout>
#include <QHBoxLayout>

QScrollArea* area1=NULL;
QScrollArea* area2=NULL;
QScrollArea* area3=NULL;
QScrollArea* area4=NULL;

QWidget* area1_widget=NULL;
frmEquipment::frmEquipment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmEquipment)
{
    ui->setupUi(this);
    connect(ui->btnAdd,SIGNAL(clicked(bool)),this,SLOT(btn_click_add(bool)));
    connect(ui->btnSave,SIGNAL(clicked(bool)),this,SLOT(btn_click_save(bool)));
    connect(ui->btnUpdate,SIGNAL(clicked(bool)),this,SLOT(btn_click_update(bool)));
    InActivatedTopButton();

    /*
    ui->scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QWidget* widget=new QWidget();
     ui->scrollArea_2->setGeometry(0,0,100,200);
    widget->setGeometry(0,0,200,400);
    QWidget* widget33=ui->scrollArea_2->takeWidget();
    delete widget33;
    //ui->scrollAreaWidgetContents_3->setGeometry(0,0,200,400);
    widget->setStyleSheet("background-color: rgb(255, 255, 127);");
    ui->scrollArea_2->setWidget(widget);
    ui->scrollArea_2->setWidgetResizable(false);

*/

    /*
    area3=new QScrollArea(ui->widgetMenu3);
    area3->setGeometry(10,15,201,351);
    QWidget* widget2=new QWidget();
    widget2->setGeometry(0,0,300,400);
    area3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    widget2->setStyleSheet("background-color: rgb(255, 255, 127);");
    area3->setWidget(widget2);
    area3->setWidgetResizable(false);
    */



    area1=new QScrollArea(ui->widgetMenu1);
    area1->setGeometry(10,15,201,351);
    area1_widget=new QWidget();

    area1->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    area1->setStyleSheet("background-color: rgba(255, 255, 127,0);border:0px solid #FF00FF;");
    area1_widget->setStyleSheet("background-color: rgba(255, 255, 127,0);border:0px solid #FF00FF;");
    area1->setWidget(area1_widget);
    area1->setWidgetResizable(false);


init_onelayer_menu();


}

frmEquipment::~frmEquipment()
{
    delete ui;
    if(area1_widget!=NULL)
    {
        delete area1_widget;
        area1_widget=NULL;
    }
}

void frmEquipment::InActivatedTopButton()
{
    ui->btnAdd->setStyleSheet("QPushButton{border-image: url(:/images/btn_add2.png);}"
                              "QPushButton{backgroud-image: url(:/images/btn_add2.png);}");
    ui->btnSave->setStyleSheet("QPushButton{border-image: url(:/images/btn_save2.png);}"
                               "QPushButton:{border-image: url(:/images/btn_save2.png);}");
    ui->btnUpdate->setStyleSheet("QPushButton{border-image: url(:/images/btn_update2.png);}"
                                 "QPushButton:{border-image: url(:/images/btn_update2.png);}");
}

void frmEquipment::ActivatedTopButton(int which)
{

    InActivatedTopButton();
    switch (which) {
    case 1:
        ui->btnAdd->setStyleSheet("QPushButton{border-image: url(:/images/btn_add.png);}"
                                  "QPushButton{backgroud-image: url(:/images/btn_add.png);}");
        break;case 2:
        ui->btnSave->setStyleSheet("QPushButton{border-image: url(:/images/btn_save.png);}"
                                   "QPushButton:{border-image: url(:/images/btn_save.png);}");
        break;
    case 3:
        ui->btnUpdate->setStyleSheet("QPushButton{border-image: url(:/images/btn_update.png);}"
                                     "QPushButton:{border-image: url(:/images/btn_update.png);}");
        break;
    default:
        break;
    }
}
void frmEquipment::hideTreeMenu()
{
    ui->widgetMenu1->hide();
    ui->widgetMenu2->hide();
    ui->widgetMenu3->hide();
    ui->widgetMenu4->hide();
}
void frmEquipment::clearItems(QWidget* pWidget)
{
#if 0
    QLayoutItem *child;
    int count=pWidget->count();
    for(int i=count-1;i>=0;i--)
    {
        child=pWidget->itemAt(i);
        pWidget->removeItem(child);
        delete child;
    }
    /*
    while(child=pWidget->takeAt(0)) {
          pWidget->removeItem(child);
        delete child;
    }
    */
    pWidget->update();
    pWidget->invalidate();
#endif


    QList<TreeButtonItem*> btns = pWidget->findChildren<TreeButtonItem*>();
    foreach (TreeButtonItem* btn, btns) {   delete btn;  }


    /*
    QLayoutItem *child=NULL;
    while (true) {
         QLayout *layout =pWidget->layout();
         if(layout!=NULL)
         {
             child=layout->takeAt(0);
             if(child==NULL)
             {
                  break;
             }
             delete child;
         }
         else
         {
             break;
         }
    }
    */

    //QObjectList list= ui->widgetMenu1_vl->children();
    /*   QList<QPushButton*> btns = ui->widgetMenu1->findChildren<QPushButton*>();
    foreach (QPushButton* btn, btns) {
        //ui->widgetMenu1_vl->removeWidget(btn);
        // delete btn;
    }
    */


    /*QObjectList list =ui->widgetMenu1->children();
      list.clear();
      ui->widgetMenu1.
      */
    /*
    QLayoutItem *child=NULL;
    while (true) {
         QObjectList list =ui->widgetMenu1->children();
         if(layout!=NULL)
         {
             child=layout->takeAt(0);
             if(child==NULL)
             {
                  break;
             }
             delete child;
         }
         else
         {
             break;
         }
    }
    */
    //while(child= ui->widgetMenu1->layout()->takeAt(0)) {
    // ui->widgetMenu1->removeItem(child);
    //delete child;
    //}

}

void frmEquipment::clear_onelayer_menu()
{
    if(area1_widget!=NULL)
    {
        clearItems(area1_widget);
    }
}
void frmEquipment::init_onelayer_menu()
{
    clear_onelayer_menu();
    int _y=0;
    TreeButtonItem * btn=new TreeButtonItem();
    connect(btn,SIGNAL(sig_click(TreeButtonItem*,QString)),this,SLOT(on_btn_click_onelayer(TreeButtonItem*,QString)));
    btn->move(0,_y);
    btn->setParent(area1_widget);
    btn->setValue("1");
    btn->setCurrent(false);
    btn->show();
    _y=btn->height()*1;

    btn=new TreeButtonItem();
    connect(btn,SIGNAL(sig_click(TreeButtonItem*,QString)),this,SLOT(on_btn_click_onelayer(TreeButtonItem*,QString)));
    btn->move(0,_y);
    btn->setParent(area1_widget);
    btn->setValue("2");
    btn->setCurrent(false);
    btn->show();
    _y=btn->height()*2;

    btn=new TreeButtonItem();
    connect(btn,SIGNAL(sig_click(TreeButtonItem*,QString)),this,SLOT(on_btn_click_onelayer(TreeButtonItem*,QString)));
    btn->move(0,_y);
    btn->setParent(area1_widget);
    btn->setValue("3");
    btn->setCurrent(false);
    btn->show();
    _y=btn->height()*3;

    btn=new TreeButtonItem();
    connect(btn,SIGNAL(sig_click(TreeButtonItem*,QString)),this,SLOT(on_btn_click_onelayer(TreeButtonItem*,QString)));
    btn->move(0,_y);
    btn->setParent(area1_widget);
    btn->setValue("4");
    btn->setCurrent(false);
    btn->show();
    _y=btn->height()*4;

    area1_widget->setGeometry(0,0,btn->width(),_y);
}


void frmEquipment::on_btn_click_onelayer(TreeButtonItem* btn,QString value)
 {
    QList<TreeButtonItem*> btns = area1_widget->findChildren<TreeButtonItem*>();
    foreach (TreeButtonItem* btn, btns) {    btn->setCurrent(false);  }
    btn->setCurrent(true);

 }

void frmEquipment::on_btn_click_twolayer(TreeButtonItem* btn,QString value)
{

}
void frmEquipment::clear_twolayer_menu()
{

}
void frmEquipment::init_twolayer_menu()
{

}

void frmEquipment::on_btn_click_threelayer(TreeButtonItem* btn,QString value)
{

}
void frmEquipment::clear_threelayer_menu()
{

}
void frmEquipment::init_threelayer_menu()
{

}

void frmEquipment::on_btn_click_fourlayer(TreeButtonItem* btn,QString value)
{

}
void frmEquipment::clear_fourlayer_menu()
{

}
void frmEquipment::init_fourlayer_menu()
{

}


void frmEquipment::showOneLayerMenu()
{


}
void frmEquipment::btn_click_add(bool)
{
    ActivatedTopButton(1);
    showOneLayerMenu();

}
void frmEquipment::btn_click_save(bool)
{
    ActivatedTopButton(2);
    this->close();
    emit this->sig_close();
}
void frmEquipment::btn_click_update(bool)
{
    ActivatedTopButton(3);

    QPushButton* st=new QPushButton();
    st->setText("Test");
    st->setMinimumHeight(20);
    st->setMaximumWidth(100);
    //ui->widgetMenu1_vl->addWidget(st);

    QPushButton* btn=new QPushButton();
    btn->setText("123");
    btn->resize(100,30);

}
