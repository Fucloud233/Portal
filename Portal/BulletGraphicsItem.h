#pragma once

#include "BulletThread.h"
#include "GraphicsItem.h"
#include "BlockGameGraphicsItem.h"

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>
#include <QRect>
#include <QtMath>

class BulletGraphicsItem : public QObject, public QGraphicsItem {
	Q_OBJECT
public:
	BulletGraphicsItem(Qt::GlobalColor color, qreal angle = 0, const QPointF& pos = QPointF(0, 0));

	QPainterPath shape() const override;
	QRectF boundingRect() const override;

private:
	BulletThread* thread;
	int R;

	Qt::GlobalColor color;
	int speed;
	qreal angle;

	bool checkcolliding();

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

signals:
	void collideWall(QPoint pos, Block::Side side, bool isRed);

private slots:
	void fly();
};

