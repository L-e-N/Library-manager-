#include "persistentobject.h"

#include "persistentobject.h"

using namespace std;

PersistentObject::PersistentObject(QString table) {
    this->table = table;
    this->attributes = new QList<PersistentAttribute*>;
}

// Ajoute un attribut à la liste des attributs de l'objet
void PersistentObject::addAttributes(PersistentAttribute* newattribute) {
    this->attributes->append(newattribute);
}

// Getters
QString PersistentObject::getTableName(){
    return this->table;
}

QList<PersistentAttribute*> * PersistentObject::getAttributeList(){
    return this->attributes;
}

