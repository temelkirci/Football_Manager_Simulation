#ifndef NEWS_H
#define NEWS_H

#include <QString>

enum class NewsTypes
{
    WELCOME_TO_CLUB,
    SCOUT_PLAYER,
    OFFER_CONTRACT_PLAYER,
    DECLINE_CONTRACT_OFFER_PLAYER,
    ACCEPT_CONTRACT_OFFER_PLAYER,

};

class News
{
public:
    News();


    void CreateNews();
private:
    QString mMessageHeader;
    QString mMessageContext;
    bool isReadMessage;

};

#endif // NEWS_H
