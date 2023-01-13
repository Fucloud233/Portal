#include "BlockStatusView.h"


#include <QHeaderView>
#include <QSizePolicy>

BlockStatusView::BlockStatusView(QWidget* parent):
	QTableView(parent) {

	setupUi();
}

void BlockStatusView::setupUi() {
	horizontalHeader()->setVisible(false);
	setEditTriggers(EditTrigger::AllEditTriggers);
	setMinimumWidth(120);
	setColumnWidth(0, width());

	//setModel(new QStandardItemModel());

	// 设置委托
	setItemDelegateForRow(BlockStatus::NAME, new ReadOnlyDelegate());
	setItemDelegateForRow(BlockStatus::CODE, new ReadOnlyDelegate());

	blockTypeDelegate = new ComboBoxDelegate();
	setItemDelegateForRow(BlockStatus::TYPE, blockTypeDelegate);
	connect(blockTypeDelegate, SIGNAL(indexChanged(QString)), SLOT(updateBlockType(QString)));
}

void BlockStatusView::clearStatus() {
	status = NULL;
	setModel(NULL);
}

void BlockStatusView::updateStatus(BlockStatus* status) {
	this->status = status;
	if (!status) {
		return;
	}
	setModel(status->getStatusModel());

	this->blockTypeDelegate->setItems(status->getBlockTypes());
}

void BlockStatusView::updateBlockType(QString text) {
	status->setBlockType(Block::TypeFromString(text));
	emit statusChanged();
}