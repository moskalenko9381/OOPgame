#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QDesktopWidget>
#include <QMessageBox>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/new/cheb.png"));

    field = &Field::getInstance(HEIGHT,WIDTH);

    playerControl = new Controller(Player(),field);

    gameRuller = new GameRuller(playerControl, field);

    command = new CommandClass();
    command->setCommand(new CreateGameCommand(gameRuller));
    scene = makeScene();
   }

QGraphicsScene* MainWindow::makeScene(){
    ui->lives->setText("LIVES: " + QString::number(playerControl->controlLivesPlayer()));
    ui->coins->setText("COINS: " + QString::number(playerControl->controlCoinsPlayer()));
    ui->weapon->setText("WEAPON: " + QString::number(playerControl->controlWeaponPlayer()));
    scene = new QGraphicsScene();
    screenSize = QDesktopWidget().availableGeometry(this).size();
    setFixedSize(screenSize);
    ui->graphicsView->setFixedSize(screenSize);
    makeRects();
    ui->graphicsView->setScene(scene);
    return scene;
}

void MainWindow::makeRects(){
    int rectHeight = screenSize.height()*0.8/HEIGHT;
    int rectWidth = screenSize.width()*0.8/WIDTH;
    rects = new QGraphicsRectItem** [HEIGHT];

    for (auto i = 0; i < HEIGHT; i++)
        rects[i] = new QGraphicsRectItem*[WIDTH];

     for(Square square : *field){ //ITERATOR
           Coords c = square.getCoords();
           auto i = c.h;
           auto j = c.w;
           QBrush brush;
           rects[i][j] = scene->addRect(QRectF(i*rectWidth, j*rectHeight,rectWidth, rectHeight));
           if (playerControl->checkEnemy(c)){
               brush = enemyBrush(c);
           }
                  else
           brush = getBrush(field->field[j][i].getType());
             rects[i][j]->setBrush(brush);
            }
 }


QBrush MainWindow::enemyBrush(Coords c){
    int rectHeight = screenSize.height()*0.8/HEIGHT;
    int rectWidth = screenSize.width()*0.8/WIDTH;
    AbstractEnemy* enemy = playerControl->getEnemy(c);
         auto &type = enemy->getEnemyType();
         if (type == typeid(Enemy<TheftBehavior>))
                return QBrush(QImage(":/new/theft.png").scaled(rectWidth, rectHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
         else if (type == typeid(Enemy<AttackBehavior>))
                return QBrush(QImage(":/new/attack.png").scaled(rectWidth,rectHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
         else  return QBrush(QImage(":/new/stalker.png").scaled(rectWidth,rectHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    }

QBrush MainWindow::getBrush(Type type){
    int rectHeight = screenSize.height()*0.8/HEIGHT;
    int rectWidth = screenSize.width()*0.8/WIDTH;
    switch(type){
    case ENTRY:
             return (QBrush(QImage(":/new/open.jpg").scaled(rectWidth,rectHeight,Qt :: IgnoreAspectRatio ,Qt::SmoothTransformation)));
    case CLOSE:
              return (QBrush(QImage(":/new/rock.png").scaled(rectWidth,rectHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    case EXIT:
             return (QBrush(QImage(":/new/doors.jpg").scaled(rectWidth,rectHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    case OPEN:
            return (QBrush(QImage(":/new/green.png").scaled(rectWidth,rectHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    case COINS:
            return (QBrush(QImage(":/new/coin.png").scaled(rectWidth,rectHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    case PLAYER:
            return (QBrush(QImage(":/new/rat.png").scaled(rectWidth,rectHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    case VORTEX:
            return (QBrush(QImage(":/new/vortex.png").scaled(rectWidth,rectHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    case WEAPON:
         return (QBrush(QImage(":/new/weapon.png").scaled(rectWidth,rectHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        }
}


void MainWindow::startNewGame(){
    delete scene;
    QMessageBox::information(this, "START NEW GAME.", "STARTING NEW GAME!");
    command->setCommand(new StartNewGameCommand(gameRuller));
    scene = makeScene();
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    ui->lives->setText("LIVES: " + QString::number(playerControl->controlLivesPlayer()));
    ui->coins->setText("COINS: " + QString::number(playerControl->controlCoinsPlayer()));
    ui->weapon->setText("WEAPON: " + QString::number(playerControl->controlWeaponPlayer()));
     if (playerControl->playerWin()){
          QMessageBox::information(this, "Game over", "You won! Starting new game.");
          startNewGame();
          return;
     }

     if (playerControl->controlLivesPlayer() <= 0){
             QMessageBox::warning(this, "OOPS", "GAME OVER. YOU LOST.");
             startNewGame();
             return;
     }

     playerCoords = playerControl->getPlayerCoords();

     switch(event->key()){

         case Qt::Key_W:
             newCoords = playerControl->controlMovePlayer(UP);
             break;

         case Qt::Key_A:
             newCoords = playerControl->controlMovePlayer(LEFT);
         break;

        case Qt::Key_S:
             newCoords = playerControl->controlMovePlayer(DOWN);
         break;

         case Qt::Key_D:
             newCoords = playerControl->controlMovePlayer(RIGHT);
         break;

         case Qt::Key_H:
           startNewGame();
           return;

         case Qt::Key_J:
            delete scene;
            QMessageBox::information(this, "THE END.", "GOODBYE!");
            command->setCommand(new EndGameCommand(gameRuller));
            this->close();
            return;

       case Qt::Key_R:{
              command->setCommand(new SaveGameCommand(gameRuller));
         break;
     }
     case Qt::Key_K:{
          command->setCommand(new LoadGameCommand(gameRuller));
          newCoords = playerControl->getPlayer().getCoords();
          makeRects();
          QMessageBox::information(this, "LOADED.", "LOADED!");
          break;
     }

      default:
            return;
     }

       ui->lives->setText("LIVES: " + QString::number(playerControl->controlLivesPlayer()));
       ui->coins->setText("COINS: " + QString::number(playerControl->controlCoinsPlayer()));
       ui->weapon->setText("WEAPON: " + QString::number(playerControl->controlWeaponPlayer()));
       rects[newCoords.w][newCoords.h]->setBrush(getBrush(PLAYER));

      if (playerCoords.w != newCoords.w || playerCoords.h != newCoords.h )
         rects[playerCoords.w][playerCoords.h]->setBrush(getBrush(OPEN));


     if (playerControl->playerWin()){
         QMessageBox::information(this, "Game over", "You won! Please start new game.");
         return;
     }
}



MainWindow::~MainWindow()
{
    delete gameRuller;
    delete ui;
}
