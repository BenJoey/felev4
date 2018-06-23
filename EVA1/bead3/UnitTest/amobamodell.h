#ifndef AMOBAMODELL_H
#define AMOBAMODELL_H

#include <QObject>
#include <QVector>
#include <QString>
#include "amobadataaccess.h"

class AmobaModell : public QObject
{
    Q_OBJECT
public:
    enum Player { NoPlayer, PlayerX, PlayerO };

    AmobaModell(amobadataaccess* _dataAcc);
    void newGame(int n, int m);
    void step(int oszlop);
    QVector<QString> saveGameList() const{return _dataaccess->saveGameList();}
    Player getPlayer(int i, int j) const;
    Player CurrentPlayer() const{return currentplayer;}
    bool loadGame(int index);
    bool saveGame(int index);

signals:
    void updateText();
    void restart();
    void gameOver(AmobaModell::Player won);
    void newSize(int i, int j);

private:
    void checkGame();
    int width, height;
    Player currentplayer;
    QVector<QVector<Player> > gameStatus;

    amobadataaccess* _dataaccess;
};

#endif // AMOBAMODELL_H
