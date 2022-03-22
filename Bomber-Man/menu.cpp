#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setWindowTitle(tr("Bomberman"));
    setWindowIcon(QPixmap(":img/img/bomb.png"));
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_play_clicked()
{
    jugar = new MainWindow;
    jugar->show();
    this->close();
}


void Menu::on_exit_clicked()
{
    this->close();
}

void Menu::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()){
        case Qt::Key_Return:
            jugar = new MainWindow;
            jugar->show();
            this->close();
        break;
        case Qt::Key_Enter:
            jugar = new MainWindow;
            jugar->show();
            this->close();
        break;
        case Qt::Key_Escape:
            this->close();
        break;
    }
}

