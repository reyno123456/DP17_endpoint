#ifndef FRMPARAMETERSSETTING_H
#define FRMPARAMETERSSETTING_H

#include <QWidget>
#include "frmequipment.h"
namespace Ui {
class frmParametersSetting;
}

class frmParametersSetting : public QWidget
{
    Q_OBJECT

public:
    explicit frmParametersSetting(QWidget *parent = 0);
    ~frmParametersSetting();

private:
    Ui::frmParametersSetting *ui;
    frmEquipment* pEquipment;

    void InActivatedStateTopMenu();
    void ActivatedStateTopMenu(int which);
    void InActivatedStateLeftMenu();
    void ActivatedStateLeftMenu(int which);

private slots:
    void btn_click_new_config(bool);
    void btn_click_equipment(bool);
    void btn_click_device(bool);
    void btn_click_start(bool);

    void btn_click_left_menu1(bool);
    void btn_click_left_menu2(bool);
    void btn_click_left_menu3(bool);
    void btn_click_left_menu4(bool);
    void frmEquipmentClose();

};

#endif // FRMPARAMETERSSETTING_H
