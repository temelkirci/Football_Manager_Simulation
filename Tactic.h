#ifndef TACTIC_H
#define TACTIC_H

#include <qstring.h>
#include <vector>

enum class GameStyle
{
    moreDefensive, // defense = %90   ,  attack = %10
    defensive, // defense = 75   ,  attack = 25
    normal, // defense = 50   ,   attack = 50
    attack,  // defense = 25   ,   attack = 75
    moreAttack //  defense = 10     ,    attack = %90
};

enum class Formation
{
    m4_4_2,
    m4_2_3_1,
    m4_3_3,
    m4_2_1_2_1,
    m3_4_2_1
};

enum class AttackPosition
{
    left,
    middle,
    right
};

enum class Tackling
{
    soft, // faul = %10
    normal, // faul = %30
    hard  // faul = %50
};

enum class LongShots
{
    rarely,  // longshot = %10
    sometimes, // longshot = %25
    often // longshot = %50
};

class Tactic
{
public:
    Tactic();

    void createTactics();

    void setGameStyle(GameStyle);
    void setFormation(Formation);
    void setAttackPosition(AttackPosition);
    void setTackling(Tackling);

    int generateRandomNumber(int, int);

    unsigned int getAttackChance();
    unsigned int getFaulChance();
    unsigned int getLongShotChance();

    GameStyle getGameStyle();
    Formation getFormation();
    AttackPosition getAttackPosition();
    Tackling getTackling();
    LongShots getLongShots();

private:
    GameStyle createGameStyle();
    Formation createFormation();
    AttackPosition createAttackPosition();
    Tackling createTackling();
    LongShots createLongShots();

private:
    std::vector<GameStyle> gameStyleVector { GameStyle::moreDefensive, GameStyle::defensive, GameStyle::normal, GameStyle::attack, GameStyle::moreAttack };
    std::vector<Formation> formationVector { Formation::m4_3_3, Formation::m4_4_2, Formation::m3_4_2_1, Formation::m4_2_3_1, Formation::m4_2_1_2_1 };
    std::vector<AttackPosition> AttackPositionVector { AttackPosition::left, AttackPosition::right, AttackPosition::middle };
    std::vector<Tackling> TacklingVector { Tackling::hard, Tackling::soft, Tackling::normal };
    std::vector<LongShots> LongShotsVector { LongShots::often, LongShots::rarely, LongShots::sometimes };

    GameStyle mGameStyle;
    Formation mFormation;
    AttackPosition mAttackPosition;
    Tackling mTackling;
    LongShots mLongShots;

    unsigned int mAttackChance;
    unsigned int mFaulChance;
    unsigned int mLongShotChance;
};

#endif // TACTIC_H
