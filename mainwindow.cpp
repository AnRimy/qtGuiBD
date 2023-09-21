#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tableFrame = new QFrame(this);
    tableFrame->setVisible(false);
    tableFrame->setGeometry(0, 0, 781, 600);
    tableFrame->setStyleSheet("background-color: rgb(155, 155, 155);");

    table_widget = new QTableView(tableFrame);
    table_widget->setGeometry(0, 0, 781, 500);
    table_widget->setStyleSheet("background-color: rgb(0, 0, 0);");

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./db.db");

    if (db.open())
        qDebug() << "Database opened";
    else
        qDebug() << "Database not opened";

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE IF NOT EXISTS users(login TEXT, password TEXT);");

    model = new QSqlTableModel(tableFrame, db);
    model->setTable("users");
    model->select();
    table_widget->setModel(model);

    add_row = new QPushButton(tableFrame);
    add_row->setGeometry(10, 550, 50, 50);
    add_row->setStyleSheet("background-color: rgb(255, 0, 0);");

    del_row = new QPushButton(tableFrame);
    del_row->setGeometry(400, 550, 50, 50);
    del_row->setStyleSheet("background-color: rgb(255, 0, 0);");


    connect(add_row, &QPushButton::clicked, this, &MainWindow::on_add_row_clicked);
    connect(del_row, &QPushButton::clicked, this, &MainWindow::on_del_row_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_visitMainFrame_clicked()
{
    if (ui->mainFrame->isVisible()) {
        ui->mainFrame->setVisible(false);
        tableFrame->setVisible(true);
    }
    else {
        ui->mainFrame->setVisible(true);
        tableFrame->setVisible(false);
    }
}


void MainWindow::on_add_row_clicked()
{
    model->insertRow(model->rowCount());
}

void MainWindow::on_del_row_clicked()
{
    QItemSelectionModel *select = table_widget->selectionModel();
    QModelIndexList selectedRows = select->selectedRows();

    for (QModelIndex index : selectedRows) {
        model->removeRow(index.row());
    }
    model->select();
}

void MainWindow::on_log_button_clicked()
{

    QString login = ui->loginEnter->text();
    QString password = ui->passwordEnter->text();

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE login =:login AND password =:password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.finish();
    if (query.exec()){
        if (query.next()){
            db.close();
            ui->log_button->setStyleSheet("background-color: rgb(0, 255, 0);");
            ui->mainFrame->setVisible(false);
            ui->visitMainFrame->setVisible(false);
            menu = new Menu(this);
        }
        else
            ui->log_button->setStyleSheet("background-color: rgb(255, 0, 0);");
    }
}

void MainWindow::on_inButton_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (login, password) VALUES (:login, :password)");

    query.bindValue(":login", ui->loginEnter->text());
    query.bindValue(":password", ui->passwordEnter->text());
    query.finish();
    if (query.exec()) {
        qDebug() << "Запись успешно добавлена";
    } else {
        qDebug() << "Ошибка выполнения запроса INSERT:";
    }
}

