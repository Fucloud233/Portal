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


	static void test();
public:
	BlockInfoOperator();
	~BlockInfoOperator();

	static void initial();

	static bool loadBlocks();
	static bool saveBlocks();

	static Block* value(int blockCode);

	static QStringList getNames();
	// 得到包括图标信息的对象
	static BlockInfoModel* getInfoModel();
};

