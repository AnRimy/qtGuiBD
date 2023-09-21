#include<dowUp.h>

DowUp::DowUp(QWidget *parent) : QMainWindow(parent) {
    parent->setGeometry(0, 0, 800, 600);
    mainFrame = new QFrame(parent);
    mainFrame->setGeometry(0, 0, 800, 600);
    mainFrame->setStyleSheet("background-color: rgb(155, 155, 155);");
    mainFrame->setVisible(true);

    downloadButton = new QPushButton(mainFrame);
    downloadButton->setGeometry(100, 250, 200, 100);
    downloadButton->setVisible(true);
    downloadButton->setText("Загрузить из файла");

    uploadButton = new QPushButton(mainFrame);
    uploadButton->setGeometry(500, 250, 200, 100);
    uploadButton->setVisible(true);
    uploadButton->setText("Выгрузить в файл");

    backButton = new QPushButton(mainFrame);
    backButton->setGeometry(700, 550, 100, 50);
    backButton->setVisible(true);
    backButton->setText("Назад");

    connect(downloadButton, &QPushButton::clicked, [=]() {
        loadFromTextFile("down.txt");
    });
    connect(uploadButton, &QPushButton::clicked, [=]() {
        saveToTextFile("out.txt");
    });
    connect(backButton, &QPushButton::clicked,this,  &DowUp::on_backButton_clicked);
}
DowUp::~DowUp(){}


// Загрузка данных из текстового файла в базу данных
bool DowUp::loadFromTextFile(const QString &filename) {
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка открытия файла:" << file.errorString();
            return false;
    }

    QTextStream in(&file);
    QSqlDatabase db = DatabaseManager::instance().database();

    // Создайте объект priceRegex только один раз
    QRegularExpression dataRegex("^[a-zA-Z0-9\\s]+$");

    while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList data = line.split(',');

            if (data.size() < 4) {
                qDebug() << "Ошибка: некорректные данные в строке:" << line;
                continue;
            }

            // Проверка данных
            for (const QString& item : data) {
                if (!dataRegex.match(item).hasMatch()) {
                    qDebug() << "Ошибка валидации данных:" << item;
                    continue;
                }
            }

            QSqlQuery query(db);
            query.prepare("INSERT INTO Medicines (code, name, manufacturer, price) VALUES (?, ?, ?, ?)");
            query.bindValue(0, data[0]);
            query.bindValue(1, data[1]);
            query.bindValue(2, data[2]);
            query.bindValue(3, data[3].toDouble());

            if (!query.exec()) {
                qDebug() << "Ошибка выполнения SQL-запроса:" << query.lastError().text();
                    continue; // Пропустить запись при ошибке
            }
    }

    file.close();
    downloadButton->setStyleSheet("background-color:rgb(0, 255, 0);");
    return true;
}

bool DowUp::saveToTextFile(const QString &filename) {
    QFile file(filename);

    // Открываем файл только для записи
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Ошибка открытия файла для записи:" << file.errorString();
        return false;
    }

    QTextStream out(&file);
    QSqlDatabase db = DatabaseManager::instance().database();

    QSqlQuery query(db);
    if (!query.exec("SELECT code, name, manufacturer, price FROM Medicines")) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        file.close();
        return false;
    }

    while (query.next()) {
        QString line = query.value(0).toString() + "," +
                       query.value(1).toString() + "," +
                       query.value(2).toString() + "," +
                       QString::number(query.value(3).toDouble(), 'f', 2);
        out << line << "\n";
    }

    file.close();
    uploadButton->setStyleSheet("background-color:rgb(0, 255, 0);");
    return true;
}

void DowUp::on_backButton_clicked(){
    mainFrame->close();
}
