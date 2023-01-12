#include "BlockStatusView.h"

#include "ItemDelegate.h"

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
}

void BlockStatusView::updateStatus(BlockStatus* status) {
	this->status = status;
	if (!status) {
		return;
	}

	setModel(status->getStatusModel());
	setColumnWidth(0, width());

	// 设置委托
	setItemDelegateForRow(BlockStatus::NAME, new ReadOnlyDelegate());
	setItemDelegateForRow(BlockStatus::CODE, new ReadOnlyDelegate());

	ComboBoxDelegate* blockTypeDelegate = new ComboBoxDelegate(status->getBlockTypes());
	setItemDelegateForRow(BlockStatus::TYPE, blockTypeDelegate);
	connect(blockTypeDelegate, SIGNAL(indexChanged(QString)), SLOT(updateBlockType(QString)));
}

void BlockStatusView::clearStatus() {
	status = NULL;
	setModel(NULL);
}

void BlockStatusView::updateBlockType(QString text) {
	status->setBlockType(Block::TypeFromString(text));
	statusChanged();
}