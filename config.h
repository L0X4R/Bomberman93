#pragma once

// PROGRAM DATA.
#define FRAMERATE 144
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960

#define MAP_WIDTH 20
#define MAP_HEIGHT 15
#define TILE_MARGIN 4
#define TILE_SIZE 64

// LOG MESSAGES.
#define LOG(msg) cout << "[INFO]: " << msg << endl;
#define GOOD(msg) cout << "[SUCCESS]: " << msg << endl;
#define ERROR(msg) cout << "[ERROR]: " << msg << endl;
#define ADD(msg) cout << "[CREATED]: " << msg << endl;
#define DEL(msg) cout << "[REMOVED]: " << msg << endl;