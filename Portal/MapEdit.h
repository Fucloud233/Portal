#pragma once

#include "Map.h"
#include "BlockEditGraphicsItem.h"

class BlockEditGraphicsItem;

class MapEdit : public Map{
private:
	QPoint selected_block_index;

public:
	MapEdit(int blockSize = 48);
	~MapEdit();

	void initial(int width = 10, int height = 10);
	
	bool swap(const QPoint& source, const QPoint& target);
	bool swap(int s_x, int s_y, int t_x, int t_y);

	// 设置选中的方块类型
	bool hasSelected() const;
	void setSelectedPos(const QPoint& point);
	QPoint getSelectedPos() const;
	BlockEditGraphicsItem* getSelectedItem() const;
	BlockStatus* SelectedBlockStatus() const;
};
