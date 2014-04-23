#ifndef __CONFIG__
#define __CONFIG__

//---------------------------------------------------------------------------------------------------------------------------------
#define FPS                     (1.0f / 60.0f)
#define SCREEN_WIDTH            1024
#define SCREEN_HEIGHT           768

#define DEBUG_DRAW              true

#define AUDIO_DEFAULT_VOLUME    1.0f
#define SOUND_DEFAULT_VOLUME    1.0f
#define MUSIC_DEFAULT_VOLUME    1.0f

enum duration_move{
    DM_LEFT = 0,
    DM_TOP = 1,
    DM_RIGHT = 2,
    DM_DOWN = 3,
    DM_NONE = 4
};

//---------------------------------------------------------------------------------------------------------------------------------
#endif //__CONFIG__