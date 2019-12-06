#include "table.h"
#include "book.h"
#include <vector>

Table::Table()
{
    // Initialize les paramètres de la table (taille, ligne, column, headers)
    setFixedSize(460, 450);
    setColumnCount(4);
    setRowCount(10);
    setColumnWidth(0, 100);
    setColumnWidth(1, 200);
    setColumnWidth(2, 50);
    setColumnWidth(3, 100);

    // Initialize les headers de la table
    QStringList tableHeaders;
    tableHeaders << "author" << "title" << "isbn" << "publication";
    setHorizontalHeaderLabels(tableHeaders);
}

// Affiche les livres de la liste dans le widget
void Table::displayList(QList<Book*> bookList)
{
    setRowCount(0); // Clear la table

    // Re-initialize la taille de la table
    int size = bookList.size();
    if(size > 10) {
        setRowCount(size);
    } else {
        setRowCount(10);
    }

    // Pour chaque ligne, rajoute les attributs dans la case correspondante
    for(unsigned long i=0; i<size; i+=1){
        QTableWidgetItem author(bookList[i]->author);
        QTableWidgetItem title(bookList[i]->title);
        QTableWidgetItem isbn(bookList[i]->isbn);
        QTableWidgetItem publication(bookList[i]->publication);

        // Empêche ces cases d'être éditable
        author.setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        title.setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        isbn.setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        publication.setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        setItem(i, 0, new QTableWidgetItem(author));
        setItem(i, 1, new QTableWidgetItem(title));
        setItem(i , 2, new QTableWidgetItem(isbn));
        setItem(i, 3, new QTableWidgetItem(publication));
    }
}
