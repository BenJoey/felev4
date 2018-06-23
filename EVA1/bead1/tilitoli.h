#ifndef TILITOLI_H
#define TILITOLI_H

#include <QWidget>
#include <QPushButton>
#include <QInputDialog>
#include <QGridLayout>
#include <QMessageBox>
#include <QTime>

class TiliToli : public QWidget
{
    Q_OBJECT

public:
    TiliToli(QWidget *parent = 0);

private slots:
    void newGameClicked();
    void buttonClick();
private:
    void newGame();
    void checkGame();
    void generateBoard();
    void move(int koord1, int koord2);
    void enableButtons();
    bool ellenor(int vizsgalt, int tav);

    int stepCount;
    int boardSize;
    int null1,null2;
    QGridLayout* tableLO;
    QVBoxLayout* mainLO;
    QPushButton* newGameButton;
    QVector<QVector<QPushButton*> > buttonTable;
    QVector<QVector<int> > gameTable;
};

#endif // TILITOLI_H
