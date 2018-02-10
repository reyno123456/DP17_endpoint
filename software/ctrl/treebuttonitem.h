#ifndef TREEBUTTONITEM_H
#define TREEBUTTONITEM_H

#include <QWidget>

namespace Ui {
class TreeButtonItem;
}

class TreeButtonItem : public QWidget
{
    Q_OBJECT

public:
    explicit TreeButtonItem(QWidget *parent = 0);
    ~TreeButtonItem();
    void setCurrent(bool flag);
    void setValue(QString value);
    QString getValue( );

private:
    Ui::TreeButtonItem *ui;
    QString _value;

public slots:
    void on_click(bool);

signals:
    void sig_click(TreeButtonItem* btn,QString value);
};

#endif // TREEBUTTONITEM_H
