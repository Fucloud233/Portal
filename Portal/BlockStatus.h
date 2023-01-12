#pragma once

#include "Block.h"

#include <QStandardItemModel>

// 存储已经存放的方块信息
class BlockStatus {
private:
	// 基础信息
	Block block;
	int direct;
	Block::Type type;

	// 用于显示的信息
	QStandardItemModel* statusModel;
	
public:
	// 用于得到对应字段名
	enum BlockStatusField {
		NAME, CODE, TYPE, DIRECT
	};

	BlockStatus();

	void initial(const Block& block);

	virtual void write(QJsonObject& json);
	virtual void read(const QJsonObject& json);

	QStandardItemModel* getStatusModel();
	QStringList getFieldList();
	QList<QStandardItem*> getItemsList();

	Block getInfo();
	QStringList getBlockTypes();
	Block::Type getBlockType();
	void setBlockType(QString text);
	void setBlockType(Block::Type type);
};