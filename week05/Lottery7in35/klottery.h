#ifndef KLOTTERY_H
#define KLOTTERY_H

#include <QMainWindow>
#include <QVector>

namespace Ui {
class KLottery;
}

class KLottery : public QMainWindow
{
    Q_OBJECT

public:
    explicit KLottery(QWidget *parent = 0);
    ~KLottery();

private slots:
    void on_m_btn0_clicked();

    void on_m_btn1_clicked();

    void on_m_btn2_clicked();

    void on_m_btn3_clicked();

    void on_m_btn4_clicked();

    void on_m_btn5_clicked();

    void on_m_btn6_clicked();

    void on_m_btn7_clicked();

    void on_m_btn8_clicked();

    void on_m_btn9_clicked();

    void on_m_btnOK_clicked();

    void on_m_btnClear_clicked();

    void on_m_btnOpen_clicked();

private:
    Ui::KLottery *m_ui;
    QVector<int> m_inputNum;
    int m_newNumber=0;
};

#endif // KLOTTERY_H
