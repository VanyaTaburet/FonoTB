#include "TrackModel.h"
#include <QDebug>

TrackModel::TrackModel(QObject* parent)
    : QAbstractListModel(parent) {
}

void TrackModel::setTracks(const std::vector<Track>& newTracks) {
    beginResetModel();
    tracks = newTracks;
    endResetModel();
}

void TrackModel::addTrack(const Track& track) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    tracks.push_back(track);
    endInsertRows();
}

int TrackModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return static_cast<int>(tracks.size());
}

QVariant TrackModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= static_cast<int>(tracks.size())) {
        return QVariant();
    }

    const Track& track = tracks.at(index.row());
    switch (role) {
    case IdRole:
        return track.id;
    case NameRole:
        return track.name;
    case CommentRole:
        return track.comment;
    case DateRole:
        return track.date;
    case UsersRole:
        qDebug() << "trackUsers: " << track.users;
        return QVariant::fromValue(track.users);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TrackModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[CommentRole] = "comment";
    roles[DateRole] = "date";
    roles[UsersRole] = "users";
    return roles;
}

void TrackModel::updateTrackUsers(const QString& trackId, const QStringList& users) {
    for (int i = 0; i < tracks.size(); ++i) {
        if (tracks[i].id == trackId) {
<<<<<<< HEAD
            tracks[i].users = std::vector<QString>(users.begin(), users.end());
=======
            tracks[i].users = users.toVector().toStdVector();
>>>>>>> ed77ba25d9687baffcebfe9c1339e63e9e3c856a
            QModelIndex index = createIndex(i, 0);
            emit dataChanged(index, index, { UsersRole });
            break;
        }
    }
}
