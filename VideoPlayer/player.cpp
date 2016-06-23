#include "player.h"


Player::Player(Phonon::Category category,QWidget *parent) :
    Phonon::VideoPlayer(category,parent)
{
}

void Player::mousePressEvent (QMouseEvent *event)
{
    if (isPlaying())
        pause();
    else
        play();
}
