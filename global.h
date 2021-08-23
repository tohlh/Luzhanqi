#ifndef GLOBAL_H
#define GLOBAL_H
#include <QTimer>
#include "server.h"
#include "client.h"

namespace network {
    extern Server* server;
    extern Client* client;
};

namespace timer {
    extern QTimer* timer;
    extern int currTimer;
};

namespace player {
    extern bool isTurn;
    extern int steps;
    extern int color;
    extern int lastColor;
};

#endif // GLOBAL_H
