#ifndef KTODOLIST_H
#define KTODOLIST_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QDebug>
#include <QPoint>
#include <QResizeEvent>
#include <QListWidget>
#include <QListWidgetItem>
#include <QWidget>
#include <QLabel>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QCheckBox>
#include <QMenu>
#include <QMessageBox>
#include <QVBoxLayout>
#include "kdatabase.h"

namespace Ui {
class KToDoList;
}

class KToDoList : public QMainWindow
{
    Q_OBJECT

public:
    explicit KToDoList(QWidget *parent = 0);
    ~KToDoList();

    void resizeEvent(QResizeEvent *event);

    void createTodoItem(const QString& item_name,const QString& item_detail,int set_red,const QString& id);
    void createCheckBox(const QString& name,bool state);
    void createGroupButton();

    void showHomePage();
    void showGroup();
    void showGroupPage(const QString& page_name,ShowWay way);

private slots:

    void on_m_inputButton_clicked();

    void on_m_lineEdit_returnPressed();

    void on_m_cldrButton_clicked();

    void on_m_cancelButton_clicked();

    void on_m_okButton_clicked();

    void on_m_closeButton_clicked();

    void on_m_groupInput_returnPressed();

    void on_m_setDeadline_clicked();

    void on_m_leftWidget_itemClicked(QListWidgetItem *item);

    void on_m_itemsWidget_itemClicked(QListWidgetItem *item);

    void on_m_refreshButton_clicked();

    void on_m_cldrRemindTime_clicked();

    void on_m_calendar_clicked(const QDate &date);

    void on_m_calendar2_clicked(const QDate &date);

    void on_m_removeRemindTime_clicked();

    void on_m_cldrOkButton_clicked();

    void on_m_removeEndDate_clicked();

    void on_m_setDescription_clicked();

    void on_m_setPlace_clicked();

    void on_m_setRemarks_clicked();

    void on_m_detailCloseButton_clicked();

    void on_m_detailCancelButton_clicked();

    void on_m_detailOkButton_clicked();

    void on_m_detailInput_returnPressed();

    void on_m_endDate_editingFinished();

    void on_m_circleDays_currentIndexChanged(int index);

    void on_m_remindTime_editingFinished();

    void on_m_setPriorityLevel_currentIndexChanged(int index);

    void on_m_closeInfoButton_clicked();

    void on_m_setItemName_clicked();

    void on_m_leftWidget_customContextMenuRequested(const QPoint &pos);

    void on_m_itemsWidget_customContextMenuRequested(const QPoint &pos);

    void on_m_itemRank_currentIndexChanged(int index);

    void on_m_checkBox_stateChanged(int arg1);

    void createGroupItem(const QString& group_name,const QIcon& icon=QIcon(":/分类.svg"));

    void setHasFinished(int a);

    void setNotArranged(int a);

    void setOverdue(int a);

    void setInsideSeven(int a);

    void setLater(int a);

    void showWidget();

    void deleteItem();

    void deleteGroupItem();

private:
    Ui::KToDoList *m_ui;
    KDatabase m_db;
    QString m_calendarDate;
    QString m_calendar2DateTime;
    int m_circleDays;
    bool m_sure;
    bool m_calendarChanged;
    bool m_calendar2Changed;
    QMenu* popMenu_in_m_homeWidget;
    QMenu* popMenu_in_m_toDoList;
    bool m_hasFinished;
    bool m_notArranged;
    bool m_overdue;
    bool m_insideSeven;
    bool m_later;
};

#endif // KTODOLIST_H
