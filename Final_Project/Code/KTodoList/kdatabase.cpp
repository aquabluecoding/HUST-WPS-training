#include "kdatabase.h"

KDatabase::KDatabase()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        m_db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE","qt_sql_default_connection");
        m_db.setDatabaseName("ToDoList.db");
        m_db.setUserName("User");
        m_db.setPassword("123456");
    }
    m_db.open();
    QSqlQuery sql_query(m_db);
    QString creat_sql ="create table if not exists my_todo(id integer auto_increment primary key,name varchar(200) not null,state varchar(1),";
    creat_sql+="priority_level integer,end_date date,circle_day integer,remind_time datetime,description varchar(1000),";
    creat_sql+="belong varchar(100),place varchar(100),remarks varchar(1000))";
    sql_query.prepare(creat_sql);
    if(!sql_query.exec())
        qDebug()<<"创建my_todo表失败:"<<sql_query.lastError();
    else
        qDebug()<<"创建my_todo表成功！";
    creat_sql ="create table if not exists group_names(id integer auto_increment primary key,name varchar(200) not null)";
    sql_query.prepare(creat_sql);
    if(!sql_query.exec())
        qDebug()<<"创建group_names表失败:"<<sql_query.lastError();
    else
        qDebug()<<"创建group_names表成功！";
    m_db.close();
}

bool KDatabase::openDb()
{
    if(!m_db.open())
    {
        qDebug()<<"打开数据库失败！" << m_db.lastError();
        return false;
    }
    return true;
}

void KDatabase::closeDb()
{
    m_db.close();
}

void KDatabase::insertDataToToDo(const QString& name,const QString& belong,const QString& end_date,const QString& remind_time,const int& circle_days)
{
    int num=0;
    QString num_sql="select max(id) from my_todo";
    QSqlQuery sql_query(m_db);
    sql_query.prepare(num_sql);
    if(!sql_query.exec())
        qDebug()<<"求数据数目失败:"<<sql_query.lastError();
    else
    {
        sql_query.next();
        qDebug()<<"求数据数目成功";
        num=sql_query.value(0).toInt()+1;
        qDebug()<<"数据数目为"<<sql_query.value(0).toInt();
        QString insert_sql="insert into my_todo values (?,?,?,?,?,?,?,?,?,?,?)";
        sql_query.prepare(insert_sql);
        sql_query.addBindValue(num);
        sql_query.addBindValue(name);
        sql_query.addBindValue("N");
        sql_query.addBindValue(0);
        sql_query.addBindValue(end_date);
        sql_query.addBindValue(circle_days);
        sql_query.addBindValue(remind_time);
        sql_query.addBindValue(" ");
        sql_query.addBindValue(belong);
        sql_query.addBindValue(" ");
        sql_query.addBindValue(" ");
        if(!sql_query.exec())
            qDebug()<<"插入数据失败:"<<sql_query.lastError();
        else
            qDebug()<<"插入数据成功";
    }
}

void KDatabase::insertDataToGroupNames(const QString& name)
{
    int num=0;
    QString num_sql="select max(id) from group_names";
    QSqlQuery sql_query(m_db);
    sql_query.prepare(num_sql);
    if(!sql_query.exec())
        qDebug()<<"求数据数目失败:"<<sql_query.lastError();
    else
    {
        sql_query.next();
        qDebug()<<"求数据数目成功";
        num=sql_query.value(0).toInt()+1;
        qDebug()<<"数据数目为"<<sql_query.value(0).toInt();
        QString insert_sql="insert into group_names values (?,?)";
        sql_query.prepare(insert_sql);
        sql_query.addBindValue(num);
        sql_query.addBindValue(name);
        if(!sql_query.exec())
            qDebug()<<"插入数据失败:"<<sql_query.lastError();
        else
            qDebug()<<"插入数据成功";
    }
}

QSqlQuery KDatabase::getHomeData()
{
    QSqlQuery sql_query(m_db);
    QString data_sql="select * from my_todo order by end_date";
    sql_query.prepare(data_sql);
    if(!sql_query.exec())
    {
        qDebug()<<"读取数据失败:"<<sql_query.lastError();
    }
    return sql_query;
}

QSqlQuery KDatabase::getGroup()
{
    QSqlQuery sql_query(m_db);
    QString data_sql="select name from group_names order by id";
    sql_query.prepare(data_sql);
    if(!sql_query.exec())
    {
        qDebug()<<"读取数据失败:"<<sql_query.lastError();
    }
    return sql_query;
}

bool KDatabase::findGroupItem(const QString& name)
{
    QSqlQuery sql_query(m_db);
    QString find_sql="select * from group_names where name=?";
    sql_query.prepare(find_sql);
    sql_query.addBindValue(name);
    if(!sql_query.exec())
    {
        qDebug()<<"查找数据失败:"<<sql_query.lastError();
    }
    return sql_query.next();
}

QSqlQuery KDatabase::getGroupData(const QString& name,ShowWay way)
{
    QSqlQuery sql_query(m_db);
    QString data_sql="select * from my_todo";
    data_sql+=" where belong=?";
    switch (way)
    {
        case DateShowWay:
            data_sql+=" order by end_date";
            break;
        case CreateDateShowWay:
            data_sql+=" order by id";
            break;
        case PriorityLevelShowWay:
            data_sql+=" order by priority_level desc";
    }
    sql_query.prepare(data_sql);
    sql_query.addBindValue(name);
    if(!sql_query.exec())
    {
        qDebug()<<"读取数据失败:"<<sql_query.lastError();
    }
    return sql_query;
}

QSqlQuery KDatabase::findToDoItem(const int& id)
{
    QSqlQuery sql_query(m_db);
    QString data_sql="select * from my_todo where id=?";
    sql_query.prepare(data_sql);
    sql_query.addBindValue(id);
    if(!sql_query.exec())
    {
        qDebug()<<"读取数据失败:"<<sql_query.lastError();
    }
    return sql_query;
}

void KDatabase::updateDataToToDo(Member member,const QString& str,const int& id)
{

    QSqlQuery sql_query(m_db);
    QString update_sql="update my_todo set ";
    switch (member) {
        case NameMember:
            update_sql+="name=? where id=?";
            sql_query.prepare(update_sql);
            sql_query.addBindValue(str);
            break;
        case StateMember:
            update_sql+="state=? where id=?";
            sql_query.prepare(update_sql);
            sql_query.addBindValue(str);
            break;
        case PriortityLevelMember:
            update_sql+="priority_level=? where id=?";
            sql_query.prepare(update_sql);
            sql_query.addBindValue(str.toInt());
            break;
        case EndDateMember:
            update_sql+="end_date=? where id=?";
            sql_query.prepare(update_sql);
            sql_query.addBindValue(str);
            break;
        case CircleDayMember:
            update_sql+="circle_day=? where id=?";
            sql_query.prepare(update_sql);
            sql_query.addBindValue(str.toInt());
            break;
        case RemindTimeMember:
            update_sql+="remind_time=? where id=?";
            sql_query.prepare(update_sql);
            sql_query.addBindValue(str);
            break;
        case DescriptionMember:
            update_sql+="description=? where id=?";
            sql_query.prepare(update_sql);
            sql_query.addBindValue(str);
            break;
        case PlaceMember:
            update_sql+="place=? where id=?";
            sql_query.prepare(update_sql);
            sql_query.addBindValue(str);
            break;
        case RemarksMember:
            update_sql+="remarks=? where id=?";
            sql_query.prepare(update_sql);
            sql_query.addBindValue(str);
            break;
    }
    sql_query.addBindValue(id);
    if(!sql_query.exec())
    {
        qDebug()<<"更新数据失败:"<<sql_query.lastError();
    }
    else
        qDebug()<<"更新数据成功";
}
void KDatabase::deleteDataFromToDo(const int& id)
{
    QSqlQuery sql_query(m_db);
    QString delete_sql="delete from my_todo where id=?";
    sql_query.prepare(delete_sql);
    sql_query.addBindValue(id);
    if(!sql_query.exec())
    {
        qDebug()<<"删除数据失败:"<<sql_query.lastError();
    }
}

void KDatabase::deleteDataFromToDo(const QString& name)
{
    QSqlQuery sql_query(m_db);
    QString delete_sql="delete from my_todo where belong=?";
    sql_query.prepare(delete_sql);
    sql_query.addBindValue(name);
    if(!sql_query.exec())
    {
        qDebug()<<"删除数据失败:"<<sql_query.lastError();
    }
}
void KDatabase::deleteDataFromGroupNames(const QString& name)
{
    QSqlQuery sql_query(m_db);
    QString delete_sql="delete from group_names where name=?";
    sql_query.prepare(delete_sql);
    sql_query.addBindValue(name);
    if(!sql_query.exec())
    {
        qDebug()<<"删除数据失败:"<<sql_query.lastError();
    }
    else
    {
        deleteDataFromToDo(name);
    }
}

KDatabase::~KDatabase()
{
}
