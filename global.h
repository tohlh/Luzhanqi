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
    extern int overTimeCnt;
};

namespace player {
    extern bool isTurn;
    extern int steps;
    extern int myColor;
    extern int myLastColor;
    extern int theirColor;
    extern int theirLastColor;
};

#endif // GLOBAL_H
