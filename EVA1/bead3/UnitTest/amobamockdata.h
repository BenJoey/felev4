#ifndef AMOBAMOCKDATA_H
#define AMOBAMOCKDATA_H

#include "amobadataaccess.h"

class AmobaMockData : public amobadataaccess
{
    bool isAvailable() const { return true; }
    QVector<QString> saveGameList() const
    {
        return QVector<QString>(5); // üres listát adunk vissza
    }
    bool loadGame(int gameIndex, QVector<int> &saveGameData)
    {
        saveGameData.resize(43);
        saveGameData[0]=8;saveGameData[1]=5; //a mock objektumban 8x5-ös pályát használunk
        saveGameData[2]=1;
        qDebug() << "game loaded to slot (" << gameIndex << ") with values: ";
        for (int i = 3; i < 43; i++)
        {
            qDebug() << saveGameData[i] << " ";
        }
        qDebug() << endl;
        return true;
    }
    bool saveGame(int gameIndex, const QVector<int> &saveGameData)
    {
        qDebug() << "game saved to slot (" << gameIndex << ") with values: ";
        for (int i = 3; i < 43; i++)
        {
            qDebug() << saveGameData[i] << " ";
        }
        qDebug() << endl;
        return true;
    }
};

#endif // AMOBAMOCKDATA_H
