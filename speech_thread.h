#ifndef SPEECH_THREAD_H
#define SPEECH_THREAD_H

#include <QObject>
#include <QThread>
#include <sapi.h>
#include <atlbase.h>

class Speech_Thread : public QThread
{
    Q_OBJECT
public:
    Speech_Thread();
    ~Speech_Thread();
    ISpVoice *pSpVoice;
    void init();
    void uninit();
    QString text,seperate;
    int position;
    bool running;
    void run();
signals:
    void select_Changed(int begin,int end);
};

#endif // SPEECH_THREAD_H
