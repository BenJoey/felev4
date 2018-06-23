#ifndef AMOBAWINDOW_H
#define AMOBAWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QWidget>
#include "amobamodell.h"
#include "loadgamewidget.h"
#include "savegamewidget.h"

class AmobaWindow : public QWidget
{
    Q_OBJECT

public:
    AmobaWindow(QWidget *parent = 0);
    ~AmobaWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void newGamePushed();
    void buttonClick();
    void update();
    void modifySize(int i, int j);
    void model_GameOver(AmobaModell::Player won);
    void loadGame();
    void saveGame();
    void rebuild();

private:
    int gameWidth, gameHeight;
    QPushButton* _smallGame;
    QPushButton* _mediumGame;
    QPushButton* _bigGame;
    QHBoxLayout* buttonline;
    QGridLayout* tableLO;
    QVector<QPushButton*> gameButtons;
    QVector<QVector<QLabel*> > gameTable;
    savegamewidget* _savewidget;
    loadgamewidget* _loadwidget;
    AmobaModell _model;
};

#endif // AMOBAWINDOW_H
