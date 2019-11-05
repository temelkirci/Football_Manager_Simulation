#include "player.h"
#include <iostream>

Player::Player(QString playerName, QString playerPosition, QString playerTeam, QString playerContractExpire, QString playerBirthDay, unsigned long long int playerValue, int playerWage, int playerForm)
{
    mPlayerName = playerName;
    mPlayerPosition = playerPosition;
    mPlayerTeamName = playerTeam;
    mPlayerContractExpire = playerContractExpire;

    mPlayerBirthDate = playerBirthDay;
    mPlayerWage = playerWage;
    mPlayerForm = playerForm;
    mPlayerValue = playerValue;
}

Player::~Player()
{

}

void Player::addContractOffers(Team* team, int salary)
{
    mContractOffers.insert(std::pair<Team*, int>(team, salary));
}

void Player::setPlayerPA(int PA)
{
    mPlayerPotentialAbility = PA;
}
int Player::getPlayerPA()
{
    return mPlayerPotentialAbility;
}

void Player::setPlayerCA(int CA)
{
    mPlayerCurrentAbility = CA;
}
int Player::getPlayerCA()
{
    return mPlayerCurrentAbility;
}

void Player::addTransferOffer(Team* team, unsigned long long int offer)
{
    mTransferOffers.erase(team);

    mTransferOffers[team] = offer;
}

std::map<Team*, unsigned long long int> Player::getTransferOffer()
{
    return mTransferOffers;
}

void Player::releasePlayer()
{
    mTransferList = false;
    mAskingPrice = 0;
    mPlayerWage = 0;
    mPlayerValue = 0;
    mPlayerContractExpire = "expired";
    mPlayerTeamName = "";
}

unsigned long long int Player::getAskingPrice()
{
    return mAskingPrice;
}

QString Player::getPlayerTeam()
{
    return mPlayerTeamName;
}
void Player::setTransferList(bool transfer)
{
    mTransferList = transfer;
}

bool Player::isTransferList()
{
    return mTransferList;
}

void Player::setAskingPrice(unsigned long long int askingPrice)
{
    mAskingPrice = askingPrice;
}

int Player::getPlayerReflexes()
{
    return mPlayerAttributes["Reflexes"];
}

int Player::getPlayerTackling()
{
    return mPlayerAttributes["Tackling"];
}

int Player::getPlayerPassing()
{
    return mPlayerAttributes["Passing"];
}

int Player::getPlayerPace()
{
    return mPlayerAttributes["Pace"];
}

int Player::getPlayerTechnique()
{
    return mPlayerAttributes["Technique"];
}

int Player::getPlayerFinishing()
{
    return mPlayerAttributes["Finishing"];
}

QString Player::getPlayerName()
{
    return mPlayerName;
}

int Player::getPlayerWage()
{
    return mPlayerWage;
}

unsigned long long int Player::getPlayerValue()
{
    return mPlayerValue;
}

int Player::getPlayerForm()
{
    return mPlayerForm;
}

QString Player::getPlayerBirthDay()
{
    return mPlayerBirthDate;
}

QString Player::getPlayerContractExpires()
{
    return mPlayerContractExpire;
}

QString Player::getPlayerPosition()
{
    return mPlayerPosition;
}

void Player::setPlayerAttributes(int Reflexes, int Tackling, int Passing, int Technique, int Pace, int Finishing)
{
    mPlayerAttributes["Reflexes"] = Reflexes;
    mPlayerAttributes["Tackling"] = Tackling;
    mPlayerAttributes["Passing"] = Passing;
    mPlayerAttributes["Technique"] = Technique;
    mPlayerAttributes["Pace"] = Pace;
    mPlayerAttributes["Finishing"] = Finishing;
}
