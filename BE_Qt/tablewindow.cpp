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
    connect(newButton, SIGNAL(clicked()), this, SLOT(newLibrary()));

    addButton = new QPushButton(tr("&Add a book"));
    connect(addButton, SIGNAL(clicked()), this, SLOT(addBook()));

    deleteButton = new QPushButton(tr("&Delete a book"));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteBook()));

    loadButton = new QPushButton(tr("&Load a library"));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadLibrary()));

    saveButton = new QPushButton(tr("&Save"));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveLibrary()));

    saveAsButton = new QPushButton(tr("&Save as"));
    connect(saveAsButton, SIGNAL(clicked()), this, SLOT(saveAsLibrary()));

    // -------- LAYOUT -------------
    // Layout vertical des boutons
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(newButton);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(saveAsButton);

    // Layout de la table à gauche et boutons à droite
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(table, 1, 1); // x, y, hauteur, largeur
    layout->addLayout(buttonLayout, 1, 2);
    setLayout(layout); // Active le layout
}

void TableWindow::addBook()
{
    QString author;
    QString title;
    QString isbn;
    QString publication;

    // Récupère les inputs du nouveau livre
    bool ok = false; // ok sert à savoir si l'user n'a pas clické sur cancel pour continuer

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
                    // Création du nouveau livre et ajout à la liste
                    Book* book = new Book(author, title, isbn, publication);
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
    int taille = bookList.size(); // Taille pour limiter la valeur de l'index que l'user peut choisir

    // Demande l'index du livre à supprimer
    bool ok = false;
    int i = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"),
                                     tr("Index:"), 0, 0, taille-1, 1, &ok);
    if (ok)
    {
        delete bookList[i];
        bookList.removeAt(i);
        table->displayList(bookList);
    }

}

// Vide la liste et coupe la connexion à la db
void TableWindow::newLibrary()
{
    bookList.clear();
    table->displayList(bookList);
    closeDatabase();
}

void TableWindow::saveLibrary()
{
    if(bookList.size() != 0){
        saveToDatabase(this, &bookList, false);
    }
}

void TableWindow::saveAsLibrary()
{
    if(bookList.size() != 0){
        saveToDatabase(this, &bookList, true);
    }
}

void TableWindow::loadLibrary()
{
    bookList = getBookList(this);
    table->displayList(bookList);
}

// Destructeur, destruction de toutes les instances crées dynamiquement
TableWindow::~TableWindow()
{
    delete table;
    delete newButton;
    delete addButton;
    delete loadButton;
    delete saveButton;
    delete saveAsButton;

    int taille = bookList.size(); // Taille pour limiter la valeur de l'index que l'user peut choisir
    for(int i=0; i<taille; i++){
        delete bookList[i];
    }
}
