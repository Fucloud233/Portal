#pragma once

#include "Block.h"

class BlockInfoOperator
{
private:
	QMap<int, Block*> data;

	static QString FilePath;
	static QString FileName;

	void test();
public:
	BlockInfoOperator();

	bool loadBlocks();
	bool saveBlocks();
};

