#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <map>
#include <QDebug>

class Team;

class Player
{
public:
    Player(QString, QString, QString, QString, QString, unsigned long long int, int, int);
    virtual ~Player();

    void setPlayerAttributes(int Reflexes, int Tackling, int Passing, int Technique, int Pace, int Finishing);
    QString getPlayerName();
    QString getPlayerPosition();
    QString getPlayerBirthDay();
    QString getPlayerContractExpires();

    int getPlayerReflexes();
    int getPlayerTackling();
    int getPlayerPassing();
    int getPlayerPace();
    int getPlayerTechnique();
    int getPlayerFinishing();
    QString getPlayerTeam();

    int getPlayerForm();
    int getPlayerWage();
    unsigned long long int getPlayerValue();

    void setAskingPrice(unsigned long long int askingPrice);
    unsigned long long int getAskingPrice();
    void setTransferList(bool);
    bool isTransferList();

    void setPlayerPA(int);
    int getPlayerPA();

    void setPlayerCA(int);
    int getPlayerCA();

    void addContractOffers(Team* team, int salary);
    void releasePlayer();
    void addTransferOffer(Team*, unsigned long long int);
    std::map<Team*, unsigned long long int> getTransferOffer();

private:
    std::map<Team*, int> mContractOffers;
    std::map<Team*, unsigned long long int> mTransferOffers;

    int mPlayerCurrentAbility;
    int mPlayerPotentialAbility;

    std::map<QString, int> mPlayerAttributes;
    QString mPlayerContractExpire;
    QString mPlayerContractStart;
    QString mPlayerTeamName;
    unsigned long long int mPlayerValue;
    int mPlayerWage;
    int mPlayerAge;
    QString mPlayerBirthDate;
    QString mPlayerName;
    int mPlayerForm;
    QString mPlayerPosition;
    unsigned long long int mAskingPrice;
    bool mTransferList;
    QString mPlayerNationality;

};

#endif // PLAYER_H
