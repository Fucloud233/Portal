#include "BlockStatus.h"

BlockStatus::BlockStatus() {

}

void BlockStatus::initial(const Block& block, Block::Type type) {
	this->block = block;
	this->type = type;
	direct = 0;

	statusModel = new QStandardItemModel();

	statusModel->setVerticalHeaderLabels(getFieldList());
	statusModel->insertColumn(statusModel->columnCount(), getItemsList());
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
	list.append(new QStandardItem(block.BlockCode()));
	return list;
}