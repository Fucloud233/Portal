#pragma once

#include "BlockStatus.h"

#include <QLabel>
#include <QWidget>
#include <QFormLayout>
#include <QTableView>

class BlockStatusView : public QTableView {
	Q_OBJECT
public:
	BlockStatusView(QWidget* parent = nullptr);

	void clearStatus();
	void updateStatus(BlockStatus* status);

private:
	BlockStatus* status;

	void setupUi();
};

