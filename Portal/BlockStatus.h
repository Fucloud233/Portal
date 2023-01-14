#pragma once

#include "Block.h"

#include <QStandardItemModel>

// 存储已经存放的方块信息
class BlockStatus {
private:
	const Block* block;
	// 记录当前的状态
	Block::Type type;
	int direct;

	// 用于显示的信息
	QStandardItemModel* statusModel;

	void initial(int blockCode, Block::Type blockType = Block::EMPTY);

	QList<QStandardItem*> getItemsList();
	
public:
	// 用于得到对应字段名
	enum BlockStatusField {
		NAME, CODE, TYPE, DIRECT
	};

	BlockStatus(int blockCode = -1);

	virtual void write(QJsonObject& json);
	virtual void read(const QJsonObject& json);

	// 得到状态显示类
	QStandardItemModel* getStatusModel();

	QPixmap BlockImg();

	void setBlockType(QString text);
	void setBlockType(Block::Type blockType);
	QStringList getBlockTypes();
	Block::Type getBlockType();

	bool isNULL() const;
};