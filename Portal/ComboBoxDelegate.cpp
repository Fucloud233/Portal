#include "ComboBoxDelegate.h"

ComboBoxDelegate::ComboBoxDelegate(const QStringList& list) {
	this->items = list;
}

QWidget* ComboBoxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
	const QModelIndex& index) const {

	QComboBox* editor = new QComboBox(parent);
	for (QString item : items) {
		editor->addItem(item);
	}

	// 连接槽函数 用于控制关闭
	connect(editor, SIGNAL(editingFinished()), SLOT(commitAndCloseEditor()));
	
	return editor;
}

void ComboBoxDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
	const QModelIndex& index) const {

	// 设置显示的文字
	QString text = index.model()->data(index, Qt::DisplayRole).toString();
	QStyleOptionViewItem curOption = option;
	curOption.displayAlignment = Qt::AlignHCenter | Qt::AlignVCenter;

	drawDisplay(painter, curOption, curOption.rect, text);
	drawFocus(painter, curOption, curOption.rect);
}

void ComboBoxDelegate::commitAndCloseEditor() {
	QComboBox* editor = qobject_cast<QComboBox*>(sender());
	
	// 发送信号
	emit commitData(editor);
	emit closeEditor(editor);
}
