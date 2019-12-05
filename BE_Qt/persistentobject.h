#ifndef PERSISTENTOBJECT_H
#define PERSISTENTOBJECT_H

#include <persistentattribute.h>
#include <QList>
#include <QString>

class PersistentObject {

    private:
        QList<PersistentAttribute*> *attributes;
        QString table;

    public:
        PersistentObject(QString);
        void addAttributes(PersistentAttribute*);
        QString getTableName();
        QList<PersistentAttribute*> * getAttributeList();
};

#endif // PERSISTENTOBJECT_H