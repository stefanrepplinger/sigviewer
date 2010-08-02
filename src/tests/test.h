#ifndef TEST_H
#define TEST_H

#include "file_handling/event_manager.h"
#include "gui/application_context.h"

#include <QSharedPointer>
#include <QObject>
#include <QString>

namespace SigViewer_
{

namespace Tests_
{

#define VERIFY(condition, message) {if(!(condition)) return message; else increasePassedTests();}
#define RUN_SUB_TEST(subtest) {QString result = subtest; if (result.size()) return result;}

//-----------------------------------------------------------------------------
/// Test
/// base class for all tests
class Test : public QObject
{
    Q_OBJECT
public:
    Test (QString const& name) : name_ (name), passed_tests_(0) {}

    QString getName () {return name_;}
    unsigned passed () {return passed_tests_;}

    virtual void init () {};

    virtual QString run () = 0;

    virtual void cleanup () {};
protected:
    void increasePassedTests () {passed_tests_++;}

    //-------------------------------------------------------------------------
    QSharedPointer<EventManager> createEventManagerWithDummyData ();

    //-------------------------------------------------------------------------
    QSharedPointer<ApplicationContext> applicationContext ();

    //-------------------------------------------------------------------------
    QAction* action (QString const& action_name);

    //-------------------------------------------------------------------------
    QSharedPointer<SignalVisualisationModel> currentVisModel ();
private:
    QString name_;
    unsigned passed_tests_;
};

}

}

#endif // TEST_H
