#include "savegamewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

savegamewidget::savegamewidget(QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(300, 200);
    setWindowTitle("Potyogós Amőba - Játék mentése");

    _listWidget = new QListWidget();
    _okButton = new QPushButton("Ok");
    _cancelButton = new QPushButton("Mégse");

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(_okButton);
    hlayout->addWidget(_cancelButton);

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addWidget(_listWidget);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void savegamewidget::setGameList(QVector<QString> saveGameList)
{
    _listWidget->clear();

    for (int i = 0; i < 5; i++)
    {
        if (i < saveGameList.size() && !saveGameList[i].isEmpty())
            _listWidget->addItem(saveGameList[i]);
        else
            _listWidget->addItem("empty");
    }
}
