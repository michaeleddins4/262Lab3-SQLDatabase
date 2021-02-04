#include <QMainWindow>
#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QPushButton>
#include <QtSql>
#include <string>
#include <QTableWidget>
#include <QToolButton>
#include "query.h"
#include "loanquerywindow.h"

#ifndef __WINDOW_H
#define __WINDOW_H

class QueryWindow;
class QVBoxLayout;
class QMouseEvent;
class QMenuBar;
class QMenu;
class QLabel;

class Window : public QMainWindow
{
	Q_OBJECT
	private:
		QToolBar* m_toolbar;
		QMenu* m_menu;
		QToolButton* m_qmenu;
		QAction* m_submit;
		QAction* m_bookquery;
		QAction* m_loanquery;
		QAction* m_openloans;
		QAction* m_quit;
		QAction* m_openauthorpatron;
		QPushButton* m_forward;
		QPushButton* m_back;
		QVBoxLayout* m_layout;
		QSqlDatabase m_db;
		QTableWidgetItem* m_f1;
		QTableWidgetItem* m_f2;
		QTableWidgetItem* m_f3;
		QTableWidgetItem* m_f4;
		QTableWidgetItem* m_f5;
		QTableWidgetItem* m_f6; // Binding and Publisher
		QTableWidgetItem* m_f7;
		Query* m_display;
		QSqlQuery* m_query;
		int m_pos;
		std::string m_type;	

	private slots:
		void bookquery();
		void loanquery();
		void openloans();
		void openauthpat();
		void submit();
		void forward();
		void back();
		
	public:
		Window();
		~Window();
};


#endif

