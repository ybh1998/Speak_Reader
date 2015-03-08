#include "speech_thread.h"

Speech_Thread::Speech_Thread()
{
    position=0;
    running=false;
}

Speech_Thread::~Speech_Thread()
{

}
void Speech_Thread::init(){
    CoInitialize(NULL);
    CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER, IID_ISpVoice, (void**)&pSpVoice);
    running=true;
    pSpVoice->SetSyncSpeakTimeout(1000000000);
}
void Speech_Thread::uninit(){
    pSpVoice->Release();
    CoUninitialize();
    running=false;
}
void Speech_Thread::run(){
    int len=text.length(),i,j;
    QString read_string;
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
        pSpVoice->Speak(read_string.toStdWString().c_str(), SPF_DEFAULT, NULL);
    }
}
