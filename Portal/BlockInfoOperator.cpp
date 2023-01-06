#include "BlockInfoOperator.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QByteArray>

QString BlockInfoOperator::FilePath = "./Block/";
QString BlockInfoOperator::FileName = "Blocks.json";

BlockInfoOperator::BlockInfoOperator() {
	loadBlocks();
}

BlockInfoOperator::~BlockInfoOperator() {

	saveBlocks();
	for (auto it = data.begin()	; it != data.end(); it++) {
		delete it.value();
	}
}

bool BlockInfoOperator::loadBlocks() {
	QFile saveFile(FilePath + FileName);
	if (!saveFile.open(QIODevice::ReadOnly)) {
		qWarning("文件打开失败!");
		return false;
	}

	QByteArray saveData = saveFile.readAll();

	QJsonDocument jsonDoc(QJsonDocument::fromJson(saveData));

	QJsonArray jsonArray = jsonDoc.object()["Blocks"].toArray();
	for (int i = 0; i < jsonArray.size(); i++) {
		Block* block = new Block();
		block->read(jsonArray[i].toObject());

		data.insert(block->BlockCode(), block);
	}
}

bool BlockInfoOperator::saveBlocks() {
	// 将Block信息转换为Json数组
	QJsonArray jsonArray;
	for (auto it = data.begin(); it != data.end();it++) {
		QJsonObject blockJson;
		Block* block = it.value();
		block->write(blockJson);
		jsonArray.append(blockJson);
	}
	
	QJsonObject json;
	json["Blocks"] = jsonArray;

	// 然后再将整个数组作为一个Json存储
	QFile saveFile(FilePath + FileName);
	if (!saveFile.open(QIODevice::WriteOnly)) {
		qWarning("文件打开失败!");
		return false;
	}

	saveFile.write(QJsonDocument(json).toJson());
	return true;
}

// 测试函数
void BlockInfoOperator::test() {
	Block* block1 = new Block("Temp", Block::FULL);
	Block* block2 = new Block("Wood", Block::FLOOR);
	data.insert(block1->BlockCode(), block1);
	data.insert(block2->BlockCode(), block2);

	saveBlocks();
}