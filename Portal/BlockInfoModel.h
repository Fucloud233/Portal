#pragma once

#include "Block.h"

#include <QAbstractListModel>
#include <QMimeData>
#include <QByteArray>

class BlockInfoModel : public QAbstractListModel {
	Q_OBJECT
public:
	explicit BlockInfoModel(QObject* parent = nullptr);

	void addBlockInfo(Block* info);

	// 重载父类的虚函数
	QVariant data(const QModelIndex& index, int role = Qt::UserRole) const;
	int rowCount(const QModelIndex& parent) const;
	
	Qt::ItemFlags flags(const QModelIndex& index) const;


	// 实现对MimeData的操作
	//bool dropMimeData(const QMimeData* data, Qt::DropAction action,
	//	int row, int column, const QModelIndex& parent) override;
	QMimeData* mimeData(const QModelIndexList& indexes) const override;
	QStringList mimeTypes() const override;

private:
	QList<Block*> blockInfos;
};