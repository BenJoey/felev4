#include "gamewindow.h"
#include <QMessageBox>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(800,800);
    setWindowTitle(trUtf8("Elszabadult Robot"));

    _GManager = new GameManager;
    connect(_GManager, SIGNAL(gameOver(int, int, bool)), this, SLOT(GM_GameOver(int,int,bool)));
    connect(_GManager, SIGNAL(imageChange(int,int,int)), this, SLOT(GM_Image_Change(int,int,int)));
    connect(_GManager, SIGNAL(buttonCTRL(int,int,bool)), this, SLOT(enableButton(int,int,bool)));

    _smallGameButton = new QPushButton(trUtf8("Könnyű játék (7x7)"));
    connect(_smallGameButton, SIGNAL(clicked()), this, SLOT(newGameBut()));
    _middleGameButton = new QPushButton(trUtf8("Közepes játék (11x11)"));
    connect(_middleGameButton, SIGNAL(clicked()), this, SLOT(newGameBut()));
    _largeGameButton = new QPushButton(trUtf8("Nehéz játék (15x15)"));
    connect(_largeGameButton, SIGNAL(clicked()), this, SLOT(newGameBut()));

    _pauseButton = new QPushButton(trUtf8("Szünet/folytatás"));
    _pauseButton->setEnabled(false);
    connect(_pauseButton, SIGNAL(clicked()), _GManager, SLOT(pauseGame()));

    _messageLabel = new QLabel(trUtf8("Játék kezdéséhez válassz nehézséget!"));
    connect(_GManager, SIGNAL(messageChanged(QString)), _messageLabel, SLOT(setText(QString)));

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(_smallGameButton);
    hLayout->addWidget(_middleGameButton);
    hLayout->addWidget(_largeGameButton);
    hLayout->addWidget(_pauseButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    tableLO = new QGridLayout();
    tableLO->setSpacing(0);
    mainLayout->addLayout(hLayout);
    mainLayout->addWidget(_messageLabel, 0, Qt::AlignHCenter);
    mainLayout->addLayout(tableLO);

    setLayout(mainLayout);
}

void GameWindow::newGameBut()
{
    for(int i=0;i<gameButtons.size();++i){
        for(int j=0;j<gameButtons[i].size();++j){
            delete gameButtons[i][j];
        }
    }

    if (QObject::sender() == _smallGameButton) gameSize=7;
    if (QObject::sender() == _middleGameButton) gameSize=11;
    if (QObject::sender() == _largeGameButton) gameSize=15;
    gameButtons.resize(gameSize);
    _pauseButton->setEnabled(true);

    for(int i = 0; i < gameSize; ++i){
        gameButtons[i].resize(gameSize);
        for(int j = 0;j < gameSize; ++j){
            gameButtons[i][j] = new QPushButton();
            gameButtons[i][j]->setFixedSize(800 / gameSize, 800 / gameSize);
            gameButtons[i][j]->setIconSize(QSize(800 / gameSize, 800 / gameSize));
            connect(gameButtons[i][j], SIGNAL(clicked()), this, SLOT(buttonClick()));
            tableLO->addWidget(gameButtons[i][j], i, j);
        }
    }
    _GManager->newGame(gameSize);
}

void GameWindow::GM_GameOver(int minutes, int seconds, bool win)
{
    if(win){
        QMessageBox::information(this, ("Gratulálok"), ("Elkaptad a robotot " + QString::number(minutes) + " perc és " + QString::number(seconds) + " másodperc alatt"));
    }
    else{
        QMessageBox::information(this, ("Vesztettél"), ("A robotot már nem lehet elkapni."));
    }
}

void GameWindow::enableButton(int i, int j, bool valtozas)
{
    gameButtons[i][j]->setEnabled(valtozas);
}

void GameWindow::GM_Image_Change(int i, int j, int imagenumber)
{
    gameButtons[i][j]->setIcon(_GManager->getImage(imagenumber));
}

void GameWindow::buttonClick()
{
    if(!_GManager->canPlay()) return;
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender());
    senderButton->setEnabled(false);
    int location = tableLO->indexOf(senderButton);
    _GManager->click(location / gameSize, location % gameSize);
}

GameWindow::~GameWindow()
{
    delete _GManager;
}
