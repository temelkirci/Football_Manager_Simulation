#include "Player.h"
#include <iostream>

Player::Player( QString playerName,
                QString playerPosition,
                std::shared_ptr< Club > playerClub,
                QString playerContractExpire,
                QDate playerBirthDay,
                unsigned playerValue,
                unsigned playerWage,
                unsigned playerForm )
{
    mPlayerClub = ( playerClub );

    mPlayerName = playerName;
    mPlayerPosition = playerPosition;
    mPlayerContractExpire = playerContractExpire;

    mPlayerBirthDate = playerBirthDay;
    mPlayerWage = playerWage;
    mPlayerForm = playerForm;
    mPlayerValue = playerValue;

    mCondition = 100;
    mMoral = 100;

    mInjured = false;

    mPlayerDevelopAttributes["Reflexes"] = 0;
    mPlayerDevelopAttributes["Tackling"] = 0;
    mPlayerDevelopAttributes["Passing"] = 0;
    mPlayerDevelopAttributes["Technique"] = 0;
    mPlayerDevelopAttributes["Pace"] = 0;
    mPlayerDevelopAttributes["Finishing"] = 0;
}

Player::~Player()
{

}

void Player::PlayerDevelopAttributes( QString attribute, int value )
{
    mPlayerDevelopAttributes[ attribute ] = mPlayerDevelopAttributes[ attribute ] + value;

    if(mPlayerDevelopAttributes[ attribute ] >= 1000)
    {
        mPlayerDevelopAttributes[ attribute ] = mPlayerDevelopAttributes[ attribute ] - 1000;
        mPlayerAttributes[ attribute ] = mPlayerAttributes[ attribute ] + 1;
    }

    calculateCA();
}

void Player::calculateCA()
{
    if( mPlayerPosition == "GK" )
    {
        mPlayerCurrentAbility = mPlayerAttributes[ "Reflexes" ];
    }
    else
    {
        mPlayerCurrentAbility = ( mPlayerAttributes[ "Tackling" ] + mPlayerAttributes[ "Passing" ] + mPlayerAttributes[ "Technique" ] + mPlayerAttributes[ "Pace" ] + mPlayerAttributes[ "Finishing" ] ) / 5;
    }

    if(mPlayerCurrentAbility > mPlayerPotentialAbility )
    {
        mPlayerCurrentAbility = mPlayerPotentialAbility;
    }
}

bool Player::isInjured()
{
    return mInjured;
}

QDate Player::getInjuredFinish()
{
    return mInjuredFinishDate;
}

void Player::setPlayerNationality( QString country )
{
    mPlayerNationality = country;
}

QString Player::getPlayerNationality()
{
    return mPlayerNationality;
}

void Player::setMoral( int moral )
{
    mMoral = moral;
}

int Player::getMoral()
{
    return mMoral;
}

void Player::setCondition( int condition )
{
    mCondition = condition;
}

int Player::getCondition()
{
    return mCondition;
}

void Player::setMinimumInterestReputation( int reputation )
{
    mMinimumInterestReputation = reputation;
}

int Player::getMinimumInterestReputation()
{
    return mMinimumInterestReputation;
}

void Player::setFacePath( QString PlayerFacePath )
{
    mPlayerFacePath = PlayerFacePath;
}

QString Player::getFacePath()
{
    return mPlayerFacePath;
}

void Player::setPlayerPA( int PA )
{
    mPlayerPotentialAbility = PA;
}

int Player::getPlayerPA()
{
    return mPlayerPotentialAbility;
}

int Player::getPlayerCA()
{
    return mPlayerCurrentAbility;
}

void Player::releasePlayer()
{
    mTransferList = false;
    mAskingPrice = 0;
    mPlayerWage = 0;
    mPlayerValue = 0;
    mPlayerContractExpire = "expired";
}

unsigned Player::getAskingPrice()
{
    return mAskingPrice;
}

void Player::addContractOffers( ContractOffer contractOffer )
{
    contractOffersToPlayer.push_back( contractOffer );
}

std::shared_ptr< Club > Player::getPlayerClub()
{
    return (mPlayerClub);
}

void Player::setTransferList( bool transfer )
{
    mTransferList = transfer;
}

bool Player::isTransferList()
{
    return mTransferList;
}

void Player::setAskingPrice( unsigned askingPrice )
{
    mAskingPrice = askingPrice;
}

int Player::getPlayerReflexes()
{
    return mPlayerAttributes[ "Reflexes" ];
}

int Player::getPlayerTackling()
{
    return mPlayerAttributes[ "Tackling" ];
}

int Player::getPlayerPassing()
{
    return mPlayerAttributes[ "Passing" ];
}

int Player::getPlayerPace()
{
    return mPlayerAttributes[ "Pace" ];
}

int Player::getPlayerTechnique()
{
    return mPlayerAttributes[ "Technique" ];
}

int Player::getPlayerFinishing()
{
    return mPlayerAttributes[ "Finishing" ];
}

QString Player::getPlayerName()
{
    return mPlayerName;
}

int Player::getPlayerWage()
{
    return mPlayerWage;
}

unsigned Player::getPlayerValue()
{
    return mPlayerValue;
}

int Player::getPlayerForm()
{
    return mPlayerForm;
}

QDate Player::getPlayerBirthDay()
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

unsigned int Player::getPlayerAge()
{
    return mPlayerAge;
}

void Player::setPlayerAttributes( int Reflexes, int Tackling, int Passing, int Technique, int Pace, int Finishing )
{
    mPlayerAttributes[ "Reflexes" ] = Reflexes;
    mPlayerAttributes[ "Tackling" ] = Tackling;
    mPlayerAttributes[ "Passing" ] = Passing;
    mPlayerAttributes[ "Technique" ] = Technique;
    mPlayerAttributes[ "Pace" ] = Pace;
    mPlayerAttributes[ "Finishing" ] = Finishing;

    calculateCA();
}

void Player::setPlayerClub( std::shared_ptr< Club > pPlayerClub )
{
    mPlayerClub = ( pPlayerClub );
}
