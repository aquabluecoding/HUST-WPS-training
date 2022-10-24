#include "klottery.h"
#include "ui_klottery.h"

KLottery::KLottery(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::KLottery)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_ui->setupUi(this);
    m_inputNum.reserve(7);
    m_ui->m_newNumber->setNum(0);
}

KLottery::~KLottery()
{
    delete m_ui;
}

void KLottery::on_m_btn0_clicked()
{
    int a=m_newNumber*10;
    if(a>=1&&a<=35)
        m_newNumber=a;
    m_ui->m_newNumber->setNum(m_newNumber);
}

void KLottery::on_m_btn1_clicked()
{
    int a=m_newNumber*10+1;
    if(a>=1&&a<=35)
        m_newNumber=a;
    m_ui->m_newNumber->setNum(m_newNumber);
}

void KLottery::on_m_btn2_clicked()
{
    int a=m_newNumber*10+2;
    if(a>=1&&a<=35)
        m_newNumber=a;
    m_ui->m_newNumber->setNum(m_newNumber);
}

void KLottery::on_m_btn3_clicked()
{
    int a=m_newNumber*10+3;
    if(a>=1&&a<=35)
        m_newNumber=a;
    m_ui->m_newNumber->setNum(m_newNumber);
}

void KLottery::on_m_btn4_clicked()
{
    int a=m_newNumber*10+4;
    if(a>=1&&a<=35)
        m_newNumber=a;
    m_ui->m_newNumber->setNum(m_newNumber);
}

void KLottery::on_m_btn5_clicked()
{
    int a=m_newNumber*10+5;
    if(a>=1&&a<=35)
        m_newNumber=a;
    m_ui->m_newNumber->setNum(m_newNumber);
}

void KLottery::on_m_btn6_clicked()
{
    int a=m_newNumber*10+6;
    if(a>=1&&a<=35)
        m_newNumber=a;
    m_ui->m_newNumber->setNum(m_newNumber);
}

void KLottery::on_m_btn7_clicked()
{
    int a=m_newNumber*10+7;
    if(a>=1&&a<=35)
        m_newNumber=a;
    m_ui->m_newNumber->setNum(m_newNumber);
}

void KLottery::on_m_btn8_clicked()
{
    int a=m_newNumber*10+8;
    if(a>=1&&a<=35)
        m_newNumber=a;
    m_ui->m_newNumber->setNum(m_newNumber);
}

void KLottery::on_m_btn9_clicked()
{
    int a=m_newNumber*10+9;
    if(a>=1&&a<=35)
        m_newNumber=a;
    m_ui->m_newNumber->setNum(m_newNumber);
}

void KLottery::on_m_btnOK_clicked()
{
    if(m_inputNum.count(m_newNumber)==0 && m_inputNum.size()<7 && m_newNumber>0)
        m_inputNum.push_back(m_newNumber);
    QString str="";
    for(QVector<int>::iterator it=m_inputNum.begin();it!=m_inputNum.end();it++)
    {
        str+=QString::number(*it);
        str+=" ";
    }
    m_ui->m_allNumber->setText(str);
    m_newNumber=0;
    m_ui->m_newNumber->setNum(m_newNumber);
}

void KLottery::on_m_btnClear_clicked()
{
    m_newNumber=0;
    m_ui->m_newNumber->setNum(m_newNumber);
}

void KLottery::on_m_btnOpen_clicked()
{
    int visited[35]={0};
    int hitNum=0;
    QString str="";
    qsrand(time(NULL));
    for(int i=0;i<7;i++)
    {
        int randNum=0;
        do{
            randNum=qrand()%35;
        }while(visited[randNum]);
        visited[randNum]=1;
        str+=QString::number(randNum+1);
        str+=" ";
        hitNum+=m_inputNum.count(randNum+1);
    }
    m_ui->m_targetNumber->setText(str);
    switch(hitNum)
    {
        case 0:
            m_ui->m_result->setText("谢谢参与!");
            break;
        case 1:
            m_ui->m_result->setText("恭喜获得奖金5元！");
            break;
        case 2:
            m_ui->m_result->setText("恭喜获得奖金50元！");
            break;
        case 3:
            m_ui->m_result->setText("恭喜获得奖金100元！");
            break;
        case 4:
            m_ui->m_result->setText("恭喜获得奖金500元！");
            break;
        case 5:
            m_ui->m_result->setText("恭喜获得大奖100,000元！");
            break;
        case 6:
            m_ui->m_result->setText("恭喜获得大奖300,000元！");
            break;
        case 7:
            m_ui->m_result->setText("恭喜获得超级大奖5,000,000元！");
            break;
    }
}

