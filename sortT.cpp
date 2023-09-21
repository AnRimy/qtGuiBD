#include"sortT.h"

SortT::SortT(QWidget *parent): QMainWindow(parent){
    parent->setGeometry(0, 0, 800, 650);
    mainFrame = new QFrame(parent);
    mainFrame->setGeometry(0, 0, 800, 650);
    mainFrame->setStyleSheet("background-color: rgb(155, 155, 155);");
    mainFrame->setVisible(true);

    backButton = new QPushButton(mainFrame);
    backButton->setGeometry(700, 620, 100, 30);
    backButton->setStyleSheet("background-color: rgb(155, 155, 155);");
    backButton->setText("Назад");
    backButton->setVisible(true);
    connect(backButton, &QPushButton::clicked, [=]() {
        on_back_clicked(parent);
    });


    QSqlDatabase db = DatabaseManager::instance().database();
    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных: ";
    }

    sortComboBox_medicines = new QComboBox(mainFrame);
    sortComboBox_medicines->setGeometry(0, 280, 100, 20);
    sortComboBox_medicines->setVisible(true);
    sortComboBox_medicines->addItem("ID");
    sortComboBox_medicines->addItem("Код");
    sortComboBox_medicines->addItem("Название");
    sortComboBox_medicines->addItem("Производитель");
    sortComboBox_medicines->addItem("Цена");

    model_medicines = new QSqlTableModel(mainFrame);
    model_medicines->setTable("Medicines");
    model_medicines->select();

    table_medicines = new QTableView(mainFrame);
    table_medicines->setGeometry(0, 0, 400, 280);
    table_medicines->setStyleSheet("background-color:rgb(0, 0, 0);");
    table_medicines->setVisible(true);
    table_medicines->setModel(model_medicines);

    connect(sortComboBox_medicines, QOverload<int>::of(&QComboBox::activated), [this](int index) {
        QString fieldName;
        switch (index) {
        case 0: fieldName = "id"; break;
        case 1: fieldName = "code"; break;
        case 2: fieldName = "name"; break;
        case 3: fieldName = "manufacturer"; break;
        case 4: fieldName = "price"; break;
        default: fieldName = "id"; break;
        }

        model_medicines->setSort(model_medicines->fieldIndex(fieldName), Qt::AscendingOrder);
        model_medicines->select();
    });





    sortComboBox_pharmacies = new QComboBox(mainFrame);
    sortComboBox_pharmacies->setGeometry(400, 280, 100, 20);
    sortComboBox_pharmacies->setVisible(true);
    sortComboBox_pharmacies->addItem("ID");
    sortComboBox_pharmacies->addItem("Номер");
    sortComboBox_pharmacies->addItem("Название");
    sortComboBox_pharmacies->addItem("Адрес");
    sortComboBox_pharmacies->addItem("Телефон");

    model_pharmacies = new QSqlTableModel(mainFrame);
    model_pharmacies->setTable("Pharmacies");
    model_pharmacies->select();

    table_pharmacies = new QTableView(mainFrame);
    table_pharmacies->setGeometry(400, 0, 400, 280);
    table_pharmacies->setStyleSheet("background-color:rgb(0, 0, 0);");
    table_pharmacies->setVisible(true);
    table_pharmacies->setModel(model_pharmacies);

    connect(sortComboBox_pharmacies, QOverload<int>::of(&QComboBox::activated), [this](int index) {
        QString fieldName;
        switch (index) {
        case 0: fieldName = "id"; break;
        case 1: fieldName = "number"; break;
        case 2: fieldName = "name"; break;
        case 3: fieldName = "address"; break;
        case 4: fieldName = "phone"; break;
        default: fieldName = "id"; break;
        }

        model_pharmacies->setSort(model_pharmacies->fieldIndex(fieldName), Qt::AscendingOrder);
        model_pharmacies->select();
    });




    sortComboBox_orders = new QComboBox(mainFrame);
    sortComboBox_orders->setGeometry(0, 580, 100, 20);
    sortComboBox_orders->setVisible(true);
    sortComboBox_orders->addItem("ID");
    sortComboBox_orders->addItem("Номер");
    sortComboBox_orders->addItem("Дата");
    sortComboBox_orders->addItem("ID Аптеки");
    sortComboBox_orders->addItem("Дата завершения");

    model_orders = new QSqlTableModel(mainFrame);
    model_orders->setTable("Orders");
    model_orders->select();

    table_orders = new QTableView(mainFrame);
    table_orders->setGeometry(0, 300, 400, 280);
    table_orders->setStyleSheet("background-color:rgb(0, 0, 0);");
    table_orders->setVisible(true);
    table_orders->setModel(model_orders);

    connect(sortComboBox_orders, QOverload<int>::of(&QComboBox::activated), [this](int index) {
        QString fieldName;
        switch (index) {
        case 0: fieldName = "id"; break;
        case 1: fieldName = "number"; break;
        case 2: fieldName = "date"; break;
        case 3: fieldName = "pharmacy_id"; break;
        case 4: fieldName = "completed_date"; break;
        default: fieldName = "id"; break;
        }

        model_orders->setSort(model_orders->fieldIndex(fieldName), Qt::AscendingOrder);
        model_orders->select();
    });




    sortComboBox_purchaseMedicines = new QComboBox(mainFrame);
    sortComboBox_purchaseMedicines->setGeometry(400, 580, 100, 20);
    sortComboBox_purchaseMedicines->setVisible(true);
    sortComboBox_purchaseMedicines->addItem("ID");
    sortComboBox_purchaseMedicines->addItem("ID Заказа");
    sortComboBox_purchaseMedicines->addItem("Код Лекарства");
    sortComboBox_purchaseMedicines->addItem("Количество");

    model_purchaseMedicines = new QSqlTableModel(mainFrame);
    model_purchaseMedicines->setTable("PurchaseMedicines");
    model_purchaseMedicines->select();

    table_purchaseMedicines = new QTableView(mainFrame);
    table_purchaseMedicines->setGeometry(400, 300, 400, 280);
    table_purchaseMedicines->setStyleSheet("background-color:rgb(0, 0, 0);");
    table_purchaseMedicines->setVisible(true);
    table_purchaseMedicines->setModel(model_purchaseMedicines);

    connect(sortComboBox_purchaseMedicines, QOverload<int>::of(&QComboBox::activated), [this](int index) {
        QString fieldName;
        switch (index) {
        case 0: fieldName = "id"; break;
        case 1: fieldName = "order_id"; break;
        case 2: fieldName = "medicine_code"; break;
        case 3: fieldName = "quantity"; break;
        default: fieldName = "id"; break;
        }

        model_purchaseMedicines->setSort(model_purchaseMedicines->fieldIndex(fieldName), Qt::AscendingOrder);
        model_purchaseMedicines->select();
    });
}
SortT::~SortT(){}

void SortT::on_back_clicked(QWidget *parent){
    mainFrame->close();
    parent->setGeometry(0, 0, 800, 600);
}
