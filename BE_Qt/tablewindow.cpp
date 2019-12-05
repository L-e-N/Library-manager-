#include "tablewindow.h"
#include "book.h"
#include <vector>
#include "table.h"
#include <QPushButton>
#include <QGridLayout>
#include <QInputDialog>
#include "connection.h"
#include <QVBoxLayout>
#include "util.h"

TableWindow::TableWindow()
{
    // ---------- TABLE ------------
    table = new Table();
    table->displayList(bookList);

    // --------- BUTTON ----------
    newButton = new QPushButton(tr("&New Library"));
    newButton->show();
    connect(newButton, SIGNAL(clicked()), this, SLOT(newLibrary()));

    addButton = new QPushButton(tr("&Add a book"));
    addButton->show();
    connect(addButton, SIGNAL(clicked()), this, SLOT(addBook()));

    deleteButton = new QPushButton(tr("&Delete a book"));
    deleteButton->show();
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteBook()));

    loadButton = new QPushButton(tr("&Load a library"));
    loadButton->show();
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadLibrary()));

    saveButton = new QPushButton(tr("&Save"));
    saveButton->show();
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveLibrary()));

    saveAsButton = new QPushButton(tr("&Save as"));
    saveAsButton->show();
    connect(saveAsButton, SIGNAL(clicked()), this, SLOT(saveAsLibrary()));

    // -------- LAYOUT -------------
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(newButton);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(saveAsButton);

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

                    displayValidation("Book added!");
                }
            }
        }
    }
}

void TableWindow::deleteBook()
{
    int taille = bookList.size();
    bool ok = false;
    int i = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"),
                                     tr("Index:"), 0, 0, taille-1, 1, &ok);
    if (ok)
    {
        bookList.removeAt(i);
        table->displayList(bookList);
    }

}

void TableWindow::newLibrary()
{
    bookList.clear();
    table->displayList(bookList);
    closeDatabase();
}

void TableWindow::saveLibrary()
{
    if(bookList.size() != 0){
        saveToDatabase(this, bookList, false);
    }
}

void TableWindow::saveAsLibrary()
{
    if(bookList.size() != 0){
        saveToDatabase(this, bookList, true);
    }
}

void TableWindow::loadLibrary()
{
    bookList = getBookList(this);
    table->displayList(bookList); // Problème, affiche encore les anciennes valeurs si pas écrites par dessus.
}

TableWindow::~TableWindow()
{
    delete table;
    delete newButton;
    delete addButton;
    delete loadButton;
    delete saveButton;
    delete saveAsButton;
}
