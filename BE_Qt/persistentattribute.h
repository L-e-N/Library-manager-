#ifndef PERSISTENTATTRIBUTE_H
#define PERSISTENTATTRIBUTE_H

#include <Qvariant>
#include <QString>

class PersistentAttribute
{
public:
    QString name;
    QVariant::Type type;
    void *pData; // pointeur vers la donnée
    PersistentAttribute(QString, QVariant::Type, void *);
};

#endif // PERSISTENTATTRIBUTE_H
