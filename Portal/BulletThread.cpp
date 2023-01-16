#include "BulletThread.h"
#include <QDebug>


BulletThread::BulletThread(QObject* parent):
	QThread(parent) {
	end_flag = false;
}

void BulletThread::end() {
	end_flag = true;
}

void BulletThread::run() {
	// 发送飞行信号
	for (int i = 0; i < 100 && !end_flag; i++) {
		emit flying();
		msleep(10);
		//qDebug() << i;
	}
}