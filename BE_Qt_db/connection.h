
#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

/*
    This file defines a helper function to open a connection to an
    in-memory SQLITE database and to create a test table.

    If you want to use another database, simply modify the code
    below. All the examples in this directory use this function to
    connect to a database.
*/
//! [0]
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        return false;
    }

    QSqlQuery query;
    query.exec("create table library (id int primary key, "
               "firstname varchar(20), lastname varchar(20))");
    query.exec("insert into library values(101, 'Danny', 'Young')");
    query.exec("insert into library values(102, 'Christine', 'Holand')");
    query.exec("insert into library values(103, 'Lars', 'Gordon')");
    query.exec("insert into library values(104, 'Lais', 'Gordan')");

    query.prepare("INSERT INTO library (id, firstname, lastname) VALUES (:id, :firstname, :lastname)");
    query.bindValue(":id", 105);
    query.bindValue(":firstname", "Bart");
    query.bindValue(":lastname", "Simpson");
    query.exec();

    return true;
}
//! [0]

#endif
