#include <QObject>
#include <QTest>

#include <QDebug>

class TestRegExp : public QObject
{
    Q_OBJECT

public:
    TestRegExp();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void mockTest();
    void mockTest_data();
};

TestRegExp::TestRegExp() {}

void TestRegExp::initTestCase()
{
    qDebug() << "initTestCase";
}
void TestRegExp::cleanupTestCase()
{
    qDebug() << "cleanupTestCase";
}

void TestRegExp::init()
{
    qDebug() << "init";
}
void TestRegExp::cleanup()
{
    qDebug() << "cleanup";
}

void TestRegExp::mockTest()
{
    QFETCH(QString, regexp);
    QFETCH(bool, expected);

    QVERIFY(expected);
}

void TestRegExp::mockTest_data()
{
    QTest::addColumn<QString>("regexp");
    QTest::addColumn<bool>("expected");

    QTest::addRow("regexp1") << "" << true;
    QTest::addRow("regexp2") << "" << true;
    QTest::addRow("regexp3") << "" << true;
    QTest::addRow("regexp4") << "" << true;
    QTest::addRow("regexp5") << "" << true;
}

QTEST_MAIN(TestRegExp)

#include "tst_regexp.moc"
