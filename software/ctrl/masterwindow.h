#ifndef MASTERWINDOW_H
#define MASTERWINDOW_H

#include <QMainWindow>
#include "frmsysmenu.h"
#include "frmbottommenu.h"
#include "frmhome.h"
#include "frmconfigdevice.h"
#include "frmparameterssetting.h"

#include "config.h"
#include <QKeyEvent>
namespace Ui {
class MasterWindow;
}

class MasterWindow : public QMainWindow
{
    Q_OBJECT

public:
    frmSysMenu* pSysMenu;
    frmBottomMenu* pBottomMenu;
    frmHome* pHome;
    frmParametersSetting*pParametersSetting;
    frmConfigDevice* pConfigDevice;

    QWidget* pBottomTitle;



    explicit MasterWindow(QWidget *parent = 0);
    ~MasterWindow();

private:
    Ui::MasterWindow *ui;
    int height_top;
    int height_center;
    int height_bottom;
    void setBottomMenuTitlePos(int);
    void keyReleaseEvent(QKeyEvent *event);
public slots:
    void btn_system_click();
    void btn_home_click(int);
    void btn_bottom_menu_click(int);

};

#endif // MASTERWINDOW_H
