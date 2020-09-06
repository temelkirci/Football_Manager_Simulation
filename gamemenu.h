#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QDialog>
#include "MainWindow.h"
#include <QCheckBox>
#include <QtSql>

namespace Ui {
class GameMenu;
}

class GameMenu : public QDialog
{
    Q_OBJECT

public:
    explicit GameMenu(QWidget *parent = nullptr);
    ~GameMenu();
    std::vector<QString> getLeaguesFromDatabase();
    void drawLeagues();
    void setDatabase();

private slots:
    void on_startGame_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::GameMenu *ui;
    MainWindow *mMainWindow;
    int mLeagueNumber;
    QSqlDatabase mydb;

    std::vector<QCheckBox*> mCheckBox;
};

#endif // GAMEMENU_H
