#ifndef SORTT_H
#define SORTT_H

#include<QMainWindow>
#include<QFrame>
#include<QPushButton>


#include <QApplication>
#include <QComboBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QDebug>

#include"databaseManager.h"

class SortT : public QMainWindow {
    Q_OBJECT
public:
    SortT(QWidget *parent = nullptr);
    ~SortT();

private slots:
    void on_back_clicked(QWidget *parent);

private:
    QFrame *mainFrame;

    QPushButton *backButton;

    QComboBox *sortComboBox_medicines;
    QComboBox *sortComboBox_pharmacies;
    QComboBox *sortComboBox_orders;
    QComboBox *sortComboBox_purchaseMedicines;

    QTableView *table_medicines;
    QTableView *table_pharmacies;
    QTableView *table_orders;
    QTableView *table_purchaseMedicines;

    QSqlTableModel *model_medicines;
    QSqlTableModel *model_pharmacies;
    QSqlTableModel *model_orders;
    QSqlTableModel *model_purchaseMedicines;

};
#endif // SORTT_H
