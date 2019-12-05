#include "book.h"
#include <QString>

Book::Book(QString givenAuthor, QString givenTitle, QString givenIsbn, QString givenPublication) : PersistentObject("book")
{
    author = givenAuthor;
    title = givenTitle;
    isbn = givenIsbn;
    publication = givenPublication;

    PersistentAttribute* persistent_author = new PersistentAttribute("author", QVariant::String , (void *)(&(this->author)));
    this->addAttributes(persistent_author);
    PersistentAttribute* persistent_title = new PersistentAttribute("title", QVariant::String, (void *)(&(this->title)));
    this->addAttributes(persistent_title);
    PersistentAttribute* persistent_isbn = new PersistentAttribute("isbn", QVariant::String, (void *)(&(this->isbn)));
    this->addAttributes(persistent_isbn);
    PersistentAttribute* persistent_year = new PersistentAttribute("publication", QVariant::String, (void *)(&(this->publication)));
    this->addAttributes(persistent_year);
}
