#include "BlockStatusView.h"

#include <QHeaderView>

BlockStatusView::BlockStatusView(QWidget* parent):
	QTableView(parent) {

	setupUi();
}

void BlockStatusView::setupUi() {
	horizontalHeader()->setVisible(false);
	setColumnWidth(0, width());
}

void BlockStatusView::updateStatus(BlockStatus* status) {
	this->status = status;
	if (status) {
		setModel(status->getStatusModel());
	}
}

void BlockStatusView::clearStatus() {
	status = NULL;
	setModel(NULL);
}