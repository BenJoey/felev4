#include "amobamodell.h"

void AmobaModell::newGame(int n, int m)
{
    width = n; height = m;
    gameStatus.resize(m);
    for(int i = 0;i<m;++i){
        gameStatus[i].resize(n);
        for(int j = 0;j<n;++j){
            gameStatus[i][j] = NoPlayer;
        }
    }
    currentplayer = PlayerX;
    emit restart();
}

bool AmobaModell::loadGame(int index)
{
    QVector<int> saveData;

    if(!_dataaccess.loadGame(index,saveData)) return false;

    width=saveData[0]; height=saveData[1];
    emit newSize(width,height);
    currentplayer=(Player)saveData[2];
    gameStatus.resize(height);
    for(int i = 0; i<height;i++){
        gameStatus[i].resize(width);
        for(int j = 0;j<width;j++){
            gameStatus[i][j]=(Player)saveData[i*width+j+3];
        }
    }
    emit restart();
    return true;
}

bool AmobaModell::saveGame(int index)
{
    QVector<int> saveData;
    saveData.push_back(width);
    saveData.push_back(height);
    saveData.push_back((int)currentplayer);
    for(int i = 0; i<height;i++){
        for(int j = 0;j<width;j++){
            saveData.push_back((int)gameStatus[i][j]);
        }
    }
    return _dataaccess.saveGame(index, saveData);
}

AmobaModell::Player AmobaModell::getPlayer(int i, int j) const
{
    if(i<0 || i>height-1 || j<0 || j>width-1) return NoPlayer;
    return gameStatus[i][j];
}

void AmobaModell::step(int oszlop)
{
    if(getPlayer(0,oszlop)!=NoPlayer || oszlop<0 || oszlop>width-1)return;
    int sor;
    for(sor = 0;sor<(height-1);sor++)
    {
        if(gameStatus[sor+1][oszlop]!=NoPlayer)break;
    }
    gameStatus[sor][oszlop] = currentplayer;
    currentplayer = (Player)(currentplayer % 2 + 1);
    emit updateText();
    checkGame();
}

void AmobaModell::checkGame()
{
    bool tie = true;
    for(int i = 0; i < height; i++){
        for(int j = 0;j<width;j++){
            if(getPlayer(i,j)!=NoPlayer && getPlayer(i,j)==getPlayer(i,j+1) && getPlayer(i,j+2)==getPlayer(i,j+3) && getPlayer(i,j+1)==getPlayer(i,j+2)){
                emit gameOver(getPlayer(i,j));
            }
            if(getPlayer(i,j)!=NoPlayer && getPlayer(i,j) == getPlayer(i+1,j+1) && getPlayer(i+2,j+2) == getPlayer(i+3,j+3) && getPlayer(i,j) == getPlayer(i+2,j+2)){
                emit gameOver(getPlayer(i,j));
            }
            if(getPlayer(i,j)!=NoPlayer && getPlayer(i,j) == getPlayer(i+1,j-1) && getPlayer(i+2,j-2) == getPlayer(i+3,j-3) && getPlayer(i,j) == getPlayer(i+2,j-2)){
                emit gameOver(getPlayer(i,j));
            }
            tie = tie && getPlayer(i,j)!=NoPlayer; //ha a pályán nincs üres mező és egyik játékos se nyert akkor döntetlennel ér véget a játék
        }
    }
    if(tie) emit gameOver(NoPlayer);
}
