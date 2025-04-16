// Track.h
#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <vector>

struct Track {
    QString id;
    QString name;
    QString comment;
    QString date;
    std::vector<QString> users;
};

#endif // TRACK_H
