#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <iostream>
#include "book.h"
#include <QVariant>

static bool closeConnection(QSqlDatabase db)
{
    qDebug("drop table");
    QSqlQuery query;
    query.exec("DROP TABLE library"); // Working?
    db.close();
}

static bool createConnection(QSqlDatabase db)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        std::cout << "unable to open the databse" << std::endl;
    }

    std::cout << "open the database" << std::endl;

    QSqlQuery query;
    query.exec("create table library (author varchar(20) primary key, title varchar(20), isbn varchar(10), publication varchar(10))");

    return true;

}

static bool insertBook(Book book)
{
    qDebug("insert book");
    QSqlQuery query;
    query.prepare("INSERT INTO library (author, title, isbn, publication) VALUES (:author, :title, :isbn, :publication)");
    query.bindValue(":author", book.author);
    query.bindValue(":title", book.title);
    query.bindValue(":isbn", book.isbn);
    query.bindValue(":publication", book.publication);
    query.exec();

    query.exec("SELECT author FROM library");
    while(query.next())
    {
        QString author = query.value(0).toString();
        qDebug(author.toLatin1());
    }
}

#endif
