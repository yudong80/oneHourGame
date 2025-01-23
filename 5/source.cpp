// [1]헤더를 인클루드하는 곳

#include <stdio.h>  // [1-1]표준 입출력 헤더를 인클루드한다
#include <stdlib.h> // [1-2]표준 라이브러리 헤더를 인클루드한다
#include <string.h> // [1-3]문자열 조작 헤더를 인클루드한다
#include <time.h>   // [1-4]시간 관리 헤더를 인클루드한다
#include <conio.h>  // [1-5]콘솔 입출력 헤더를 인클루드한다
#include <vector>   // [1-6]벡터 헤더를 인클루드한다

// [2]상수를 정의하는 곳

#define MAZE_WIDTH  (19)            // [2-1]미로의 너비를 정의한다
#define MAZE_HEIGHT (19)            // [2-2]미로의 높이를 정의한다

#define FPS         (2)             // [2-3]1초당 갱신 빈도를 정의한다
#define INTERVAL    (1000 / FPS)    // [2-4]갱신별 대기 시간(밀리초)을 정의한다

// [3]열거 상수를 정의하는 곳

// [3-1]캐릭터의 종류를 정의한다
enum
{
    CHARACTER_PLAYER,   // [3-1-1]플레이어
    CHARACTER_RANDOM,   // [3-1-2]변덕 몬스터
    CHARACTER_CHASE,    // [3-1-3]추적 몬스터
    CHARACTER_AMBUSH,   // [3-1-4]전진 몬스터
    CHARACTER_SIEGE,    // [3-1-5]협공 몬스터
    CHARACTER_MAX       // [3-1-6]캐릭터의 개수
};

// [3-2]방향의 종류를 정의한다
enum
{
    DIRECTION_UP,       // [3-2-1]상
    DIRECTION_LEFT,     // [3-2-2]좌
    DIRECTION_DOWN,     // [3-2-3]하
    DIRECTION_RIGHT,    // [3-2-4]우
    DIRECTION_MAX       // [3-2-5]방향의 개수
};

// [4]구조체를 선언하는 곳

// [4-1]벡터 구조체를 선언한다
typedef struct {
    int x, y;   // [4-1-1]좌표
} VEC2;

// [4-2]캐릭터 구조체를 선언한다
typedef struct {
    VEC2        position;           // [4-2-1]좌표
    const VEC2  defaultPosition;    // [4-2-2]초기 좌표
    VEC2        lastPosition;       // [4-2-3]이전 좌표
} CHARACTER;

// [5]변수를 선언하는 곳

// [5-1]미로를 선언한다
char maze[MAZE_HEIGHT][MAZE_WIDTH + 1];

// [5-2]미로의 초기 상태를 선언한다
const char defaultMaze[MAZE_HEIGHT][MAZE_WIDTH + 1] =
{
    "#########o#########",
    "#ooooooo#o#ooooooo#",
    "#o###o#o#o#o#o###o#",
    "#o# #o#ooooo#o# #o#",
    "#o###o###o###o###o#",
    "#ooooooooooooooooo#",
    "#o###o###o###o###o#",
    "#ooo#o#ooooo#o#ooo#",
    "###o#o#o###o#o#o###",
    "oooooooo# #oooooooo",
    "###o#o#o###o#o#o###",
    "#ooo#o#ooooo#o#ooo#",
    "#o###o###o###o###o#",
    "#oooooooo oooooooo#",
    "#o###o###o###o###o#",
    "#o# #o#ooooo#o# #o#",
    "#o###o#o#o#o#o###o#",
    "#ooooooo#o#ooooooo#",
    "#########o#########"
};

// [5-3]캐릭터의 배열을 선언한다
CHARACTER characters[CHARACTER_MAX] =
{
    // [5-3-1]CHARACTER_PLAYER  플레이어
    {
        {},         // [5-3-2]VEC2          position
        {9, 13},    // [5-3-3]const VEC2    defaultPosition
        {},         // [5-3-4]VEC2          lastPosition
    },

    // [5-3-5]CHARACTER_RANDOM  변덕 몬스터
    {
        {},         // [5-3-6]VEC2          position
        {1, 1},     // [5-3-7]const VEC2    defaultPosition
        {},         // [5-3-8]VEC2          lastPosition
    },

    // [5-3-9]CHARACTER_CHASE   추적 몬스터
    {
        {},         // [5-3-10]VEC2         position
        {17, 1},    // [5-3-11]const VEC2   defaultPosition
        {},         // [5-3-12]VEC2         lastPosition
    },

    // [5-3-13]CHARACTER_AMBUSH 전진 몬스터
    {
        {},         // [5-3-14]VEC2         position
        {1, 17},    // [5-3-15]const VEC2   defaultPosition
        {},         // [5-3-16]VEC2         lastPosition
    },

    // [5-3-17]CHARACTER_SIEGE      협공 몬스터
    {
        {},         // [5-3-18]VEC2         position
        {17, 17},   // [5-3-19]const VEC2   defaultPosition
        {},         // [5-3-20]VEC2         lastPosition
    }
};

// [5-4]방향 벡터의 배열을 선언한다
VEC2 directions[DIRECTION_MAX] =
{
    { 0,-1},    // [5-4-1]DIRECTION_UP      상
    {-1, 0},    // [5-4-2]DIRECTION_LEFT    좌
    { 0, 1},    // [5-4-3]DIRECTION_DOWN    하
    { 1, 0}     // [5-4-4]DIRECTION_RIGHT   우
};

// [6]함수를 선언하는 곳

// [6-1]벡터를 더하는 함수를 선언한다
VEC2 Vec2Add(VEC2 _v0, VEC2 _v1)
{
    // [6-1-1]더한 벡터를 반환한다
    return
    {
        _v0.x + _v1.x,
        _v0.y + _v1.y
    };
}

// [6-2]벡터를 빼는 함수를 선언한다
VEC2 Vec2Subtract(VEC2 _v0, VEC2 _v1)
{
    // [6-2-1]뺀 벡터를 반환한다
    return
    {
        _v0.x - _v1.x,
        _v0.y - _v1.y
    };
}

// [6-3]벡터끼리 동일한지 여부를 판정하는 함수를 선언한다
bool Vec2Equal(VEC2 _v0, VEC2 _v1)
{
    // [6-3-1]벡터끼리 동일한지 여부를 반환한다
    return (_v0.x == _v1.x) && (_v0.y == _v1.y);
}

// [6-4]상하좌우로 루프한 좌표를 구하는 함수를 선언한다
VEC2 GetLoopPosition(VEC2 _position)
{
    // [6-4-1]상하좌우로 루프한 좌표를 반환한다
    return
    {
        (MAZE_WIDTH + _position.x) % MAZE_WIDTH,
        (MAZE_HEIGHT + _position.y) % MAZE_HEIGHT
    };
}

// [6-5]랜덤한 이동 목적지를 얻는 함수를 선언한다
VEC2 GetRandomPosition(CHARACTER _character)
{
    // [6-5-1]이동 목적지의 후보 리스트를 선언한다
    std::vector<VEC2> positions;

    // [6-5-2]모든 방향을 반복한다
    for (int i = 0; i < DIRECTION_MAX; i++)
    {
        // [6-5-3]각 방향의 좌표를 선언한다
        VEC2 newPosition = Vec2Add(_character.position, directions[i]);

        // [6-5-4]대상 좌표를 상하좌우로 루프시킨다
        newPosition = GetLoopPosition(newPosition);

        // [6-5-5]대상 좌표에 이동 가능한지 여부를 판정한다
        if (
            // 벽이 아니다
            (maze[newPosition.y][newPosition.x] != '#')

            // 그리고 이전 회의 좌표와 같지 않다
            && (!Vec2Equal(newPosition, _character.lastPosition))
            )
        {
            // [6-5-6]대상 좌표를 이동 목적지의 후보 리스트에 추가한다
            positions.push_back(newPosition);
        }
    }

    // [6-5-7]이동 목적지의 후보 중에서 랜덤으로 좌표를 반환한다
    return positions[rand() % positions.size()];
}

// [6-6]목표 지점까지의 최단 경로에서 첫 좌표를 얻는 함수를 선언한다
VEC2 GetChasePosition(CHARACTER _character, VEC2 _targetPosition)
{
    // [6-6-1]경로를 탐색해야 하는 좌표 리스트를 선언한다
    std::vector<VEC2> toCheckPositions;

    // [6-6-2]탐색을 하는 캐릭터 자신의 좌표를 탐색해야 하는 좌표 리스트에 추가한다
    toCheckPositions.push_back(_character.position);

    // [6-6-3]탐색 시작 지점에서 각 칸까지의 거리를 보유하는 배열을 선언한다
    int distances[MAZE_HEIGHT][MAZE_WIDTH];

    // [6-6-4]미로의 모든 행을 반복한다
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        // [6-6-5]미로의 모든 열을 반복한다
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-6-6]대상 칸까지의 거리를 미설정으로 초기화한다
            distances[y][x] = -1;
        }
    }

    // [6-6-7]탐색을 하는 캐릭터 자신의 좌표까지의 거리는 0으로 설정한다
    distances[_character.position.y][_character.position.x] = 0;

    // [6-6-8]탐색 시작 지점에서 각 칸까지의 경로를 보유하는 배열을 선언한다
    std::vector<VEC2> routes[MAZE_HEIGHT][MAZE_WIDTH];

    // [6-6-9]탐색해야 하는 좌표 리스트가 비워질 때까지 반복한다
    while (!toCheckPositions.empty())
    {
        // [6-6-10]모든 방향을 반복한다
        for (int i = 0; i < DIRECTION_MAX; i++)
        {
            // [6-8-11]탐색 중인 좌표에 인접하는 각 방향의 좌표를 구한다
            VEC2 newPosition = Vec2Add(toCheckPositions.front(), directions[i]);

            // [6-6-12]대상 좌표를 상하좌우로 루프시킨 좌표로 변환한다
            newPosition = GetLoopPosition(newPosition);

            // [6-6-13]대상 좌표까지의 거리를 선언한다
            int newDistance =
                distances[toCheckPositions.front().y][toCheckPositions.front().x] + 1;

            // [6-6-14]대상 좌표를 검색해야 하는지 여부를 판정한다
            if (
                (
                    // 미설정
                    (distances[newPosition.y][newPosition.x] < 0)

                    // 또는 최단 경로
                    || (newDistance < distances[newPosition.y][newPosition.x])
                    )

                // 그리고 벽이 아니다
                && (maze[newPosition.y][newPosition.x] != '#')
                )
            {
                // [6-6-15]대상 좌표까지의 거리를 갱신한다
                distances[newPosition.y][newPosition.x] = newDistance;

                // [6-6-16]대상 좌표를 탐색해야 하는 좌표 리스트로 추가한다
                toCheckPositions.push_back(newPosition);

                // [6-6-17]대상 좌표까지의 경로를 1개 전 좌표의 경로로 초기화한다
                routes[newPosition.y][newPosition.x] =
                    routes[toCheckPositions.front().y][toCheckPositions.front().x];

                // [6-6-18]대상 좌표까지의 경로에 대상 좌표를 추가한다
                routes[newPosition.y][newPosition.x].push_back(newPosition);
            }
        }

        // [6-6-19]탐색해야 하는 좌표 리스트에서 맨 앞의 좌표를 삭제한다
        toCheckPositions.erase(toCheckPositions.begin());
    }

    // [6-6-20]목표 지점까지의 경로가 있는지 여부를 판정한다
    if (
        // 경로가 있다
        (!routes[_targetPosition.y][_targetPosition.x].empty())

        // 그리고 이전 회의 좌표와 다른 좌표라면
        && (!Vec2Equal(
            routes[_targetPosition.y][_targetPosition.x].front(),
            _character.lastPosition)
            )
        )
    {
        // [6-6-21]목표 지점까지의 경로 1개 전 좌표를 반환한다
        return routes[_targetPosition.y][_targetPosition.x].front();
    }
    // [6-6-22]목표 지점까지의 경로가 없으면
    else
    {
        // [6-6-23]랜덤한 좌표를 반환한다
        return GetRandomPosition(_character);
    }
}

// [6-7]미로를 그리는 함수를 선언한다
void DrawMaze()
{
    // [6-7-1]화면 버퍼를 선언한다
    char screen[MAZE_HEIGHT][MAZE_WIDTH + 1];

    // [6-7-2]화면 버퍼에 미로를 복사한다 
    memcpy(screen, maze, sizeof maze);

    // [6-7-3]모든 캐릭터를 반복한다
    for (int i = 0; i < CHARACTER_MAX; i++)
    {
        // [6-7-4]캐릭터의 번호를 화면 버퍼에 써넣는다
        screen[characters[i].position.y][characters[i].position.x] = i;
    }

    system("cls");// [6-7-5]화면을 클리어한다

    // [6-7-6]미로의 모든 행을 반복한다
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        // [6-7-7]미로의 모든 열을 반복한다
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-7-8]칸을 그린다
            switch (screen[y][x])
            {
            case ' ':               printf("　");    break;  // [6-7-9]바닥
    	case '#':               printf("■");    break;  // [6-7-10]벽을 그린다
            case 'o':               printf("・");    break;  // [6-7-11]도트
            case CHARACTER_PLAYER:  printf("○");    break;  // [6-7-12]플레이어
            case CHARACTER_RANDOM:  printf("☆");    break;  // [6-7-13]변덕 몬스터
            case CHARACTER_CHASE:   printf("凸");    break;  // [6-7-14]추적 몬스터
            case CHARACTER_AMBUSH:  printf("◇");    break;  // [6-7-15]전진 몬스터
            case CHARACTER_SIEGE:   printf("凹");    break;  // [6-7-16]협공 몬스터
            }
        }

        // [6-7-17]1행 그릴 때마다 줄바꿈한다
        printf("\n");
    }
}

// [6-8]게임을 초기화하는 함수를 선언한다
void Init()
{
    // [6-8-1]미로에 초기 상태를 복사한다
    memcpy(maze, defaultMaze, sizeof maze);

    // [6-8-2]모든 캐릭터를 반복한다
    for (int i = 0; i < CHARACTER_MAX; i++)
    {
        // [6-8-3]캐릭터의 좌표를 초기화한다
        characters[i].position
            = characters[i].lastPosition
            = characters[i].defaultPosition;
    }
}

// [6-9]게임 오버 함수를 선언한다
bool IsGameOver()
{
    // [6-9-1]모든 몬스터를 반복한다
    for (int i = CHARACTER_PLAYER + 1; i < CHARACTER_MAX; i++)
    {
        // [6-9-2]대상 몬스터와 플레이어의 좌표가 동일한지 여부를 판정한다
        if (Vec2Equal(
            characters[i].position,                 // 대상 몬스터의 좌표
            characters[CHARACTER_PLAYER].position)) // 플레이어의 좌표
        {
            // [6-9-3]화면을 클리어한다
            system("cls");

            // [6-9-4]미로 높이의 반만큼 반복한다
            for (int j = 0; j < MAZE_HEIGHT / 2; j++)
            {
                // [6-9-5]줄바꿈한다
                printf("\n");
            }

            // [6-9-6]게임 오버 메시지를 표시한다
            printf("　　　　　ＧＡＭＥ　ＯＶＥＲ");
            


            // [6-9-7]키보드 입력을 기다린다
            _getch();

            // [6-9-8]게임 오버가 되었다는 결과를 반환한다
            return true;
        }
    }

    // [6-9-9]게임 오버가 되지 않았다는 결과를 반환한다
    return false;
}

// [6-10]엔딩 함수를 선언한다
bool IsComplete()
{
    // [6-10-1]미로의 모든 행을 반복한다
    for (int y = 0; y < MAZE_HEIGHT; y++)
    {
        // [6-10-2]미로의 모든 열을 반복한다
        for (int x = 0; x < MAZE_WIDTH; x++)
        {
            // [6-10-3]대상 칸이 도트인지 여부를 판정한다
            if (maze[y][x] == 'o')
            {
                // [6-10-4]클리어가 아니라는 결과를 반환한다
                return false;
            }
        }
    }

    // [6-10-5]화면을 클리어한다
    system("cls");

    // [6-10-6]미로 높이의 반만큼 반복한다
    for (int i = 0; i < MAZE_HEIGHT / 2; i++)
    {
        // [6-10-7]줄바꿈한다
        printf("\n");
    }

    // [6-10-8]엔딩 메시지를 표시한다
    printf("　　ＣＯＮＧＲＡＴＵＬＡＴＩＯＮＳ！");

    // [6-10-9]키보드 입력을 기다린다
    _getch();

    // [6-10-10]클리어했다는 결과를 반환한다
    return true;
}

// [6-11]프로그램 실행의 시작점을 선언한다
int main()
{
    system("chcp 65001 > nul");// [6-11-0]콘솔의 문자 세트를 UTF-8로 설정한다

    // [6-11-1]난수를 현재 시각으로 섞는다
    srand((unsigned int)time(NULL));

start:  // [6-11-2]게임 시작 라벨
    ;   // [6-11-3]빈 문장

    // [6-11-4]게임을 초기화하는 함수를 호출한다
    Init();

    // [6-11-5]미로를 그리는 함수를 호출한다
    DrawMaze();

    // [6-11-6]이전 회의 갱신 시각을 선언한다
    time_t lastClock = clock();

    // [6-11-7]메인 루프
    while (1)
    {
        // [6-11-8]현재 시각을 선언한다
        time_t newClock = clock();

        // [6-11-9]이전 회의 갱신으로부터 대기 시간이 경과했는지 여부를 판정한다
        if (newClock > lastClock + INTERVAL)
        {
            // [6-11-10]이전 회의 갱신 시각을 현재 시각으로 갱신한다
            lastClock = newClock;

            // [6-11-11]모든 몬스터를 반복한다
            for (int i = CHARACTER_PLAYER + 1; i < CHARACTER_MAX; i++)
            {
                // [6-11-12]이동 목적지의 좌표를 선언한다
                VEC2 newPosition = characters[i].position;

                // [6-11-13]몬스터의 종류에 따라 분기한다
                switch (i)
                {
                    // [6-11-14]변덕 몬스터
                case CHARACTER_RANDOM:

                    // [6-11-15]랜덤한 이동 목적지의 좌표를 설정한다
                    newPosition = GetRandomPosition(characters[i]);

                    break;

                    // [6-11-16]추적 몬스터
                case CHARACTER_CHASE:

                    // [6-11-17]플레이어를 추적하는 좌표를 설정한다
                    newPosition =
                        GetChasePosition(characters[i], characters[CHARACTER_PLAYER].position);

                    break;

                    // [6-11-18]전진 몬스터
                case CHARACTER_AMBUSH:
                {
                    // [6-11-19]플레이어의 방향 벡터를 선언한다
                    VEC2 playerDirection = Vec2Subtract(
                        characters[CHARACTER_PLAYER].position,
                        characters[CHARACTER_PLAYER].lastPosition);

                    // [6-11-20]목표 지점을 선언한다
                    VEC2 targetPosition = characters[CHARACTER_PLAYER].position;

                    // [6-11-21]3회 반복한다
                    for (int j = 0; j < 3; j++)
                    {
                        // [6-11-22]목표 지점에 플레이어의 방향 벡터를 더한다
                        targetPosition = Vec2Add(targetPosition, playerDirection);
                    }

                    // [6-11-23]목표 지점을 상하좌우로 루프시킨 좌표로 변환한다
                    targetPosition = GetLoopPosition(targetPosition);

                    // [6-11-24]목표 지점을 목표로 하는 좌표를 설정한다
                    newPosition = GetChasePosition(characters[i], targetPosition);

                    break;
                }
                // [6-11-25]협공 몬스터
                case CHARACTER_SIEGE:
                {
                    // [6-11-26]추적 몬스터에서 플레이어까지의 벡터를 얻는다
                    VEC2 chaseToPlayer = Vec2Subtract(
                        characters[CHARACTER_PLAYER].position,  // 플레이어의 좌표
                        characters[CHARACTER_CHASE].position);  // 추적 몬스터의 좌표

                    // [6-11-27]목적지를 선언한다
                    VEC2 targetPosition =

                        // 벡터를 더한다
                        Vec2Add(

                            // 플레이어의 좌표
                            characters[CHARACTER_PLAYER].position,

                            // 추적 몬스터에서 플레이어까지의 벡터
                            chaseToPlayer);

                    // [6-11-28]목표 지점을 상하좌우로 루프시킨 좌표로 변환한다
                    targetPosition = GetLoopPosition(targetPosition);

                    // [6-11-29]목표 지점을 목표로 하는 좌표를 설정한다
                    newPosition = GetChasePosition(characters[i], targetPosition);

                    break;
                }
                }

                // [6-11-30]이전 회의 좌표를 현재 좌표로 갱신한다 
                characters[i].lastPosition = characters[i].position;

                // [6-11-31]이동 목적지로 이동시킨다
                characters[i].position = newPosition;
            }

            // [6-11-32]게임 오버가 되었는지 여부를 판정한다
            if (IsGameOver())
            {
                goto start; // [6-11-33]게임 시작 라벨로 점프한다
            }

            // [6-11-34]화면을 다시 그린다
            DrawMaze();
        }

        // [6-11-35]키보드 입력이 었었는지 여부를 판정한다
        if (_kbhit())
        {
            // [6-11-36]플레이어의 새로운 좌표를 선언한다
            VEC2 newPosition = characters[CHARACTER_PLAYER].position;

            // [6-11-37]입력된 키에 따라 분기한다
            switch (_getch())
            {
            case 'w':   newPosition.y--;    break;  // [6-11-38]w를 누르면 위쪽으로 이동한다
            case 's':   newPosition.y++;    break;  // [6-11-39]s를 누르면 아래쪽으로 이동한다
            case 'a':   newPosition.x--;    break;  // [6-11-40]a를 누르면 왼쪽으로 이동한다
            case 'd':   newPosition.x++;    break;  // [6-11-41]d를 누르면 오른쪽으로 이동한다
            }

            // [6-11-42]이동 목적지의 좌표를 상하좌우로 이동시킨다
            newPosition = GetLoopPosition(newPosition);

            // [6-11-43]이동 목적지가 벽이 아닌지 여부를 판정한다
            if (maze[newPosition.y][newPosition.x] != '#')
            {
                // [6-11-44]플레이어의 이전 좌표를 현재 좌표로 갱신한다
                characters[CHARACTER_PLAYER].lastPosition =
                    characters[CHARACTER_PLAYER].position;

                // [6-11-45]플레이어의 좌표를 갱신한다
                characters[CHARACTER_PLAYER].position = newPosition;

                // [6-11-46]게임 오버가 되었는지 여부를 판정한다
                if (IsGameOver())
                {
                    goto start; // [6-11-47]게임 시작 라벨로 점프한다
                }

                // [6-11-48]플레이어의 좌표에 도트가 있는지 여부를 판정한다
                if (maze[characters[CHARACTER_PLAYER].position.y]
                    [characters[CHARACTER_PLAYER].position.x] == 'o')
                {
                    // [6-11-49]플레이어 좌표의 도트를 지운다
                    maze[characters[CHARACTER_PLAYER].position.y]
                        [characters[CHARACTER_PLAYER].position.x] = ' ';

                    // [6-11-50]클리어했는지 여부를 판정한다
                    if (IsComplete())
                    {
                        goto start; // [6-11-51]게임 시작 라벨로 점프한다
                    }
                }
            }

            // [6-11-52]미로를 다시 그린다
            DrawMaze();
        }
    }
}