#ifndef GLOBAL_H
#define GLOBAL_H
#include <QTimer>
#include "server.h"
#include "client.h"
#include "player.h"

namespace network {
    extern Server* server;
    extern Client* client;
};

namespace timer {
    extern QTimer* timer;
    extern int currTimer;
};

namespace player {
    extern Player* player;
    extern bool isTurn;
};

#endif // GLOBAL_H
