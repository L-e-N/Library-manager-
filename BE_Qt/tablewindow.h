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

    // Slots pour chaque handler de click des boutons
    public slots:
        void newLibrary();
        void addBook();
        void deleteBook();
        void saveLibrary();
        void saveAsLibrary();
        void loadLibrary();

    private:
        // UX/UI
        Table *table;
        QPushButton *newButton;
        QPushButton *addButton;
        QPushButton *deleteButton;
        QPushButton *saveButton;
        QPushButton *saveAsButton;
        QPushButton *loadButton;

        // Retient la liste des livres en cache
        QList<Book*> bookList;


};

#endif // TABLEWINDOW_H
