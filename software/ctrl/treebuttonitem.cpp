#include "treebuttonitem.h"
#include "ui_treebuttonitem.h"

TreeButtonItem::TreeButtonItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeButtonItem)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(on_click(bool)));
    setCurrent(false);
}

TreeButtonItem::~TreeButtonItem()
{
    delete ui;
}
void TreeButtonItem::on_click(bool)
{
emit this->sig_click(this,_value);

}
void TreeButtonItem::setCurrent(bool flag)
{
    if(flag)
    {
        ui->widget->show();
        ui->pushButton->setStyleSheet("QPushButton{border-image: url(:/images/treemenu/m"+_value+"_b.png);}"
                                       "QPushButton{backgroud-image: url(:/images/treemenu/m"+_value+"_b.png);}");
    }
    else
    {
        ui->widget->hide();
        ui->pushButton->setStyleSheet("QPushButton{border-image: url(:/images/treemenu/m"+_value+".png);}"
                                       "QPushButton{backgroud-image: url(:/images/treemenu/m"+_value+".png);}");
    }
}

void TreeButtonItem::setValue(QString value)
{
    this->_value=value;
    ui->pushButton->setStyleSheet("QPushButton{border-image: url(:/images/treemenu/m"+_value+".png);}"
                                   "QPushButton{backgroud-image: url(:/images/treemenu/m"+_value+".png);}");
    return;
}

