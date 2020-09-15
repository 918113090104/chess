#ifndef PLISTREADER_H
#define PLISTREADER_H

#include<QXmlStreamReader>
#include<QIODevice>
#include<QVariant>
#include<QMap>

//读取.plist文件
class PlistReader
{
public:
    PlistReader();
    bool read(QIODevice *device);
    const QList<QVariant> data() const;
    QString errorString() const;

private:
    void readPlist();
    void readDict(QList<QVariant> &array);
    void readArray(QList<QVariant> &array);
    void readKey(QMap<QString, QVariant> &dict);

private:
    QXmlStreamReader xmlReader;
    QList<QVariant> date;

};

#endif // PLISTREADER_H
