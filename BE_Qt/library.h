#ifndef LIBRARY_H
#define LIBRARY_H
#include <QWidget>
#include <QtGui>
#include <QMap>

class QLabel;
class QLineEdit;
class QTextEdit;
class QPushButton;

class Library : public QWidget
{
    Q_OBJECT

public:
    Library(QWidget *parent = 0);

public slots:
    void addBook();
    void submitBook();
    void cancel();
    // save and load library
    void saveToFile();
    void loadFromFile();

private:
    QPushButton *addButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;

    QLineEdit *authorLine;
    QTextEdit *titleText;
    QLineEdit *isbnLine;
    QLineEdit *publicationLine;

    QMap<QString, QString> books; //dictionary of (title, author)
    QString oldAuthor; //change to QStringList
    QString oldTitle;
    QString oldIsbn;
    QString oldPublication;

    // save and load library
    QPushButton *loadButton;
    QPushButton *saveButton;
};

#endif
