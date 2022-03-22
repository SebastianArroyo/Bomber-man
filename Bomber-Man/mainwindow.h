#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <vector>

#include "jugador.h"
#include "campo.h"
#include "puntaje.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer = new QTimer();
    QTime time;
    QMessageBox msgBox;
    std::vector<std::vector<Campo *>> campos;

public slots:
    void actualizarEstado();
    void actualizarCronometro();
    void ResultadoFinal();
    void jugadorMuerto();
    void enemigoMuerto();


private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event);
    void move(Campo *campo);
    void campos_de_inicio(int frecuencia);
    void inicializarJuego();
    QGraphicsView *vista;
    QGraphicsScene *escena;
    Jugador *jugador1;
    Jugador *jugador2;
    Enemigo *enemigo1;
//    Enemigo *enemigo2;
    Puntaje *puntos;
    int conteodejugadores;
    int conteoEnemigos;
};

#endif // MAINWINDOW_H
