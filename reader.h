#ifndef READER_H
#define READER_H

#include <QObject>
#include <QSettings>
#include "speech_thread.h"

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(QObject *parent = 0);
    ~Reader();
    Speech_Thread thread;
    QSettings *ini_file;
    bool opened;
    int position,rate,vol;
    Q_PROPERTY(QString text READ text NOTIFY text_Changed)
    QString text(){
        return thread.text;
    }
    Q_INVOKABLE void read(QString url);
    Q_INVOKABLE void position_save();
    Q_INVOKABLE void position_set(int pos);
    Q_INVOKABLE void read_start();
    Q_INVOKABLE void read_stop();
    Q_INVOKABLE void read_pause();
    Q_INVOKABLE void read_resume();
    Q_INVOKABLE void rate_change(int newrate);
    Q_INVOKABLE void volume_change(int newvol);
signals:
    void text_Changed(QString &text);
    void select_Changed(int begin,int end);
public slots:
};

#endif // READER_H
