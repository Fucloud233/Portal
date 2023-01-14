#include "MapEdit.h"

#include "BlockInfoOperator.h"

MapEdit::MapEdit(int blockSize):
	Map(blockSize) {

	selected_block_index = QPoint();
}

MapEdit::~MapEdit() {

}

void MapEdit::initial(int width, int height) {
	qDebug() << "MapEdit initial";

	// 初始化变量
	this->width = width; this->height = height;
	
	statuses = Matrix<BlockStatus*>(width, height, NULL);
	items = Matrix<BlockGraphicsItem*>(width, height, NULL);

	// 每个Item 由于所在坐标不同 需要单独设置
	for (int i = items.bound(Direct::TOP); i != items.bound(Direct::BOTTOM); i++) {
		for (int j = items.bound(Direct::LEFT); j != items.bound(Direct::RIGHT); j++) {
			// 创建item对象
			statuses[i][j] = new BlockStatus();
			items[i][j] = new BlockEditGraphicsItem(j, i, this);
		}
	}
}

bool MapEdit::swap(const QPoint& source, const QPoint& target) {
	return this->swap(source.x(), source.y(), target.x(), target.y());
}

bool MapEdit::swap(int s_x, int s_y, int t_x, int t_y) {
	// 判断Pos是否越界
	if (!statuses.checkIndex(s_y, s_x) || !statuses.checkIndex(t_y, t_x)) {
		return false;
	}
	
	// 判断移动是否满足情况
	//if (data[s_y][s_x] == NULL) {
	//	return false;
	//}

	// 这里调用的是基类的函数
	items[s_y][s_x]->setPos(t_x, t_y);
	items[t_y][t_x]->setPos(s_x, s_y);

	items.swap(s_y, s_x, t_y, t_x);
	//data.swap(s_y, s_x, t_y, t_x);
	statuses.swap(s_y, s_x, t_y, t_x);

	return true;
}

bool MapEdit::hasSelected() const {
	return !selected_block_index.isNull();
}

void MapEdit::setSelectedPos(const QPoint& point) {
	this->selected_block_index = point;
}

QPoint MapEdit::getSelectedPos() const {
	return selected_block_index;
}

BlockEditGraphicsItem* MapEdit::getSelectedItem() const {
	// 需要强制转换
	return (BlockEditGraphicsItem*)getItem(selected_block_index);
}

BlockStatus* MapEdit::SelectedBlockStatus() const {
	if (selected_block_index.isNull()) 
		return NULL;
	else
		return statuses[selected_block_index.y()][selected_block_index.x()];
}
