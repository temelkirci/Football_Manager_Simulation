#include "Tactic.h"
#include <vector>
#include <random>
#include <iostream>
#include <QDebug>

Tactic::Tactic()
{
    mGameStyle = GameStyle::normal;
    mFormation = Formation::m4_2_3_1;
    mAttackPosition = AttackPosition::middle;
    mTackling = Tackling::normal;
    mLongShots = LongShots::sometimes;

    mAttackChance = 0;
    mFaulChance = 0;
    mLongShotChance = 0;
}

void Tactic::createTactics()
{
    mGameStyle = createGameStyle();
    mFormation = createFormation();
    mAttackPosition = createAttackPosition();
    mTackling = createTackling();
    mLongShots = createLongShots();

    if(mGameStyle == GameStyle::moreDefensive)
    {
        mAttackChance = 10;
    }
    if(mGameStyle == GameStyle::defensive)
    {
        mAttackChance = 25;
    }
    if(mGameStyle == GameStyle::normal)
    {
        mAttackChance = 50;
    }
    if(mGameStyle == GameStyle::attack)
    {
        mAttackChance = 70;
    }
    if(mGameStyle == GameStyle::moreAttack)
    {
        mAttackChance = 100;
    }



    if(mTackling == Tackling::soft)
    {
        mFaulChance = 10;
    }
    if(mTackling == Tackling::normal)
    {
        mFaulChance = 25;
    }
    if(mTackling == Tackling::hard)
    {
        mFaulChance = 50;
    }


    if(mLongShots == LongShots::rarely)
    {
        mLongShotChance = 10;
    }
    if(mLongShots == LongShots::sometimes)
    {
        mLongShotChance = 25;
    }
    if(mLongShots == LongShots::often)
    {
        mLongShotChance = 50;
    }
}

unsigned int Tactic::getAttackChance()
{
    return mAttackChance;
}

unsigned int Tactic::getLongShotChance()
{
    return mLongShotChance;
}

unsigned int Tactic::getFaulChance()
{
    return mFaulChance;
}


GameStyle Tactic::getGameStyle()
{
    return mGameStyle;
}

Formation Tactic::getFormation()
{
    return mFormation;
}

AttackPosition Tactic::getAttackPosition()
{
    return mAttackPosition;
}

Tackling Tactic::getTackling()
{
    return mTackling;
}

LongShots Tactic::getLongShots()
{
    return mLongShots;
}

int Tactic::generateRandomNumber(int lower, int upper)
{
   return (qrand() % (upper - lower + 1)) + lower;
}

GameStyle Tactic::createGameStyle()
{
    int tGameStyle = generateRandomNumber(0,5);
/*
    if(tGameStyle == 0)
        qDebug() << "Game Style = More Defensive" << endl;
    if(tGameStyle == 1)
        qDebug() << "Game Style = Defensive" << endl;
    if(tGameStyle == 2)
        qDebug() << "Game Style = Normal" << endl;
    if(tGameStyle == 3)
        qDebug() << "Game Style = Attack" << endl;
    if(tGameStyle == 4)
        qDebug() << "Game Style = More Attack" << endl;

*/
    return gameStyleVector[tGameStyle];
}

Formation Tactic::createFormation()
{
    int tGameStyle = generateRandomNumber(0,5);
/*
    if(tGameStyle == 0)
        qDebug() << "Formation = 4-3-3" << endl;
    if(tGameStyle == 1)
        qDebug() << "Formation = 4-2-2" << endl;
    if(tGameStyle == 2)
        qDebug() << "Formation = 3-4-2-1" << endl;
    if(tGameStyle == 3)
        qDebug() << "Formation = 4-2-3-1" << endl;
    if(tGameStyle == 4)
        qDebug() << "Formation = 4-2-1-2-1" << endl;
*/
    return formationVector[tGameStyle];
}

AttackPosition Tactic::createAttackPosition()
{
    int tGameStyle = generateRandomNumber(0,3);
/*
    if( tGameStyle == 0)
        qDebug() << "Attack Position = left" << endl;
    if( tGameStyle == 1)
        qDebug() << "Attack Position = right" << endl;
    if( tGameStyle == 2)
        qDebug() << "Attack Position = middle" << endl;
*/
    return AttackPositionVector[tGameStyle];
}

Tackling Tactic::createTackling()
{
    int tGameStyle = generateRandomNumber(0,3);
/*
    if(tGameStyle == 0)
        qDebug() << "Tackling = hard" << endl;
    if(tGameStyle == 1)
        qDebug() << "Tackling = soft" << endl;
    if(tGameStyle == 2)
        qDebug() << "Tackling = normal" << endl;
*/
    return TacklingVector[tGameStyle];
}

LongShots Tactic::createLongShots()
{
    int tGameStyle = generateRandomNumber(0,3);
/*
    if(tGameStyle == 0)
        qDebug() << "Long Shot = often" << endl << endl;
    if(tGameStyle == 1)
        qDebug() << "Long Shot = rarely"  << endl << endl;
    if(tGameStyle == 2)
        qDebug() << "Long Shot = sometimes" << endl << endl;
*/

    return LongShotsVector[tGameStyle];
}

