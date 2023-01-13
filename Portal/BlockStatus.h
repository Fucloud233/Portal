#pragma once

#include "Block.h"

#include <QStandardItemModel>

// 存储已经存放的方块信息
class BlockStatus {
private:
	const Block* block;
	// 基础信息
	int code;
	Block::Type type;
	int direct;

	// 用于显示的信息
	QStandardItemModel* statusModel;
	
public:
	// 用于得到对应字段名
	enum BlockStatusField {
		NAME, CODE, TYPE, DIRECT
	};

	BlockStatus(int blockCode = -1);
	BlockStatus(const Block* block);

	void initialModel();

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

	bool isNULL() const;
};