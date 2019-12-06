#include "persistentattribute.h"

PersistentAttribute::PersistentAttribute(QString name, QVariant::Type type, void * pData) {
    this->name = name;
    this->type = type;
    this->pData = pData;
}
