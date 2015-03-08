#include "reader.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QUrl>

Reader::Reader(QObject *parent) : QObject(parent)
{
    ini_file=NULL;
    opened=false;
    position=0,rate=0,vol=80;
    connect(&thread,&Speech_Thread::select_Changed,this,&Reader::select_Changed);
    QFile seperate_file(":/seperate.txt");
    seperate_file.open(QIODevice::ReadOnly);
    QTextStream seperate_stream(&seperate_file);
    thread.seperate=seperate_stream.readAll();
    read(qApp->arguments()[1]);
}

Reader::~Reader()
{

}

void Reader::read(QString url){
    if(ini_file) delete ini_file;
    ini_file=new QSettings(QUrl(url).toLocalFile().append(".ini"),
                           QSettings::IniFormat);
    position=ini_file->value("/Reader/position").toInt();
    QFile txt_file(QUrl(url).toLocalFile());
    if(txt_file.open(QIODevice::ReadOnly)){
        QTextStream txt_stream(&txt_file);
        thread.text=txt_stream.readAll();
        thread.text.replace(QRegExp("\n")," \n");
        emit text_Changed(thread.text);
        opened=true;
        emit select_Changed(position,position);
        return;
    }
    txt_file.setFileName(url);
    if(txt_file.open(QIODevice::ReadOnly)){
        QTextStream txt_stream(&txt_file);
        thread.text=txt_stream.readAll();
        thread.text.replace(QRegExp("\n")," \n");
        emit text_Changed(thread.text);
        opened=true;
        emit select_Changed(position,position);
        return;
    }
}
void Reader::position_save(){
    if(opened)
        ini_file->setValue("/Reader/position",position);
}
void Reader::position_set(int pos){
    position=pos;
    thread.position=position;
}

void Reader::read_start(){
    thread.init();
    thread.pSpVoice->SetRate(rate);
    thread.pSpVoice->SetVolume(vol);
    thread.start();
}
void Reader::read_stop(){
    if(thread.running){
        thread.terminate();
        thread.uninit();
    }
}
void Reader::read_pause(){
    if(thread.running) thread.pSpVoice->Pause();
}
void Reader::read_resume(){
    if(thread.running) thread.pSpVoice->Resume();
}
void Reader::rate_change(int newrate){
    rate=newrate;
    if(thread.running) thread.pSpVoice->SetRate(rate);
}
void Reader::volume_change(int newvol){
    vol=newvol;
    if(thread.running) thread.pSpVoice->SetVolume(vol);
}
