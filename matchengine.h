#ifndef MATCHENGINE_H
#define MATCHENGINE_H

#include <QMainWindow>
#include <QRunnable>
#include <QThread>
#include "Match.h"
#include <QObject>

namespace Ui {
class MainWindow;
}

class MatchEngine : public QObject
{
    Q_OBJECT
public:
    MatchEngine(Ui::MainWindow*);
    void startMatch(std::shared_ptr< Match >);
    unsigned int generateRandomNumber(int lower, int upper);
    void run();
    void writeMatchEvent(QString);
    std::shared_ptr< Player > getAttackStart(std::shared_ptr< Club > tAttackClub);

public slots:
    void count();
    void eventTime();

public:
    Ui::MainWindow *mpMatchEngine;
private:
    std::shared_ptr< Match > mMatch;
    QTimer* mTimer;
    QTimer* mEventTimer;
    unsigned int mMatchSpeed;
    std::shared_ptr< Player > mpBallPlayer;

};

#endif // MATCHENGINE_H
