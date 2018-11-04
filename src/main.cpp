#include "wordboard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase sqlite = QSqlDatabase::addDatabase("QSQLITE");
    sqlite.setDatabaseName("database.db");
    if(!sqlite.open())
    {
        QMessageBox::critical(nullptr, QObject::tr("Error"), sqlite.lastError().text());
        return 1;
    }

    WordBoard w(sqlite);
    w.show();

    return a.exec();
}
