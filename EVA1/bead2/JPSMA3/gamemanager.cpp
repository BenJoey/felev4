#include "gamemanager.h"

#include <QTime>

GameManager::GameManager()
{
    _timer = new QTimer();
    _timer->setInterval(1000);

    qsrand(QTime::currentTime().msec());

    connect(_timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));

    for(int i = 0;i < 4; ++i){
        _images.append(QPixmap(":/images/"+ QString::number(i+1) + ".png")); // 0-Robot  1-Fal  2-Ledöntött Fal  3-Blank
    }
}

GameManager::~GameManager()
{
    _timer->stop();
    delete _timer;
}

void GameManager::pauseGame()
{
    if (_timer->isActive())
    {
        messageChanged(trUtf8("Játék megállítva"));
        _timer->stop();
    }
    else _timer->start();
}

void GameManager::newGame(int size)
{
    if(_timer->isActive()) _timer->stop();
    tableStatus.clear();
    gameTime = 0;
    gameSize = size;
    robot1 = qrand() % size;
    robot2 = qrand() % size;
    tableStatus.resize(size);
    for(int i = 0; i<size;++i){
        tableStatus[i].resize(size);
        for(int j = 0; j<size;++j){
            tableStatus[i][j] = Clean;
            emit buttonCTRL(i,j,true);
        }
    }
    emit imageChange(robot1, robot2, 0);
    emit buttonCTRL(robot1, robot2, false);
    changeDir();

    _timer->start();
}

void GameManager::click(int i, int j)
{
    tableStatus[i][j]=Wall;
    emit imageChange(i,j,1);
}

void GameManager::hitWall(int i, int j)
{
    if(i < gameSize && i >= 0 && j < gameSize && j >= 0){
        tableStatus[i][j]=Destroyed;
    }
}

void GameManager::changeDir()
{
    QVector<Iranyok> PossibleDirections = {Bal, Jobb, Fel, Le};
    PossibleDirections.erase(std::remove(PossibleDirections.begin(), PossibleDirections.end(), RobotDirection), PossibleDirections.end());
    RobotDirection = PossibleDirections[qrand() % PossibleDirections.size()];
}

bool GameManager::test()
{
    bool a;
    int x = 0,y = 0;
    switch (RobotDirection) {
    case Bal: a = (robot2==0 || tableStatus[robot1][robot2-1]==Wall); y = -1;break;
    case Jobb: a = robot2 == gameSize-1 || tableStatus[robot1][robot2+1]==Wall; y = 1;break;
    case Fel: a = robot1 == 0 || tableStatus[robot1-1][robot2]==Wall; x = -1;break;
    case Le: a = robot1 == gameSize -1 || tableStatus[robot1+1][robot2]==Wall; x = 1;break;
    }
    if(a)hitWall(robot1+x,robot2+y);
    return a;
}

bool GameManager::stuck()
{
    bool a = true;
    for(int i = 0; i < gameSize;++i){
        a = a && tableStatus[i][0]==Destroyed && tableStatus[0][i] == Destroyed && tableStatus[i][gameSize-1]==Destroyed && tableStatus[gameSize-1][i] == Destroyed;
    }
    a = a && (robot1 == 0 || robot1 == gameSize-1) && (robot2 == 0 || robot2 == gameSize-1);
    return a;
}

void GameManager::timerTimeout()
{
    gameTime++;
    if(robot1==(gameSize/2) && robot2==(gameSize/2)){
        _timer->stop();
        emit gameOver(gameTime/60, gameTime%60, true);
    }
    else if(stuck()){
        _timer->stop();
        emit gameOver(gameTime/60, gameTime%60, false);
    }
    else{
        messageChanged(trUtf8("Eltelt idő: ") + QString::number(gameTime / 60) + ":" + QString::number(gameTime % 60));

        while(test())
        {
            changeDir();
        }

        switch(RobotDirection){
        case Fel:robot1-=1;break;
        case Le:robot1+=1;break;
        case Bal:robot2-=1;break;
        case Jobb:robot2+=1;break;
        }

        for(int i = 0; i<gameSize;++i){
            for(int j = 0; j<gameSize;++j){
                if(tableStatus[i][j]==Clean){
                    emit buttonCTRL(i,j,true);
                    emit imageChange(i,j,3);
                }
                if(tableStatus[i][j]==Destroyed){
                    emit imageChange(i,j,2);
                }
            }
        }
        emit imageChange(robot1, robot2, 0);
        emit buttonCTRL(robot1,robot2,false);
    }
}
