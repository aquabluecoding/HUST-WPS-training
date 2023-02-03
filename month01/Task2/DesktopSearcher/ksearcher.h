#ifndef KSEARCHER_H
#define KSEARCHER_H

#include <QDialog>
#include <QDir>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStandardPaths>
#include <QShortcut>
#include <QHotkey>
#include <QDebug>

#include "tablewidget.h"
#include "pinyinhelper.h"


class KSearcher : public QDialog
{
    Q_OBJECT

public:
    explicit KSearcher(QWidget *parent = 0);

public slots:
    void switchVisible();

private slots:
    void browse();
    void find();
    void openFileOfItem(int row, int column);

    void onActionDelete();

private:
    QStringList findContent(const QStringList &files, const QString &text);
    void showFiles(const QStringList &files);
    QPushButton *createButton(const QString &text, const char *member);
    QComboBox *createComboBox(const QString &text = QString());
    void createFilesTable();

    QComboBox *m_fileComboBox;
    QComboBox *m_directoryComboBox;
    QLabel *m_fileLabel;
    QLabel *m_directoryLabel;
    QLabel *m_filesFoundLabel;
    QPushButton *m_browseButton;
    QPushButton *m_findButton;
    TableWidget *m_filesTable;
    QDir m_currentDir;
};

#endif // KSEARCHER_H
