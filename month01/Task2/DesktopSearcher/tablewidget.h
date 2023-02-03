//TableWidget类，继承QTableWidget，加入右键菜单和删除动作

#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QMouseEvent>
class TableWidget : public QTableWidget
{
    Q_OBJECT
public:
    TableWidget(QWidget *parent = nullptr);
    TableWidget(int rows, int columns, QWidget *parent = nullptr);
    ~TableWidget();
    QAction *m_delAction;

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QMenu *m_contextMenu;

};


#endif // TABLEWIDGET_H
