#include "book.h"
#include <QString>

Book::Book(QString givenAuthor, QString givenTitle, QString givenIsbn, QString givenPublication)
{
    author = givenAuthor;
    title = givenTitle;
    isbn = givenIsbn;
    publication = givenPublication;
}
