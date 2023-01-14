#include "BlockStatus.h"
#include "BlockInfoOperator.h"

BlockStatus::BlockStatus(int blockCode) {
	// [注意] 指针的初始化
	statusModel = NULL;
	setBlock(blockCode);
}

void BlockStatus::setModel() {
	if (statusModel) {
		delete statusModel;
	}

	if (block) {
		statusModel = new QStandardItemModel();
		statusModel->setVerticalHeaderLabels(getFieldList());
		statusModel->insertColumn(statusModel->columnCount(), getItemsList());
	}
	else
		statusModel = NULL;
}

void BlockStatus::write(QJsonObject& json) {
	json["code"] = code;
	json["type"] = type;
}

void BlockStatus::read(const QJsonObject& json) {
	code = json["code"].toInt();
	type = (Block::Type)json["type"].toInt();
	block = BlockInfoOperator::value(code);

	// 记得要初始化Model 用于存储显示的状态表
	setModel();
}

QStandardItemModel* BlockStatus::getStatusModel() {
	return statusModel;
}

QStringList BlockStatus::getFieldList() {
	QStringList list;
	list << "名称" << "编号" << "类型" << "方向";
	return list;
}

QList<QStandardItem*> BlockStatus::getItemsList() {
	QList<QStandardItem*> list;
	list.append(new QStandardItem(block->BlockName()));
	list.append(new QStandardItem(block->BlockCodeText()));
	// 根据当前的Type来设置
	list.append(new QStandardItem(Block::StringFromType(type)));
	return list;
}

QStringList BlockStatus::getBlockTypes() {
	return block->BlockTypesText();
}

Block::Type BlockStatus::getBlockType() {
	return type;
}

void BlockStatus::setBlockType(QString text) {
	type = Block::TypeFromString(text);
}

void BlockStatus::setBlockType(Block::Type type) {
	this->type = type;
}

void BlockStatus::setBlock(int blockCode) {
	block = BlockInfoOperator::value(blockCode);
	code = blockCode;
	if (block)
		type = block->BlockType() != Block::ALL ? block->BlockType() : Block::FULL;
	else
		type = Block::EMPTY;

	direct = 0;

	setModel();
}

bool BlockStatus::isNULL() const {
	return !block;
}