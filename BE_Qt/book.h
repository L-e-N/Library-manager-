#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <persistentobject.h>

class Book: public PersistentObject
{
public:
    Book(QString author, QString title, QString isbn, QString publication);
    QString author; //change to QStringList
    QString title;
    QString isbn;
    QString publication;
};

#endif // BOOK_H
