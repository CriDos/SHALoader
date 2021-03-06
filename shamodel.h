#pragma once
#include <QObject>
#include <QVector>
#include <QSharedPointer>
#include <QVariantMap>
#include <QVariantList>
#include <QStack>
#include <QJsonDocument>

class SHAModel : public QObject
{
    Q_OBJECT

public:
    enum class ParseDataType {
        Null = 0,
        Int,
        Cast_Int,
        Str,
        Cast_Str,
        Real,
        Cast_Real,
        StrList,
        Array
    };
    Q_ENUM(ParseDataType)

    enum LineType {
        Null,
        Undefined,
        Ignore,
        Make,
        Ver,
        Add,
        OpenBlock,
        CloseBlock,
        Link,
        Point,
        HideProp,
        Prop,
        BEGIN_SDK,
        END_SDK,
        Empty
    };
    Q_ENUM(LineType)

    enum ParseType {
        BeginToEnd,
        EndToBegin
    };
    Q_ENUM(ParseType)

private:
    QStringList m_content;
    QString m_filePath;

public:
    explicit SHAModel(const QString &filePath, QObject *parent = 0);
    explicit SHAModel(QObject *parent = 0);

public:
    bool loadSha();
    QJsonDocument toJson();
    QByteArray toBson();
    bool saveJsonToFile(const QString &filePath, QJsonDocument::JsonFormat format = QJsonDocument::Indented);
    bool saveJsonToFile(QJsonDocument::JsonFormat format = QJsonDocument::Indented);
    QString getFilePath() const;
    void setFilePath(const QString &filePath);

private:
    QString findBlock(const QString &line, const QString &beginTok,
                      const QString &endTok);
    QStringList findMultiBlock(QString &str, const QString &beginTok,
                               const QString &endTok,
                               bool cutBlock = false,
                               bool removeTok = false);
    QPair<QString, QString> splitSLine(const QString &sline, const QChar &del, ParseType type = BeginToEnd);
    ParseDataType getValueType(const QString &svalue);

    QVariantMap linkToVariantMap(const QString &sline);
    QVariantMap propToVariantMap(const QString &sline);
    LineType getLineType(const QString &sline);
    LineType getLineType(const QStringList &content, int idx);

    QVariantMap parseHeader();
    QVariantList parseElements(int begin = 0, int _size = 0, int *prev = 0);
};
