#include <QWidget>
#include <QPushButton>
#include <QtSql>
#include <QGridLayout>

#ifndef __LOANQUERYWINDOW_H
#define __LOANQUERYWINDOW_H

class QLabel;
class QLineEdit;
class QPushButton;
class QListView;
class QGridLayout;
class QTableWidget;

class LoanQueryWindow : public QWidget
{
        Q_OBJECT
        private:
                QLineEdit* m_author;
                QLineEdit* m_patron;
                QPushButton* m_submit;
                QLabel* m_author_label;
                QLabel* m_patron_label;
                QTableWidget* m_table;
                QGridLayout* m_layout;

        private slots:
                void submit();

        public:
                LoanQueryWindow();
                ~LoanQueryWindow();         
};


#endif

