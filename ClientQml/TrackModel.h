#ifndef TRACKMODEL_H
#define TRACKMODEL_H

#include <QAbstractListModel>
#include "Track.h"

class TrackModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum TrackRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        CommentRole,
        DateRole,
        UsersRole
    };

    explicit TrackModel(QObject* parent = nullptr);

    void setTracks(const std::vector<Track>& newTracks);
    void addTrack(const Track& track);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void updateTrackUsers(const QString& trackId, const QStringList& users);

private:
    std::vector<Track> tracks;
};

#endif // TRACKMODEL_H
