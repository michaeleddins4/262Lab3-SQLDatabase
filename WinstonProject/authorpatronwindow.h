#include <QWidget>
#include <QPushButton>
#include <QtSql>
#include <QGridLayout>

#ifndef __AUTHORPATRONWINDOW_H
#define __AUTHORPATRONWINDOW_H

class QLabel;
class QLineEdit;
class QPushButton;
class QListView;
class QGridLayout;
class QTableWidget;

class AuthorPatronWindow : public QWidget
{
	Q_OBJECT
	private:
		QLineEdit* authorSearch;
		QLineEdit* patronSearch;
		QPushButton* submitButton;
		QLabel* authorLabel;
		QLabel* patronLabel;
		QTableWidget* fullView;
		QGridLayout* gridLayout;

	private slots:
		void submit();

	public:
		AuthorPatronWindow();
      		~AuthorPatronWindow();		
};


#endif
