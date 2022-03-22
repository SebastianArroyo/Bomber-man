#include <QRandomGenerator>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configuracion.h"
#include "jugador.h"
#include "enemigo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizarEstado()));
    escena = new QGraphicsScene(this);
    int fil=(tamanios::Filas)*(tamanios::TamanioCampo);
    int col=(tamanios::Columnas)*(tamanios::TamanioCampo);
    escena->setSceneRect(0, 0, col, fil);
    escena->clearFocus();

    vista=ui->graphicsView;
    vista->setScene(escena);
    ui->centralwidget->adjustSize();
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setFixedSize(col+2, fil+2);

    setWindowTitle(tr("Bomberman"));
    setWindowIcon(QPixmap(":img/img/bomb.png"));

    campos_de_inicio(2);

    inicializarJuego();
}

void MainWindow::inicializarJuego(){
    conteodejugadores = tamanios::Jugadores;
    conteoEnemigos = tamanios::Enemigos;

    jugador1 = new Jugador(0, 0);
    connect(jugador1, SIGNAL(jugadorMuerto()), this, SLOT(jugadorMuerto()));
    campos[0][0]->playerOn(jugador1);

    jugador2 = new Jugador(tamanios::Columnas - 1, tamanios::Filas - 1);
    connect(jugador2, SIGNAL(jugadorMuerto()), this, SLOT(jugadorMuerto()));
    campos[tamanios::Filas - 1][tamanios::Columnas - 1]->playerOn(jugador2);

    enemigo1 = new Enemigo(10,6);
    connect(enemigo1, SIGNAL(enemigoMuerto()), this, SLOT(enemigoMuerto()));
    campos[10][6]->enemigoOn(enemigo1);
    enemigo1->mover(Derecha2,campos);
    enemigo1->mover(Izquierda2,campos);

//    enemigo2 = new Enemigo(16,6);
//    connect(enemigo2, SIGNAL(enemigoMuerto()), this, SLOT(enemigoMuerto()));
//    campos[16][6]->enemigoOn(enemigo2);
//    enemigo2->mover(Derecha2,campos);
//    enemigo2->mover(Izquierda2,campos);

    escena->addItem(jugador1);
    escena->addItem(jugador2);
    escena->addItem(enemigo1);
//    escena->addItem(enemigo2);

    puntos= new Puntaje();
    setFocus();


    time.setHMS(0,2,0);
    ui->cronometro->setText(time.toString("m:ss"));
    timer->start();
}

void MainWindow::ResultadoFinal(){
    msgBox.setWindowTitle("Juego terminado");
    msgBox.setIcon(QMessageBox::Information);
    if(time.toString()=="00:00:00"){
        timer->stop();
        msgBox.setText("¡¡¡¡¡¡Perdiste!!!!!!");
        msgBox.exec();
        QCoreApplication::quit();
    }
}

void MainWindow::actualizarCronometro(){
    time=time.addMSecs(-1);
    ui->cronometro->setText(time.toString("m:ss"));
}

void MainWindow::actualizarEstado(){
    ui->score->setText(QString::number(puntos->getScore()));
    ui->left->setText(QString::number(jugador1->getVida()));
    ui->left_2->setText(QString::number(jugador2->getVida()));
    ui->left_3->setText(QString::number(enemigo1->getVida2()));
//    ui->left_3->setText(QString::number(enemigo2->getVida2()));

    actualizarCronometro();
    ResultadoFinal();
}

MainWindow::~MainWindow() {
    for (std::size_t i = 0; i < tamanios::Filas; i++) {
        for(std::size_t j = 0; j < tamanios::Columnas; j++) {
          delete  campos[i][j];
        }
    }

    delete jugador1;
    delete jugador2;
    delete enemigo1;
//    delete enemigo2;
    delete escena;
    delete vista;
    delete ui;
}

void MainWindow::jugadorMuerto()
{
    conteodejugadores--;
    if(conteodejugadores == 0) {
        delete this;
    }
    timer->stop();
    msgBox.setText("¡¡¡¡¡¡Perdiste!!!!!!");
    msgBox.exec();
    this->close();
}

void MainWindow::enemigoMuerto()
{
    conteoEnemigos--;
    if(conteoEnemigos == 0) {
        escena->removeItem(enemigo1);
    }
    timer->stop();
    msgBox.setText("¡¡¡¡¡¡Ganaste!!!!!!");
    msgBox.exec();
    this->close();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    setFocus();
    //control jugador 1
    switch (event->key()) {
        case Qt::Key_A:
            jugador1->mover(Izquierda, campos);
            break;
        case Qt::Key_D:
            jugador1->mover(Derecha, campos);
            break;
        case Qt::Key_S:
            jugador1->mover(Abajo, campos);
            break;
        case Qt::Key_W:
            jugador1->mover(Arriba, campos);
            break;
        case Qt::Key_E:
            jugador1->plantarBomba(campos);
            break;
    }

    //control jugador 2
    switch (event->key()) {
        case Qt::Key_Left:
            jugador2->mover(Izquierda, campos);
            break;
        case Qt::Key_Right:
            jugador2->mover(Derecha, campos);
            break;
        case Qt::Key_Down:
            jugador2->mover(Abajo, campos);
            break;
        case Qt::Key_Up:
            jugador2->mover(Arriba, campos);
            break;
        case Qt::Key_Shift:
            jugador2->plantarBomba(campos);
            break;
    }
}

void MainWindow::campos_de_inicio(int frecuencia) {
    for (int i = 0; i < tamanios::Filas; i++) {
        campos.push_back(std::vector<Campo *>());
        for(int j = 0; j < tamanios::Columnas; j++) {
            Campo *nuevoCampo = new Campo(j * tamanios::TamanioCampo, i * tamanios::TamanioCampo);
            campos[static_cast<std::size_t>(i)].push_back(nuevoCampo);
            escena->addItem(nuevoCampo);
            //Bloques indestructibles
            if (i % 2 && j % 2) {
                nuevoCampo->ubiBloqueIndestruible(new BloqueIndestruible());
            }
            //Bloques destructibles
            else if ((i > 1 || j > 1) && (i < tamanios::Filas - 2 || j < tamanios::Columnas - 2) && ((i!=6)||(j!=9)) && ((i!=6)||(j!=10)) && ((i!=6)||(j!=11))) {
                if(QRandomGenerator::global()->bounded(frecuencia)) { //frecuencia de bloques destructibles
                    nuevoCampo->ubiBloqueDestruible(new BloqueDestruible());
                }
            }
        }
    }
}
