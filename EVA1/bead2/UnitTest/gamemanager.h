#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QTimer>
#include <QVector>
#include <algorithm>

enum Status {Clean, Wall, Destroyed};
enum Iranyok {Bal, Jobb, Fel, Le};

class GameManager : public QObject
{
    Q_OBJECT
public:
    GameManager();
    bool canPlay() const {return _timer->isActive();}
    void click(int i, int j);
    void hitWall(int i, int j);
    bool stuck();
    Status allapot(int i, int j) const {return tableStatus[i][j];}
    ~GameManager();

public slots:
    void newGame(int size);
    void pauseGame();

private slots:
    void timerTimeout();

signals:
    void messageChanged(QString message);
    void buttonCTRL(int i, int j, bool valtozas);
    void imageChange(int i, int j, int imagenumber);
    void gameOver(int minutes, int seconds, bool win);

private:
    void changeDir();
    bool test();
    int gameTime, gameSize;
    int robot1, robot2;
    Iranyok RobotDirection;
    QTimer* _timer;
    QVector<QVector<Status> > tableStatus;
};

#endif // GAMEMANAGER_H
