#include "global.h"

namespace network {
    Server *server = nullptr;
    Client *client = nullptr;
};

namespace timer {
    QTimer *timer = new QTimer();
    int currTimer = 0;
};

namespace player {
    bool isTurn = false;
};
