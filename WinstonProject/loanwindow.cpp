#include "loanwindow.h"
#include "query.h"
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QtGui>
#include <QPushButton>
#include <QTableWidget>
#include <QtSql>
#include <QLabel>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QVBoxLayout>
LoanWindow::LoanWindow() : QWidget()
{
	ml_layout = new QVBoxLayout;
	ml_toolbar = new QToolBar(this);
	ml_submit = new QAction(tr("Submit"));
	ml_quit = new QAction(tr("Quit"));
	ml_forward = new QPushButton(tr("Next"));
	ml_back = new QPushButton(tr("Previous"));
	
	ml_toolbar->setMovable(false);
	ml_toolbar->addSeparator();
	ml_toolbar->addAction(ml_submit);
	ml_toolbar->addSeparator();
	ml_toolbar->addAction(ml_quit);
	ml_toolbar->addSeparator();
	ml_query = new QSqlQuery;
	ml_query->exec("SELECT ISBN, Patron FROM Loans;");
	ml_query->first();
	ml_f1 = new QTableWidgetItem(ml_query->value(0).toString());
	ml_f2 = new QTableWidgetItem(ml_query->value(1).toString());
	ml_display = new QTableWidget;
        ml_display->setColumnCount(2);
        ml_display->setHorizontalHeaderItem(0, ml_f1);
        ml_display->setHorizontalHeaderItem(1, ml_f2);

	connect(ml_submit, SIGNAL(triggered()), this, SLOT(lsubmit()));
	connect(ml_quit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ml_forward, SIGNAL(clicked()), this, SLOT(lforward()));
	connect(ml_back, SIGNAL(clicked()), this, SLOT(lback()));

	ml_layout->addWidget(ml_display);
	ml_layout->addWidget(ml_forward);
	ml_layout->addWidget(ml_back);
	ml_layout->setMenuBar(ml_toolbar);
	setLayout(ml_layout);

}
LoanWindow::~LoanWindow()
{
	delete ml_query;
	delete ml_display;
	delete ml_f1;
	delete ml_f2;
	delete ml_forward;
	delete ml_back;
	delete ml_quit;
	delete ml_toolbar;
	delete ml_submit;
	delete ml_layout;
}

void LoanWindow::lsubmit()
{
        QDialog dialog(this);
        QFormLayout val_submit(&dialog);
        QLineEdit* isbn_val = new QLineEdit(&dialog);
        QLineEdit* patron_val = new QLineEdit(&dialog);

        val_submit.addRow(tr("ISBN:"), isbn_val);
        val_submit.addRow(tr("Patron:"), patron_val);
        QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
        val_submit.addRow(&buttons);
        QObject::connect(&buttons, SIGNAL(accepted()), &dialog, SLOT(accept()));
        QObject::connect(&buttons, SIGNAL(rejected()), &dialog, SLOT(reject()));

        if(dialog.exec() == QDialog::Accepted) {
                int isbn = isbn_val->text().toInt();
                QString patron = patron_val->text();
                QSqlQuery q;
                q.prepare("INSERT INTO Loans(ISBN, Patron)"
                        "VALUES(?, ?);");
                q.addBindValue(isbn);
                q.addBindValue(patron);
                q.exec();
        }
	delete isbn_val;
	delete patron_val;
}
void LoanWindow::lforward()
{
        if(!ml_query->next()) {
                ml_query->previous();
                int pos = ml_query->at();
                lsubmit();
                ml_query->exec("SELECT ISBN, Patron FROM Loans;");
                ml_query->seek(pos);
        }
        ml_f1->setText(ml_query->value(0).toString());
        ml_f2->setText(ml_query->value(1).toString());

}
void LoanWindow::lback()
{
        if(!ml_query->previous()) return;
        ml_f1->setText(ml_query->value(0).toString());
        ml_f2->setText(ml_query->value(1).toString());

}
