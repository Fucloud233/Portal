#pragma once

#include "Map.h"
#include "BlockEditGraphicsItem.h"

class BlockEditGraphicsItem;

class MapEdit : public Map{
private:
	QPoint selected_block_index;

public:
	MapEdit(int blockSize = 0);
	MapEdit(int width, int height, int blockSize);
	~MapEdit();

	void initial(int width, int height, int blockSize) override;
	
	bool modify(int x, int y, BlockStatus* status) override;
	bool swap(const QPoint& source, const QPoint& target);
	bool swap(int s_x, int s_y, int t_x, int t_y);

	// 设置选中的方块类型
	bool hasSelected() const;
	void setSelectedPos(const QPoint& point);
	QPoint getSelectedPos() const;
	BlockEditGraphicsItem* getSelectedItem() const;
	BlockStatus* SelectedBlockStatus() const;
};
