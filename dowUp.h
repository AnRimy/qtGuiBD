#ifndef DOWUP_H
#define DOWUP_H

#include<QMainWindow>
#include<QFrame>
#include<QPushButton>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QSqlError>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include"databaseManager.h"

class DowUp : public QMainWindow {
    Q_OBJECT
public:
    DowUp(QWidget *parent = nullptr);
    ~DowUp();

private slots:
    bool loadFromTextFile(const QString &filename);
    bool saveToTextFile(const QString &filename);
    void on_backButton_clicked();


private:
    QFrame *mainFrame;
    QPushButton *downloadButton;
    QPushButton *uploadButton;
    QPushButton *backButton;
};
#endif // DOWUP_H
