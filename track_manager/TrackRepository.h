#ifndef TRACKREPOSITORY_H
#define TRACKREPOSITORY_H

#include <QObject>
#include <QSqlDatabase>
#include <QList>
#include <QUuid>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

class TrackRepository : public QObject
{
    Q_OBJECT
public:
    explicit TrackRepository(QSqlDatabase& db, QObject* parent = nullptr);

    // CRUD операции
    QList<QStringList> getAllTracks(); // Получить все записи
    bool updateComment(int id, const QString& newComment);
    bool addTrack(const QString& sysname, const QString& comment); // Добавить запись
    bool deleteTrack(int id); // Удалить запись

protected:
    QSqlDatabase& m_db;
    QString uuidMy;
    void uuidGen(const QString& sysname){
        QSqlQuery query(m_db);
        QUuid  myUuid = QUuid::createUuid();
        qDebug() <<  "Def form: " << myUuid;
        this->uuidMy =  myUuid.toString(QUuid::WithoutBraces);
        qDebug() << "With -: " << this->uuidMy;
        query.prepare(
                "INSERT INTO worksession (ses_id, sysname, begtime, endtime, ses_uid)"  
                 "VALUES (?, ?, NOW(), NOW(), ?);");

        query.addBindValue(sysname);
        query.addBindValue(sysname);
        query.addBindValue(this->uuidMy);

        if (!query.exec()) {
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        }

    }
    QString getUuid () {return uuidMy;}

};

#endif // TRACKREPOSITORY_H
