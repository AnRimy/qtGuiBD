#ifndef MENU_H
#define MENU_H
#include<QMainWindow>
#include<QFrame>
#include<QPushButton>

#include "tableWindow.h"
#include"dowUp.h"
#include"sortT.h"

class Menu : public QMainWindow {
    Q_OBJECT
public:
    Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_printTable_clicked(QWidget *parent);
    void on_dowUp_clicked(QWidget *parent);
    void on_sort_clicked(QWidget *parent);

private:
    QFrame *mainFrame;

    QPushButton *showTableButton;
    QPushButton *showDowUpButton;
    QPushButton *sortButton;

    TableWindow *tableWindow;
    DowUp *dowUp;
    SortT *sortT;
};


#endif // MENU_H
