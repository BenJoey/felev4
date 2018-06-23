#include "loadgamewidget.h"
#include <QMessageBox>

loadgamewidget::loadgamewidget(QWidget *parent) :
    savegamewidget(parent)
{
    setWindowTitle("Potyogós Amőba - Játék betöltése");

    disconnect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_okButton, SIGNAL(clicked()), this, SLOT(okButton_Clicked()));
}

void loadgamewidget::okButton_Clicked()
{
    if (_listWidget->currentItem()->text() == "empty")
    {
        QMessageBox::warning(this, tr("Potyogós Amőba"), tr("Nincs játék kiválasztva!"));
        return;
    }

    accept();
}
