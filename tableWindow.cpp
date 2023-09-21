#include "tableWindow.h"
#include <unistd.h>

TableWindow::TableWindow(QWidget *parent) : QMainWindow(parent) {
    parent->setGeometry(0, 0, 1000, 700);
    mainFrame = new QFrame(parent);
    mainFrame->setGeometry(0, 0, 1000, 700);
    mainFrame->setStyleSheet("background-color: rgb(155, 155, 155);");
    mainFrame->setVisible(true);

    QSqlDatabase& db = DatabaseManager::instance().database();
    db.setDatabaseName("./zadanie.db");
    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных.";
    }
    query = new QSqlQuery(db);

    // Создание таблицы "Лекарства"
    if (!query->exec("CREATE TABLE IF NOT EXISTS Medicines ("
                     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                     "code TEXT, "
                     "name TEXT, "
                     "manufacturer TEXT, "
                     "price REAL)")) {
        qDebug() << "Ошибка создания таблицы 'Лекарства': " << query->lastError().text();
    }

    // Создание таблицы "Аптеки"
    if (!query->exec("CREATE TABLE IF NOT EXISTS Pharmacies ("
                     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                     "number TEXT, "
                     "name TEXT, "
                     "address TEXT, "
                     "phone TEXT)")) {
        qDebug() << "Ошибка создания таблицы 'Аптеки': " << query->lastError().text();
    }

    // Создание таблицы "Заявки"
    if (!query->exec("CREATE TABLE IF NOT EXISTS Orders ("
                     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                     "number TEXT, "
                     "date TEXT, "
                     "pharmacy_id INTEGER, "
                     "completed_date TEXT, "
                     "FOREIGN KEY (pharmacy_id) REFERENCES Pharmacies(id))")) {
        qDebug() << "Ошибка создания таблицы 'Заявки': " << query->lastError().text();
    }

    // Создание таблицы "Закупки лекарственных препаратов"
    if (!query->exec("CREATE TABLE IF NOT EXISTS PurchaseMedicines ("
                     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                     "order_id INTEGER, "
                     "medicine_code TEXT, "
                     "quantity INTEGER, "
                     "FOREIGN KEY (order_id) REFERENCES Orders(id), "
                     "FOREIGN KEY (medicine_code) REFERENCES Medicines(code))")) {
        qDebug() << "Ошибка создания таблицы 'Закупки лекарственных препаратов': " << query->lastError().text();
    }

    qDebug() << "База данных успешно создана.";


    table_widget_medicines = new QTableView(mainFrame);
    model_medicines = new QSqlTableModel(mainFrame, db);
    createTable(table_widget_medicines, model_medicines, 0, 0, 500, 300, "Medicines");

    table_widget_pharmacies = new QTableView(mainFrame);
    model_pharmacies = new QSqlTableModel(mainFrame, db);
    createTable(table_widget_pharmacies, model_pharmacies, 500, 0, 500, 300, "Pharmacies");

    table_widget_orders = new QTableView(mainFrame);
    model_orders = new QSqlTableModel(mainFrame, db);
    createTable(table_widget_orders, model_orders, 0, 350, 500, 300, "Orders");

    table_widget_purchaseMedicines = new QTableView(mainFrame);
    model_purchaseMedicines = new QSqlTableModel(mainFrame, db);
    createTable(table_widget_purchaseMedicines, model_purchaseMedicines, 500, 350, 500, 300, "PurchaseMedicines");


    addDataButton_medicines = new QPushButton(mainFrame);
    createButton(addDataButton_medicines, 0, 300, 100, 50, "Добавить");
    connect(addDataButton_medicines, &QPushButton::clicked, this, [this]() {
        on_addButton_clicked(model_medicines);
    });

    delDataButton_medicines = new QPushButton(mainFrame);
    createButton(delDataButton_medicines, 100, 300, 100, 50, "Удалить");
    connect(delDataButton_medicines, &QPushButton::clicked, this, [this]() {
        on_delButton_clicked(model_medicines, table_widget_medicines);
    });

    addDataButton_pharmacies = new QPushButton(mainFrame);
    createButton(addDataButton_pharmacies, 500, 300, 100, 50, "Добавить");
    connect(addDataButton_pharmacies, &QPushButton::clicked, this, [this]() {
        on_addButton_clicked(model_pharmacies);
    });

    delDataButton_pharmacies = new QPushButton(mainFrame);
    createButton(delDataButton_pharmacies, 600, 300, 100, 50, "Удалить");
    connect(delDataButton_pharmacies, &QPushButton::clicked, this, [this]() {
        on_delButton_clicked(model_pharmacies, table_widget_pharmacies);
    });

    addDataButton_orders = new QPushButton(mainFrame);
    createButton(addDataButton_orders, 0, 650, 100, 50, "Добавить");
    connect(addDataButton_orders, &QPushButton::clicked, this, [this]() {
        on_addButton_clicked(model_orders);
    });

    delDataButton_orders = new QPushButton(mainFrame);
    createButton(delDataButton_orders, 100, 650, 100, 50, "Удалить");
    connect(delDataButton_orders, &QPushButton::clicked, this, [this]() {
        on_delButton_clicked(model_orders, table_widget_orders);
    });

    addDataButton_purchaseMedicines = new QPushButton(mainFrame);
    createButton(addDataButton_purchaseMedicines, 500, 650, 100, 50, "Добавить");
    connect(addDataButton_purchaseMedicines, &QPushButton::clicked, this, [this]() {
        on_addButton_clicked(model_purchaseMedicines);
    });

    delDataButton_purchaseMedicines = new QPushButton(mainFrame);
    createButton(delDataButton_purchaseMedicines, 600, 650, 100, 50, "Удалить");
    connect(delDataButton_purchaseMedicines, &QPushButton::clicked, this, [this]() {
        on_delButton_clicked(model_purchaseMedicines, table_widget_purchaseMedicines);
    });

    backButton = new QPushButton(mainFrame);
    backButton->setVisible(true);
    backButton->setGeometry(900, 650, 100, 50);
    backButton->setText("Назад");
    connect(backButton, &QPushButton::clicked, [=]() {
        on_back_clicked(parent);
    });
}


TableWindow::~TableWindow(){}
void TableWindow::createTable(QTableView *table, QSqlTableModel *model, int x, int y, int width, int height, QString name){
    table->setGeometry(x, y, width, height);
    table->setStyleSheet("background-color: rgb(0, 0, 0);");
    table->setVisible(true);
    model->setTable(name);
    model->select();
    table->setModel(model);
}


void TableWindow::createButton(QPushButton *button, int x, int y, int width, int height, QString name){
    button->setGeometry(x, y, width, height);
    button->setText(name);
    button->setVisible(true);
}


void TableWindow::on_addButton_clicked(QSqlTableModel *model) {
    model->insertRow(model->rowCount());
}


void TableWindow::on_delButton_clicked(QSqlTableModel *model, QTableView *table) {
    QItemSelectionModel *selection = table->selectionModel();
    QModelIndexList selectedRows = selection->selectedRows();

    for (const QModelIndex &index : selectedRows) {
        model->removeRow(index.row());
    }

    model->submitAll();
}
void TableWindow::on_back_clicked(QWidget *parent){
    mainFrame->close();
    parent->setGeometry(0, 0, 800, 600);
}
