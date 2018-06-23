#ifndef LOADGAMEWIDGET_H
#define LOADGAMEWIDGET_H

#include "savegamewidget.h"

class loadgamewidget : public savegamewidget
{
    Q_OBJECT
public:
    explicit loadgamewidget(QWidget *parent = 0);

    protected slots:
        void okButton_Clicked();
};

#endif // LOADGAMEWIDGET_H
