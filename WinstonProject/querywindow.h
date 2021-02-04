#include <QWidget>
#include <QPushButton>
#include <QtSql>
#include <QGridLayout>

#ifndef __QUERYWINDOW_H
#define __QUERYWINDOW_H

class QLabel;
class QLineEdit;
class QPushButton;
class QListView;
class QGridLayout;
class QTableWidget;

class QueryWindow : public QWidget
{
	Q_OBJECT
	private:
		QLineEdit* authorEdit;
		QLineEdit* titleEdit;
		QLineEdit* callEdit;
		QPushButton* submitButton;
		QLabel* authorLabel;
		QLabel* titleLabel;
		QLabel* callLabel;
		QTableWidget* fullView;
		QGridLayout* gridLayout;

	private slots:
		void submit();

	public:
		QueryWindow();
      		~QueryWindow();		
};


#endif
