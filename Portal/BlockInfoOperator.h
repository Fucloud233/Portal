#pragma once

#include "Block.h"

#include <QStringList>
#include <QStandardItemModel>

class BlockInfoOperator
{
private:

	static QString FilePath;
	static QString FileName;

	static QMap<int, Block*> data;
	static QStandardItemModel* InfoItems;

	void initial();

	void test();
public:
	BlockInfoOperator();
	~BlockInfoOperator();

	bool loadBlocks();
	bool saveBlocks();

	QStringList getNames();
	// 得到包括图标信息的对象
	QStandardItemModel* getInfoItems();
};

