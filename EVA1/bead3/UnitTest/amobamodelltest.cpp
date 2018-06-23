#include <QString>
#include <QtTest>
#include <amobamodell.h>
#include <amobamockdata.h>

class AmobaTest : public QObject
{
    Q_OBJECT

private:
    AmobaModell* _model;
    amobadataaccess* _data;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testNewGame();
    void testStep();
    void testFullColumn();
    void testLoadGame();
    void testSaveGame();
};

void AmobaTest::initTestCase()
{
    _data = new AmobaMockData();
    _model = new AmobaModell(_data);
}

void AmobaTest::cleanupTestCase()
{
    delete _data;
    delete _model;
}

void AmobaTest::testNewGame()
{
    _model->newGame(8,5);
    QCOMPARE(_model->CurrentPlayer(),AmobaModell::PlayerX);
    for(int i = 0;i<5;i++){
        for(int j = 0;j<8;j++){
            QCOMPARE(_model->getPlayer(i,j),AmobaModell::NoPlayer); //minden mező üresre inicializálása
        }
    }
}

void AmobaTest::testStep()
{
    _model->newGame(8,5);
    _model->step(3); //egy lépés, valamint játékosváltása tesztelése

    QCOMPARE(_model->CurrentPlayer(),AmobaModell::PlayerO);
    QCOMPARE(_model->getPlayer(4,3),AmobaModell::PlayerX);
    for(int i = 0;i<5;i++){
        for(int j = 0;j<8;j++){
            QVERIFY((i==4 && j==3) || _model->getPlayer(i,j)==AmobaModell::NoPlayer); //többi mező ne változzon
        }
    }

    _model->step(4); //még egy lépés utána újra X jön
    QCOMPARE(_model->CurrentPlayer(),AmobaModell::PlayerX);
    QCOMPARE(_model->getPlayer(4,4),AmobaModell::PlayerO);

    //hibás lépés tesztelése
    _model->step(-2);
    QCOMPARE(_model->CurrentPlayer(),AmobaModell::PlayerX); //jelenlegi játkos nem változik
}

void AmobaTest::testFullColumn()
{
    _model->newGame(8,5);
    for(int i = 0;i<5;i++){
        _model->step(2); //feltöltjük az egyik oszlopot
    }
    //5 lépés történt azaz a következő játékos jelenleg O
    QCOMPARE(_model->CurrentPlayer(),AmobaModell::PlayerO);

    _model->step(2); //megpróbálunk mégegyszer elemet rakni bele
    //mivel tele van, nem lehet és nem változik a jelenlegi játékos
    QCOMPARE(_model->CurrentPlayer(),AmobaModell::PlayerO);
}

void AmobaTest::testLoadGame()
{
    _model->newGame(8,5);

    //egy lépés után a O-nek kell jönnie
    _model->step(2);
    QCOMPARE(_model->CurrentPlayer(),AmobaModell::PlayerO);

    QVERIFY(_model->loadGame(0)); //új játék betöltése
    QCOMPARE(_model->CurrentPlayer(),AmobaModell::PlayerX); //viszont itt már X-nek kell kezdenie
    for(int i = 0;i<5;i++){
        for(int j = 0;j<8;j++){
            QVERIFY(_model->getPlayer(i,j)==AmobaModell::NoPlayer); //megnézzük, hogy üres-e a teljes játékmező
        }
    }
}

void AmobaTest::testSaveGame()
{
    _model->newGame(8,5);

    //egy lépés után a O-nek kell jönnie
    _model->step(2);
    QCOMPARE(_model->CurrentPlayer(),AmobaModell::PlayerO);

    QVERIFY(_model->saveGame(0));
}

QTEST_APPLESS_MAIN(AmobaTest)

#include "amobamodelltest.moc"
