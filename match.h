#ifndef MATCH_H
#define MATCH_H

#include "Club.h"
#include "Player.h"

class Match
{
public:
    Match();

    void setMatch( int week, std::shared_ptr< Club > home_Club,std::shared_ptr< Club > away_Club, QDate match_date, bool friendly_match = false );
    void run();
    bool isPlayed();
    std::shared_ptr< Club > getHomeClub();
    std::shared_ptr< Club > getAwayClub();
    QDate getMatchDate();

    void eventsInGame(int, QString);
    void addScoreForHomeClub(unsigned int tScore);
    void addScoreForAwayClub(unsigned int tScore);

    unsigned int getScoreForHomeClub();
    unsigned int getScoreForAwayClub();


    unsigned int mTime;
    unsigned int mHomeAttack;
    unsigned int mAwayAttack;

    unsigned int mHomeAttackChance;
    unsigned int mAwayAttackChance;

private:


    bool mPlayed;
    QDate mMatchDate;
    std::shared_ptr< Club > mHomeClub;
    std::shared_ptr< Club > mAwayClub;

    unsigned int mHomeScore;
    unsigned int mAwayScore;

    std::map<unsigned int, QString> mEvents;
};

#endif // MATCH_H
