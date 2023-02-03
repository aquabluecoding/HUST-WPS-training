#include "TableWidget.h"

TableWidget::TableWidget(QWidget *parent)
: QTableWidget(parent)
{
    //创建一个菜单
    m_contextMenu = new QMenu;
    m_delAction = new QAction("del Item",this);
    m_contextMenu->addAction(m_delAction);
}

TableWidget::TableWidget(int rows, int columns, QWidget *parent)
: QTableWidget(rows, columns, parent)
{
    m_contextMenu = new QMenu;
    m_delAction = new QAction("del Item",this);
    m_contextMenu->addAction(m_delAction);
}

TableWidget::~TableWidget() {}

void TableWidget::mousePressEvent(QMouseEvent *event)
{
    //确保右键点击，然后跳出菜单.
    if (event->button() == Qt::RightButton)
    {
        m_contextMenu->exec(event->globalPos());
    }
    //要继续保留QListWidget原有的点击事件.
    QTableWidget::mousePressEvent(event);
}
