#include "MapEdit.h"

#include "BlockInfoOperator.h"

MapEdit::MapEdit():
	Map() {
}

MapEdit::MapEdit(int width, int height, int blockSize) {
	initial(width, height, blockSize);
}

MapEdit::~MapEdit() {

}

void MapEdit::initial(int width, int height, int blockSize) {
	Map::initial(width, height, blockSize);

	// 每个Item 由于所在坐标不同 需要单独设置
	for (int i = items.bound(Direct::TOP); i != items.bound(Direct::BOTTOM); i++) {
		for (int j = items.bound(Direct::LEFT); j != items.bound(Direct::RIGHT); j++) {
			// 创建item对象
			blocks[i][j] = new BlockStatus();
			items[i][j] = new BlockEditGraphicsItem(j, i, this);
		}
	}
}

bool MapEdit::modify(const QPoint& point, BlockStatus* status) {
	// 派生类调用基类函数时 会优先调用派生的override函数
	return modify(point.x(), point.y(), status);
}

bool MapEdit::modify(int x, int y, BlockStatus* status) {
	if (!blocks.checkIndex(y, x)) {
		return false;
	}

	if (blocks[y][x]) delete blocks[y][x];
	if (items[y][x]) delete items[y][x];

	blocks[y][x] = status;
	items[y][x] = new BlockEditGraphicsItem(x, y, status->BlockImg(), this);

	return true;
}

bool MapEdit::swap(const QPoint& source, const QPoint& target) {
	return this->swap(source.x(), source.y(), target.x(), target.y());
}

bool MapEdit::swap(int s_x, int s_y, int t_x, int t_y) {
	// 判断Pos是否越界
	if (!blocks.checkIndex(s_y, s_x) || !blocks.checkIndex(t_y, t_x)) {
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
	blocks.swap(s_y, s_x, t_y, t_x);

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
		return blocks[selected_block_index.y()][selected_block_index.x()];
}
