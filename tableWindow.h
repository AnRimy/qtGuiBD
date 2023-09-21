#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include<QMainWindow>
#include<QFrame>
#include<QSqlQuery>
#include<QTableView>
#include<QSqlTableModel>
#include<QSqlDatabase>
#include<QDebug>
#include<QtSql>
#include<QPushButton>

#include "databaseManager.h"


class TableWindow : public QMainWindow {

public:
    TableWindow(QWidget *parent);
    ~TableWindow();
    void createTable(QTableView *table, QSqlTableModel *model, int x, int y, int width, int height, QString name);
    void createButton(QPushButton *button, int x, int y, int width, int height, QString name);

private slots:
    void on_addButton_clicked(QSqlTableModel *model);
    void on_delButton_clicked(QSqlTableModel *model, QTableView *table);
    void on_back_clicked(QWidget *parent);

private:
    QPushButton *addDataButton_medicines;
    QPushButton *delDataButton_medicines;

    QPushButton *addDataButton_pharmacies;
    QPushButton *delDataButton_pharmacies;

    QPushButton *addDataButton_orders;
    QPushButton *delDataButton_orders;

    QPushButton *addDataButton_purchaseMedicines;
    QPushButton *delDataButton_purchaseMedicines;

    QPushButton *backButton;

    QFrame *mainFrame;
    QSqlDatabase db;
    QSqlQuery *query;

    QTableView *table_widget_medicines;
    QTableView *table_widget_pharmacies;
    QTableView *table_widget_orders;
    QTableView *table_widget_purchaseMedicines;

    QSqlTableModel *model_medicines;
    QSqlTableModel *model_pharmacies;
    QSqlTableModel *model_orders;
    QSqlTableModel *model_purchaseMedicines;
};

#endif // TABLEWINDOW_H
