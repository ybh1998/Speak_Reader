#include "speech_thread.h"

Speech_Thread::Speech_Thread()
{
    position=0;
    running=false;
    speech.setControl("SAPI.SpVoice");
    speech.dynamicCall("SetSyncSpeakTimeout(1000000000)");
}

Speech_Thread::~Speech_Thread()
{

}
void Speech_Thread::run(){
    int len=text.length(),i,j;
    QString read_string;
    running=true;
    while(1){
        read_string.clear();
        QThread::msleep(100);
        for(i=1;position+i<len-1;i++){
            for(j=0;j<seperate.length();j++){
                if(text[position+i]==seperate[j]) goto found;
            }
        }
        found:
        read_string=text.mid(position,i+1);
        if(position+i+1>len) emit select_Changed(position,len);
        else emit select_Changed(position,position+i+1);
        if(read_string.length()>0) speech.dynamicCall("Speak(QString)",read_string);
    }
}
