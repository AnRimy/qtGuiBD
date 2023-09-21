#include<menu.h>

Menu::Menu(QWidget *parent) : QMainWindow(parent) {
    parent->setGeometry(0, 0, 800, 600);
    mainFrame = new QFrame(parent);
    mainFrame->setGeometry(0, 0, 800, 600);
    mainFrame->setStyleSheet("background-color: rgb(155, 155, 155);");
    mainFrame->setVisible(true);

    showTableButton = new QPushButton(mainFrame);
    showTableButton->setGeometry(50, 250, 200, 100);
    showTableButton->setVisible(true);
    showTableButton->setText("Редактировать таблицы");

    showDowUpButton = new QPushButton(mainFrame);
    showDowUpButton->setGeometry(550, 250, 200, 100);
    showDowUpButton->setVisible(true);
    showDowUpButton->setText("Работа с файлом");

    sortButton = new QPushButton(mainFrame);
    sortButton->setGeometry(300, 250, 200, 100);
    sortButton->setVisible(true);
    sortButton->setText("Сортировка");

    connect(showTableButton, &QPushButton::clicked, [=]() {
        on_printTable_clicked(parent);
    });

    connect(showDowUpButton, &QPushButton::clicked, [=]() {
        on_dowUp_clicked(parent);
    });

    connect(sortButton, &QPushButton::clicked, [=]() {
        on_sort_clicked(parent);
    });
}

Menu::~Menu(){}
void Menu::on_printTable_clicked(QWidget *parent){
    mainFrame->setVisible(false);
    tableWindow = new TableWindow(parent);
    mainFrame->setVisible(true);
}

void Menu::on_dowUp_clicked(QWidget *parent){
    mainFrame->setVisible(false);
    dowUp = new DowUp(parent);
    mainFrame->setVisible(true);
}

void Menu::on_sort_clicked(QWidget *parent){
    mainFrame->setVisible(false);
    sortT = new SortT(parent);
    mainFrame->setVisible(true);
}
