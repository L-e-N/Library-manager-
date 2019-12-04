#include "tablewindow.h"
#include "book.h"
#include <vector>
#include "table.h"
#include <QPushButton>
#include <QGridLayout>
#include <QInputDialog>
#include "connection.h"
#include <QVBoxLayout>

TableWindow::TableWindow()
{
    // ---------- OPEN DB ----------
    createConnection(db);

    // ---------- TABLE ------------
    // Init table
    Book book1("Dang", "Arthur", "le", "boss");
    Book book2("Dang", "ArthurvArthurArthurArthur", "le", "boss");
    bookList.push_back(book1);
    bookList.push_back(book2);

    table = new Table();
    table->displayList(bookList);

    // --------- BUTTON ----------
    addButton = new QPushButton(tr("&Add"));
    addButton->show();
    connect(addButton, SIGNAL(clicked()), this, SLOT(addBook()));

    saveButton = new QPushButton(tr("&Save"));
    saveButton->show();
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveLibrary()));

    // -------- LAYOUT -------------
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(addButton, Qt::AlignTop);
    buttonLayout->addWidget(saveButton);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(table, 1, 1); // x, y, hauteur, largeur
    layout->addLayout(buttonLayout, 1, 2);
    setLayout(layout);
}

void TableWindow::addBook()
{
    QString author;
    QString title;
    QString isbn;
    QString publication;

    bool ok = false;
    author = QInputDialog::getText(this, "Add Book", "Who is the author of the book?", QLineEdit::Normal, QString(), &ok);

    if (ok && !author.isEmpty())
    {
        ok = false;
        title = QInputDialog::getText(this, "Add Book", "What is the title of the book?", QLineEdit::Normal, QString(), &ok);

        if (ok && !title.isEmpty())
        {
            ok = false;
            isbn = QInputDialog::getText(this, "Add Book", "What is the isbn of the book?", QLineEdit::Normal, QString(), &ok);

            if (ok && !isbn.isEmpty())
            {
                ok = false;
                publication = QInputDialog::getText(this, "Add Book", "What is the publication of the book?", QLineEdit::Normal, QString(), &ok);

                if(ok)
                {
                    Book book(author, title, isbn, publication);
                    bookList.push_back(book);
                    table->displayList(bookList);
                }
            }
        }
    }
}

void TableWindow::saveLibrary()
{
    insertBook(bookList[0]);
}
