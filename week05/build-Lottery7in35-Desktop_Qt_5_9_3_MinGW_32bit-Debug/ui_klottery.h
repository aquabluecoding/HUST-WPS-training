/********************************************************************************
** Form generated from reading UI file 'klottery.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KLOTTERY_H
#define UI_KLOTTERY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KLottery
{
public:
    QWidget *centralWidget;
    QPushButton *m_btn1;
    QPushButton *m_btnOpen;
    QLabel *m_targetNumber;
    QLabel *m_newNumber;
    QPushButton *m_btn2;
    QPushButton *m_btn3;
    QPushButton *m_btn4;
    QPushButton *m_btn6;
    QPushButton *m_btn5;
    QPushButton *m_btn7;
    QPushButton *m_btn9;
    QPushButton *m_btn8;
    QPushButton *m_btnOK;
    QPushButton *m_btnClear;
    QPushButton *m_btn0;
    QLabel *m_allNumber;
    QLabel *m_result;
    QPushButton *m_btnClose;

    void setupUi(QMainWindow *KLottery)
    {
        if (KLottery->objectName().isEmpty())
            KLottery->setObjectName(QStringLiteral("KLottery"));
        KLottery->resize(697, 471);
        centralWidget = new QWidget(KLottery);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        m_btn1 = new QPushButton(centralWidget);
        m_btn1->setObjectName(QStringLiteral("m_btn1"));
        m_btn1->setGeometry(QRect(10, 140, 101, 41));
        m_btnOpen = new QPushButton(centralWidget);
        m_btnOpen->setObjectName(QStringLiteral("m_btnOpen"));
        m_btnOpen->setGeometry(QRect(10, 340, 321, 41));
        m_targetNumber = new QLabel(centralWidget);
        m_targetNumber->setObjectName(QStringLiteral("m_targetNumber"));
        m_targetNumber->setGeometry(QRect(10, 400, 321, 51));
        m_targetNumber->setFrameShape(QFrame::StyledPanel);
        m_targetNumber->setFrameShadow(QFrame::Plain);
        m_newNumber = new QLabel(centralWidget);
        m_newNumber->setObjectName(QStringLiteral("m_newNumber"));
        m_newNumber->setGeometry(QRect(10, 80, 161, 41));
        m_newNumber->setFrameShape(QFrame::StyledPanel);
        m_newNumber->setFrameShadow(QFrame::Plain);
        m_btn2 = new QPushButton(centralWidget);
        m_btn2->setObjectName(QStringLiteral("m_btn2"));
        m_btn2->setGeometry(QRect(120, 140, 101, 41));
        m_btn3 = new QPushButton(centralWidget);
        m_btn3->setObjectName(QStringLiteral("m_btn3"));
        m_btn3->setGeometry(QRect(230, 140, 101, 41));
        m_btn4 = new QPushButton(centralWidget);
        m_btn4->setObjectName(QStringLiteral("m_btn4"));
        m_btn4->setGeometry(QRect(10, 190, 101, 41));
        m_btn6 = new QPushButton(centralWidget);
        m_btn6->setObjectName(QStringLiteral("m_btn6"));
        m_btn6->setGeometry(QRect(230, 190, 101, 41));
        m_btn5 = new QPushButton(centralWidget);
        m_btn5->setObjectName(QStringLiteral("m_btn5"));
        m_btn5->setGeometry(QRect(120, 190, 101, 41));
        m_btn7 = new QPushButton(centralWidget);
        m_btn7->setObjectName(QStringLiteral("m_btn7"));
        m_btn7->setGeometry(QRect(10, 240, 101, 41));
        m_btn9 = new QPushButton(centralWidget);
        m_btn9->setObjectName(QStringLiteral("m_btn9"));
        m_btn9->setGeometry(QRect(230, 240, 101, 41));
        m_btn8 = new QPushButton(centralWidget);
        m_btn8->setObjectName(QStringLiteral("m_btn8"));
        m_btn8->setGeometry(QRect(120, 240, 101, 41));
        m_btnOK = new QPushButton(centralWidget);
        m_btnOK->setObjectName(QStringLiteral("m_btnOK"));
        m_btnOK->setGeometry(QRect(10, 290, 101, 41));
        m_btnClear = new QPushButton(centralWidget);
        m_btnClear->setObjectName(QStringLiteral("m_btnClear"));
        m_btnClear->setGeometry(QRect(230, 290, 101, 41));
        m_btn0 = new QPushButton(centralWidget);
        m_btn0->setObjectName(QStringLiteral("m_btn0"));
        m_btn0->setGeometry(QRect(120, 290, 101, 41));
        m_allNumber = new QLabel(centralWidget);
        m_allNumber->setObjectName(QStringLiteral("m_allNumber"));
        m_allNumber->setGeometry(QRect(10, 10, 621, 51));
        m_allNumber->setFrameShape(QFrame::StyledPanel);
        m_allNumber->setFrameShadow(QFrame::Plain);
        m_result = new QLabel(centralWidget);
        m_result->setObjectName(QStringLiteral("m_result"));
        m_result->setGeometry(QRect(390, 140, 241, 171));
        m_result->setFrameShape(QFrame::StyledPanel);
        m_result->setFrameShadow(QFrame::Plain);
        m_btnClose = new QPushButton(centralWidget);
        m_btnClose->setObjectName(QStringLiteral("m_btnClose"));
        m_btnClose->setGeometry(QRect(650, 10, 41, 41));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(48);
        m_btnClose->setFont(font);
        KLottery->setCentralWidget(centralWidget);

        retranslateUi(KLottery);
        QObject::connect(m_btnClose, SIGNAL(clicked()), KLottery, SLOT(close()));

        QMetaObject::connectSlotsByName(KLottery);
    } // setupUi

    void retranslateUi(QMainWindow *KLottery)
    {
        KLottery->setWindowTitle(QApplication::translate("KLottery", "KLottery", Q_NULLPTR));
        m_btn1->setText(QApplication::translate("KLottery", "1", Q_NULLPTR));
        m_btnOpen->setText(QApplication::translate("KLottery", "\345\274\200\345\245\226", Q_NULLPTR));
        m_targetNumber->setText(QString());
        m_newNumber->setText(QString());
        m_btn2->setText(QApplication::translate("KLottery", "2", Q_NULLPTR));
        m_btn3->setText(QApplication::translate("KLottery", "3", Q_NULLPTR));
        m_btn4->setText(QApplication::translate("KLottery", "4", Q_NULLPTR));
        m_btn6->setText(QApplication::translate("KLottery", "6", Q_NULLPTR));
        m_btn5->setText(QApplication::translate("KLottery", "5", Q_NULLPTR));
        m_btn7->setText(QApplication::translate("KLottery", "7", Q_NULLPTR));
        m_btn9->setText(QApplication::translate("KLottery", "9", Q_NULLPTR));
        m_btn8->setText(QApplication::translate("KLottery", "8", Q_NULLPTR));
        m_btnOK->setText(QApplication::translate("KLottery", "OK", Q_NULLPTR));
        m_btnClear->setText(QApplication::translate("KLottery", "Clear", Q_NULLPTR));
        m_btn0->setText(QApplication::translate("KLottery", "0", Q_NULLPTR));
        m_allNumber->setText(QString());
        m_result->setText(QString());
        m_btnClose->setText(QApplication::translate("KLottery", "\303\227", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class KLottery: public Ui_KLottery {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KLOTTERY_H
