#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QTextStream>
#include <QUuid>
#include "TrackRepository.h"

void displayMenu() {
    qDebug() << "\n=== Меню управления записями ===";
    qDebug() << "1. Показать все записи";
    qDebug() << "2. Добавить новую запись";
    qDebug() << "3. Обновить комментарий";
    qDebug() << "4. Удалить запись";
    qDebug() << "5. Выход";
    qDebug() << "Выберите действие (1-5):";
}

void showAllRecords(TrackRepository& repo) {
    auto tracks = repo.getAllTracks();
    if(tracks.isEmpty()) {
        qDebug() << "В базе нет записей.";
        return;
    }

    qDebug() << "\nСписок всех записей:";
    qDebug() << "ID\tНазвание\tДата\tКомментарий";
    qDebug() << "----------------------------------------";
    for(const auto& track : tracks) {
        qDebug() << track[0] << "\t" << track[1].left(10) << "\t" 
                 << track[2] << "\t" << track[3];
    }
}

void addNewRecord(TrackRepository& repo) {
    QTextStream stream(stdin);
    QString name, date, comment;

    qDebug() << "\nДобавление новой записи:";
    qDebug() << "Введите название поста:";
    name = stream.readLine();
    
    qDebug() << "Введите комментарий:";
    comment = stream.readLine();

    if(repo.addTrack(name, comment)) {
        qDebug() << "Запись успешно добавлена!";
    } else {
        qDebug() << "Ошибка при добавлении записи!";
    }
}

void updateComment(TrackRepository& repo) {
    QTextStream stream(stdin);
    int id;
    QString newComment;

    showAllRecords(repo);
    
    qDebug() << "\nВведите ID записи для обновления:";
    id = stream.readLine().toInt();
    
    qDebug() << "Введите новый комментарий:";
    newComment = stream.readLine();

    if(repo.updateComment(id, newComment)) {
        qDebug() << "Комментарий успешно обновлен!";
    } else {
        qDebug() << "Ошибка при обновлении!";
    }
}

void deleteRecord(TrackRepository& repo) {
    QTextStream stream(stdin);
    int id;

    showAllRecords(repo);
    
    qDebug() << "\nВведите ID записи для удаления:";
    id = stream.readLine().toInt();

    if(repo.deleteTrack(id)) {
        qDebug() << "Запись успешно удалена!";
    } else {
        qDebug() << "Ошибка при удалении!";
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    
    QString sessionUId = QUuid::createUuid().toString(QUuid::WithoutBraces);

    // Настройка подключения
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("dfpostdb");
    db.setUserName("postgres");
    db.setPassword("31415926");
    
    if(!db.open()) {
        qDebug() << "Ошибка подключения к БД:";
        return -1;
    }

    TrackRepository repo(db);
    QTextStream stream(stdin);
    int choice = 0;

    while(choice != 5) {
        displayMenu();
        choice = stream.readLine().toInt();

        switch(choice) {
            case 1: showAllRecords(repo); break;
            case 2: addNewRecord(repo); break;
            case 3: updateComment(repo); break;
            case 4: deleteRecord(repo); break;
            case 5: qDebug() << "Выход..."; break;
            default: qDebug() << "Неверный выбор!"; break;
        }
    }

    db.close();
    return 0;
}
