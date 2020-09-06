#include "MatchEngine.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMutex>
#include <QTimer>

MatchEngine::MatchEngine(Ui::MainWindow* tUI)
{
    mpMatchEngine = tUI;
    mMatch = nullptr;
    mpBallPlayer = nullptr;

    mMatchSpeed = 1000;

    mTimer = new QTimer();
    connect(mTimer, SIGNAL(timeout()), this, SLOT(count()));

    mEventTimer = new QTimer();
    connect(mEventTimer, SIGNAL(timeout()), this, SLOT(eventTime()));
}

unsigned int MatchEngine::generateRandomNumber(int lower, int upper)
{
   return (qrand() % (upper - lower + 1)) + lower;
}

void MatchEngine::writeMatchEvent(QString tEvent)
{
    mpMatchEngine->match_events->setText(tEvent);

    if(tEvent == "Goal Kick")
    {
        mEventTimer->stop();
        mTimer->start(mMatchSpeed);
    }
    if(tEvent == "Goal")
    {
        mEventTimer->stop();
        mTimer->start(mMatchSpeed);
    }
    if(tEvent == "Saved by goalkeeper")
    {
        mEventTimer->stop();
        mTimer->start(mMatchSpeed);
    }
}

void MatchEngine::eventTime()
{
    int temp = generateRandomNumber(0,5);

    if(temp == 0)
        writeMatchEvent("Shoot");
    if(temp == 1)
        writeMatchEvent("Goal");
    if(temp == 2)
        writeMatchEvent("Saved by goalkeeper");
    if(temp == 3)
        writeMatchEvent("Corner");
    if(temp == 4)
        writeMatchEvent("Goal Kick");

}

void MatchEngine::count()
{
    mMatch->mTime = mMatch->mTime + generateRandomNumber(0,10);

    if( mMatch->mTime <= 90 )
    {
        mpMatchEngine->match_time->setText(QString::number(mMatch->mTime));

        if(generateRandomNumber(0,100) < mMatch->mHomeAttack)
        {
            writeMatchEvent(mMatch->getHomeClub()->getClubName() + " Attack started");
            getAttackStart(mMatch->getHomeClub());

        }
        else
        {
            writeMatchEvent(mMatch->getAwayClub()->getClubName() + " Attack started");
            getAttackStart(mMatch->getAwayClub());
        }

        mTimer->stop();
        mEventTimer->start(mMatchSpeed);
    }
    else
    {
        writeMatchEvent("Match finished");
        mpMatchEngine->match_time->setText("90+" + QString::number(mMatch->mTime-90));

        mpMatchEngine->hometeam_goal->setText(QString::number(mMatch->getScoreForHomeClub()));
        mpMatchEngine->awayteam_goal->setText(QString::number(mMatch->getScoreForAwayClub()));

        mTimer->stop();
    }
}

std::shared_ptr< Player > MatchEngine::getAttackStart(std::shared_ptr< Club > tAttackClub)
{
    unsigned int firstRegion = 0;
    unsigned int secondRegion = 0;
    unsigned int thirdRegion = 0;

    mpBallPlayer = nullptr;

    if(tAttackClub->getClubManager()->getManagerGameStyle() == "More Defensive")
    {
        firstRegion = 50;
        secondRegion = 70;
        thirdRegion = 90;
    }
    if(tAttackClub->getClubManager()->getManagerGameStyle() == "Defensive")
    {
        firstRegion = 40;
        secondRegion = 60;
        thirdRegion = 80;
    }
    if(tAttackClub->getClubManager()->getManagerGameStyle() == "Normal")
    {
        firstRegion = 30;
        secondRegion = 50;
        thirdRegion = 70;
    }
    if(tAttackClub->getClubManager()->getManagerGameStyle() == "Attack")
    {
        firstRegion = 20;
        secondRegion = 40;
        thirdRegion = 60;
    }
    if(tAttackClub->getClubManager()->getManagerGameStyle() == "More Attack")
    {
        firstRegion = 10;
        secondRegion = 30;
        thirdRegion = 50;
    }

    unsigned int tAttack = generateRandomNumber( 0,100 );

    if( tAttack < firstRegion )
    {
        for( size_t x=0; x < tAttackClub->getMatchPlayers().size(); x++ )
        {
            if(tAttackClub->getClubManager()->getAttackPosition() == "Left")
            {
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "DL")
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
            }
            if(tAttackClub->getClubManager()->getAttackPosition() == "Middle")
            {
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "DC")
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
            }
            if(tAttackClub->getClubManager()->getAttackPosition() == "Right")
            {
                if(tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "DR")
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
            }
        }

    }

    if( tAttack >= firstRegion && tAttack < secondRegion )
    {
        for( size_t x=0; tAttackClub->getMatchPlayers().size(); x++ )
        {
            if( tAttackClub->getClubManager()->getAttackPosition() == "Left" )
            {
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "WBL" )
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "DL" )
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
            }
            if( tAttackClub->getClubManager()->getAttackPosition() == "Middle" )
            {
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "DMC" )
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
                if(tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "DC")
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
            }
            if(tAttackClub->getClubManager()->getAttackPosition() == "Right")
            {
                if(tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "WBR")
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
                if(tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "DR")
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
            }
        }
    }
    else if( tAttack >= secondRegion  && tAttack<= thirdRegion )
    {
        for( size_t x=0; x < tAttackClub->getMatchPlayers().size(); x++ )
        {
            if( tAttackClub->getClubManager()->getAttackPosition() == "Left" )
            {
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "ML" )
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "WBL" )
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
            }
            if( tAttackClub->getClubManager()->getAttackPosition() == "Middle" )
            {
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "MC" )
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "DMC" )
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
            }
            if( tAttackClub->getClubManager()->getAttackPosition() == "Right" )
            {
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "MR" )
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "WBR" )
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
            }
        }
    }
    else
    {
        for( size_t x=0; x < tAttackClub->getMatchPlayers().size(); x++ )
        {
            if( tAttackClub->getClubManager()->getAttackPosition() == "Left" )
            {
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "AML" )
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "ML" )
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
            }
            if( tAttackClub->getClubManager()->getAttackPosition() == "Middle" )
            {
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "AMC" )
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "MC" )
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
            }
            if( tAttackClub->getClubManager()->getAttackPosition() == "Right" )
            {
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "AMR" )
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
                if( tAttackClub->getMatchPlayers()[x]->getPlayerPosition() == "MR" )
                {
                    mpBallPlayer = ( tAttackClub->getMatchPlayers()[x] );
                    break;
                }
            }
        }
    }

    if(mpBallPlayer != nullptr)
        writeMatchEvent(mpBallPlayer->getPlayerName() + " topu sürüyor");
    else
        writeMatchEvent("Hücum başlamadan bitiyor");

    return ( mpBallPlayer );
}

void MatchEngine::startMatch(std::shared_ptr< Match > tMatch)
{
    mpMatchEngine->match_time->setText(QString::number(tMatch->mTime));

    mpMatchEngine->hometeam->setText(tMatch->getHomeClub()->getClubName());
    mpMatchEngine->awayteam->setText(tMatch->getAwayClub()->getClubName());

    writeMatchEvent(tMatch->getHomeClub()->getClubName() + " Maça başladı");

    mMatch = (tMatch);
    mMatch->mHomeAttackChance = 0;
    mMatch->mAwayAttackChance = 0;

    mMatch->mHomeAttack = 0;
    mMatch->mAwayAttack = 0;


    int mHomeManagerGameStyleAttackChance = mMatch->getHomeClub()->getClubManager()->getTactics()->getAttackChance();
    int mAwayManagerGameStyleAttackChance = mMatch->getAwayClub()->getClubManager()->getTactics()->getAttackChance();

    int tHomeManagerAffect =  mMatch->getHomeClub()->getClubManager()->getMotivation() + mMatch->getHomeClub()->getClubManager()->getClubManagement();
    int tAwayManagerAffect =  mMatch->getAwayClub()->getClubManager()->getMotivation() + mMatch->getAwayClub()->getClubManager()->getClubManagement();


    qDebug() << "mHomeManagerGameStyleAttackChance : " << mHomeManagerGameStyleAttackChance << endl;
    qDebug() << "mAwayManagerGameStyleAttackChance : " << mAwayManagerGameStyleAttackChance << endl;

    qDebug() << "tHomeManagerAffect : " << tHomeManagerAffect << endl;
    qDebug() << "tAwayManagerAffect : " << tAwayManagerAffect << endl;

    for(size_t x=0; x < mMatch->getHomeClub()->getMatchPlayers().size(); x++ )
    {
        if( mMatch->getHomeClub()->getMatchPlayers()[x]->getPlayerPosition() != "GK")
            mMatch->mHomeAttackChance = mMatch->mHomeAttackChance + mMatch->getHomeClub()->getMatchPlayers()[x]->getPlayerCA() + mMatch->getHomeClub()->getMatchPlayers()[x]->getPlayerForm() + mHomeManagerGameStyleAttackChance + tHomeManagerAffect;
    }


    for(size_t x=0; x < mMatch->getAwayClub()->getMatchPlayers().size(); x++ )
    {
        if(mMatch->getHomeClub()->getMatchPlayers()[x]->getPlayerPosition() != "GK")
            mMatch->mAwayAttackChance = mMatch->mAwayAttackChance + (mMatch->getHomeClub()->getMatchPlayers()[x]->getPlayerCA() + mMatch->getHomeClub()->getMatchPlayers()[x]->getPlayerForm() + mAwayManagerGameStyleAttackChance + tAwayManagerAffect);
    }

    mMatch->mAwayAttackChance = (mMatch->mAwayAttackChance*90)/100;

    unsigned int divide = (mMatch->mHomeAttackChance + mMatch->mAwayAttackChance) / 100;
    mMatch->mHomeAttack = (mMatch->mHomeAttackChance / divide);
    mMatch->mAwayAttack = 100 - mMatch->mHomeAttack;

    qDebug() << mMatch->getHomeClub()->getClubName() + " attack chance is = % " << mMatch->mHomeAttack << endl;
    qDebug() << mMatch->getAwayClub()->getClubName() + " attack chance is = % " << mMatch->mAwayAttack << endl;


    QMutex mutex;
    // prevent other threads from changing the "Stop" value
    mutex.lock();

    mTimer->start(mMatchSpeed);

    mutex.unlock();
}

void MatchEngine::run()
{
    qDebug() << "Hello world from MatchEngine thread" <<  QThread::currentThread() << endl;
}
