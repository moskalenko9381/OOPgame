#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene>
#include <QMainWindow>
#include <QKeyEvent>
#include "gamecommands.h"
#include "gameruller.h"
#include "commandclass.h"
#include "saveandload.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
   void keyPressEvent(QKeyEvent* event);
private:

    QSize screenSize;
    Ui::MainWindow *ui;
    QGraphicsScene* scene;

     Field* field;
     Controller* playerControl;

    GameRuller* gameRuller;
    CommandClass* command;

    QGraphicsRectItem*** rects;
    QBrush getBrush(Type type);
    QBrush enemyBrush(Coords c);

    void eventsCheck(Dir direction);
    void makeRects();
    void startNewGame();

    QGraphicsScene* makeScene();

    Coords playerCoords;
    Coords newCoords;
};
#endif // MAINWINDOW_H

