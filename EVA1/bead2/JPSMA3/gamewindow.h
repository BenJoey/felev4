#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include "gamemanager.h"

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = 0);
    ~GameWindow();

private slots:
    void newGameBut();
    void buttonClick();
    void enableButton(int i, int j, bool valtozas);
    void GM_Image_Change(int i, int j, int imagenumber);
    void GM_GameOver(int minutes, int seconds, bool win);

private:
    int gameSize;
    GameManager* _GManager;
    QPushButton* _smallGameButton;
    QPushButton* _middleGameButton;
    QPushButton* _largeGameButton;
    QPushButton* _pauseButton;
    QLabel* _messageLabel;
    QGridLayout* tableLO;
    QVector<QVector<QPushButton*>> gameButtons;
};

#endif // GAMEWINDOW_H
