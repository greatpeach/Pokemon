#include "music_thread.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>

music_thread::music_thread(QObject *parent)
    : QThread(parent)
{
}

void music_thread::run()
{
    QMediaPlaylist *music_list = new QMediaPlaylist;
    music_list->addMedia(QUrl::fromLocalFile("C:\\Users\\dell1\\Desktop\\Qt\\Pokemon\\source\\bgm.mp3"));
    music_list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    player = new QMediaPlayer;
    player->setPlaylist(music_list);
    player->play();
    exec();
}

void music_thread::stop_music()
{
    qDebug("end_music");
    player->stop();
}
