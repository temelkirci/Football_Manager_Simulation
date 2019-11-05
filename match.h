#ifndef MATCH_H
#define MATCH_H

#include "team.h"
#include "player.h"

class Match
{
public:
    Match();
    void setMatch( int week, Team* home_team,Team* away_team, QDate match_date, bool friendly_match = false );
    bool isPlayed();
    Team* getHomeTeam();
    Team* getAwayTeam();
    QDate getMatchDate();
private:
    bool mPlayed;
    QDate mMatchDate;
    Team* mHomeTeam;
    Team* mAwayTeam;
};

#endif // MATCH_H
