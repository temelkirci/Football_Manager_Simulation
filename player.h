#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <map>
#include <QDebug>
#include <QDate>
#include <memory>

class Club;

class Player
{
public:
    Player( QString, QString, std::shared_ptr< Club >, QString, QDate, unsigned, unsigned, unsigned );
    ~Player();

    struct ContractOffer
    {
        QDate contractStart;
        QDate contractFinish;
        unsigned contractSalary;
        std::shared_ptr< Club > contractByClub;

        QDate contractRelpyStart;
        QDate contractRelpyFinish;

        bool isContractAccept;
    };

    void setPlayerAttributes( int Reflexes, int Tackling, int Passing, int Technique, int Pace, int Finishing );
    QString getPlayerName();
    QString getPlayerPosition();
    QDate getPlayerBirthDay();
    QString getPlayerContractExpires();

    int getPlayerReflexes();
    int getPlayerTackling();
    int getPlayerPassing();
    int getPlayerPace();
    int getPlayerTechnique();
    int getPlayerFinishing();

    int getPlayerForm();
    int getPlayerWage();

    void calculatePlayerValue();

    unsigned getPlayerValue();

    void setAskingPrice( unsigned askingPrice );
    unsigned getAskingPrice();
    void setTransferList( bool );
    bool isTransferList();

    void setPlayerPA( int );
    int getPlayerPA();

    int getPlayerCA();
    void calculateCA();

    void setFacePath( QString );
    QString getFacePath();

    void addContractOffers( ContractOffer );
    void setMinimumInterestReputation( int );
    int getMinimumInterestReputation();
    void releasePlayer();
    void addTransferOffer( std::shared_ptr< Club >, unsigned );

    unsigned int getPlayerAge();
    void setMoral( int );
    int getMoral();

    void setCondition( int );
    int getCondition();

    void setPlayerNationality( QString );
    QString getPlayerNationality();

    std::map< std::shared_ptr< Club >, unsigned > getTransferOffer();

    bool isInjured();
    QDate getInjuredFinish();
    void setMainSquad();
    void setU19Squad();

    void setSquadStatus();
    void setPlayerClub( std::shared_ptr< Club > pPlayerClub );
    std::shared_ptr< Club > getPlayerClub();
    void PlayerDevelopAttributes( QString, int );

private:
    std::shared_ptr< Club > mPlayerClub;
    std::vector < ContractOffer > contractOffersToPlayer;

    unsigned mYellowCards;
    unsigned mRedCards;

    QString mSquad;
    QString mSquadStatus;

    bool mInjured;
    QDate mInjuredFinishDate;    

    unsigned mPlayerCurrentAbility;
    unsigned mPlayerPotentialAbility;

    std::map< QString, unsigned > mPlayerAttributes;
    std::map< QString, unsigned > mPlayerDevelopAttributes;

    QString mPlayerContractExpire;
    QString mPlayerContractStart;

    unsigned mPlayerValue;
    unsigned mPlayerWage;
    unsigned mPlayerAge;
    QDate mPlayerBirthDate;
    QString mPlayerName;
    int mPlayerForm;
    QString mPlayerPosition;
    unsigned mAskingPrice;
    bool mTransferList;
    QString mPlayerNationality;
    QString mPlayerFacePath;
    unsigned mCondition;
    unsigned mMoral;
    unsigned mMinimumInterestReputation;
};

#endif // PLAYER_H
