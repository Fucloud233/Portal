#include "BlockStatus.h"

BlockStatus::BlockStatus(){
}

void BlockStatus::initial(const Block& block) {
	this->block = block;
	type = block.BlockType() != Block::ALL ? block.BlockType() : Block::FULL;
	direct = 0;

	statusModel = new QStandardItemModel();

	statusModel->setVerticalHeaderLabels(getFieldList());
	statusModel->insertColumn(statusModel->columnCount(), getItemsList());
}

void BlockStatus::write(QJsonObject& json) {

}

void BlockStatus::read(const QJsonObject& json) {

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
	list.append(new QStandardItem(block.BlockName()));
	list.append(new QStandardItem(block.BlockCodeText()));
	// 根据当前的Type来设置
	list.append(new QStandardItem(Block::StringFromType(type)));
	return list;
}

QStringList BlockStatus::getBlockTypes() {
	return block.BlockTypesText();
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