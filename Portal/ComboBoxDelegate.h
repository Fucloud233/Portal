#pragma once

#include <QComboBox>
#include <QItemDelegate>

class ComboBoxDelegate : public QItemDelegate {
	Q_OBJECT

public:
	ComboBoxDelegate(const QStringList& list);
	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

private:
	QStringList items;

private slots:
	void commitAndCloseEditor();
}; 
