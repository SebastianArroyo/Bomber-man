#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QKeyEvent>

#include "mainwindow.h"

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_play_clicked();

    void on_exit_clicked();

private:
    Ui::Menu *ui;
    MainWindow *jugar;
    void keyPressEvent(QKeyEvent *event);

};

#endif // MENU_H
