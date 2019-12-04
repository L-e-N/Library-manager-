#include "table.h"
#include "book.h"
#include <vector>

Table::Table()
{
    // Instancie les paramètres de la table (taille, ligne, column, headers)
    setFixedSize(460, 450);
    setColumnCount(4);
    setRowCount(10);
    setColumnWidth(0, 100);
    setColumnWidth(1, 200);
    setColumnWidth(2, 50);
    setColumnWidth(3, 100);

    QStringList tableHeaders;
    tableHeaders << "author" << "title" << "isbn" << "publication";
    setHorizontalHeaderLabels(tableHeaders);
}


void Table::displayList(QList<Book> bookList)
{
    int size = bookList.size();
    for(unsigned long i=0; i<size; i+=1){
        setItem(i, 0, new QTableWidgetItem(bookList[i].author));
        setItem(i, 1, new QTableWidgetItem(bookList[i].title));
        setItem(i , 2, new QTableWidgetItem(bookList[i].isbn));
        setItem(i, 3, new QTableWidgetItem(bookList[i].publication));
    }
}
