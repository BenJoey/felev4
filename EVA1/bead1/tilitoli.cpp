#include "tilitoli.h"

TiliToli::TiliToli(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(400,400);
    setBaseSize(400,400);
    setWindowTitle(tr("Tili-Toli játék"));
    mainLO = new QVBoxLayout();
    newGameButton = new QPushButton(trUtf8("Új játék"));
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(newGameClicked()));
    mainLO->addWidget(newGameButton);
    newGame();
}

void TiliToli::newGameClicked(){
    newGame();
}

void TiliToli::buttonClick(){
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender());
    int location = tableLO->indexOf(senderButton);
    move(location / boardSize, location % boardSize);
}

void TiliToli::move(int koord1, int koord2){
    gameTable[null1][null2] = gameTable[koord1][koord2];
    gameTable[koord1][koord2] = 0;
    stepCount++;
    checkGame();
}

void TiliToli::newGame(){
    for (int i = 0; i < boardSize; ++i){
        for (int j = 0; j < boardSize; ++j)
        {
            delete buttonTable[i][j];
        }
    }
    stepCount = 0;

    tableLO = new QGridLayout();
    generateBoard();

    mainLO->addLayout(tableLO);
    setLayout(mainLO);
}

void TiliToli::generateBoard(){
    bool ok;
    qsrand(QTime::currentTime().msec());
    boardSize = QInputDialog::getInt(this, tr("A tábla mérete"), tr("n*n-es tábla, n="), 3, 2, 50, 1, &ok);
    gameTable.resize(boardSize);
    buttonTable.resize(boardSize);
    for(int i = 0; i < boardSize; ++i){
        buttonTable[i].resize(boardSize);
        gameTable[i].resize(0);
        for (int j = 0; j < boardSize; ++j){
            int seged = qrand() % (boardSize*boardSize);
            while(ellenor(seged, i)){
                seged = qrand() % (boardSize*boardSize);
            }
            gameTable[i].push_back(seged);
            buttonTable[i][j]= new QPushButton(this);
            buttonTable[i][j]->setFont(QFont("Times New Roman", 20, QFont::Bold));
            buttonTable[i][j]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            tableLO->addWidget(buttonTable[i][j], i, j);

            connect(buttonTable[i][j], SIGNAL(clicked()), this, SLOT(buttonClick()));
        }
    }
    checkGame();
}

bool TiliToli::ellenor(int vizsgalt, int tav){
    for(int i = 0; i <= tav; ++i){
        if(gameTable[i].contains(vizsgalt)) return true;
    }
    return false;
}

void TiliToli::checkGame(){
    int won = boardSize*boardSize;
    for(int i = 0; i < boardSize; ++i){
        for(int j = 0; j < boardSize; ++j){
            if(gameTable[i][j]==i*boardSize+j+1)won-=1;
            if(gameTable[i][j]!=0){buttonTable[i][j]->setText(QString::number(gameTable[i][j]));}
            else{null1=i;null2=j;buttonTable[i][j]->setText(" ");}
            buttonTable[i][j]->setEnabled(false);
        }
    }
    if(won!=1){
        enableButtons();
    }
    else{
        QMessageBox::information(this, trUtf8("Játék vége!"), ("Megoldottad " + QString::number(stepCount) + " lépésből"));
        newGame();
    }
}

void TiliToli::enableButtons(){
    if(null1 != boardSize-1)buttonTable[null1+1][null2]->setEnabled(true);
    if(null1 != 0)buttonTable[null1-1][null2]->setEnabled(true);
    if(null2 != boardSize-1)buttonTable[null1][null2+1]->setEnabled(true);
    if(null2 != 0)buttonTable[null1][null2-1]->setEnabled(true);
}
