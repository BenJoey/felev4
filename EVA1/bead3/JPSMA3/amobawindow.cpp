#include "amobawindow.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QApplication>

AmobaWindow::AmobaWindow(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(500, 150);
    setFixedSize(500,150);
    setWindowTitle(tr("Potyogós Amőba"));

    _loadwidget = NULL;
    _savewidget = NULL;

    _smallGame = new QPushButton(tr("Kis Pálya (8x5)"));
    connect(_smallGame, SIGNAL(clicked()), this, SLOT(newGamePushed()));
    _mediumGame = new QPushButton(tr("Közepes Pálya (10x6)"));
    connect(_mediumGame, SIGNAL(clicked()), this, SLOT(newGamePushed()));
    _bigGame = new QPushButton(tr("Nagy Pálya (12x7)"));
    connect(_bigGame, SIGNAL(clicked()), this, SLOT(newGamePushed()));

    connect(&_model, SIGNAL(updateText()), this, SLOT(update()));
    connect(&_model, SIGNAL(gameOver(AmobaModell::Player)), this, SLOT(model_GameOver(AmobaModell::Player)));
    connect(&_model, SIGNAL(newSize(int,int)), this, SLOT(modifySize(int,int)));
    connect(&_model, SIGNAL(restart()), this, SLOT(rebuild()));

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(_smallGame);
    hLayout->addWidget(_mediumGame);
    hLayout->addWidget(_bigGame);

    buttonline = new QHBoxLayout();
    buttonline->setSpacing(0);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(hLayout);
    mainLayout->addLayout(buttonline);
    tableLO = new QGridLayout();
    tableLO->setSpacing(0);
    mainLayout->addLayout(tableLO);

    setLayout(mainLayout);
}

void AmobaWindow::newGamePushed()
{
    if (QObject::sender() == _smallGame){modifySize(8,5);}
    if (QObject::sender() == _mediumGame){modifySize(10,6);}
    if (QObject::sender() == _bigGame){modifySize(12,7);}
    _model.newGame(gameWidth,gameHeight);
}

void AmobaWindow::rebuild()
{
    setMinimumSize(gameWidth*80, (gameHeight+2)*80);
    setFixedSize(gameWidth*80,(gameHeight+2)*80);
    for(int i=0;i<gameButtons.size();++i){
            delete gameButtons[i];
    }    
    for(int i=0;i<gameTable.size();++i){
        for(int j=0;j<gameTable[i].size();++j){
            delete gameTable[i][j];
        }
    }
    gameButtons.resize(gameWidth);
    gameTable.resize(gameHeight);
    for(int i = 0;i<gameWidth;++i){
        gameButtons[i] = new QPushButton();
        gameButtons[i]->setFixedSize(80,80);
        connect(gameButtons[i],SIGNAL(clicked()),this ,SLOT(buttonClick()));
        buttonline->addWidget(gameButtons[i]);
    }
    for(int i = 0;i<gameHeight;++i){
        gameTable[i].resize(gameWidth);
        for(int j = 0;j<gameWidth;++j){
            gameTable[i][j] = new QLabel();
            gameTable[i][j]->setAlignment(Qt::AlignCenter);
            gameTable[i][j]->setFixedSize(80,80);
            tableLO->addWidget(gameTable[i][j],i,j);
        }
    }
    update();
}

void AmobaWindow::modifySize(int i, int j){gameWidth=i;gameHeight=j;}

void AmobaWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_L && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        if (_loadwidget == NULL)
        {
            _loadwidget = new loadgamewidget();
            connect(_loadwidget, SIGNAL(accepted()), this, SLOT(loadGame()));
        }
        _loadwidget->setGameList(_model.saveGameList());
        _loadwidget->open();
    }
    if (event->key() == Qt::Key_S && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        if (_savewidget == NULL)
        {
            _savewidget = new savegamewidget();
            connect(_savewidget, SIGNAL(accepted()), this, SLOT(saveGame()));
        }
        _savewidget->setGameList(_model.saveGameList());
        _savewidget->open();
    }
}

void AmobaWindow::buttonClick()
{
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender());
    int location = buttonline->indexOf(senderButton);
    _model.step(location);
}

void AmobaWindow::update()
{
    QString def = "border: 2px solid black; font-weight: bold; font-size: 35px;";
    QString circ = "color: red";
    QString mark = "color: black";
    for(int i = 0;i<gameHeight;i++){
        for(int j = 0;j<gameWidth;j++){
            switch (_model.getPlayer(i,j)) {
            case AmobaModell::PlayerO:gameTable[i][j]->setText("O");gameTable[i][j]->setStyleSheet(def+circ); break;
            case AmobaModell::PlayerX:gameTable[i][j]->setText("X");gameTable[i][j]->setStyleSheet(def+mark); break;
            case AmobaModell::NoPlayer:gameTable[i][j]->setText("");gameTable[i][j]->setStyleSheet(def); break;
            }
        }
    }
}

void AmobaWindow::model_GameOver(AmobaModell::Player won)
{
    QString msg;
    switch (won)
    {
    case AmobaModell::PlayerX:msg="Az X nyerte a játékot!"; break;
    case AmobaModell::PlayerO:msg="A O nyerte a játékot!"; break;
    case AmobaModell::NoPlayer:msg="A játék döntetlen lett!"; break;
    }
    QMessageBox::information(this, tr("Potyogós Amőba"), tr("Játék vége! ")+msg);
    _model.newGame(gameWidth,gameHeight);
    update();
}

AmobaWindow::~AmobaWindow()
{
    if (_loadwidget != NULL) delete _loadwidget;
    if (_savewidget != NULL) delete _savewidget;
}

void AmobaWindow::loadGame()
{
    if (_model.loadGame(_loadwidget->selectedGame()))
    {
        update();
        QMessageBox::information(this, tr("Potyogós Amőba"), tr("Játék betöltve, következik: ") + ((_model.CurrentPlayer() == AmobaModell::PlayerX) ? "X" : "O") + "!");
    }
    else
    {
        QMessageBox::warning(this, tr("Potyogós Amőba"), tr("A játék betöltése sikertelen!"));
    }
}

void AmobaWindow::saveGame()
{
    if (_model.saveGame(_savewidget->selectedGame()))
    {
        update();
        QMessageBox::information(this, tr("Potyogós Amőba"), tr("Játék sikeresen mentve!"));
    }
    else
    {
        QMessageBox::warning(this, tr("Potyogós Amőba"), tr("A játék mentése sikertelen!"));
    }
}
