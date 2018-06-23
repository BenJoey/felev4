#ifndef SAVEGAMEWIDGET_H
#define SAVEGAMEWIDGET_H

#include <QDialog>
#include <QPushButton>
#include <QListWidget>

class savegamewidget : public QDialog
{
    Q_OBJECT
public:
    explicit savegamewidget(QWidget *parent = 0);
        void setGameList(QVector<QString> saveGameList);
        int selectedGame() const { return _listWidget->currentRow(); }

    protected:
        QPushButton* _okButton;
        QPushButton* _cancelButton;
        QListWidget* _listWidget;
};

#endif // SAVEGAMEWIDGET_H
