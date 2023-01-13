#pragma once

#include "BlockStatus.h"

#include "ItemDelegate.h"

#include <QLabel>
#include <QWidget>
#include <QFormLayout>
#include <QTableView>

class BlockStatusView : public QTableView {
	Q_OBJECT
public:
	BlockStatusView(QWidget* parent = nullptr);

	void clearStatus();

private:
	BlockStatus* status;

	ComboBoxDelegate* blockTypeDelegate;

	void setupUi();

public slots:
	void updateStatus(BlockStatus* status);

private slots:
	void updateBlockType(QString text);

signals:
	void statusChanged();
};

