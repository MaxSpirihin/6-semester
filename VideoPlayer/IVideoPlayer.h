#ifndef IVIDEOPLAYER_H
#define IVIDEOPLAYER_H
#include "main.h"

class IVideoPlayer
{
 public:
 virtual void Start(int argc, char *argv[]) = 0;
 virtual void Play(QString filemane,int mode) = 0;
};


#endif // IVIDEOPLAYER_H
