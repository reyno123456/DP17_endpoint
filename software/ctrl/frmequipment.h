#ifndef FRMEQUIPMENT_H
#define FRMEQUIPMENT_H

#include <QWidget>
#include <QVBoxLayout>
#include "treebuttonitem.h"
namespace Ui {
class frmEquipment;
}

class frmEquipment : public QWidget
{
    Q_OBJECT

public:
    explicit frmEquipment(QWidget *parent = 0);
    ~frmEquipment();

private:
    Ui::frmEquipment *ui;
    void InActivatedTopButton();
    void ActivatedTopButton(int which);
    void hideTreeMenu();
    void clearItems(QWidget* pWidget);
    void showOneLayerMenu();

private slots:
    void btn_click_add(bool);
    void btn_click_save(bool);
    void btn_click_update(bool);

    void on_btn_click_onelayer(TreeButtonItem* btn,QString value);
    void clear_onelayer_menu();
    void init_onelayer_menu();

    void on_btn_click_twolayer(TreeButtonItem* btn,QString value);
    void clear_twolayer_menu();
    void init_twolayer_menu();

    void on_btn_click_threelayer(TreeButtonItem* btn,QString value);
    void clear_threelayer_menu();
    void init_threelayer_menu();

    void on_btn_click_fourlayer(TreeButtonItem* btn,QString value);
    void clear_fourlayer_menu();
    void init_fourlayer_menu();
signals:
    void sig_close();
};

#endif // FRMEQUIPMENT_H
