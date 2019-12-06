#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>
#include <QWidget>
#include <book.h>
#include <vector>

class Table: public QTableWidget
{
public:
    Table();
    void displayList(QList<Book*> bookList);
private:
};

#endif // TABLE_H
