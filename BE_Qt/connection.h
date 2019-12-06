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
    // Récupération de l'instance db (QSqlDatabase a une unique instance globale)
    QSqlDatabase db = QSqlDatabase::database();

    // Si l'instance n'a pas de connexion, en crée une
    if(!db.isValid()){
        db = QSqlDatabase::addDatabase("QSQLITE");
    }

    // Désactive la connection pour changer le nom de la db auquelle elle est liée
    if(db.isOpen())
    {
        db.close();
    }
    db.setDatabaseName(databaseName); // Lie la connexion à la db choisie (soit nouveau nom, ou path to .db)

    // Active la connection
    if (!db.open()) {
        std::cout << "Unable to open the database" << std::endl;
    }

    return true;
}

// Récupère les livres de la base de données et les renvoie
QList<Book*> getBookList(QWidget *parent)
{
    // Choisi le fichier .db d'où récupérer les livres
    QString databaseName = QFileDialog::getOpenFileName(
                parent,
                "Open a database file",
                "",
                "All Files (*.db)");

    // Connection à cette base de donnée
    createConnection(databaseName);

    QList<Book*> bookList;
    Book book("a","a", "a", "a"); // Pas ouf mais crée un sample de livre pour récupérer le nom de la table...
    QString tableName = book.getTableName();
    QList<PersistentAttribute*> *attributes = book.getAttributeList(); // Récupère la liste des attributs

    // SELECT author, title, isbn, publication FROM <tableName>
    QSqlQuery query;

    QString queryString = "SELECT ";
    for (int j = 0; j < attributes->size(); ++j) {
        if(j>0){
            queryString += ", ";
        }
        queryString += attributes->at(j)->name;
    }
    queryString += " FROM "+tableName;
    query.exec(queryString);

    // Create book and the bookList from the result
    QList<QString> values; // Liste de types différents? ou de QVariant à convert en itérant?
    while(query.next())
    {
        values.clear();
        for(int i=0; i<attributes->size(); i++){
            switch(attributes->at(i)->type){
                case QVariant::String:
                    values.push_back(query.value(attributes->at(i)->name).toString());
                    break;
                default:
                    std::cout << "Not implemented type" << std::endl;
            }
        }
        // Constructeur pour créer l'object persistant itérativement?
        Book *book = new Book(values[0], values[1], values[2], values[3]); // Syntaxes pour mettre la liste en argument?
        bookList.push_back(book);
    }

      displayValidation("Library loaded!");
      return bookList;

      // -- Ancien code --
      //    query.exec("SELECT * FROM "+tableName);

      //    int authorNo = query.record().indexOf("author");
      //   int titleNo = query.record().indexOf("title");
      //   int isbnNo = query.record().indexOf("isbn");
      //   int publicationNo = query.record().indexOf("publication");
      //   while(query.next())
      //   {
      //       QString author = query.value(authorNo).toString();
      //       QString title = query.value(titleNo).toString();
      //       QString isbn = query.value(isbnNo).toString();
      //       QString publication = query.value(publicationNo).toString();
      //       Book *book = new Book(author, title, isbn, publication);
      //       bookList.push_back(book);
      //   }
      // -----------------
}

// Sauvegarde les livres d'une liste donnée dans une base de donnée
static void saveToDatabase(QWidget *parent, QList<Book*> *pBookList, bool newFile)
{
    QList<Book*> bookList = *pBookList; // Récupère le pointeur à la bookList pour pas avoir une copie et avoir des mauvais pointeurs dedans
    QString tableName = bookList[0]->getTableName(); // Récupère le nom de la table
    QList<PersistentAttribute*> *attributes = bookList[0]->getAttributeList(); // Récupère la liste des attributs

    // --------------- CONNECTION A LA DB --------------
    QSqlDatabase db = QSqlDatabase::database();
    // On sauvegarde dans une nouvelle database il n'a pas de connexion active ou si on veut dans un nouveau fichier
    if(!db.isValid() || newFile){
        QString databaseName = QInputDialog::getText(parent, "Save to a database", "What is the name of the file to save in?");
        createConnection(databaseName);
    }

    // Pas commode, au lieu de delete de la databse un livre, on drop tout et on réinsère tout
    QSqlQuery query;
    query.exec(QString("DROP TABLE "+tableName));

    // ---------- CREATION DE LA TABLE -------------
    // RQ: pas obligatoire d'avoir une primary key
    // CREATE TABLE book (author varchar(20) primary key, title varchar(20), isbn varchar(20), publication varchar(20))
    QString queryString = "CREATE TABLE "+tableName+" (";
    for (int i = 0; i <attributes->size(); ++i) {
        if(i>0){
            queryString += ", ";
        }
        QString type;
        switch(attributes->at(i)->type) {
            case QVariant::String :
                type = " varchar (20)";
            break;
            default:
                return;
        }
        queryString += attributes->at(i)->name+type;
    }
    queryString += ")";
    query.exec(queryString);

    // RQ: first attribute is
    // --------------- INSERTION DES LIVRES DANS LA DB --------------
    // INSERT INTO book (author, title, isbn, publication) VALUES (:author, :title, :isbn, :publication)"
    for(int i=0; i<bookList.size(); i+=1){
        queryString = "INSERT INTO "+tableName+" (";

        // INSERT INTO book (author, title, isbn, publication
        for (int j = 0; j <attributes->size(); ++j) {
            if(j>0){
                queryString += ", ";
            }
            queryString += attributes->at(j)->name;
        }

        // INSERT INTO book (author, title, isbn, publication) VALUES (
        queryString += ") VALUES (";

        // INSERT INTO book (author, title, isbn, publication) VALUES (:author, :title, :isbn, :publication)
        for (int j = 0; j <attributes->size(); ++j) {
            if(j>0){
                queryString += ", ";
            }
            queryString += ":"+attributes->at(j)->name;
        }
        queryString += ")";

        // Associe les valeurs du livre aux :author, :title...
        query.prepare(queryString);
        attributes = bookList[i]->getAttributeList();
        for (int j = 0; j <attributes->size(); ++j) {
            QString name = attributes->at(j)->name;
            switch(attributes->at(i)->type) {
                case QVariant::String:
                    query.bindValue(":"+name, *((QString*) attributes->at(j)->pData));
                    break;
                default:
                    return;
            }
        }
        query.exec();
    }
    displayValidation("Library saved!");
}

static void closeDatabase()
{
    QSqlDatabase::removeDatabase(QSqlDatabase::database().connectionName());
}



#endif
