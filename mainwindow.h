#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QFrame>
#include <QTableView>
#include <QSqlTableModel>
#include <QPushButton>

#include<menu.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_visitMainFrame_clicked();
    void on_add_row_clicked();
    void on_del_row_clicked();

    void on_log_button_clicked();
    void on_inButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QFrame *tableFrame;
    QTableView *table_widget;
    QSqlTableModel *model;

    QPushButton *add_row;
    QPushButton *del_row;
    Menu *menu;
};
#endif // MAINWINDOW_H
