#include "BlockInfoModel.h"

#include <QDataStream>

BlockInfoModel::BlockInfoModel(QObject* parent) :
	QAbstractListModel(parent) {
}

void BlockInfoModel::addBlockInfo(Block* info) {
	blockInfos.append(info);
}

// Model 在显示数据时 调用data函数
QVariant BlockInfoModel::data(const QModelIndex& index, int role) const {
	if (!index.isValid()) {
		return QVariant();
	}

	Block* block = blockInfos[index.row()];

	// 返回用数据数
	switch (role) {
	case Qt::UserRole:
		return QVariant::fromValue(block);
	case Qt::DisplayRole:
		return block->BlockName();
	case Qt::DecorationRole:
		return block->BlockImg();
	default:
		return QVariant();
	}
}

int BlockInfoModel::rowCount(const QModelIndex& parent) const {
	return parent.isValid() ? 0 : blockInfos.size();
}

Qt::ItemFlags BlockInfoModel::flags(const QModelIndex& index) const {
	if (index.isValid())
		return (QAbstractListModel::flags(index) | Qt::ItemIsDragEnabled);

	return Qt::ItemIsDropEnabled;
}

// dropMimeData
//bool BlockInfoModel::dropMimeData(const QMimeData* data, Qt::DropAction action,
//	int row, int column, const QModelIndex& parent)  {
//
//	//if (!data->hasFormat(mimeTypes()[0])) 
//	//	return false;
//	//
//	//if (action == Qt::IgnoreAction) 
//	//	return false;
//
//	//if (column > 0) 
//	//	return false;
//
//	//int endRow;
//
//	//if (!parent.isValid()) {
//	//	if (row < 0)
//	//		endRow = blockInfos.size();
//	//	else
//	//		endRow = qMin(row, blockInfos.size());
//	//}
//	//else 
//	//	endRow = parent.row();
//	//
//	//QByteArray encodedData = data->data(mimeTypes()[0]);
//	//QDataStream stream(&encodedData, QDataStream::ReadOnly);
//
//	//while (!stream.atEnd()) {
//	//	Block* block;
//	//	QVariant temp;
//	//	stream >> temp;
//
//	//	endRow++;
//	//}
//
//	return true;
//}

QMimeData* BlockInfoModel::mimeData(const QModelIndexList& indexes) const {
	QMimeData* mimeData = new QMimeData();
	QByteArray encodedData;
	QDataStream stream(&encodedData, QDataStream::WriteOnly);

	for (const QModelIndex& index : indexes) {
		if (index.isValid()) {
			Block* block = blockInfos[index.row()];

			// 得到编码
			mimeData->setText(QVariant(block->BlockCode()).toString());
			
			// 得到图片
			stream << block->BlockImg();
			mimeData->setImageData(encodedData);
		}
	}

	return mimeData;
}

QStringList BlockInfoModel::mimeTypes() const {
	QStringList types;
	// 在拖拽时 我们只传输编号
	types << "image/x-block-info";
	return types;
}