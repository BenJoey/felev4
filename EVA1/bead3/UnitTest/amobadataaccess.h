#ifndef AMOBADATAACCESS_H
#define AMOBADATAACCESS_H

#include <QVector>
#include <QString>

class amobadataaccess
{
public:
    amobadataaccess() {}
    virtual ~amobadataaccess(){}

    virtual bool isAvailable() const { return false; }

    virtual QVector<QString> saveGameList() const = 0;

    virtual bool loadGame(int gameIndex, QVector<int> &saveGameData) = 0;
    virtual bool saveGame(int gameIndex, const QVector<int> &saveGameData) = 0;
};

#endif // AMOBADATAACCESS_H
