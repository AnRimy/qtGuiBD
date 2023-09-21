#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QDebug>

class DatabaseManager {
public:
    static DatabaseManager& instance();
    QSqlDatabase& database();

private:
    DatabaseManager();
    ~DatabaseManager();
    QSqlDatabase m_db;
};
#endif // DATABASEMANAGER_H
