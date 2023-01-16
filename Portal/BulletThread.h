#pragma once

#include <QThread>

class BulletThread : public QThread {
	Q_OBJECT
public:
	BulletThread(QObject* parent = nullptr);

	void end();
protected:
	bool end_flag;
	void run() override;

signals:
	void flying();
};	