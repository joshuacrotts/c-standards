#ifndef MAIN_H
#define MAIN_H

#include "commons.h"
#include "../lib/stds/include/draw.h"
#include "../lib/stds/include/text.h"

App app;
Stage stage;
extern Background* background;

extern void initGame(const char*, int, int);
extern void updateCamera(Entity*);
extern void loop();

#endif
