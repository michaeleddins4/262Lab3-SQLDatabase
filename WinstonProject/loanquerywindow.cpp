#include "loanquerywindow.h"
#include <QWidget>
#include <QPushButton>
#include <QtSql>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <vector>

LoanQueryWindow::LoanQueryWindow() : QWidget()
{
	m_author = new QLineEdit;
	m_patron = new QLineEdit;
	m_submit = new QPushButton(tr("Submit"));
	m_author_label = new QLabel(tr("Author:"));
	m_patron_label = new QLabel(tr("Patron:"));
	m_table = new QTableWidget;
	m_layout = new QGridLayout;

	m_layout->addWidget(m_author_label, 0, 0);
	m_layout->addWidget(m_patron_label, 1, 0);
	m_layout->addWidget(m_author, 0, 1);
	m_layout->addWidget(m_patron, 1, 1);
	m_layout->addWidget(m_submit, 2, 1);
	m_layout->addWidget(m_table, 0, 2, 3, 1);
	setLayout(m_layout);

	QTableWidgetItem* header1 = new QTableWidgetItem ("ISBN");
        QTableWidgetItem* header2 = new QTableWidgetItem ("Title");
        QTableWidgetItem* header3 = new QTableWidgetItem ("Author");
        QTableWidgetItem* header4 = new QTableWidgetItem ("Call #");
        QTableWidgetItem* header5 = new QTableWidgetItem ("Pages");
	QTableWidgetItem* header6 = new QTableWidgetItem ("Binding");
	QTableWidgetItem* header7 = new QTableWidgetItem ("Publisher");

        m_table->setColumnCount(7);
        m_table->setHorizontalHeaderItem(0, header1);
        m_table->setHorizontalHeaderItem(1, header2);
        m_table->setHorizontalHeaderItem(2, header3);
        m_table->setHorizontalHeaderItem(3, header4);
        m_table->setHorizontalHeaderItem(4, header5);
	m_table->setHorizontalHeaderItem(5, header6);
	m_table->setHorizontalHeaderItem(6, header7);

        connect(m_submit, SIGNAL(clicked()), this, SLOT(submit()));

}

LoanQueryWindow::~LoanQueryWindow()
{
	delete m_author;
	delete m_patron;
	delete m_submit;
	delete m_author_label;
	delete m_patron_label;
	delete m_table;
	delete m_layout;
}

void LoanQueryWindow::submit()
{
	int count = 0;
        QSqlQuery* book_query = new QSqlQuery;
	QSqlQuery* loan_query = new QSqlQuery;
        QString patron = m_patron->text();
        QString author = m_author->text();
	if (patron.isEmpty() == false && author.isEmpty()== false) {
		book_query->prepare("SELECT ISBN, Title, Author, Call_Number, Pages, Binding, Publisher FROM Book WHERE Author = ?;");
		book_query->addBindValue(author);
		loan_query->prepare("SELECT ISBN, Patron FROM Loans WHERE Patron = ?;");
		loan_query->addBindValue(patron);
		book_query->exec();
		loan_query->exec();
		std::vector<QSqlRecord> books;
		std::vector<QSqlRecord> loans;
		std::vector<QSqlRecord> matches; //This is messy, but I firmly regard iterators as the devil, so we're doing this.
		while(book_query->next()) {
			books.push_back(book_query->record());
		}
		while(loan_query->next()) {
			loans.push_back(loan_query->record());
		}
		for(QSqlRecord b : books) {
			for(QSqlRecord l : loans) {
				if( b.value(0) == l.value(0)) {
					matches.push_back(b);
				}
			}
		}
		for(QSqlRecord m : matches) {
			QTableWidgetItem* isbnItem = new QTableWidgetItem(m.value(0).toString());
                	QTableWidgetItem* titleItem = new QTableWidgetItem(m.value(1).toString());
                	QTableWidgetItem* authorItem = new QTableWidgetItem(m.value(2).toString());
                	QTableWidgetItem* callNumItem = new QTableWidgetItem(m.value(3).toString());
                	QTableWidgetItem* pagesItem = new QTableWidgetItem(m.value(4).toString());
			QTableWidgetItem* bindingItem = new QTableWidgetItem(m.value(5).toString());
			QTableWidgetItem* publisherItem = new QTableWidgetItem(m.value(6).toString());
			m_table->insertRow(count);
		        m_table->setItem(count, 0, isbnItem);
	                m_table->setItem(count, 1, titleItem);
        	        m_table->setItem(count, 2, authorItem);
             	 	m_table->setItem(count, 3, callNumItem);
             		m_table->setItem(count, 4, pagesItem);
			m_table->setItem(count, 5, bindingItem);
			m_table->setItem(count, 6, publisherItem);
              		++count;
		}
	}
}

