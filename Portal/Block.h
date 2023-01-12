#pragma once

#include <QPixmap>
#include <QString>
#include <QJsonObject>

class Block {
public:
	enum Type {
		EMPTY, ALL, FULL, FLOOR, COMPONENT
	};

private:
	static QMap<Type, QString> Types;

	static int BaseBlockCode;

protected:
	static QString FilePath;

	QString block_name;
	Type block_type;
	QPixmap block_img;
	QString block_img_path;

	int block_code;

public:
	Block();
	Block(const QString& name, Type type, QString imgPath = QString());

	// 将对象存储为json
	virtual void write(QJsonObject& json);
	virtual void read(const QJsonObject& json);

	bool saveInfo();	// 保存信息
	void loadInfo();	// 加载信息

	static void setBaseBlockCodeCount(int code);
	static Type TypeFromString(const QString& text);
	static QString StringFromType(Type type);

	int BlockCode() const;
	QString BlockCodeText() const;
	QString BlockName() const;
	Type BlockType() const;
	QString BlockTypeText() const;
	QStringList BlockTypesText() const;
	QPixmap BlockImg() const;
};
Q_DECLARE_METATYPE(Block)
