#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QtSql>
#include <QAction>
#include "query.h"

#ifndef __LOANWINDOW_H
#define __LOANWINDOW_H

class QVBoxLayout;
class QMouseEvent;
class QMenuBar;
class QToolBar;
class QMenu;
class LoanWindow : public QWidget
{
	Q_OBJECT
	private:
		QToolBar* ml_toolbar;	
                QAction* ml_submit;
                QAction* ml_quit;
                QPushButton* ml_forward;
                QPushButton* ml_back;
                QVBoxLayout* ml_layout;
                QTableWidgetItem* ml_f1;
                QTableWidgetItem* ml_f2;
		QTableWidget* ml_display;
		QSqlQuery* ml_query;

	private slots:
		void lsubmit();
		void lforward();
		void lback();
	public:
		LoanWindow();
		~LoanWindow();
};
#endif
