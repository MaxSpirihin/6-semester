#ifndef PLAYER_H
#define PLAYER_H
#include <Phonon/VideoPlayer>

class Player : public Phonon::VideoPlayer
{
    Q_OBJECT
public:
    explicit Player(Phonon::Category category, QWidget *parent = 0);
private:
    void mousePressEvent ( QMouseEvent * event );
signals:

public slots:
};

#endif // PLAYER_H
