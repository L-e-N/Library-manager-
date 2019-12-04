#include <QApplication>

#include "connection.h"
#include "tableeditor.h"

//! [0]
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if (!createConnection())
        return 1;

    TableEditor editor("library");
    editor.show();
    return app.exec();
}
