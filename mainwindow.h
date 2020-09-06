#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTableView>
#include <QTabWidget>
#include <QTableWidgetItem>
#include <string>
#include "CreateGame.h"
#include <map>
#include <QPushButton>
#include <vector>
#include <QSignalMapper>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget *parent = nullptr );
    ~MainWindow();

    std::shared_ptr< Club > getMyClub();
    void showMyClub();
    void InitGame( QString pManagerName, QString pMyClub, std::vector<QString> pLeagueList );
    void createInbox( QString, QString );
    void showMyInbox();
    void showTransferList();
    void showScoutList();
    QString getValueColor( int );
    QDate mToday;
    Ui::MainWindow *ui;
    void setIcons();
    void setMatchUI( std::shared_ptr< Match > x );

private slots:

    void drawLeague( QString );
    void on_pushButton_clicked();
    void on_myClub_cellClicked( int row, int column );
    void showMyMessage( QString );

    void on_ProgressButton_clicked();
    void on_freePlayersCheckbox_stateChanged( int arg1 );
    void on_LeagueTable_cellClicked( int row, int column );
    void on_releasePlayerButton_clicked();

    void on_addTransferListButton_clicked();
    void on_playMatchButton_clicked();
    void on_pushButton_2_clicked();

private:

    std::shared_ptr< ClubDatabase > mClubDatabase;
    std::shared_ptr< Club > mMyClub;
    std::shared_ptr< Match > tMatch;

    QTableWidget* pTable;
    std::shared_ptr< CreateGame > mCreateWindow;
    QString mMyClubName;
    std::shared_ptr< Player > mSelectedPlayer;
    bool init;
    std::map<QPushButton*, QString> mInbox;
};

#endif // MAINWINDOW_H
