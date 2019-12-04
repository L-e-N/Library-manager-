#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QPushButton>
#include "book.h"
#include <vector>
#include "table.h"
#include <QSqlDatabase>

class TableWindow : public QWidget
{
    Q_OBJECT
    public:
        TableWindow();

    public slots:
        void addBook();
        void saveLibrary();

    private:
        QPushButton *addButton;
        QPushButton *saveButton;
        QList<Book> bookList;
        Table *table;
        QSqlDatabase db;
};

#endif // TABLEWINDOW_H
