#pragma once

#include "Block.h"

#include <QComboBox>
#include <QItemDelegate>

class ComboBoxDelegate : public QItemDelegate {
	Q_OBJECT

public:
	ComboBoxDelegate(const QStringList& list = QStringList());
	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

	void setItems(const QStringList& list);

private:
	QStringList items;

private slots:
	void emitData(int);

signals:
	void indexChanged(QString);
}; 

class ReadOnlyDelegate : public QItemDelegate {
	Q_OBJECT

public:
    ReadOnlyDelegate(QWidget* parent = NULL); 

	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
		const QModelIndex& index) const override; 
};
