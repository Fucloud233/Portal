#pragma once

#include "Block.h"
#include "BlockInfoModel.h"

#include <QStringList>
#include <QStandardItemModel>

class BlockInfoOperator
{
private:

	static QString FilePath;
	static QString FileName;

	static QMap<int, Block*> data;
	static BlockInfoModel* infoModel;

	void initial();

	void test();
public:
	BlockInfoOperator();
	~BlockInfoOperator();

	bool loadBlocks();
	bool saveBlocks();

	Block* value(int blockCode);

	QStringList getNames();
	// 得到包括图标信息的对象
	BlockInfoModel* getInfoModel();
};

