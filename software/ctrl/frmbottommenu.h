#ifndef FRMBOTTOMMENU_H
#define FRMBOTTOMMENU_H

#include <QWidget>

namespace Ui {
class frmBottomMenu;
}

class frmBottomMenu : public QWidget
{
    Q_OBJECT

public:
    explicit frmBottomMenu(QWidget *parent = 0);
    ~frmBottomMenu();
    void paintEvent(QPaintEvent *);

private:
    Ui::frmBottomMenu *ui;


private slots:
    void btn_click_home(bool);
    void btn_click_warning(bool);
    void btn_click_process(bool);
    void btn_click_status(bool);
    void btn_click_pause(bool);
    void btn_click_video(bool);
    void btn_click_back(bool);


signals:
    void sig_button_click(int which);

};

#endif // FRMBOTTOMMENU_H
