#ifndef UTIL_H
#define UTIL_H

#include <QMessageBox>

static void displayValidation(const char* msg)
{
    QString string = msg;
    QMessageBox msgBox;
    msgBox.setText(string);
    msgBox.exec();
}

#endif // UTIL_H
