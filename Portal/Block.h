#pragma once
#include <QString>
#include <QJsonObject>

class Block {
public:
	enum BlockType {
		EMPTY, FULL, FLOOR, COMPONENT
	};

private:
	QString blockTypeText();
	static int BaseBlockCode;

protected:
	static QString FilePath;

	QString block_name;
	BlockType block_type;
	int block_code;

public:
	Block();
	Block(const QString& name, BlockType type);

	// 将对象存储为json
	virtual void write(QJsonObject& json);
	virtual void read(const QJsonObject& json);

	bool saveInfo();	// 保存信息
	void loadInfo();	// 加载信息

	static void setBaseBlockCodeCount(int code);

	int BlockCode();
	QString BlockName();
};

