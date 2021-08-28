# 2021夏-程序设计训练（杜立恒 - 计01）

清华大学2021夏季学期 - 程序设计训练 - 大作业（一）- 军棋

# 报告

我的军旗对战大作业分成了以下几个主要的部分（大字母开头均为类）：

1. `main`
2. `MainWindow` - 主窗口页面
3. `Chessboard` - 棋盘背景
4. `ChessGrid` - 维持棋盘与棋子状态
5. `Validator` - 判断正确走棋、吃子和胜负
6. `ChessPiece` - 棋子的类
7. `Grid` - 棋盘上各空格的类
8. `global` - 共享的变量和对象
9. `Server` - 服务器
10. `Client` - 客户端
11. `Command` - 处理通过网络传输的信息

以上各类之间的调用关系

```
(6 -> 7) -> 5 -> 4 -> 3 -> 2 -> 1
(9, 10) -> 8 (共享资源)
```

## `Chesspiece` 类

每一个棋子都为 `Chesspiece` 类（`QLabel` 子类），当中储存的数据包括了：当前棋子是哪一方、当前棋子是哪一种和当前棋子在棋盘上的坐标位置。

为了方便记录所有棋子的种类和他们之间的吃子关系，我构造了以下的 `enum`

```cpp
typedef enum {
    junqi = 0,
    gongbing,
    paizhang,
    lianzhang,
    yingzhang,
    tuanzhang,
    lvzhang,
    shizhang,
    junzhang,
    siling,
    dilei,
    zhadan,
} chessPieceTypedef;
```

从工兵至司令都有着小到大的关系。

## `Grid` 类

`Grid` （也是 `QLabel` 子类）记录了棋盘上每个格的当前状态，其中包括了当前格子的坐标位置、当前格子是否为空，不为空的话格子当前有着哪一个 `Chesspiece`。当中也有成员函数用作放置棋子

## `Chessboard` 类

`Chessboard` 控制棋盘的背景，并持有 `Chessgrid` 对象。它在每次创建新游戏时会创建一个新的 `Chessgrid` 对象。

## `ChessGrid` 类
`ChessGrid` 类是整个游戏最主要的部分，它负责初始化游戏，包括随机布局棋子，以及维持游戏过程中每个棋子的位置和双方所持有的棋子，并接收和处理用户所作的每个操作。`ChessGrid` 中最重要的是以下提到的 `actionStruct` 结构。

## 棋子的移动和销毁

棋子移动的时候调用了 `QLabel::move()`函数，将棋子移动至 `ChessGrid` 上的特定的坐标（这里所指的坐标是具体的像素坐标，`ChessPiece` 和 `Grid` 内所记录的是以棋盘作为参考的简化坐标，即一个 5 x 12 的坐标系统）。

棋子销毁的时候则调用了 `QLabel::remove()` 函数，将棋子在 `ChessGrid` 上删除。

## 记录动作的 `actionStruct` 结构
为了统一当前用户以及网络另一端用户的动作的处理形式，我构造了 `actionStruct` 方便记录所有的动作。

``` cpp
struct actionStruct {
    int id;
    int xCoord;
    int yCoord;
};
```

其中，`id` 为已被点击棋子的 `id`（每一个棋子都有独特的`id`），若点击棋盘上空格则统一记为 `-1`。
`xCoord` 和 `yCoord` 则分别是被棋子或空格的 `x` 与 `y` 坐标（非像素）。

对战期间的所有动作会被交由 `ChessGrid` 内的 `appendAction` 槽处理并随后记录在 `actionStruct` 中。在对比前一个动作时，`appendAction` 能判断当前动作为选棋、取消选项、移动或者吃子。例如：前一个动作点击了**棋子A**，紧接着的下一个动作点击**棋子B**，代表了用户想用**棋子A**吃**棋子B**；前一个动作点击了**棋子A**，紧接着的下一个动作点击了**空格B**，代表了用户想将**棋子A**移动至**空格B**。

## 网络数据传输
用户所作的每一个动作将从 `Server` 或 `Client` 通过 `QTcpSocket` 传到网络另一端的用户。其中，被传的数据为以下形式

1. `!sta <50 个棋子的排列顺序>`: 服务器在游戏刚开始时会传送**已随机排列后**的棋子排列顺序给客户端。
2. `!act id x y`: `id`、`x`、`y` 对应 `actionStruct` 中的三个变量。 此数据形式也有可能后缀 `!pas`，收到的话意味着另一端已经走了一步并轮到自己了。
3. `!end color`: 代表游戏结束，其中 `color` 为获胜方。

基本上，不管是当前用户的动作或是从网络传来的动作，所有的动作都用以下信号/槽机制处理。

```cpp
sendAction(int type, int id, int x, int y) // 信号
// 1) 用户点击 Grids 或 Chesspiece 时, 2) 收到另一端用户的动作时

appendAction(int type, int id, int x, int y) // 槽
// ChessGrid 类中
```

## 公用数据 `Global`

储存在 `Global` 中的变量和指针能由 (1) - (7) 所读取与更新，其中 `global` 有着4种命名空间：

1. 与网络相关的 `network` 
```cpp
namespace network {
    extern Server* server;
    extern Client* client;
};
```
2. 与计时相关的 `timer`
```cpp
namespace timer {
    extern QTimer* timer;
    extern int currTimer;
    extern int overTimeCnt;
};
```
3. 与用户相关的 `player`
```cpp
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
```

将这些变量储存在 `global` 的好处在于这些常用的的资源将维持在集中的状态，避免出现不同对象维持着各自状态的情况。

## `Validator` 对象
Validator 对象有三个主要的函数: `checkLost`, `checkMove`, `checkAttack`

1. `checkLost` 在每一次用户作出一个操作后被调用，它负责检测棋盘上两方棋子是否无棋可走，并判胜负。
2. `checkMove(ChessPiece* chess, int x, int y)` 将判断`chess` 是否能合法移动到坐标为 (`x`, `y`) 的空格处。
3. `checkAttack(ChessPiece* chess1, ChessPiece* chess2)` 将判断 `chess1` 是否可以合法吃 `chess2`，并返回相应的结果：毁灭`chess2`、`chess1` 方获胜（正确扛起军旗）或双方同时毁灭。
