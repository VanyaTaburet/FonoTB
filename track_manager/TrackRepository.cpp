#include "TrackRepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QUuid>

TrackRepository::TrackRepository(QSqlDatabase& db, QObject* parent) 
    : QObject(parent), m_db(db) {}

QList<QStringList> TrackRepository::getAllTracks() {
    QList<QStringList> result;
    
    QSqlQuery query("SELECT sys_id, sysname, dt, commentary FROM track", m_db);
    while(query.next()) {
        QStringList row;
        row << query.value(0).toString(); // ID
        row << query.value(1).toString(); // Название
        row << query.value(2).toString(); // Дата
        row << query.value(3).toString(); // Комментарий
        result.append(row);
    }
    
    return result;
}

bool TrackRepository::updateComment(int id, const QString& newComment) {
    QSqlQuery query(m_db);
    query.prepare("UPDATE track SET commentary = ? WHERE sys_id = ?");
    query.addBindValue(newComment);
    query.addBindValue(id);
    
    if(!query.exec()) {
        qDebug() << "Ошибка обновления комментария:" << query.lastError().text();
        return false;
    }
    return true;
}

bool TrackRepository::addTrack(const QString& sysname, const QString& comment) 
{
    QSqlQuery query(m_db);
    uuidGen(sysname);
    query.prepare(
       "INSERT INTO track (ses_id, sysname, commentary, dt, recstate, ses_uid) "
       "VALUES (?, ?, ?, NOW(), 1, ?)" // 1 = ACTIVE, 0 = INACTIVE и т.д
    );
    
    query.addBindValue(sysname);
    query.addBindValue(sysname);
    query.addBindValue(comment);
    query.addBindValue(getUuid());

    if(!query.exec()) {
        qDebug() << "Ошибка добавления записи:" << query.lastError().text();
        return false;
    }
    return true;
}

bool TrackRepository::deleteTrack(int id) {
    m_db.transaction();
    QSqlQuery query(m_db);
    
    query.prepare("SELECT ses_uid FROM track  WHERE sys_id = ?");
    query.addBindValue(id);

    if(!query.exec() || !query.next()){
        qDebug() << "Ошибка считывания uuid:" << query.lastError().text();
	m_db.rollback();
        return false;
    }

    QString uuid = query.value(0).toString();
    query.prepare("DELETE FROM worksession WHERE ses_uid = ?");
    query.addBindValue(uuid);

    if(!query.exec()){
        qDebug() << "Ошибка удаления сессии:" << query.lastError().text();
        m_db.rollback();
	return false;
    }

    query.prepare("DELETE FROM track WHERE sys_id = ?");
    query.addBindValue(id);

    if(!query.exec()){
        qDebug() << "Ошибка удаления записи:" << query.lastError().text();
	m_db.rollback();
        return false;
    }

    return m_db.commit();
}

