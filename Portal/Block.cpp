#include "Block.h"

#include <QFile>
#include <QJsonDocument>

QString Block::FilePath = "./Block/";

QString Block::blockTypeText() {
	switch(block_type) {
	case FULL:
		return "FULL";
	case FLOOR:
		return "FLOOR";
	case COMPONENT:
		return "COMPONENT";
	}
}

Block::Block(const QString& name, BlockType type) {
	this->block_name = name;
	this->block_type = type;
}

bool Block::saveInfo() {

	QFile saveFile(FilePath + block_name + ".json");

	if (!saveFile.open(QIODevice::WriteOnly)) {
		qWarning("文件打开失败!");
		return false;
	}

	// 将方块信息存储为Json
	QJsonObject json;
	write(json);
	saveFile.write(QJsonDocument(json).toJson());

	return true;
}

void Block::write(QJsonObject& json) {
	json["block_name"] = block_name;
	json["block_type"] = blockTypeText();
}

void Block::loadInfo() {
}


void Block::setBaseBlockCodeCount(int code) {
	BaseBlockCode = code;
}