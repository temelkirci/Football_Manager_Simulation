#include "Manager.h"
#include <QDebug>
#include <iostream>

int generateRandomNumber(int lower, int upper)
{
   return (qrand() % (upper - lower + 1)) + lower;
}


Manager::Manager(QString ManagerFullName,
                 QString ManagerNationality,
                 QString ManagerCurrentClub)
{
    mManagerFullName = ManagerFullName;
    mManagerNationality = ManagerNationality;
    mManagerCurrentClub = ManagerCurrentClub;


    int tDay = generateRandomNumber(0, 30);

    int tMonth = generateRandomNumber(0, 12);

    int tYear = generateRandomNumber(1950, 1980);

    mManagerBirthDate.setDate(tYear, tMonth, tDay);

    mpTactic = nullptr;

    qDebug() << "Manager Current Club :" << mManagerCurrentClub << endl;
    qDebug() << "Manager BirthDate :" << mManagerBirthDate.toString() << endl;


    setTactics();
}

void Manager::setManagerAttributes( int Motivation,  int ClubManagement,  int Training)
{
    mMotivation = Motivation;
    mClubManagement = ClubManagement;
    mTraining = Training;

    qDebug() << "Manager Motivation :" << Motivation << endl;
    qDebug() << "Manager ClubManagement :" << ClubManagement << endl;
    qDebug() << "Manager Training :" << Training << endl << endl;
}

int Manager::getClubManagement()
{
    return mClubManagement;
}

int Manager::getMotivation()
{
    return mMotivation;
}

int Manager::getTraining()
{
    return mTraining;
}

std::shared_ptr< Tactic > Manager::getTactics()
{
    return (mpTactic);
}

void Manager::setTactics()
{
    std::shared_ptr< Tactic > tTactic = std::shared_ptr< Tactic > (new Tactic());
    tTactic->createTactics();

    mpTactic = (tTactic);
}

void Manager::FiredByClub()
{
    mManagerCurrentClub = "";
}

void Manager::SignClub(QString newClub)
{
    mManagerCurrentClub = newClub;

}

QString Manager::getManagerGameStyle()
{
    QString tGameStyle = "Normal";

    if(mpTactic->getGameStyle() == GameStyle::moreDefensive)
        tGameStyle = "More Defensive";
    if(mpTactic->getGameStyle() == GameStyle::defensive)
        tGameStyle = "Defensive";
    if(mpTactic->getGameStyle() == GameStyle::normal)
        tGameStyle = "Normal";
    if(mpTactic->getGameStyle() == GameStyle::attack)
        tGameStyle = "Attack";
    if(mpTactic->getGameStyle() == GameStyle::moreAttack)
        tGameStyle = "More Attack";

    return tGameStyle;
}

QString Manager::getTackling()
{
    QString tTackling = "Normal";

    if(mpTactic->getTackling() == Tackling::soft)
        tTackling = "Soft";
    if(mpTactic->getTackling() == Tackling::normal)
        tTackling = "Normal";
    if(mpTactic->getTackling() == Tackling::hard)
        tTackling = "Hard";

    return tTackling;
}


QString Manager::getAttackPosition()
{
    QString tAttackPosition = "Middle";

    if(mpTactic->getAttackPosition() == AttackPosition::left)
        tAttackPosition = "Left";
    if(mpTactic->getAttackPosition() == AttackPosition::middle)
        tAttackPosition = "Middle";
    if(mpTactic->getAttackPosition() == AttackPosition::right)
        tAttackPosition = "Right";

    return tAttackPosition;
}

QString Manager::getLongShots()
{
    QString tLongShot = "Sometimes";

    if(mpTactic->getLongShots() == LongShots::often)
        tLongShot = "Often";
    if(mpTactic->getLongShots() == LongShots::sometimes)
        tLongShot = "Sometimes";
    if(mpTactic->getLongShots() == LongShots::rarely)
        tLongShot = "Rarely";

    return tLongShot;
}

QString Manager::getFormation()
{
    QString tFormation = "4-4-2";

    if(mpTactic->getFormation() == Formation::m4_3_3)
        tFormation = "4-3-3";
    if(mpTactic->getFormation() == Formation::m4_4_2)
        tFormation = "4-4-2";
    if(mpTactic->getFormation() == Formation::m3_4_2_1)
        tFormation = "3-4-2-1";
    if(mpTactic->getFormation() == Formation::m4_2_3_1)
        tFormation = "4-2-3-1";
    if(mpTactic->getFormation() == Formation::m4_2_1_2_1)
        tFormation = "4-2-1-2-1";

    return tFormation;
}

QString Manager::getManagerName()
{
    return mManagerFullName;
}
