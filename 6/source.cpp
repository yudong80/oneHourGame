// [1]헤더를 인클루드하는 곳

#include <stdio.h>  // [1-1]표준 입출력 헤더를 인클루드한다
#include <stdlib.h> // [1-2]표준 라이브러리 헤더를 인클루드한다
#include <time.h>   // [1-3]시간 관리 헤더를 인클루드한다
#include <conio.h>  // [1-4]콘솔 입출력 헤더를 인클루드한다
#include <vector>   // [1-5]벡터 헤더를 인클루드한다

// [2]상수를 정의하는 곳

#define MAZE_WIDTH  (8)                 // [2-1]미로의 너비를 정의한다
#define MAZE_HEIGHT (8)                 // [2-2]미로의 높이를 정의한다

#define GOAL_X      (MAZE_WIDTH - 1)    // [2-3]목표 지점의 열을 정의한다
#define GOAL_Y      (MAZE_HEIGHT - 1)   // [2-4]목표 지점의 행을 정의한다

// [3]열거 상수를 정의하는 곳 

// [3-1]방위의 종류를 정의한다
enum
{
    DIRECTION_NORTH,    // [3-1-1]북
    DIRECTION_WEST,     // [3-1-2]서
    DIRECTION_SOUTH,    // [3-1-3]남
    DIRECTION_EAST,     // [3-1-4]동
    DIRECTION_MAX       // [3-1-5]방위의 개수
};

// [3-2]플레이어로부터의 상대 위치 종류를 정의한다
enum
{
    LOCATION_FRONT_LEFT,    // [3-2-1]왼쪽 앞
    LOCATION_FRONT_RIGHT,   // [3-2-2]오른쪽 앞
    LOCATION_FRONT,         // [3-2-3]앞쪽
    LOCATION_LEFT,          // [3-2-4]왼쪽
    LOCATION_RIGHT,         // [3-2-5]오른쪽
    LOCATION_CENTER,        // [3-2-6]중심
    LOCATION_MAX            // [3-2-7]위치의 개수
};

// [4]구조체를 선언하는 곳

// [4-1]벡터의 구조체를 선언한다
typedef struct {
    int x, y;// [4-1-1]좌표
} VEC2;

// [4-2]미로 칸의 구조체를 선언한다 
typedef struct {
    bool walls[DIRECTION_MAX];  // [4-2-1]각 방위의 벽 유무 
} TILE;

// [4-3]플레이어의 구조체를 선언한다
typedef struct {
    VEC2 position;  // [4-3-1]좌표
    int direction;  // [4-3-2]향하고 있는 방위
} CHARACTER;

// [5]변수를 선언하는 곳

// [5-1]각 방위의 벡터를 선언한다
VEC2 directions[] =
{
    { 0,-1},    // DIRECTION_NORTH  북
    {-1, 0},    // DIRECTION_WEST   서
    { 0, 1},    // DIRECTION_SOUTH  남
    { 1, 0}     // DIRECTION_EAST   동
};

// [5-2]기준이 되는 아스키아트를 선언한다
const char* all =
"L       /\n"
"#L     /#\n"
"#|L _ /|#\n"
"#|#|#|#|#\n"
"#|#|_|#|#\n"
"#|/   L|#\n"
"#/     L#\n"
"/       L\n";

// [5-3]왼쪽 전방 벽의 아스키아트를 선언한다
const char* frontLeftNorth =
"         \n"
"         \n"
"  _      \n"
" |#|     \n"
" |_|     \n"
"         \n"
"         \n"
"         \n";

// [5-4]오른쪽 전방 벽의 아스키아트를 선언한다
const char* frontRightNorth =
"         \n"
"         \n"
"      _  \n"
"     |#| \n"
"     |_| \n"
"         \n"
"         \n"
"         \n";

// [5-5]전방 앞쪽 벽의 아스키아트를 선언한다
const char* frontNorth =
"         \n"
"         \n"
"    _    \n"
"   |#|   \n"
"   |_|   \n"
"         \n"
"         \n"
"         \n";

// [5-6]전방 왼쪽 벽의 아스키아트를 선언한다
const char* frontWest =
"         \n"
"         \n"
" |L      \n"
" |#|     \n"
" |#|     \n"
" |/      \n"
"         \n"
"         \n";

// [5-7]전방 오른쪽 벽의 아스키아트를 선언한다
const char* frontEast =
"         \n"
"         \n"
"      /| \n"
"     |#| \n"
"     |#| \n"
"      L| \n"
"         \n"
"         \n";

// [5-8]왼쪽 전방 벽의 아스키아트를 선언한다
const char* leftNorth =
"         \n"
"_        \n"
"#|       \n"
"#|       \n"
"#|       \n"
"_|       \n"
"         \n"
"         \n";

// [5-9]오른쪽 전방 벽의 아스키아트를 선언한다
const char* rightNorth =
"         \n"
"        _\n"
"       |#\n"
"       |#\n"
"       |#\n"
"       |_\n"
"         \n"
"         \n";

// [5-10]앞쪽 벽의 아스키아트를 선언한다
const char* north =
"         \n"
"  _____  \n"
" |#####| \n"
" |#####| \n"
" |#####| \n"
" |_____| \n"
"         \n"
"         \n";

// [5-11]왼쪽 벽의 아스키아트를 선언한다
const char* west =
"L        \n"
"#L       \n"
"#|       \n"
"#|       \n"
"#|       \n"
"#|       \n"
"#/       \n"
"/        \n";

// [5-12]오른쪽 벽의 아스키아트를 선언한다
const char* east =
"        /\n"
"       /#\n"
"       |#\n"
"       |#\n"
"       |#\n"
"       |#\n"
"       L#\n"
"        L\n";

// [5-13]아스키아트의 테이블을 선언한다
const char* aaTable[LOCATION_MAX][DIRECTION_MAX] =
{
    // LOCATION_FRONT_LEFT  왼쪽 앞
    {
        frontLeftNorth,     // DIRECTION_NORTH  북쪽
        NULL,               // DIRECTION_WEST   서쪽
        NULL,               // DIRECTION_SOUTH  남쪽
        NULL                // DIRECTION_EAST   동쪽
    },

    // LOCATION_FRONT_RIGHT 오른쪽 앞
    {
        frontRightNorth,    // DIRECTION_NORTH  북쪽
        NULL,               // DIRECTION_WEST   서쪽
        NULL,               // DIRECTION_SOUTH  남쪽
        NULL                // DIRECTION_EAST   동쪽
    },

    // LOCATION_FRONT       앞쪽
    {
        frontNorth,         // DIRECTION_NORTH  북쪽
        frontWest,          // DIRECTION_WEST   서쪽
        NULL,               // DIRECTION_SOUTH  남쪽
        frontEast           // DIRECTION_EAST   동쪽
    },

    // LOCATION_LEFT        왼쪽
    {
        leftNorth,          // DIRECTION_NORTH  북쪽
        NULL,               // DIRECTION_WEST   서쪽
        NULL,               // DIRECTION_SOUTH  남쪽
        NULL                // DIRECTION_EAST   동쪽
    },

    // LOCATION_RIGHT       오른쪽
    {
        rightNorth,         // DIRECTION_NORTH  북쪽
        NULL,               // DIRECTION_WEST   서쪽
        NULL,               // DIRECTION_SOUTH  남쪽
        NULL                // DIRECTION_EAST   동쪽
    },

    // LOCATION_CENTER      중심
    {
        north,              // DIRECTION_NORTH  북쪽
        west,               // DIRECTION_WEST   서쪽
        NULL,               // DIRECTION_SOUTH  남쪽
        east                // DIRECTION_EAST   동쪽
    }
};

// [5-14]플레이어로부터의 상대 좌표 테이블을 선언한다
VEC2 locations[DIRECTION_MAX][LOCATION_MAX] =
{
    // DIRECTION_NORTH  북쪽
    {
        {-1,-1},    // LOCATION_FRONT_LEFT  왼쪽 앞
        { 1,-1},    // LOCATION_FRONT_RIGHT 오른쪽 앞
        { 0,-1},    // LOCATION_FRONT       앞
        {-1, 0},    // LOCATION_LEFT        왼쪽
        { 1, 0},    // LOCATION_RIGHT       오른쪽
        { 0, 0}     // LOCATION_CENTER      중심
    },

    // DIRECTION_WEST   서쪽
    {
        {-1, 1},    // LOCATION_FRONT_LEFT  왼쪽 앞
        {-1,-1},    // LOCATION_FRONT_RIGHT 오른쪽 앞
        {-1, 0},    // LOCATION_FRONT       앞
        { 0, 1},    // LOCATION_LEFT        왼쪽
        { 0,-1},    // LOCATION_RIGHT       오른쪽
        { 0, 0}     // LOCATION_CENTER      중심
    },

    // DIRECTION_SOUTH  남쪽
    {
        { 1, 1},    // LOCATION_FRONT_LEFT  왼쪽 앞
        {-1, 1},    // LOCATION_FRONT_RIGHT 오른쪽 앞
        { 0, 1},    // LOCATION_FRONT       앞
        { 1, 0},    // LOCATION_LEFT        왼쪽
        {-1, 0},    // LOCATION_RIGHT       오른쪽
        { 0, 0}     // LOCATION_CENTER      중심
    },

    // DIRECTION_EAST   동쪽
    {
        { 1,-1},    // LOCATION_FRONT_LEFT  왼쪽 앞
        { 1, 1},    // LOCATION_FRONT_RIGHT 오른쪽 앞
        { 1, 0},    // LOCATION_FRONT       앞
        { 0,-1},    // LOCATION_LEFT        왼쪽
        { 0, 1},    // LOCATION_RIGHT       오른쪽
        { 0, 0}     // LOCATION_CENTER      중심
    }
};

TILE maze[MAZE_HEIGHT][MAZE_WIDTH];  // [5-15]미로를 선언한다

CHARACTER player;// [5-16]플레이어를 선언한다

// [6]함수를 선언하는 곳

// [6-1]벡터를 더하는 함수를 선언한다
VEC2 VecAdd(VEC2 _v0, VEC2 _v1)
{
    // [6-1-1]벡터를 더해서 반환한다
    return
    {
        _v0.x + _v1.x,
        _v0.y + _v1.y
    };
}

// [6-2]대상 좌표가 미로의 범위 내인지 여부를 판정하는 함수를 선언한다
bool IsInsideMaze(VEC2 _position)
{
    // [6-2-1]대상 좌표가 미로의 범위 내인지 여부를 반환한다
    return (_position.x >= 0)
        && (_position.x < MAZE_WIDTH)
        && (_position.y >= 0)
        && (_position.y < MAZE_HEIGHT);
}

// [6-3]벽을 파는 함수를 선언한다
void DigWall(VEC2 _position, int _direction)
{
    // [6-3-1]대상 좌표가 미로 범위 내인지 여부를 판정한다
    if (!IsInsideMaze(_position))
    {
        return;// [6-3-2]함수를 빠져나간다
    }

    // [6-3-3]대상 벽을 판다
    maze[_position.y][_position.x].walls[_direction] = false;

    // [6-3-4]옆 칸의 좌표를 선언한다
    VEC2 nextPosition = VecAdd(_position, directions[_direction]);

    // [6-3-5]옆 칸이 미로의 범위 내인지 여부를 판정한다
    if (IsInsideMaze(nextPosition))
    {
        // [6-3-6]옆방의 파는 벽의 방위를 선언한다
        int nextDirection = (_direction + 2) % DIRECTION_MAX;

        // [6-3-7]옆 방의 벽을 판다
        maze[nextPosition.y][nextPosition.x].walls[nextDirection] = false;
    }
}

// [6-4]대상 벽을 파도 좋은지 여부를 판정하는 함수를 선언한다
bool CanDigWall(VEC2 _position, int _direction)
{
    // [6-4-1]옆의 좌표를 선언한다
    VEC2 nextPosition = VecAdd(_position, directions[_direction]);

    // [6-4-2]옆의 좌표가 미로 범위 내인지 여부를 판정한다
    if (!IsInsideMaze(nextPosition))
    {
        return false;// [6-4-3]파서는 안된다는 결과를 반환한다
    }

    // [6-4-4]모든 방위를 반복한다
    for (int i = 0; i < DIRECTION_MAX; i++)
    {
        // [6-4-5]벽을 팔 수 있는지 여부를 판정한다
        if (!maze[nextPosition.y][nextPosition.x].walls[i])
        {
            return false;// [6-4-6]파서는 안된다는 결과를 반환한다
        }
    }

    return true;// [6-4-7]파도 좋다는 결과를 반환한다
}

// [6-5]미로를 랜덤으로 생성하는 함수를 선언한다
void GenerateMap()
{
    // [6-5-1]미로의 모든 행을 반복한다
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        // [6-5-2]미로의 모든 열을 반복한다
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-5-3]칸의 모든 방위를 반복한다
            for (int i = 0; i < DIRECTION_MAX; i++)
            {
                // [6-5-4]대상 방위를 벽으로 한다
                maze[y][x].walls[i] = true;
            }
        }
    }

    // [6-5-5]현재 좌표를 선언한다
    VEC2 currentPosition = { 0, 0 };

    // [6-5-6]벽을 파야 하는 칸의 리스트를 선언한다
    std::vector<VEC2> toDigWallPositions;

    // [6-5-7]벽을 파야 하는 칸 리스트에 현재 칸을 더한다
    toDigWallPositions.push_back(currentPosition);

    // [6-5-8]무한 루프한다
    while (1)
    {
        // [6-5-9]팔 수 있는 벽의 방위 리스트를 선언한다
        std::vector<int> canDigDirections;

        // [6-5-10]모든 방위를 반복한다
        for (int i = 0; i < DIRECTION_MAX; i++)
        {
            // [6-5-11]대상 방위의 벽을 팔 수 있는지 여부를 판정한다
            if (CanDigWall(currentPosition, i))
            {
                // [6-5-12]팔 수 있는 벽의 방위 리스트에 추가한다
                canDigDirections.push_back(i);
            }
        }

        // [6-5-13]팔 수 있는 벽이 있는지 여부를 판정한다
        if (canDigDirections.size() > 0)
        {
            // [6-5-14]파는 벽의 방위를 선언한다
            int digDirection = canDigDirections[rand() % canDigDirections.size()];

            // [6-5-15]대상 벽을 판다
            DigWall(currentPosition, digDirection);

            // [6-5-16]판 벽의 건너편으로 이동한다
            currentPosition = VecAdd(currentPosition, directions[digDirection]);

            // [6-5-17]벽을 파야 하는 칸의 좌표 리스트에 현재 좌표를 더한다
            toDigWallPositions.push_back(currentPosition);
        }

        // [6-5-18]팔 데가 없을 때
        else
        {
            // [6-5-19]벽을 파야 하는 칸 리스트에서 현재 칸을 삭제한다
            toDigWallPositions.erase(toDigWallPositions.begin());

            // [6-5-20]벽을 파야 하는 칸 리스트가 비어 있는지 여부를 판정한다
            if (toDigWallPositions.size() <= 0)
            {
                break;// [6-5-21]루프를 빠져나간다
            }

            // [6-5-22]벽을 파야 하는 칸 리스트에서 맨앞의 칸을 구하여 이동한다
            currentPosition = toDigWallPositions.front();
        }
    }
}

// [6-6]맵을 그리는 함수를 선언한다
void DrawMap()
{
    // [6-6-1]미로의 모든 행을 반복한다
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        // [6-6-2]미로의 모든 열을 반복한다
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            //  [6-6-3]북쪽 벽을 그린다
            printf("＋%s＋", maze[y][x].walls[DIRECTION_NORTH] ? "―" : "　");
        }

        printf("\n");// [6-6-4]1행 그릴 때마다 줄바꿈한다

        // [6-6-5]미로의 모든 열을 반복한다
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-6-6]바닥의 아스키아트를 선언한다
            char floorAA[] = "　";

            // [6-6-7]플레이어의 좌표를 그리는 중이면
            if ((x == player.position.x) && (y == player.position.y))
            {
                // [6-6-8]방위의 아스키아트를 선언한다
                const char* directionAA[] =
                {
                    "↑",    // DIRECTION_NORTH  북
                    "←",    // DIRECTION_WEST   서
                    "↓",    // DIRECTION_SOUTH  남
                    "→"     // DIRECTION_EAST   동
                };

                // [6-6-9]바닥의 아스키아트에 플레이어의 아스키아트를 복사한다
                strcpy_s(floorAA, directionAA[player.direction]);
            }

            // [6-6-10]목표 지점의 좌표를 그리는 중이면
            else if ((x == GOAL_X) && (y == GOAL_Y))
            {
                // [6-6-11]바닥 아스키아트에 목표 지점 아스키아트를 복사한다
                strcpy_s(floorAA, "Ｇ");
            }

            // [6-6-12]서쪽 벽, 중심 바닥, 동쪽 벽을 그린다
            printf("%s%s%s",
                maze[y][x].walls[DIRECTION_WEST] ? "｜" : "　",
                floorAA,
                maze[y][x].walls[DIRECTION_EAST] ? "｜" : "　");
        }

        printf("\n");// [6-6-13]1행 그릴 때마다 줄바꿈한다

        // [6-6-14]미로의 모든 열을 반복한다
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-6-15]남쪽 벽을 그린다
            printf("＋%s＋", maze[y][x].walls[DIRECTION_SOUTH] ? "―" : "　");
        }

        printf("\n");// [6-6-16]1행 그릴 때마다 줄바꿈한다
    }
}

// [6-7]미로를 의사 3D 시점으로 그리는 함수를 선언한다
void Draw3D()
{
    // [6-7-1]화면 버퍼를 선언한다
    char screen[] =
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n";

    // [6-7-2]모든 상대 위치를 반복한다
    for (int i = 0; i < LOCATION_MAX; i++)
    {
        // [6-7-3]절대 위치를 선언한다
        VEC2 position = VecAdd(player.position, locations[player.direction][i]);

        // [6-7-4]절대 위치가 미로의 범위 밖인지 여부를 판정한다
        if (!IsInsideMaze(position))
            continue;// [6-7-5]다음의 상대 위치로 스킵한다

        // [6-7-6]모든 방위를 반복한다
        for (int j = 0; j < DIRECTION_MAX; j++)
        {
            // [6-7-7]상대 방위를 선언한다
            int direction = (DIRECTION_MAX + j - player.direction) % DIRECTION_MAX;

            // [6-7-8]대상 벽이 없는지 여부를 판정한다
            if (!maze[position.y][position.x].walls[j])
            {
                continue;// [6-7-9]다음 방위로 스킵한다
            }

            // [6-7-10]합성하는 아스키아트가 없는지 여부를 판정한다
            if (!aaTable[i][direction])
            {
                continue;// [6-7-11]다음 상대 위치로 스킵한다
            }

            // [6-7-12]화면 버퍼의 모든 문자를 반복한다
            for (int k = 0; k < sizeof(screen); k++)
            {
                // [6-7-13]대상 문자가 스페이스가 아닌지 여부를 판정한다
                if (aaTable[i][direction][k] != ' ')
                {
                    // [6-7-14]화면 버퍼에 합성하는 아스키아트를 적어넣는다
                    screen[k] = aaTable[i][direction][k];
                }
            }
        }
    }

    // [6-7-15]화면 버퍼의 모든 문자를 반복한다
    for (int i = 0; i < sizeof(screen); i++)
    {
        // [6-7-16]화면 버퍼의 반각 문자를 전각 문자로 변환하여 그린다
        switch (screen[i])
        {
        case ' ':   printf("　");    break; // [6-7-17]「 」을「　」로 그린다
        case '#':   printf("　");    break; // [6-7-18]「#」을「　」로 그린다
        case '_':   printf("＿");    break; // [6-7-19]「_」를「＿」로 그린다
        case '|':   printf("｜");    break; // [6-7-20]「|」을「｜」로 그린다
        case '/':   printf("／");    break; // [6-7-21]「/」를「／」로 그린다
        case 'L':   printf("＼");    break; // [6-7-22]「L」를「＼」로 그린다
        default:

            // [6-7-23]상기 이외의 문자는 그대로 그린다
            printf("%c", screen[i]);

            break;
        }
    }
}

// [6-8]게임을 초기화하는 함수를 선언한다
void Init()
{
    GenerateMap();// [6-8-1]미로를 랜덤으로 생성하는 함수를 호출한다

    player.position = { 0,0 };// [6-8-2]플레이어의 좌표를 초기화한다

    player.direction = DIRECTION_NORTH;// [6-8-3]플레이어의 방위를 초기화한다
}

// [6-9]프로그램의 실행 시작점을 선언한다
int main()
{
    system("chcp 65001 > nul");// [6-9-0]콘솔의 문자 세트를 UTF-8로 설정한다
    srand((unsigned int)time(NULL));// [6-9-1]난수를 섞는다

    Init();// [6-9-2]게임을 초기화하는 함수를 호출한다

    // [6-9-3]메인 루프
    while (1)
    {
        system("cls");// [6-9-4]화면을 클리어한다

        // [6-9-5]미로를 의사 3D 시점으로 그리는 함수를 호출한다
        Draw3D();

        // [6-9-6]맵을 그리는 함수를 호출한다
        DrawMap();

        // [6-9-7]입력된 키로 분기한다
        switch (_getch())
        {
        case 'w':// [6-9-8]w키를 누르면

            // [6-9-9]플레이어의 눈앞이 벽인지 아닌지를 판정한다
            if (!maze[player.position.y][player.position.x].walls[player.direction])
            {
                // [6-9-10]전진 목적지의 좌표를 선언한다
                VEC2 nextPosition = VecAdd(player.position, directions[player.direction]);

                // [6-9-11]전진 목적지의 좌표가 미로 내인지 여부를 판정한다
                if (IsInsideMaze(nextPosition))
                {
                    // [6-9-12]전진 목적지의 좌표를 적용한다
                    player.position = nextPosition;

                    // [6-9-13]목표 지점에 도달했는지 여부를 판정한다
                    if ((player.position.x == GOAL_X) && (player.position.y == GOAL_Y))
                    {
                        system("cls");// [6-9-14]화면을 클리어한다

                        // [6-9-15]메시지를 표시한다
                        printf(
                            "　＊　＊　ＣＯＮＧＲＡＴＵＬＡＴＩＯＮＳ　＊　＊\n"
                            "\n"
                            "   드디어 전설의 부적을 손에 넣었다!\n"
                            "\n"
                            "   하지만 어둠을 함께 한 무엇과도 바꿀 수 없는\n"
                            "  「동료」라는 보물을 손에 넣은 지금,　\n"
                            "  부적의 광채는 더 이상 눈에 들어오지 않는다...\n"
                            "\n"
                            "　　　　　　　～　ＴＨＥ　ＥＮＤ　～\n");

                        _getch();// [6-9-16]키보드 입력을 대기한다

                        Init();// [6-9-17]게임을 초기화한다
                    }
                }
            }

            break;

        case 's':// [6-9-18]s키를 누르면

            player.direction += 2;// [6-9-19]뒤를 향한다

            break;

        case 'a':// [6-9-20]a키를 누르면

            player.direction++;// [6-9-21]왼쪽을 향한다

            break;

        case 'd':// [6-9-22]d키를 누르면

            player.direction--;// [6-9-23]오른쪽을 향한다

            break;
        }

        // [6-9-24]플레이어가 향하고 있는 방위를 범위 내로 보정한다
        player.direction = (DIRECTION_MAX + player.direction) % DIRECTION_MAX;
    }
}