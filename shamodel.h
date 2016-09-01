#pragma once

#include <QObject>
#include <QVector>

class SHAModel : public QObject {
	Q_OBJECT

public:
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
		Prop,
		BEGIN_SDK,
		END_SDK,
		Empty
	};
	Q_ENUM(LineType)


private:
	QStringList m_fileContent;
	QString m_filePath;

private:
	QString m_package;
	QString m_version;

public:
	explicit SHAModel(const QString &filePath, QObject *parent = 0);
	bool loadSha();

private:
	static QString findBlock(const QString &line, const QString &beginTok, const QString &endTok);
	static QStringList findMultiBlock(QString &str, const QString &beginTok,
		const QString &endTok, bool cutBlock = false,
		bool removeTok = false);
	static void getLinkParams(const QString &line);
	static LineType getTypeLine(const QString &line);

	bool loadFile();
	bool parse();
};
