#ifndef PERSISTENTOBJECT_H
#define PERSISTENTOBJECT_H

#include <persistentattribute.h>
#include <QList>
#include <QString>

class PersistentObject {

    private:
        QString table;
        QList<PersistentAttribute*> *attributes;

    public:
        PersistentObject(QString);
        void addAttributes(PersistentAttribute*);
        QString getTableName();
        QList<PersistentAttribute*> * getAttributeList();

        void saveToDatabase();
};

#endif // PERSISTENTOBJECT_H
