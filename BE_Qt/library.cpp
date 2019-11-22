#include <QtGui>
#include <QtWidgets>
#include "library.h"

Library::Library(QWidget *parent)
    : QWidget(parent)
{   // Labels, fields
    QLabel *authorLabel = new QLabel(tr("Author(s):"));
    authorLine = new QLineEdit; //authorLine defined in library.h TODO change to QStringList
    authorLine->setReadOnly(true); //sont mis en mode lecture seule, de façon à autoriser l'affichage mais pas la modification du contact courant.

    QLabel *titleLabel = new QLabel(tr("Title:"));
    titleText = new QTextEdit; //Must be a QString
    titleText->setReadOnly(true);

    QLabel *isbnLabel = new QLabel(tr("ISBN:"));
    isbnLine = new QLineEdit; //Must be a QString
    isbnLine->setReadOnly(true);

    QLabel *publicationLabel = new QLabel(tr("Publication year:"));
    publicationLine = new QLineEdit; //TODO change to an int
    publicationLine->setReadOnly(true);

    // Buttons, Widgets, signal connection
    addButton = new QPushButton(tr("&Add"));
    addButton->show();

    submitButton = new QPushButton(tr("&Submit"));
    submitButton->hide();

    cancelButton = new QPushButton(tr("&Cancel"));
    cancelButton->hide();

    loadButton = new QPushButton(tr("&Load..."));
    loadButton->setToolTip(tr("Load books from a file")); //info displays when hovering over

    saveButton = new QPushButton(tr("Sa&ve..."));
    saveButton->setToolTip(tr("Save books to a file"));
    //saveButton->setEnabled(false);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addBook()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submitBook()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadFromFile()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveToFile()));

    // Button layouts
    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton, Qt::AlignTop);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);
    buttonLayout1->addWidget(loadButton);
    buttonLayout1->addWidget(saveButton);
    buttonLayout1->addStretch();

    // Label and fields layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(authorLabel, 0, 0);
    mainLayout->addWidget(authorLine, 0, 1);
    mainLayout->addWidget(titleLabel, 1, 0, Qt::AlignTop);
    mainLayout->addWidget(titleText, 1, 1);
    mainLayout->addWidget(isbnLabel, 2, 0, Qt::AlignTop);
    mainLayout->addWidget(isbnLine, 2, 1);
    mainLayout->addWidget(publicationLabel, 3, 0, Qt::AlignTop);
    mainLayout->addWidget(publicationLine, 3, 1);
    mainLayout->addLayout(buttonLayout1, 1, 2);

    setLayout(mainLayout);
    setWindowTitle(tr("Simple Library"));
}
/* nous stockons les détails du dernier contact affiché dans oldName et
 * oldAddress. Ensuite, nous vidons ces champs de saisie et nous désactivons
 * le mode lecture seule. Le focus est placé sur authorLine et on affiche
 * submitButton et cancelButton.
  */
void Library::addBook()
{
    oldAuthor = authorLine->text();
    oldTitle = titleText->toPlainText();
    oldIsbn = isbnLine->text();
    oldPublication = publicationLine->text();

    authorLine->clear(); //make the field blank
    titleText->clear();
    isbnLine->clear();
    publicationLine->clear();

    authorLine->setReadOnly(false); //allow writing in the field
    authorLine->setFocus(Qt::OtherFocusReason);
    titleText->setReadOnly(false);
    isbnLine->setReadOnly(false);
    publicationLine->setReadOnly(false);

    addButton->setEnabled(false);
    submitButton->show();
    cancelButton->show();
}

void Library::submitBook()
{
    QString author = authorLine->text();
    QString title = titleText->toPlainText();
    QString isbn = isbnLine->text();
    QString publication = publicationLine->text();
// on extraie les détails du livre, on vérifie que les champs author et title ne sont pas vides
    if ( author.isEmpty()|| title.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter an author and title."));
        return;
    }
     // si le livre n'existe pas on l'ajoute
    if (!books.contains(title)) {
        books.insert(title, author);
        QMessageBox::information(this, tr("Add Successful"),
            tr("\"%1\" has been added to your system.").arg(title));
    } else {
        QMessageBox::information(this, tr("Add Unsuccessful"),
            tr("Sorry, \"%1\" is already in your system.").arg(title));
        return;
    }
    // on restaure les boutons a leur etat normal
    if (books.isEmpty()) {
        authorLine->clear();
        titleText->clear();
        isbnLine->clear();
        publicationLine->clear();
    }

    authorLine->setReadOnly(true);
    titleText->setReadOnly(true);
    addButton->setEnabled(true);
    submitButton->hide();
    cancelButton->hide();
}
/*La méthode cancel() restaure les détails du dernier contact, active addButton,
 et cache submitButton et cancelButton.
 */
void Library::cancel()
{
    authorLine->setText(oldAuthor);
    authorLine->setReadOnly(true);

    titleText->setText(oldTitle);
    titleText->setReadOnly(true);

    isbnLine->setText(oldIsbn);
    isbnLine->setReadOnly(true);

    publicationLine->setText(oldPublication);
    publicationLine->setReadOnly(true);

    addButton->setEnabled(true);
    submitButton->hide();
    cancelButton->hide();
}

void Library::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, //on récupere le nom du fichier
        tr("Save Address Book"), "",
        tr("Address Book (*.abk);;All Files (*)"));
//si le fileName n'est pas vide on créé un object QFile. On essaie d'ouvrir le fichier en ecriture, si ca echoue on en informe l'utilisateur
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }
        //on instancie un object QDataStream out afin d'écrire dans le fichier
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        out << books;
    }
}

void Library::loadFromFile()
{//ib récupere fileName
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Address Book"), "",
        tr("Address Book (*.abk);;All Files (*)"));
//si fileName n'est pas vide on tente d'ouvrir en lecture
    if (fileName.isEmpty())
        return;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }
//on instancie un object QDataStream in afin d'écrire dans le fichier
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);
        books.empty();   // empty existing books
        in >> books;

        if (books.isEmpty()) {
            QMessageBox::information(this, tr("No books in file"),
                tr("The file you are attempting to open contains no books."));
        } else {
            QMap<QString, QString>::iterator i = books.begin();
            authorLine->setText(i.key());
            titleText->setText(i.value());
        }
    }
    //on met à jour l'interface afin d'activer et de désactiver les boutons de façon appropriée.
    //updateInterface(NavigationMode);
}
