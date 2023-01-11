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
	enum BlockStatusFiled {
		NAME, CODE, TYPE, DIRECT
	};

	BlockStatus();

	void initial(const Block& block, Block::Type type = Block::FULL);

	QStandardItemModel* getStatusModel();
	QStringList getFieldList();
	QList<QStandardItem*> getItemsList();
	
	Block getInfo();
};