#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QPushButton;
class QSqlTableModel;
QT_END_NAMESPACE

//! [0]
class TableEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TableEditor(const QString &tableName, QWidget *parent = nullptr);

private slots:
    void submit();

private:
    QPushButton *submitButton;
    QPushButton *revertButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QSqlTableModel *model;
};
//! [0]

#endif
