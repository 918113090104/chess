#include "plistreader.h"

PlistReader::PlistReader()
{

}

bool PlistReader::read(QIODevice *device)
{
    xmlReader.setDevice(device);  //QIODevice 是读写的接口
    //readNextStartElement() 在当前元素内，读取到下一个开始元素，若找到开始元素，就返回真，否则返回假
    if (xmlReader.readNextStartElement())
    {
        if (xmlReader.name() == "plist" && xmlReader.attributes().value("version") == "1.0")
             readPlist();
        else
            xmlReader.raiseError("The file is not an PList version 1.0 file.");
    }

    return xmlReader.error();
}

const QList<QVariant> PlistReader::data() const
{
    return date;
}

//返回错误信息
QString PlistReader::errorString() const
{
    return QString("%1\nLine %2, column %3")
            .arg(xmlReader.errorString())
            .arg(xmlReader.lineNumber())
            .arg(xmlReader.columnNumber());
}

//读取plist元素
void PlistReader::readPlist()
{
    //错误则打印错误的信息
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "plist");

    while (xmlReader.readNextStartElement())
    {
        if (xmlReader.name() == "array")
             readArray(date);
        else if (xmlReader.name() == "dict")
             readDict(date);
        else
            xmlReader.skipCurrentElement();
    }
}

//读取dict元素
void PlistReader::readDict(QList<QVariant> &array)
{
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "dict");

    QMap<QString, QVariant> dict;
    while (xmlReader.readNextStartElement())
    {
        // 这里只处理key,在readKey中,一次默认读取一对键值
        if (xmlReader.name() == "key")
             readKey(dict);
        else
            xmlReader.skipCurrentElement();
    }

    array.push_back(dict);
}

//读取array元素
void PlistReader::readArray(QList<QVariant> &array)
{
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "array");

    while (xmlReader.readNextStartElement())
    {
        if (xmlReader.name() == "array")
        {
            QList<QVariant> subArray;
             readArray(subArray);   //递归读取多对array
            array.push_back(subArray); //将读取的值放入array
        }
        else if (xmlReader.name() == "dict")
        {
             readDict(array);
        }
        else
        {
            xmlReader.skipCurrentElement();
        }
    }
}

//读取key元素
void PlistReader::readKey(QMap<QString, QVariant> &dict)
{
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "key");

    // 这里一次读取一个键值对
    QString key = xmlReader.readElementText();
    Q_ASSERT(xmlReader.readNextStartElement());
    QString value = xmlReader.readElementText();

    dict.insertMulti(key,value);
}



