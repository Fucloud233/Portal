#include "BlockStatus.h"
#include "BlockInfoOperator.h"

BlockStatus::BlockStatus(int blockCode) {
	// [注意] 指针的初始化
	initial(blockCode);
}

void BlockStatus::initial(int blockCode, Block::Type blockType) {
	block = BlockInfoOperator::value(blockCode);

	if (blockType == Block::EMPTY && block) 
		type = block->BlockType() != Block::ALL ? block->BlockType() : Block::FULL;
	else 
		type = blockType;

	direct = 0;

	// [注意] 初始化Model 用于存储显示的状态表
	if (block) {
		statusModel = new QStandardItemModel();
		QStringList list;
		list << "名称" << "编号" << "类型" << "方向";
		statusModel->setVerticalHeaderLabels(list);
		statusModel->insertColumn(statusModel->columnCount(), getItemsList());
	}
	else
		statusModel = NULL;
}

void BlockStatus::write(QJsonObject& json) {
	json["code"] = block->BlockCode();
	json["type"] = type;
}

void BlockStatus::read(const QJsonObject& json) {
	int code = json["code"].toInt();
	Block::Type type = (Block::Type)json["type"].toInt();

	initial(code, type);
}

QStandardItemModel* BlockStatus::getStatusModel() {
	return statusModel;
}

void BlockStatus::setBlockType(QString text) {
	type = Block::TypeFromString(text);
}

void BlockStatus::setBlockType(Block::Type blockType) {
	type = blockType;
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

bool BlockStatus::isNULL() const {
	return !block;
}


QPixmap BlockStatus::BlockImg() {
	return block->BlockImg();
}