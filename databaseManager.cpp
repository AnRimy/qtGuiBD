#include <databaseManager.h>

DatabaseManager::DatabaseManager() {
    // Настройка базы данных (как вы делали ранее)
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("./zadanie.db");

    if (!m_db.open()) {
        qDebug() << "Ошибка подключения к базе данных.";
    }
}

DatabaseManager::~DatabaseManager() {
    m_db.close();
}

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

QSqlDatabase& DatabaseManager::database() {
    return m_db;
}
