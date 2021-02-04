#include "authorpatronwindow.h"
#include <QWidget>
#include <QPushButton>
#include <QtSql>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class QListView;
class QGridLayout;
class QTableWidget;

AuthorPatronWindow::AuthorPatronWindow() : QWidget()
{
	authorSearch = new QLineEdit;
	patronSearch = new QLineEdit;
	submitButton = new QPushButton(tr("Submit"));
	authorLabel = new QLabel(tr("Author: "));
	patronLabel = new QLabel(tr("Patron: "));
	fullView = new QTableWidget;
	gridLayout = new QGridLayout;	

	gridLayout = new QGridLayout;
	gridLayout->addWidget(authorLabel, 0, 0);
	gridLayout->addWidget(patronLabel, 1, 0);

	gridLayout->addWidget(authorSearch, 0, 1);
	gridLayout->addWidget(patronSearch, 1, 1);
	
	gridLayout->addWidget(submitButton, 2, 1);
	gridLayout->addWidget(fullView, 0, 2, -1, -1);
	setLayout(gridLayout);

	QTableWidgetItem* header1 = new QTableWidgetItem("ISBN");
	QTableWidgetItem* header2 = new QTableWidgetItem("Title");
	QTableWidgetItem* header3 = new QTableWidgetItem("Author");
	QTableWidgetItem* header4 = new QTableWidgetItem("Call #");
	QTableWidgetItem* header5 = new QTableWidgetItem("Pages");
	QTableWidgetItem* header7 = new QTableWidgetItem("Binding");
	QTableWidgetItem* header8 = new QTableWidgetItem("Publisher");

	fullView->setColumnCount(7);
	fullView->setHorizontalHeaderItem(0, header1);
	fullView->setHorizontalHeaderItem(1, header2);
	fullView->setHorizontalHeaderItem(2, header3);
	fullView->setHorizontalHeaderItem(3, header4);
	fullView->setHorizontalHeaderItem(4, header5);
	fullView->setHorizontalHeaderItem(5, header7);
	fullView->setHorizontalHeaderItem(6, header8);

	connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));
}

AuthorPatronWindow::~AuthorPatronWindow()
{
	delete authorSearch;
	delete patronSearch;
	delete submitButton;
	delete authorLabel;
	delete patronLabel;
	delete fullView;
	delete gridLayout;	
}

void AuthorPatronWindow::submit()
{
  	QSqlQuery* authorQuery = new QSqlQuery;
	QString author = authorSearch->text();
	QString patron = patronSearch->text();
	int count = 0;

	if (author.isEmpty() == false and patron.isEmpty() == false)
	{
		authorQuery->prepare("SELECT Book.ISBN, Title, Author, Call_Number, Pages, Binding, Publisher FROM Book, Loans WHERE Book.ISBN = Loans.ISBN;");
		authorQuery->exec();

		while(authorQuery->next())
		{
		  QTableWidgetItem* isbnItem = new QTableWidgetItem(authorQuery->value(0).toString());
		  QTableWidgetItem* titleItem = new QTableWidgetItem(authorQuery->value(1).toString());
		  QTableWidgetItem* authorItem = new QTableWidgetItem(authorQuery->value(2).toString());
		  QTableWidgetItem* callNumItem = new QTableWidgetItem(authorQuery->value(3).toString());
		  QTableWidgetItem* pagesItem = new QTableWidgetItem(authorQuery->value(4).toString());
		  QTableWidgetItem* bindingItem = new QTableWidgetItem(authorQuery->value(5).toString());
		  QTableWidgetItem* publisherItem = new QTableWidgetItem(authorQuery->value(6).toString());
		  fullView->insertRow(count);
		  fullView->setItem(count, 0, isbnItem);
		  fullView->setItem(count, 1, titleItem);
		  fullView->setItem(count, 2, authorItem);
		  fullView->setItem(count, 3, callNumItem);
		  fullView->setItem(count, 4, pagesItem);
		  fullView->setItem(count, 5, bindingItem);
		  fullView->setItem(count, 6, publisherItem);
		  ++count;
		}
	}

}
