#ifndef FRMSYSMENU_H
#define FRMSYSMENU_H

#include <QWidget>
#include <QTimer>
namespace Ui {
class frmSysMenu;
}

class frmSysMenu : public QWidget
{
    Q_OBJECT

public:
    explicit frmSysMenu(QWidget *parent = 0);
    ~frmSysMenu();

    void paintEvent(QPaintEvent *);
    void setProcess(int process);

public slots:
    void btn_shutdown(bool);
    void btn_sysmenu(bool);
    void timer_update();

private:
    Ui::frmSysMenu *ui;
    QTimer timer;

};

#endif // FRMSYSMENU_H
