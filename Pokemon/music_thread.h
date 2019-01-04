#ifndef MUSIC_THREAD_H
#define MUSIC_THREAD_H

#include <QThread>
#include <QMediaPlayer>

class music_thread : public QThread
{
    Q_OBJECT

public:
    explicit music_thread(QObject *parent = nullptr);

protected:
    void run();

public slots:
    void stop_music();

private:
    QMediaPlayer *player;
};

#endif // MUSIC_THREAD_H
