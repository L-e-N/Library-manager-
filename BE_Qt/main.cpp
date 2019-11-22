#include <QtWidgets>
#include <QtGui>
#include "library.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Library library;
    library.show();

    return app.exec();
}
