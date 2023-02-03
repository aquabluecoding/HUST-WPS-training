#include "ksearcher.h"
#include <QtWidgets>


KSearcher::KSearcher(QWidget *parent) :
    QDialog(parent)
{
    //设置窗体最大化、最小化和顶层显示
    setWindowFlags(Qt::Dialog |
                   Qt::WindowMinimizeButtonHint |
                   Qt::WindowMaximizeButtonHint |
                   Qt::WindowCloseButtonHint    |
                   Qt::WindowStaysOnTopHint);
    //初始化各个组件
    m_browseButton = createButton(tr("&Browse..."), SLOT(browse()));
    m_findButton = createButton(tr("&Find"), SLOT(find()));
    m_browseButton->setFocusPolicy(Qt::NoFocus);
    m_findButton->setShortcut(Qt::Key_Return);
    m_fileComboBox = createComboBox(tr(""));
    m_directoryComboBox = createComboBox(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    m_fileLabel = new QLabel(tr("Named:"));
    m_directoryLabel = new QLabel(tr("In directory:"));
    m_filesFoundLabel = new QLabel;
    createFilesTable();
    //初始化组件布局
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(m_findButton);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(m_fileLabel, 0, 0);
    mainLayout->addWidget(m_fileComboBox, 0, 1, 1, 2);
    mainLayout->addWidget(m_directoryLabel, 1, 0);
    mainLayout->addWidget(m_directoryComboBox, 1, 1);
    mainLayout->addWidget(m_browseButton, 1, 2);
    mainLayout->addWidget(m_filesTable, 2, 0, 1, 3);
    mainLayout->addWidget(m_filesFoundLabel, 3, 0, 1, 3);
    mainLayout->addLayout(buttonsLayout, 4, 0, 1, 3);
    setLayout(mainLayout);

    setWindowTitle(tr("Auxiliary Searching Tool"));
    resize(700, 300);
}

//槽函数，调整窗口的可见性，被Alt+Space调用
void KSearcher::switchVisible()
{
    if(isVisible())
        setVisible(false);
    else
        setVisible(true);
}

//槽函数，选择目标文件夹，被按钮调用
void KSearcher::browse()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                               tr("Set target directory"),
                               QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    if (!directory.isEmpty())
    {
        if (m_directoryComboBox->findText(directory) == -1)
            m_directoryComboBox->addItem(directory);
        m_directoryComboBox->setCurrentIndex(m_directoryComboBox->findText(directory));
    }
}

//静态工具函数，更新comboBox内的输入
static void updateComboBox(QComboBox *comboBox)
{
    if (comboBox->findText(comboBox->currentText()) == -1)
        comboBox->addItem(comboBox->currentText());
}

//静态工具函数，生成用于Wildcard形式的模糊匹配字符串
static QString fuzzyMatchWildcard(const QString &name)
{
    QString ret = "*";
    for(int i = 0; i < name.size(); i++)
        ret.append(name.mid(i,1)+"*");
    return ret;
}

//静态工具函数，生成正则表达式形式的模糊匹配字符串
static QString fuzzyMatchRegExp(const QString &name)
{
    QString ret = "(.*)(";
    int i;
    for(i = 0; i < name.size()-1; i++)
    {
        ret.append(name.mid(i,1)+")(.*)(");
    }
    ret.append(name.mid(i,1)+")(.*)");
    return ret;
}

//槽函数，查找文件
void KSearcher::find()
{
    m_filesTable->setRowCount(0);
    //读取用户输入
    QString name = m_fileComboBox->currentText();
    QString path = m_directoryComboBox->currentText();
    //更新ComboBox
    updateComboBox(m_fileComboBox);
    updateComboBox(m_directoryComboBox);

    m_currentDir = QDir(path);
    QStringList files, nameFilters;

    if (name.isEmpty()) //输入为空
    {
        nameFilters.append("*");
        files = m_currentDir.entryList(nameFilters, QDir::Dirs | QDir::Files |
                                     QDir::NoSymLinks | QDir::NoDotAndDotDot);
    }
    else //输入不为空
    {
        QString nameWildcard = fuzzyMatchWildcard(name); //模糊匹配
        nameFilters = QStringList(nameWildcard);
        files = m_currentDir.entryList(nameFilters, QDir::Dirs | QDir::Files |
                                    QDir::NoSymLinks | QDir::NoDotAndDotDot);
        //下面处理拼音首字母查找的情况
        QStringList cnStrings = m_currentDir.entryList(QStringList("*"),
                                                       QDir::Dirs | QDir::Files |
                                                       QDir::NoSymLinks | QDir::NoDotAndDotDot);
        //QMap <原名字符串，拼音首字母用大写替换后的字符串>
        QMap<QString, QString> cnCharToInitial;
        foreach(QString str, cnStrings)
        {
            if(str.contains(QRegExp("[\\x4e00-\\x9fa5]+"))) //包含中文汉字
            {
                QString initial = QString::fromStdString(PinYinHelper::GetChineseSpell(str));
                cnCharToInitial.insert(str, initial);
            }
        }
        QString nameRegExp = fuzzyMatchRegExp(name).toUpper(); //注意要转大写
        QRegularExpression rx(nameRegExp); //生成正则
        QRegularExpressionMatch match; //包含匹配结果的类
        for (auto it = cnCharToInitial.begin(); it != cnCharToInitial.end(); it++)
        {
            match = rx.match(it.value());
            if(match.hasMatch())
                files.append(it.key());
        }
        //去重，防止原始匹配和拼音首字母匹配都选中了该文件
        QStringList distin;
        for(int i = 0; i < files.length(); i++)
           if(!distin.contains(files[i]))
              distin.append(files[i]);
        files = distin;
    }
    //显示到TableWidget
    showFiles(files);
}

//生成文件显示内容
void KSearcher::showFiles(const QStringList &files)
{
    for (int i = 0; i < files.size(); ++i)
    {
        QFile file(m_currentDir.absoluteFilePath(files[i]));
        QFileInfo file_info(file);
        qint64 size = file_info.size();
        QFileIconProvider icon_provider;
        //文件名（带图标）
        QTableWidgetItem *nameItem = new QTableWidgetItem(
                    icon_provider.icon(file_info), files[i]);
        //文件路径
        QTableWidgetItem *pathItem = new QTableWidgetItem(QFileInfo(file).path());
        pathItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        //文件大小
        QTableWidgetItem *sizeItem;
        if (size > 0)
            sizeItem = new QTableWidgetItem(tr("%1 KB").arg(int((size + 1023) / 1024)));
        else //文件夹不显示大小
            sizeItem = new QTableWidgetItem("");
        sizeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        int row = m_filesTable->rowCount();
        m_filesTable->insertRow(row);
        m_filesTable->setItem(row, 0, nameItem);
        m_filesTable->setItem(row, 1, pathItem);
        m_filesTable->setItem(row, 2, sizeItem);
    }
    //搜索结果显示
    m_filesFoundLabel->setText(tr("%1 file(s) found").arg(files.size()) +
                             (" (Double click on a file to open it)"));
}

//工具函数，生成按钮并绑定槽函数
QPushButton *KSearcher::createButton(const QString &text, const char *member)
{
    QPushButton *button = new QPushButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

//工具函数, 生成组合框
QComboBox *KSearcher::createComboBox(const QString &text)
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return comboBox;
}

//生成显示文件的窗口TableWidget，继承于QTableWidget，
//重写了mousePressEvent方法
void KSearcher::createFilesTable()
{
    m_filesTable = new TableWidget(0, 3);
    m_filesTable->setContextMenuPolicy(Qt::CustomContextMenu);
    m_filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_filesTable->setSelectionMode(QAbstractItemView::SingleSelection);

    QStringList header;
    header << tr("Name") << tr("Path") << tr("Size");
    m_filesTable->setHorizontalHeaderLabels(header);
    m_filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_filesTable->verticalHeader()->hide();
    m_filesTable->setShowGrid(false);
    //双击打开文件
    connect(m_filesTable, SIGNAL(cellActivated(int,int)),
            this, SLOT(openFileOfItem(int,int)));
    //删除文件
    connect(m_filesTable->m_delAction, SIGNAL(triggered()), this, SLOT(onActionDelete()));
}

//槽函数，打开文件
void KSearcher::openFileOfItem(int row, int /* column */)
{
    QTableWidgetItem *item = m_filesTable->item(row, 0);
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_currentDir.absoluteFilePath(item->text())));
}

//槽函数，删除文件
void KSearcher::onActionDelete()
{
    //获取当前选中的Item
    QList<QTableWidgetItem*> items = this->m_filesTable->selectedItems();
    if(!items.empty())
    {
        QString path = items.at(1)->text() + "/" + items.at(0)->text();
        qDebug()<<"delete path: "<<path<<endl;
        QFileInfo fileInfo(path);
        //弹出询问对话框
        if (QMessageBox::Yes == QMessageBox::question(this, QStringLiteral("Remove Item"),
            QStringLiteral("Are you sure you want to delete this file/directory? "),
            QMessageBox::Yes, QMessageBox::Cancel))
        {
            if (fileInfo.isFile())//如果是文件
                QFile::remove(path);
            else if (fileInfo.isDir())//如果是文件夹
            {
                QDir qDir(path);
                qDir.removeRecursively();
            }
            int row = this->m_filesTable->row(items.at(0));
            this->m_filesTable->removeRow(row);
            items.clear();
        }
    }
    else
        QMessageBox::warning(this,"Warning", "Please select a row before delete the item!");
}

