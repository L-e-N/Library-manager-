#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <iostream>
#include "book.h"
#include <QVariant>
#include <QSqlRecord>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

#include "util.h"

static bool createConnection(QString databaseName)
{
    QSqlDatabase db = QSqlDatabase::database();

    if(!db.isValid()){
        db = QSqlDatabase::addDatabase("QSQLITE"); // Ouvre une connexion avec le nom par défaut une fois
    }
    if(db.isOpen())
    {
        db.close(); // Ferme pour pouvoir changer le nom
    }

    db.setDatabaseName(databaseName); // Lie la connection à la database name

    if (!db.open()) {
        std::cout << "Unable to open the database" << std::endl;
    }

    return true;
}

QList<Book> getBookList(QWidget *parent)
{
    QString databaseName = QFileDialog::getOpenFileName(
                parent,
                "Open a database file",
                "",
                "All Files (*.db)");

    createConnection(databaseName);

    QList<Book> bookList;
    Book book("a","a", "a", "a"); // Sample book to retrieve tableName..
    QString tableName = book.getTableName();

    QSqlQuery query;
    query.exec(QString("SELECT * FROM "+tableName));

    int authorNo = query.record().indexOf("author");
    int titleNo = query.record().indexOf("title");
    int isbnNo = query.record().indexOf("isbn");
    int publicationNo = query.record().indexOf("publication");
    while(query.next())
    {
        QString author = query.value(authorNo).toString();
        QString title = query.value(titleNo).toString();
        QString isbn = query.value(isbnNo).toString();
        QString publication = query.value(publicationNo).toString();
        Book book(author, title, isbn, publication);
        bookList.push_back(book);
    }

    displayValidation("Library loaded!");

    return bookList;
}

static void saveToDatabase(QWidget *parent, QList<Book> bookList, bool newFile)
{
    QString tableName = bookList[0].getTableName();
    QString databaseName;
    QSqlDatabase db = QSqlDatabase::database(); // Retrouve l'objet db

    // Save dans un nouveau fichier
    if(!db.isValid() || newFile){
        qDebug("Creating a database");
        QString databaseName;
        databaseName = QInputDialog::getText(parent, "Save to a database", "What is the name of the file to save in?");

        createConnection(databaseName);
    }

    // BOURRIN pour save, je delete toute la table et je la recrée..
    QSqlQuery query;
    query.exec(QString("DROP TABLE "+tableName));

    QList<PersistentAttribute*> *attributes = bookList[0].getAttributeList();

    // CREATE TABLE
    // CREATE TABLE <tableName> (author varchar(20) primary key, title varchar(20), isbn..)
    QString queryString = "create table "+tableName+" (";
    QString test =  attributes->at(0)->name;
    for (int i = 0; i <attributes->size(); ++i) {
        QString type;
        switch(attributes->at(i)->type) {
            case QVariant::String :
                type = " varchar (20),";
            break;
            default:
                return;
        }
        queryString += attributes->at(i)->name + " "+type;
        if(i == 0){
            queryString.remove(query.size(), 1); // Remove last character
            queryString += " primary key,";
        }
    }
    queryString.remove(query.size(), 1); // Remove last character ,
    queryString.append(")");

    query.exec(queryString);

    // INSERT INTO book (author, title, isbn, publication) VALUES (:author, :title, :isbn, :publication)"
    int taille = bookList.size();
    for(int i=0; i<taille; i+=1){
        queryString = "INSERT INTO "+tableName+" (";

        // "author, title, isbn, publication"
        for (int j = 0; j <attributes->size(); ++j) {
            if(j>0){
                queryString += ", ";
            }
            queryString += attributes->at(j)->name;
        }

        queryString += ") VALUES (";
        // :author, :title, :isbn, :publication
        for (int j = 0; j <attributes->size(); ++j) {
            if(j>0){
                queryString += ", ";
            }
            queryString += ":"+attributes->at(j)->name;
        }
        queryString += ")";

        query.prepare(queryString);
        for (int j = 0; j <attributes->size(); ++j) {
            QString name = attributes->at(j)->name;
//            QString* data = (QString*) attributes->at(j)->data;
            switch(attributes->at(i)->type) {
                case QVariant::String:
                    query.bindValue(":"+name, bookList[i].author);
                    break;
                default:
                    return;
            }
        }

        query.exec();


    }

//    query.prepare(QString("INSERT INTO "+tableName+" (author, title, isbn, publication) VALUES (:author, :title, :isbn, :publication)"));
//    query.bindValue(":author", bookList[i].author);
//    query.bindValue(":title", bookList[i].title);
//    query.bindValue(":isbn", bookList[i].isbn);
//    query.bindValue(":publication", bookList[i].publication);
//    query.exec();

    displayValidation("Library saved!");
}

static void closeDatabase()
{
    QSqlDatabase::removeDatabase(QSqlDatabase::database().connectionName());
}



#endif
