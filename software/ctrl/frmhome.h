#ifndef FRMHOME_H
#define FRMHOME_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
namespace Ui {
class frmHome;
}

class frmHome : public QWidget
{
    Q_OBJECT

public:
    explicit frmHome(QWidget *parent = 0);
    ~frmHome();

private:
    Ui::frmHome *ui;

void paintEvent(QPaintEvent *);
private slots:
    void btn_click_box(bool);
    void btn_click_dev(bool);
    void btn_click_para(bool);
    void btn_click_his(bool);


signals:
    void sig_button_click(int which);
};

#endif // FRMHOME_H
