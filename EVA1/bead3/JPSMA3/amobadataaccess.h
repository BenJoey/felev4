#ifndef AMOBADATAACCESS_H
#define AMOBADATAACCESS_H

#include <QVector>
#include <QString>

class amobadataaccess
{
public:
    explicit amobadataaccess() {}

    QVector<QString> saveGameList() const;

    bool loadGame(int gameIndex, QVector<int> &saveGameData);
    bool saveGame(int gameIndex, const QVector<int> &saveGameData);
};

#endif // AMOBADATAACCESS_H
