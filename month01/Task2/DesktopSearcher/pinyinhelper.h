//用于把含有中文的字符串中的汉字替换为拼音首字母（大写）

#ifndef PINYINHELPER_H
#define PINYINHELPER_H

#include <string>
#include <QString>
#include <QTextCodec>
#include <vector>
#include <qtextcodec.h>

class PinYinHelper
{
public:
    static std::string GetChineseSpell(const QString& src);
private:
    static std::string FirstLetter(int nCode);
};

#endif // PINYINHELPER_H
