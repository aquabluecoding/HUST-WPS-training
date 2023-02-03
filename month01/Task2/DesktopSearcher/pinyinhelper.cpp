#include "pinyinhelper.h"

std::string PinYinHelper::GetChineseSpell(const QString& src)
{
    QTextCodec *codec4gbk = QTextCodec::codecForName("GBK");          //获取qt提供的gbk的解码器
    QByteArray buf = codec4gbk->fromUnicode((QString)src.unicode());  //qt用的unicode，转成gbk

    unsigned char ucHigh, ucLow;
    int  nCode;
    std::string strPinYin;
    for (int i = 0; i < buf.length(); i++)
    {
        ucHigh = buf[i];
        if (ucHigh < 0x80)//英文字母
        {
            strPinYin.push_back((char)buf[i]);
            continue;
        }
        ucLow = buf[i + 1];
        if (ucHigh < 0xa1 || ucLow < 0xa1)
        {
            continue;
        }
        else
        {
            nCode = (ucHigh - 0xa0) * 100 + ucLow - 0xa0;
        }
        strPinYin.append(FirstLetter(nCode).c_str());
        i++;
    }
    return strPinYin;
}

std::string PinYinHelper::FirstLetter(int nCode)
{
    if (nCode >= 1601 && nCode < 1637) return "A";
    if (nCode >= 1637 && nCode < 1833) return "B";
    if (nCode >= 1833 && nCode < 2078) return "C";
    if (nCode >= 2078 && nCode < 2274) return "D";
    if (nCode >= 2274 && nCode < 2302) return "E";
    if (nCode >= 2302 && nCode < 2433) return "F";
    if (nCode >= 2433 && nCode < 2594) return "G";
    if (nCode >= 2594 && nCode < 2787) return "H";
    if (nCode >= 2787 && nCode < 3106) return "J";
    if (nCode >= 3106 && nCode < 3212) return "K";
    if (nCode >= 3212 && nCode < 3472) return "L";
    if (nCode >= 3472 && nCode < 3635) return "M";
    if (nCode >= 3635 && nCode < 3722) return "N";
    if (nCode >= 3722 && nCode < 3730) return "O";
    if (nCode >= 3730 && nCode < 3858) return "P";
    if (nCode >= 3858 && nCode < 4027) return "Q";
    if (nCode >= 4027 && nCode < 4086) return "R";
    if (nCode >= 4086 && nCode < 4390) return "S";
    if (nCode >= 4390 && nCode < 4558) return "T";
    if (nCode >= 4558 && nCode < 4684) return "W";
    if (nCode >= 4684 && nCode < 4925) return "X";
    if (nCode >= 4925 && nCode < 5249) return "Y";
    if (nCode >= 5249 && nCode < 5590) return "Z";
    return "";
}
