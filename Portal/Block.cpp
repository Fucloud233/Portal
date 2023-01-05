#include "Block.h"

#include <QFile>
#include <QJsonDocument>

QString Block::FilePath = "./Block/";
int Block::BaseBlockCode = 0;

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

Block::Block() {
	this->block_name = "None";
	this->block_type = EMPTY;
	this->block_code = 0;
}

Block::Block(const QString& name, BlockType type) {
	this->block_name = name;
	this->block_type = type;
	this->block_code = BaseBlockCode++;
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
	json["block_type"] = block_type;
	json["block_code"] = block_code;
}

void Block::read(const QJsonObject& json) {
	block_name = json["block_name"].toString();
	block_type = (BlockType)json["block_type"].toInt();
	block_code = json["block_code"].toInt();
}


void Block::loadInfo() {
}


void Block::setBaseBlockCodeCount(int code) {
	BaseBlockCode = code;
}

int Block::BlockCode() {
	return block_code;
}