#include "ItemDelegate.h"

ComboBoxDelegate::ComboBoxDelegate(const QStringList& list) {
	this->items = list;
}

QWidget* ComboBoxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
	const QModelIndex& index) const {
	
	QComboBox* editor = NULL;
	if (items.size() > 1) {
		editor = new QComboBox(parent);

		for (QString item : items) {
			editor->addItem(item);
		}
		editor->setCurrentIndex(0);
		editor->setMaximumWidth(100);

		// 当选择发生变化时 发送数据
		connect(editor, SIGNAL(currentIndexChanged(int)), SLOT(emitData(int)));
	}

	return editor;
}

void ComboBoxDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
	const QModelIndex& index) const {

	// 设置显示的文字
	QString text = index.model()->data(index, Qt::EditRole).toString();

	drawDisplay(painter, option, option.rect, text);
	drawFocus(painter, option, option.rect);
}

void ComboBoxDelegate::emitData(int index) {
	// 得到信号的发送者
	QComboBox* editor = qobject_cast<QComboBox*>(sender());
	QString data = editor->itemData(index, 0).toString();
	// 发送数据
	indexChanged(data);
}

ReadOnlyDelegate::ReadOnlyDelegate(QWidget* parent) :
	QItemDelegate(parent) {
}

QWidget* ReadOnlyDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
	const QModelIndex& index) const {
	// 不返回任何editor 就没有编辑 -> 只读类型
	Q_UNUSED(parent)
	Q_UNUSED(option)
	Q_UNUSED(index)
	return NULL;
}