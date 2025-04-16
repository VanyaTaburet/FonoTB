#ifndef LOGGER_H
#define LOGGER_H

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>

class Logger
{
public:
    static Logger& instance()
    {
        static Logger instance;
        return instance;
    }

    void log(const QString& message)
    {
        QMutexLocker locker(&m_mutex);
        if (m_logFile.isOpen())
        {
            QTextStream out(&m_logFile);
            out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << " - " << message << "\n";
        }
    }

private:
    Logger()
    {
        m_logFile.setFileName("application.log");
        m_logFile.open(QIODevice::Append | QIODevice::Text);
    }

    ~Logger()
    {
        if (m_logFile.isOpen())
        {
            m_logFile.close();
        }
    }

    QFile m_logFile;
    QMutex m_mutex;
};

#endif // LOGGER_H
