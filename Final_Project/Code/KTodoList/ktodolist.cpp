#include "ktodolist.h"
#include "ui_ktodolist.h"

KToDoList::KToDoList(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::KToDoList)
{
    m_hasFinished=false;
    m_overdue=true;
    m_insideSeven=true;
    m_later=true;
    m_notArranged=true;

    popMenu_in_m_homeWidget = new QMenu(this);
    QAction* action_delete_in_m_homeWidget = new QAction(tr("Delete"), this);
    popMenu_in_m_homeWidget->addAction(action_delete_in_m_homeWidget);
    connect(action_delete_in_m_homeWidget,SIGNAL(triggered(bool)),this,SLOT(deleteGroupItem()));
    popMenu_in_m_toDoList =new QMenu(this);
    QAction* action_delete_in_m_toDoList = new QAction(tr("Delete"),this);
    popMenu_in_m_toDoList->addAction(action_delete_in_m_toDoList);
    connect(action_delete_in_m_toDoList,SIGNAL(triggered(bool)),this,SLOT(deleteItem()));

    m_calendarChanged=false;
    m_calendar2Changed=false;
    m_calendarDate="";
    m_calendar2DateTime="";

    m_ui->setupUi(this);
    m_ui->m_background->setStyleSheet("background-color:rgb(240, 255, 240);");
    on_m_setDeadline_clicked();
    m_ui->m_cldrWidget->hide();
    m_ui->m_detailInfo->hide();
    m_ui->m_itemRank->hide();

    m_db.openDb();
    m_ui->m_inputButton->setStyleSheet("QPushButton{text-align : left;}");
    m_ui->m_rightWidget->raise();
    m_ui->m_picture->raise();
    m_ui->m_reminder->raise();

    m_ui->m_createGroupWidget->hide();
    m_ui->m_setDetail->hide();
    createGroupButton();
    createGroupItem("我的首页",QIcon(":/我的首页.svg"));
    createGroupItem("我的待办",QIcon(":/我的待办.svg"));
    showHomePage();
    showGroup();
}

KToDoList::~KToDoList()
{
    delete m_ui;
    m_db.closeDb();
    if(popMenu_in_m_homeWidget)
        delete(popMenu_in_m_homeWidget);
    if(popMenu_in_m_toDoList)
        delete(popMenu_in_m_toDoList);
}

void KToDoList::on_m_lineEdit_returnPressed()
{
    QString end_date= (m_calendarDate=="" ? "2099-12-31":m_calendarDate);
    QString remind_time= (m_calendar2DateTime=="" ? "2099-12-31 23:59:59" :m_calendar2DateTime+":00");
    if(m_ui->m_lineEdit->text()!="")
    {
        if(m_ui->m_midTopLabel->text()=="我的首页")
        {
            m_db.insertDataToToDo(m_ui->m_lineEdit->text(),"我的待办",end_date,remind_time,m_circleDays);
        }
        else
        {
            m_db.insertDataToToDo(m_ui->m_lineEdit->text(),m_ui->m_midTopLabel->text(),end_date,remind_time,m_circleDays);
        }
        m_ui->m_lineEdit->setText("");
        m_ui->m_inputButton->raise();
        on_m_refreshButton_clicked();
    }
}

void KToDoList::on_m_inputButton_clicked()
{
    m_ui->m_lineEdit->raise();
    m_ui->m_cldrButton->raise();
}

void KToDoList::on_m_cldrButton_clicked()
{
    m_calendarChanged=false;
    m_calendar2Changed=false;
    if(!m_ui->m_cldrWidget->isVisible())
    {
        m_ui->m_cldrWidget->show();
        m_ui->m_cldrWidget->raise();
        QPoint pos=m_ui->m_cldrButton->pos();
        pos.setX(pos.x()-260);
        pos.setY(pos.y()+40);
        m_ui->m_cldrWidget->move(pos);
        on_m_setDeadline_clicked();
    }
    else
    {
        m_ui->m_cldrWidget->hide();
        if(m_calendarDate=="")
        {
            m_ui->m_calendar->setSelectedDate(QDate::currentDate());
            m_ui->m_setCircleDays->setCurrentIndex(0);
        }
        if(m_calendar2DateTime=="")
        {
            m_ui->m_calendar2->setSelectedDate(QDate::currentDate());
            m_ui->m_setTime->setTime(QTime::fromString("00:00"));
        }
    }
}

//动态调整各个组件的大小
void KToDoList::resizeEvent(QResizeEvent *event)
{
    int x = event->size().width();
    int y = event->size().height();

    QSize topWidgetSize=m_ui->m_topWidget->size();
    topWidgetSize.setWidth(x);
    m_ui->m_topWidget->resize(topWidgetSize);

    QSize leftWidgetSize=m_ui->m_leftWidget->size();
    leftWidgetSize.setHeight(y-70);
    m_ui->m_leftWidget->resize(leftWidgetSize);

    QSize rightWidgetSize=m_ui->m_rightWidget->size();
    rightWidgetSize.setHeight(y-70);
    m_ui->m_rightWidget->resize(rightWidgetSize);
    m_ui->m_rightWidget->move(x-rightWidgetSize.width(),70);

    QSize midWidgetSize;
    midWidgetSize.setWidth(x-leftWidgetSize.width()-rightWidgetSize.width());
    midWidgetSize.setHeight(y-70);
    m_ui->m_midWidget->resize(midWidgetSize);

    midWidgetSize.setHeight(midWidgetSize.height()-111);
    midWidgetSize.setWidth(midWidgetSize.width()-16);
    m_ui->m_itemsWidget->resize(midWidgetSize);

    QSize iBSize=m_ui->m_inputButton->size();
    iBSize.setWidth(midWidgetSize.width()-20);
    m_ui->m_inputButton->resize(iBSize);
    m_ui->m_lineEdit->resize(iBSize);

    QPoint cldrPos=m_ui->m_inputButton->pos();
    cldrPos.setX(cldrPos.x()+iBSize.width()-40);

    if(cldrPos.x()>350)
    {
        m_ui->m_cldrButton->move(cldrPos);
        m_ui->m_cldrButton->show();
    }
    else
    {
        m_ui->m_cldrButton->hide();
    }

    QPoint refreshPos=m_ui->m_refreshButton->pos();
    refreshPos.setX(m_ui->m_inputButton->pos().x()+iBSize.width()-81);
    if(refreshPos.x()>450)
        m_ui->m_refreshButton->move(refreshPos);

    QPoint picPos=m_ui->m_rightWidget->pos();
    picPos.setX(m_ui->m_rightWidget->pos().x()+100);
    picPos.setY(rightWidgetSize.height()/2-120);
    m_ui->m_picture->move(picPos);
    picPos.setX(picPos.x()-8);
    picPos.setY(picPos.y()+211);
    m_ui->m_reminder->move(picPos);

    m_ui->m_shadow->resize(x,y);
    QSize createGroupSize=m_ui->m_createGroupWidget->size();
    m_ui->m_createGroupWidget->move(0.5*x-0.5*createGroupSize.width(),0.5*y-0.5*createGroupSize.height());
    m_ui->m_setDetail->move(0.5*x-0.5*createGroupSize.width(),0.5*y-0.5*createGroupSize.height());

    m_ui->m_detailInfo->move(m_ui->m_rightWidget->pos());
    m_ui->m_detailInfo->resize(rightWidgetSize);
}


void KToDoList::showHomePage()
{
    bool show[4]={m_overdue,m_insideSeven,m_later,m_notArranged};
    int created[5]={1,0,0,0,0};
    int index=0;
    m_ui->m_itemsWidget->clear();
    QSqlQuery sql_query=m_db.getHomeData();
    createCheckBox("已逾期",m_overdue);
    while(sql_query.next())
    {
        if(sql_query.value(StateMember).toString()=="N")
        {
            QString name="";
            QString detail="   ";
            QString id=sql_query.value(IdMember).toString();
            for(int i=0;i<sql_query.value(PriortityLevelMember).toInt();i++)
                name+="!";
            name+=sql_query.value(NameMember).toString();

            int set_red=0;

            if(sql_query.value(EndDateMember).toString()!="2099-12-31")//该日期专门用来指代未安排
            {
                QDate end_date=QDate::fromString(sql_query.value(EndDateMember).toString(),"yyyy-MM-dd");
                QDate now_date=QDate::currentDate();
                detail=detail+(end_date.addDays(1)==now_date ? "昨天 ":"");
                detail=detail+(end_date==now_date ? "今天 ":"");
                detail=detail+(end_date.addDays(-1)==now_date ? "明天 ":"");
                detail=detail+(detail.length()==3 ? end_date.toString("yyyy-MM-dd ddd"):end_date.toString("ddd"));
                set_red += now_date>end_date ? 1:0;

                int circle_day=sql_query.value(CircleDayMember).toInt();
                detail=detail+(circle_day==1 ? " | 每天重复" : "");
                detail=detail+(circle_day==7 ? " | 每周重复" : "");

                detail=detail+(circle_day==1000 ? " | 每月重复" : "");

                detail=detail+(sql_query.value(RemindTimeMember).toString()=="2099-12-31 23:59:59" \
                               ? "" : " | 提醒时间:"+sql_query.value(RemindTimeMember).toString());
                QDateTime remind_time=QDateTime::fromString(sql_query.value(RemindTimeMember).toString(),"yyyy-MM-dd hh:mm:ss");
                QDateTime now_time=QDateTime::currentDateTime();
                set_red+= now_time>remind_time ? 2:0;

                if(now_date.addDays(7)>=end_date&&!created[1]&&now_date<end_date)
                {
                    index++;
                    created[1]=1;
                    createCheckBox("未来七天",m_insideSeven);
                }
                if(now_date.addDays(7)<end_date&&!created[2])
                {
                    index++;
                    created[2]=1;
                    createCheckBox("以后",m_later);
                }
            }
            else if(sql_query.value(EndDateMember).toString()=="2099-12-31"&&!created[3])
            {
                if(!created[1])
                {
                    index++;
                    created[1]=1;
                    createCheckBox("未来七天",m_insideSeven);
                }
                if(!created[2])
                {
                    index++;
                    created[2]=1;
                    createCheckBox("以后",m_later);
                }
                index++;
                created[3]=1;
                createCheckBox("未安排",m_notArranged);
            }

            if(detail!="   ")
                detail=detail+" | "+sql_query.value(BelongMember).toString();
            else
                detail=detail+sql_query.value(BelongMember).toString();
            if(!created[index+1]&&show[index])
                createTodoItem(name,detail,set_red,id);
        }
    }
    if(!created[1])
        createCheckBox("未来七天",m_insideSeven);
    if(!created[2])
        createCheckBox("以后",m_later);
    if(!created[3])
        createCheckBox("未安排",m_notArranged);
}

void KToDoList::createTodoItem(const QString& item_name,const QString& item_detail,int set_red,const QString& id)
{
    QListWidgetItem* item= new QListWidgetItem(m_ui->m_itemsWidget);
    QWidget* container =new QWidget(m_ui->m_itemsWidget);
    QVBoxLayout* layout=new QVBoxLayout();
    QLabel* label2 =new QLabel();

    QLabel * label1 =new QLabel(id);
    label1->hide();
    layout->addWidget(label1);

    label2->setText(item_name);
    QFont font=label2->font();
    font.setPointSize(14);
    label2->setFont(font);
    if(set_red==1||set_red==3)
        label2->setStyleSheet("color:red;");
    layout->addWidget(label2);

    if(item_detail!="   ")
    {
        QLabel* label=new QLabel();
        label->setText(item_detail);
        font.setPointSize(12);
        label->setFont(font);
        if(set_red==2||set_red==3)
            label->setStyleSheet("color:red;");
        layout->addWidget(label);
        item->setSizeHint(QSize(1,100));
    }
    else
        item->setSizeHint(QSize(1,50));
    container->setLayout(layout);
    m_ui->m_itemsWidget->setItemWidget(item,container);
}

void KToDoList::createGroupButton()
{
    QListWidgetItem* item=new QListWidgetItem(m_ui->m_leftWidget);
    QWidget* container=new QWidget(m_ui->m_leftWidget);
    QVBoxLayout* layout=new QVBoxLayout();
    QPushButton* pushButton=new QPushButton("添加分组");
    pushButton->setIcon(QIcon(QPixmap(":/加号.svg")));
    QFont font=pushButton->font();
    font.setPointSize(10);
    pushButton->setFont(font);
    connect(pushButton,SIGNAL(clicked(bool)),this,SLOT(showWidget()));
    layout->addWidget(pushButton);
    item->setSizeHint(QSize(1,60));
    container->setLayout(layout);
    m_ui->m_leftWidget->setItemWidget(item,container);
}
void KToDoList::createCheckBox(const QString& name,bool state)
{
    QListWidgetItem* item=new QListWidgetItem(m_ui->m_itemsWidget);
    QWidget* container=new QWidget(m_ui->m_itemsWidget);
    QVBoxLayout* layout=new QVBoxLayout();
    QCheckBox* checkBox=new QCheckBox(name);
    if(state)
       checkBox->setChecked(true);
    QFont font=checkBox->font();
    font.setPointSize(10);
    checkBox->setFont(font);
    QStringList list={"未安排","已逾期","未来七天","以后","已完成"};
    int i=0;
    while(i<5)
    {
        if(list[i]==name)
            break;
        i++;
    }
    switch (i) {
        case 0:
            connect(checkBox,SIGNAL(stateChanged(int)),this,SLOT(setNotArranged(int)));
            break;
        case 1:
            connect(checkBox,SIGNAL(stateChanged(int)),this,SLOT(setOverdue(int)));
            break;
        case 2:
            connect(checkBox,SIGNAL(stateChanged(int)),this,SLOT(setInsideSeven(int)));
            break;
        case 3:
            connect(checkBox,SIGNAL(stateChanged(int)),this,SLOT(setLater(int)));
            break;
        case 4:
            connect(checkBox,SIGNAL(stateChanged(int)),this,SLOT(setHasFinished(int)));
            break;
    }
    layout->addWidget(checkBox);
    item->setSizeHint(QSize(1,50));
    container->setLayout(layout);
    m_ui->m_itemsWidget->setItemWidget(item,container);
}
void KToDoList::createGroupItem(const QString& group_name,const QIcon& icon)
{
    QListWidgetItem *item=new QListWidgetItem(icon,group_name);
    QFont font=item->font();
    //font.setFamily("Sans Francisco");
    item->setFont(font);
    item->setSizeHint(QSize(1,40));
    m_ui->m_leftWidget->insertItem(m_ui->m_leftWidget->count()-1,item);
}

void KToDoList::deleteItem()
{
    QListWidgetItem* item=m_ui->m_itemsWidget->currentItem();
    if(item)
    {
        if (QMessageBox::Yes == QMessageBox::question(this, QStringLiteral("Remove Item"),\
                QStringLiteral("Remove 1 Item").arg(QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes)))
        {
            QListWidgetItem* item1=m_ui->m_itemsWidget->selectedItems()[0];
            QWidget * widget=m_ui->m_itemsWidget->itemWidget(item1);
            QLabel* label=widget->findChild<QLabel *>();
            int id=label->text().toInt();
            m_db.deleteDataFromToDo(id);
            on_m_refreshButton_clicked();
        }
    }
}

void KToDoList::deleteGroupItem()
{
    QListWidgetItem* item=m_ui->m_leftWidget->currentItem();
    if(item&&item!=m_ui->m_leftWidget->item(m_ui->m_leftWidget->count()-1)&&item!=m_ui->m_leftWidget->item(0)&&item!=m_ui->m_leftWidget->item(1))
    {
        if (QMessageBox::Yes == QMessageBox::question(this, QStringLiteral("Remove Item"),\
                QStringLiteral("Remove 1 groupItem").arg(QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes)))
        {
            m_db.deleteDataFromGroupNames(item->text());
            m_ui->m_leftWidget->takeItem(m_ui->m_leftWidget->currentRow());
            on_m_refreshButton_clicked();
        }
    }
}

void KToDoList::showWidget()
{
    m_ui->m_shadow->resize(this->width(), this->height());
    m_ui->m_shadow->move (0,0);
    m_ui->m_shadow->setStyleSheet("background-color:rgba(0, 0, 0, 60%);");
    m_ui->m_shadow->raise();
    m_ui->m_shadow->show();
    m_ui->m_createGroupWidget->setStyleSheet("background-color:rgb(255, 255, 255);");
    m_ui->m_createGroupWidget->show();
    m_ui->m_createGroupWidget->raise();
}

void KToDoList::on_m_cancelButton_clicked()
{
    m_ui->m_groupInput->clear();
    m_ui->m_createGroupWidget->hide();
    m_ui->m_shadow->hide();
}

void KToDoList::on_m_okButton_clicked()
{
    QString text=m_ui->m_groupInput->text();
    if(text!=""&&text!="我的首页"&&text!="我的待办"&&!m_db.findGroupItem(text))
    {
        createGroupItem(m_ui->m_groupInput->text());
        m_db.insertDataToGroupNames(m_ui->m_groupInput->text());
        m_ui->m_groupInput->clear();
        m_ui->m_createGroupWidget->hide();
        m_ui->m_shadow->hide();
    }
}

void KToDoList::on_m_closeButton_clicked()
{
    on_m_cancelButton_clicked();
}

void KToDoList::on_m_groupInput_returnPressed()
{
    on_m_okButton_clicked();
}

void KToDoList::showGroup()
{
    QSqlQuery sql_query=m_db.getGroup();
    while(sql_query.next())
    {
         createGroupItem(sql_query.value(0).toString());
    }
}

void KToDoList::showGroupPage(const QString& page_name,ShowWay way)
{
    m_ui->m_itemsWidget->clear();
    bool created=false;
    QSqlQuery sql_query=m_db.getGroupData(page_name,way);
    while(sql_query.next())
    {
        if(sql_query.value(StateMember).toString()=="Y"&&!created)
        {
            created=true;
            createCheckBox("已完成",m_hasFinished);
        }
        QString name="";
        QString detail="   ";
        QString id=sql_query.value(IdMember).toString();
        for(int i=0;i<sql_query.value(PriortityLevelMember).toInt();i++)
            name+="! ";
        name+=sql_query.value(NameMember).toString();

        int set_red;

        if(sql_query.value(EndDateMember).toString()!="2099-12-31")
        {
            QDate end_date=QDate::fromString(sql_query.value(EndDateMember).toString(),"yyyy-MM-dd");
            QDate now_date=QDate::currentDate();
            detail=detail+(end_date.addDays(1)==now_date ? "昨天":"");
            detail=detail+(end_date==now_date ? "今天":"");
            detail=detail+(end_date.addDays(-1)==now_date ? "明天":"");
            detail=detail+(detail.length()==3 ? end_date.toString("yyyy-MM-dd ddd"):end_date.toString("ddd"));
            set_red += now_date>end_date ? 1:0;

            int circle_day=sql_query.value(CircleDayMember).toInt();
            detail=detail+(circle_day==1 ? " | 每天重复" : "");
            detail=detail+(circle_day==7 ? " | 每周重复" : "");
            detail=detail+(circle_day==1000 ? " | 每月重复" : "");

            detail=detail+(sql_query.value(RemindTimeMember).toString()=="2099-12-31 23:59:59" \
                           ? "" : " | 提醒时间:"+sql_query.value(RemindTimeMember).toString());
            QDateTime remind_time=QDateTime::fromString(sql_query.value(RemindTimeMember).toString(),"yyyy-MM-dd hh:mm:ss");
            QDateTime now_time=QDateTime::currentDateTime();
            set_red+= now_time>remind_time ? 2:0;

        }
        if(sql_query.value(StateMember).toString()=="Y"&&m_hasFinished||sql_query.value(StateMember).toString()=="N")
            createTodoItem(name,detail,set_red,id);
    }
    if(!created)
    {
        created=true;
        createCheckBox("已完成",m_hasFinished);
    }
}

void KToDoList::on_m_setDeadline_clicked()
{
    if(m_calendarChanged)
        m_ui->m_cldrOkButton->setEnabled(true);
    else
        m_ui->m_cldrOkButton->setEnabled(false);
    m_ui->m_setCircleDays->show();
    m_ui->m_setTime->hide();
    m_ui->m_calendar->show();
    m_ui->m_calendar2->hide();
    m_ui->m_removeEndDate->show();
    m_ui->m_removeRemindTime->hide();
}

void KToDoList::on_m_leftWidget_itemClicked(QListWidgetItem *item)
{
    if(item->text()!=""&&item->text()!=m_ui->m_midTopLabel->text()&&item->text()!="我的首页")
    {
        ShowWay way;
        switch(m_ui->m_itemRank->currentIndex())
        {
            case 0:
                way=DateShowWay;
                break;
            case 1:
                way=CreateDateShowWay;
                break;
            case 2:
                way=PriorityLevelShowWay;
                break;
        }
        m_ui->m_detailInfo->hide();
        m_ui->m_midTopLabel->setText(item->text());
        m_ui->m_picture->show();
        m_ui->m_reminder->show();
        showGroupPage(item->text(),way);
        m_ui->m_itemRank->show();
        QPoint pos=m_ui->m_refreshButton->pos();
        pos.setX(pos.x()-160);
        m_ui->m_itemRank->move(pos);
    }
    else if(item->text()!=""&&item->text()!=m_ui->m_midTopLabel->text())
    {
        m_ui->m_itemRank->hide();
        m_ui->m_detailInfo->hide();
        m_ui->m_midTopLabel->setText(item->text());
        m_ui->m_picture->show();
        m_ui->m_reminder->show();
        showHomePage();
    }
}

void KToDoList::on_m_itemsWidget_itemClicked(QListWidgetItem *item)
{
    QWidget * widget=m_ui->m_itemsWidget->itemWidget(item);
    QCheckBox* checkBox=widget->findChild<QCheckBox *>();
    if(!checkBox)
    {
        QLabel* label=widget->findChild<QLabel *>();
        m_ui->m_picture->hide();
        m_ui->m_reminder->hide();
        m_ui->m_detailInfo->show();
        m_ui->m_detailInfo->raise();
        QSqlQuery sql_query=m_db.findToDoItem(label->text().toInt());
        if(sql_query.next())
        {
            m_ui->m_itemName->setText(sql_query.value(NameMember).toString());
            if(sql_query.value(EndDateMember).toString()!="2099-12-31")
            {
                QDate end_date=QDate::fromString(sql_query.value(EndDateMember).toString(),"yyyy-MM-dd");
                m_ui->m_endDate->setDate(end_date);
            }
            else
                m_ui->m_endDate->setDate(QDate::currentDate());
            if(sql_query.value(StateMember).toString()=="N")
                m_ui->m_checkBox->setChecked(false);
            else
                m_ui->m_checkBox->setChecked(true);
            m_ui->m_setPriorityLevel->setCurrentIndex(sql_query.value(PriortityLevelMember).toInt());
            switch(sql_query.value(CircleDayMember).toInt())
            {
                case 0:
                    m_ui->m_circleDays->setCurrentIndex(0);
                    break;
                case 1:
                    m_ui->m_circleDays->setCurrentIndex(1);
                    break;
                case 7:
                    m_ui->m_circleDays->setCurrentIndex(2);
                    break;
                case 1000:
                    m_ui->m_circleDays->setCurrentIndex(3);
            }
            if(sql_query.value(RemindTimeMember).toString()!="2099-12-31 23:59:59")
            {
                QDateTime datetime=QDateTime::fromString(sql_query.value(RemindTimeMember).toString(),"yyyy-MM-dd hh:mm:ss");
                m_ui->m_remindTime->setDateTime(datetime);
            }
            else
                m_ui->m_remindTime->setDateTime(QDateTime::currentDateTime());
            m_ui->m_description->setText(sql_query.value(DescriptionMember).toString());
            m_ui->m_description->adjustSize();
            QPoint pos=m_ui->m_setPlace->pos();
            pos.setY(m_ui->m_description->size().width()+m_ui->m_description->pos().y()+2);
            m_ui->m_setPlace->move(pos);
            pos=m_ui->m_setPlace->pos();
            pos.setY(pos.y()+30);
            m_ui->m_place->move(pos);
            m_ui->m_place->setText(sql_query.value(PlaceMember).toString());
            m_ui->m_place->adjustSize();
            pos=m_ui->m_setRemarks->pos();
            pos.setY(m_ui->m_place->size().width()+m_ui->m_place->pos().y()+2);
            m_ui->m_setRemarks->move(pos);
            pos=m_ui->m_setRemarks->pos();
            pos.setY(pos.y()+30);
            m_ui->m_remarks->move(pos);
            m_ui->m_remarks->setText(sql_query.value(RemarksMember).toString());
            m_ui->m_remarks->adjustSize();
        }
        m_ui->m_itemName->adjustSize();
        QPoint pos=m_ui->m_itemName->pos();
        QSize size=m_ui->m_itemName->size();
        pos.setX(pos.x()+size.width()+20);
        pos.setY(pos.y()-5);
        m_ui->m_setItemName->move(pos);
    }
}

void KToDoList::on_m_refreshButton_clicked()
{
    ShowWay way;
    switch(m_ui->m_itemRank->currentIndex())
    {
        case 0:
            way=DateShowWay;
            break;
        case 1:
            way=CreateDateShowWay;
            break;
        case 2:
            way=PriorityLevelShowWay;
            break;
    }
    m_ui->m_picture->show();
    m_ui->m_reminder->show();
    m_ui->m_detailInfo->hide();
    if(m_ui->m_midTopLabel->text()=="我的首页")
        showHomePage();
    else
        showGroupPage(m_ui->m_midTopLabel->text(),way);
}

void KToDoList::on_m_cldrRemindTime_clicked()
{
    if(!m_calendar2Changed)
        m_ui->m_cldrOkButton->setEnabled(false);
    else
        m_ui->m_cldrOkButton->setEnabled(true);
    m_ui->m_setCircleDays->hide();
    m_ui->m_setTime->show();
    m_ui->m_calendar->hide();
    m_ui->m_calendar2->show();
    m_ui->m_removeRemindTime->show();
}

void KToDoList::on_m_calendar_clicked(const QDate &date)
{
    m_calendarChanged=true;
    m_ui->m_cldrOkButton->setEnabled(true);
}

void KToDoList::on_m_calendar2_clicked(const QDate &date)
{
    m_calendar2Changed=true;
    m_ui->m_cldrOkButton->setEnabled(true);
}

void KToDoList::on_m_removeRemindTime_clicked()
{
    m_calendar2DateTime="";
    on_m_cldrButton_clicked();
}

void KToDoList::on_m_cldrOkButton_clicked()
{
    int circleDays[4]={0,1,7,1000};
    if(m_calendarChanged)
    {
        m_circleDays=circleDays[m_ui->m_setCircleDays->currentIndex()];
        m_calendarDate=m_ui->m_calendar->selectedDate().toString("yyyy-MM-dd");
    }
    if(m_calendar2Changed)
    {
        m_calendar2DateTime=m_ui->m_calendar2->selectedDate().toString("yyyy-MM-dd");
        m_calendar2DateTime= m_calendar2DateTime+" "+m_ui->m_setTime->time().toString("hh:mm");
    }
    m_ui->m_cldrWidget->hide();
    m_calendar2Changed=false;
    m_calendarChanged=false;
}

void KToDoList::on_m_removeEndDate_clicked()
{
    m_calendarDate="";
    m_circleDays=0;
    on_m_cldrButton_clicked();
}

void KToDoList::on_m_setDescription_clicked()
{
    m_ui->m_shadow->resize(this->width(), this->height());
    m_ui->m_shadow->move (0,0);
    m_ui->m_shadow->setStyleSheet("background-color:rgba(0, 0, 0,60%);");
    m_ui->m_shadow->raise();
    m_ui->m_shadow->show();
    m_ui->m_setDetail->setStyleSheet("background-color:rgb(255, 255, 255);");
    m_ui->m_setDetail->show();
    m_ui->m_setDetail->raise();
    m_ui->m_detailTitle->setText("添加描述   ");
    m_ui->m_detailInput->setText(m_ui->m_description->text());
}

void KToDoList::on_m_setPlace_clicked()
{
    m_ui->m_shadow->resize(this->width(), this->height());
    m_ui->m_shadow->move (0,0);
    m_ui->m_shadow->setStyleSheet("background-color:rgba(0, 0, 0,60%);");
    m_ui->m_shadow->raise();
    m_ui->m_shadow->show();
    m_ui->m_setDetail->setStyleSheet("background-color:rgb(255, 255, 255);");
    m_ui->m_setDetail->show();
    m_ui->m_setDetail->raise();
    m_ui->m_detailTitle->setText("添加地点   ");
    m_ui->m_detailInput->setText(m_ui->m_place->text());
}

void KToDoList::on_m_setRemarks_clicked()
{
    m_ui->m_shadow->resize(this->width(), this->height());
    m_ui->m_shadow->move (0,0);
    m_ui->m_shadow->setStyleSheet("background-color:rgba(0, 0, 0,60%);");
    m_ui->m_shadow->raise();
    m_ui->m_shadow->show();
    m_ui->m_setDetail->setStyleSheet("background-color:rgb(255, 255, 255);");
    m_ui->m_setDetail->show();
    m_ui->m_setDetail->raise();
    m_ui->m_detailTitle->setText("添加备注   ");
    m_ui->m_detailInput->setText(m_ui->m_remarks->text());
}

void KToDoList::on_m_detailCloseButton_clicked()
{
    m_ui->m_detailInput->clear();
    m_ui->m_setDetail->hide();
    m_ui->m_shadow->hide();
}

void KToDoList::on_m_detailCancelButton_clicked()
{
    m_ui->m_detailInput->clear();
    m_ui->m_setDetail->hide();
    m_ui->m_shadow->hide();
}

void KToDoList::on_m_detailOkButton_clicked()
{
    QListWidgetItem* item=m_ui->m_itemsWidget->selectedItems()[0];
    QWidget * widget=m_ui->m_itemsWidget->itemWidget(item);
    QLabel* label=widget->findChild<QLabel *>();
    int id=label->text().toInt();
    if(m_ui->m_detailInput->text()!="")
    {
        if(m_ui->m_detailTitle->text()=="添加描述   ")
        {
            m_db.updateDataToToDo(DescriptionMember,m_ui->m_detailInput->text(),id);
        }
        else if(m_ui->m_detailTitle->text()=="添加地点   ")
        {
            m_db.updateDataToToDo(PlaceMember,m_ui->m_detailInput->text(),id);
        }
        else if(m_ui->m_detailTitle->text()=="添加备注   ")
        {
            m_db.updateDataToToDo(RemarksMember,m_ui->m_detailInput->text(),id);
        }
        else if(m_ui->m_detailTitle->text()=="修改名称   ")
        {
            m_db.updateDataToToDo(NameMember,m_ui->m_detailInput->text(),id);
        }
    }
    m_ui->m_detailInput->clear();
    m_ui->m_setDetail->hide();
    m_ui->m_shadow->hide();
}

void KToDoList::on_m_detailInput_returnPressed()
{
    on_m_detailOkButton_clicked();
}

void KToDoList::on_m_endDate_editingFinished()
{
    QListWidgetItem* item=m_ui->m_itemsWidget->selectedItems()[0];
    QWidget * widget=m_ui->m_itemsWidget->itemWidget(item);
    QLabel* label=widget->findChild<QLabel *>();
    int id=label->text().toInt();
    QString date=m_ui->m_endDate->date().toString("yyyy-MM-dd");
    m_db.updateDataToToDo(EndDateMember,date,id);
}

void KToDoList::on_m_circleDays_currentIndexChanged(int index)
{
    int circleDays[4]={0,1,7,1000};
    QListWidgetItem* item=m_ui->m_itemsWidget->selectedItems()[0];
    QWidget * widget=m_ui->m_itemsWidget->itemWidget(item);
    QLabel* label=widget->findChild<QLabel *>();
    int id=label->text().toInt();
    m_db.updateDataToToDo(CircleDayMember,QString::number(circleDays[index]),id);
}

void KToDoList::on_m_remindTime_editingFinished()
{
    QListWidgetItem* item=m_ui->m_itemsWidget->selectedItems()[0];
    QWidget * widget=m_ui->m_itemsWidget->itemWidget(item);
    QLabel* label=widget->findChild<QLabel *>();
    int id=label->text().toInt();
    QString date_time=m_ui->m_remindTime->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    m_db.updateDataToToDo(RemindTimeMember,date_time,id);
}

void KToDoList::on_m_setPriorityLevel_currentIndexChanged(int index)
{
    QListWidgetItem* item=m_ui->m_itemsWidget->selectedItems()[0];
    QWidget * widget=m_ui->m_itemsWidget->itemWidget(item);
    QLabel* label=widget->findChild<QLabel *>();
    int id=label->text().toInt();
    m_db.updateDataToToDo(PriortityLevelMember,QString::number(index),id);
}

void KToDoList::on_m_closeInfoButton_clicked()
{
    m_ui->m_picture->show();
    m_ui->m_reminder->show();
    m_ui->m_detailInfo->hide();
}

void KToDoList::on_m_setItemName_clicked()
{
    m_ui->m_shadow->resize(this->width(), this->height());
    m_ui->m_shadow->move (0,0);
    m_ui->m_shadow->setStyleSheet("background-color:rgba(0, 0, 0, 60%);");
    m_ui->m_shadow->raise();
    m_ui->m_shadow->show();
    m_ui->m_setDetail->setStyleSheet("background-color:rgb(255, 255, 255);");
    m_ui->m_setDetail->show();
    m_ui->m_setDetail->raise();
    m_ui->m_detailTitle->setText("修改名称   ");
    m_ui->m_detailInput->setText(m_ui->m_itemName->text());
}

void KToDoList::on_m_leftWidget_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem* item=m_ui->m_leftWidget->currentItem();
    if(item&&item!=m_ui->m_leftWidget->item(m_ui->m_leftWidget->count()-1)&&item!=m_ui->m_leftWidget->item(0)&&item!=m_ui->m_leftWidget->item(1))
        popMenu_in_m_homeWidget->exec(QCursor::pos());
}

void KToDoList::on_m_itemsWidget_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem* item=m_ui->m_itemsWidget->currentItem();
    QWidget * widget=m_ui->m_itemsWidget->itemWidget(item);
    if(item&&widget->findChild<QCheckBox *>()==nullptr)
        popMenu_in_m_toDoList->exec(QCursor::pos());
}

void KToDoList::on_m_itemRank_currentIndexChanged(int index)
{
    on_m_refreshButton_clicked();
}

void KToDoList::on_m_checkBox_stateChanged(int arg1)
{
    QListWidgetItem* item=m_ui->m_itemsWidget->selectedItems()[0];
    QWidget * widget=m_ui->m_itemsWidget->itemWidget(item);
    QLabel* label=widget->findChild<QLabel *>();
    int id=label->text().toInt();
    QString state="";
    QDate date=m_ui->m_endDate->date();
    switch (arg1) {
    case 0:
        state="N";
        break;
    case 2:
        state="Y";
        switch (m_ui->m_circleDays->currentIndex()) {
            case 1:
                date=date.addDays(1);
                m_db.updateDataToToDo(EndDateMember,date.toString("yyyy-MM-dd"),id);
                state="N";
                break;
            case 2:
                date=date.addDays(7);
                m_db.updateDataToToDo(EndDateMember,date.toString("yyyy-MM-dd"),id);
                state="N";
                break;
            case 3:
                date=date.addMonths(1);
                m_db.updateDataToToDo(EndDateMember,date.toString("yyyy-MM-dd"),id);
                state="N";
                break;
        }
        break;
    }
    m_db.updateDataToToDo(StateMember,state,id);
    on_m_refreshButton_clicked();
}

void KToDoList::setHasFinished(int a)
{
    if(a==2)
        m_hasFinished=true;
    else
        m_hasFinished=false;
    on_m_refreshButton_clicked();
}

void KToDoList::setNotArranged(int a)
{
    if(a==2)
        m_notArranged=true;
    else
        m_notArranged=false;
    on_m_refreshButton_clicked();
}

void KToDoList::setOverdue(int a)
{
    if(a==2)
        m_overdue=true;
    else
        m_overdue=false;
    on_m_refreshButton_clicked();
}

void KToDoList::setInsideSeven(int a)
{
    if(a==2)
        m_insideSeven=true;
    else
        m_insideSeven=false;
    on_m_refreshButton_clicked();
}

void KToDoList::setLater(int a)
{
    if(a==2)
        m_later=true;
    else
        m_later=false;
    on_m_refreshButton_clicked();
}

