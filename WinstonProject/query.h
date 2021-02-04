#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>

#ifndef __QUERY_H
#define __QUERY_H

class Query : public QWidget
{
	Q_OBJECT 

	private:
		QTableWidget* m_table;
	public:
		Query(QTableWidgetItem* f1, QTableWidgetItem* f2, QTableWidgetItem* f3, QTableWidgetItem* f4, QTableWidgetItem* f5, QTableWidgetItem* f6, QTableWidgetItem* f7, QPushButton* next, QPushButton* prev);
		Query(QTableWidgetItem* f1, QTableWidgetItem* f2, QPushButton* next, QPushButton* prev);
		~Query();
};

#endif
