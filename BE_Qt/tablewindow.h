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
        ~TableWindow();

    public slots:
        void newLibrary();
        void addBook();
        void deleteBook();
        void saveLibrary();
        void saveAsLibrary();
        void loadLibrary();

    private:
        QPushButton *newButton;
        QPushButton *addButton;
        QPushButton *deleteButton;
        QPushButton *saveButton;
        QPushButton *saveAsButton;
        QPushButton *loadButton;
        QList<Book> bookList;
        Table *table;
};

#endif // TABLEWINDOW_H
