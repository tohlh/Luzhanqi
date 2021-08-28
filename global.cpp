#include "global.h"

namespace network {
    Server *server = nullptr;
    Client *client = nullptr;
};

namespace timer {
    QTimer *timer = new QTimer();
    int currTimer = 20;
    int overTimeCnt = 0;
};

namespace player {
    bool ready = false;
    bool theyReady = false;
    bool isTurn = false;
    int steps = 0;
    int myColor = -1;
    int myLastColor = -1;
    int theirColor = -1;
    int theirLastColor = -1;
};
