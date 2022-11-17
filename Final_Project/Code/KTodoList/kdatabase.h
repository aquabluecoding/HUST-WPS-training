#ifndef KDATABASE_H
#define KDATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

enum ShowWay
{
    DateShowWay=0,
    CreateDateShowWay,
    PriorityLevelShowWay
};

enum Member
{
    IdMember=0,
    NameMember,
    StateMember,
    PriortityLevelMember,
    EndDateMember,
    CircleDayMember,
    RemindTimeMember,
    DescriptionMember,
    BelongMember,
    PlaceMember,
    RemarksMember
};

class KDatabase
{
public:
    KDatabase();
    bool openDb();
    void closeDb();
    void insertDataToToDo(const QString& name,const QString& belong,const QString& end_date,const QString& remind_time,const int& circle_days);
    void insertDataToGroupNames(const QString& name);
    QSqlQuery getHomeData();
    QSqlQuery getGroup();
    QSqlQuery getGroupData(const QString& name,ShowWay way);
    bool findGroupItem(const QString& name);
    QSqlQuery findToDoItem(const int& id);
    void updateDataToToDo(Member member,const QString& str,const int& id);
    void deleteDataFromToDo(const int& id);
    void deleteDataFromToDo(const QString& name);
    void deleteDataFromGroupNames(const QString& name);
    ~KDatabase();
private:
    QSqlDatabase m_db;
};

#endif // KDATABASE_H
