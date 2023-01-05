#pragma once
#include <QString>
#include <QJsonObject>

class Block {
public:
	enum BlockType {
		FULL, FLOOR, COMPONENT
	};

private:
	QString blockTypeText();
	static int BaseBlockCode;

protected:
	static QString FilePath;

	QString block_name;
	BlockType block_type;
	int block_code;
	// 将对象存储为json
	virtual void write(QJsonObject& json);

public:

	Block(const QString& name, BlockType type);

	bool saveInfo();	// 保存信息
	void loadInfo();	// 加载信息

	static void setBaseBlockCodeCount(int code);
};

