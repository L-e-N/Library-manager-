#include <QtWidgets>
#include <QtGui>

#include "tablewindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TableWindow tableWindow;
    tableWindow.show();

    return app.exec();
}
