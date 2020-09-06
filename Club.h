#ifndef Club_H
#define Club_H

#include <QString>
#include "Player.h"
#include <vector>
#include <QDebug>
#include <QDate>
#include "Manager.h"
#include <memory>

class Match;

class Club
{
public:
    Club();
    Club( QString ClubName, unsigned ClubReputation, QString ClubCountry, unsigned ClubLeague, QString, unsigned, unsigned, unsigned );

    struct TransferOffer
    {
        QDate transferStart;
        QDate transferFinish;
        unsigned bidForPlayer;
        std::shared_ptr< Club > transferByClub;
        std::shared_ptr< Player > player;

        QDate transferRelpyStart;
        QDate transferRelpyFinish;

        bool isTransferAccept;
    };

    void addPlayerToClub(std::shared_ptr< Player >);

    std::vector< std::shared_ptr< Player > > getPlayersInClub();
    std::vector< std::shared_ptr< Player > > getYouthPlayersInClub();

    void addYouthPlayerToClub( std::shared_ptr< Player > player );

    QString getClubName();
    QString getClubCountry();
    QString getClubLeague();
    bool isPlayerInMatch( std::shared_ptr< Player > );
    bool isPlayerInSub( std::shared_ptr< Player > tPlayer );

    void PlayersDevelopment();
    void calculatePlayerValue();

    unsigned getTransferBudget();
    int getClubSalary();

    void setClubAvaragePoint( unsigned );
    unsigned int getClubAvaragePoint();

    void addTransferList( std::shared_ptr< Player > );
    void removeTransferList( std::shared_ptr< Player > );
    std::vector<std::shared_ptr< Player >> getPlayersInTransferList();

    void increaseTransferBudget( unsigned );
    void decreaseTransferBudget( unsigned );

    void increaseWageBudget( unsigned );
    void decreaseWageBudget( unsigned );

    void setClubManagerName( QString );
    QString getClubManagerName();

    void setClubPresidentName( QString );
    QString getClubPresidentName();

    void removePlayer( std::shared_ptr< Player > );

    void prepareMatchPlayers();
    std::vector< std::shared_ptr< Player > > getMatchPlayers();
    std::vector< std::shared_ptr< Player > > getSubMatchPlayers();
    std::vector< std::shared_ptr< Player > > getPlayersByPosition( QString );

    int getClubReputation();
    void setWageBudget( unsigned );

    unsigned getMaxWageBudget();
    void setMaxWageBudget( unsigned );

    unsigned getClubValue();
    void changeClubValue( int );

    void addScoutPlayer( std::shared_ptr< Player > player, unsigned value );
    std::map< std::shared_ptr< Player >, unsigned > getScoutingPlayers();

    std::map< std::shared_ptr< Club >, QDate > getFixtures();
    void setFixtures( std::shared_ptr< Club >, QDate );
    void setManager( std::shared_ptr< Manager > );
    int generateRandomNumber( int lower, int upper );

    std::shared_ptr< Manager > getClubManager();
    void setMatch();

    void addTransferOffers( TransferOffer offer );
    void generateTransferOffer( std::shared_ptr< Player > , unsigned );

private:
    std::map< std::shared_ptr< Player >, unsigned > mScoutingPlayers;
    std::vector< std::shared_ptr< Player > > mTransferList;
    std::vector< std::shared_ptr< Player > > mMatchPlayers;
    std::vector< std::shared_ptr< Player > > mSubMatchPlayers;
    std::vector< std::shared_ptr< Player > > mAllMatches;

    QString mClubName;
    QString mClubCountry;
    QString mContinent;
    unsigned mMediaForecast;
    unsigned mBoardForecast;
    unsigned mRemaningManagerConfidence;

    unsigned mTrainingFacilitiesLevel;
    unsigned mYouthTrainingFacilitiesLevel;
    unsigned mStadiumCapacity;

    unsigned mWageBudget;
    int mRemainingWageBudget;
    unsigned mRemainingTransferBudget;
    QString mClubLeague;
    unsigned mTransferBudget;
    std::vector< std::shared_ptr< Player > > mAllPlayersInClub;
    std::vector< std::shared_ptr< Player > > mAllPlayersInYouthClub;

    std::vector< TransferOffer > transferOffers;
    std::vector< TransferOffer > incomingTransferOffers;

    int mClubReputation;
    unsigned mClubAvarageAbility;

    unsigned mTrainingFacilities;
    unsigned mTraningStaff;

    QString mPresident;
    std::shared_ptr< Manager > mpManager;
    unsigned mClubValue;
    unsigned mMaxWageBudget;
};

#endif // Club_H
