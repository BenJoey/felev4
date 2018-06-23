#include <QString>
#include <QTest>
#include "gamemanager.h"

class GMUnitTest : public QObject
{
    Q_OBJECT

private:
    GameManager* _testManager;
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testNewGame();
    void testMakeWall();
    void testPause();
};

void GMUnitTest::initTestCase()
{
    _testManager = new GameManager();
}

void GMUnitTest::cleanupTestCase()
{
    delete _testManager;
}

void GMUnitTest::testNewGame()
{
    QVERIFY(!_testManager->canPlay());
    _testManager->newGame(7);
    QVERIFY(_testManager->canPlay());
}

void GMUnitTest::testMakeWall()
{
    _testManager->newGame(11);
    for(int i = 0; i < 11; ++i){
        for(int j = 0; j < 11; ++j){
            QCOMPARE(_testManager->allapot(i,j),Clean);
        }
    }
    _testManager->click(2,6);
    _testManager->click(4,1);
    QCOMPARE(_testManager->allapot(2,6),Wall);
    QCOMPARE(_testManager->allapot(4,1),Wall);
    _testManager->hitWall(2,6);
    _testManager->hitWall(4,1);
    QCOMPARE(_testManager->allapot(2,6),Destroyed);
    QCOMPARE(_testManager->allapot(4,1),Destroyed);
}

void GMUnitTest::testPause()
{
    _testManager->newGame(7);
    _testManager->pauseGame();
    QVERIFY(!_testManager->canPlay());
    _testManager->newGame(11);
    QVERIFY(_testManager->canPlay());
}

QTEST_APPLESS_MAIN(GMUnitTest)

#include "tst_gmunittest.moc"
