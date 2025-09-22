// [1]헤더를 인클루드하는 곳

#include <stdio.h>  // [1-1]표준 입출력 헤더를 인클루드한다
#include <stdlib.h> // [1-2]표준 라이브러리 헤더를 인클루드한다
#include <time.h>   // [1-3]시간 관리 헤더를 인클루드한다
#include <termios.h> // [1-4]터미널 I/O 헤더를 인클루드한다
#include <unistd.h>  // [1-5]유닉스 표준 헤더를 인클루드한다
#include <stdbool.h> // [1-6]bool 타입을 위한 헤더를 인클루드한다
#include <vector>   // [1-7]벡터 헤더를 인클루드한다

// [2]상수를 정의하는 곳

#define BOARD_WIDTH     (8) // [2-1]모눈판의 너비를 정의한다
#define BOARD_HEIGHT    (8) // [2-2]모눈판의 높이를 정의한다

// [3]열거 상수를 정의하는 곳

// [3-1]턴의 종류를 정의한다
enum
{
    TURN_BLACK, // [3-1-1]검은 돌
    TURN_WHITE, // [3-1-2]흰 돌
    TURN_NONE,  // [3-1-3]없음
    TURN_MAX    // [3-1-4]턴의 개수
};

// [3-2]방향의 종류를 정의한다
enum
{
    DIRECTION_UP,                  // [3-2-1]위
    DIRECTION_UP_LEFT,           // [3-2-2]왼쪽 위
    DIRECTION_LEFT,               // [3-2-3]왼쪽
    DIRECTION_DOWN_LEFT,     // [3-2-4]왼쪽 아래
    DIRECTION_DOWN,           // [3-2-5]아래
    DIRECTION_DOWN_RIGHT,  // [3-2-6]오른쪽 아래
    DIRECTION_RIGHT,            // [3-2-7]오른쪽
    DIRECTION_UP_RIGHT,       // [3-2-8]오른쪽 위
    DIRECTION_MAX              // [3-2-9]방향 수
};

// [3-3]게임 모드의 종류를 정의한다
enum
{
    MODE_1P,    // [3-3-1]AI와 대전하는 모드
    MODE_2P,    // [3-3-2]사람간의 대전 모드
    MODE_WATCH, // [3-3-3]AI간 대결의 관전 모드
    MODE_MAX    // [3-3-4]모드의 수
};

// [4]구조체를 선언하는 곳

// [4-1]벡터 구조체를 선언한다
typedef struct {
    int x, y;   // [4-1-1]좌표
} VEC2;

// [5]변수를 선언하는 곳

// [5-1]돌의 아스키아트를 선언한다 (ASCII 문자로 터미널 호환성 향상)
const char* diskAA[TURN_MAX] =
{
    "X",    // [5-1-1]TURN_BLACK    검은 돌이 놓여 있다
    "O",    // [5-1-2]TURN_WHITE    흰 돌이 놓여 있다
    ".",    // [5-1-3]TURN_NONE     돌이 놓여 있지 않다
};

// [5-2]턴의 이름을 선언한다
const char* turnNames[] =
{
    "검은 돌",   // TURN_BLACK
    "흰 돌"      // TURN_WHITE
};

// [5-3]모드의 이름을 선언한다
const char* modeNames[] =
{
    "１Ｐ　ＧＡＭＥ",   // [5-3-1]MODE_1P   AI와 대전하는 모드
    "２Ｐ　ＧＡＭＥ",   // [5-3-2]MODE_2P   사람 간의 대전 모드
    "ＷＡＴＣＨ"         // [5-3-3]MODE_WATCH    AI간 대결의 관전 모드
};

// [5-4]방향을 선언한다
VEC2 directions[DIRECTION_MAX] =
{
    { 0,-1},    // [5-4-1]DIRECTION_UP          위
    {-1,-1},    // [5-4-2]DIRECTION_UP_LEFT     왼쪽 위
    {-1, 0},    // [5-4-3]DIRECTION_LEFT        왼쪽
    {-1, 1},    // [5-4-4]DIRECTION_DOWN_LEFT   왼쪽 아래
    { 0, 1},    // [5-4-5]DIRECTION_DOWN        아래
    { 1, 1},    // [5-4-6]DIRECTION_DOWN_RIGHT  오른쪽 아래
    { 1, 0},    // [5-4-7]DIRECTION_RIGHT       오른쪽
    { 1,-1}    // [5-4-8]DIRECTION_UP_RIGHT    오른쪽 위
};

// [5-5]모눈판 각 칸의 상태를 선언한다
int board[BOARD_HEIGHT][BOARD_WIDTH];

VEC2 cursorPosition;// [5-6]커서의 좌표를 선언한다

int turn;// [5-7]현재의 턴을 선언한다

int mode;// [5-8]현재의 게임 모드를 선언한다

bool isPlayer[TURN_MAX];// [5-9]각 턴이 플레이어인지 여부를 선언한다

// [6]함수를 선언하는 곳

// [6-0]리눅스용 getch() 함수를 구현한다
int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

// [6-1]벡터를 더하는 함수를 선언한다
VEC2 VecAdd(VEC2 _v0, VEC2 _v1)
{
    // [6-1-2]더한 벡터를 반환한다
    return
    {
        _v0.x + _v1.x,
        _v0.y + _v1.y
    };
}

// [6-2]돌을 놓을 수 있는지 여부의 판정, 또는 돌을 뒤집는 함수를 선언한다
bool CheckCanPlace(
    int _color,             // 돌의 색
    VEC2 _position,         // 좌표
    bool _turnOver = false) // 뒤집을지 여부
{
    bool canPlace = false;// [6-2-1]돌을 놓을 수 있는지 여부의 플래그를 선언한다

    // [6-2-2]대상 좌표에 돌이 놓여 있지 않은지 여부를 판정한다
    if (board[_position.y][_position.x] != TURN_NONE)
    {
        return false;// [6-2-3]돌이 놓여 있으면 놓을 수 없다는 결과를 반환한다
    }

    int opponent = _color ^ 1;// [6-2-4]상대의 돌 색을 선언한다

    // [6-2-5]모든 방향을 반복한다
    for (int i = 0; i < DIRECTION_MAX; i++)
    {
        // [6-2-6]현재 체크 중인 좌표를 선언한다
        VEC2 currentPosition = _position;

        // [6-2-7]옆의 칸으로 이동한다
        currentPosition = VecAdd(currentPosition, directions[i]);

        // [6-2-7.1]체크하는 칸이 모눈판의 범위 내인지 판정한다
        if ((currentPosition.x < 0)
            || (currentPosition.x >= BOARD_WIDTH)
            || (currentPosition.y < 0)
            || (currentPosition.y >= BOARD_HEIGHT))
        {
            // [6-2-7.2]대상 방향의 체크를 스킵한다
            continue;
        }

        // [6-2-8]상대의 돌이 아닌지 판정한다
        if (board[currentPosition.y][currentPosition.x] != opponent)
        {
            // [6-2-9]상대의 돌이 아니면 그 방향의 체크를 중지한다
            continue;
        }

        // [6-2-10]무한 루프한다
        while (1)
        {
            // [6-2-11]옆 칸으로 이동한다
            currentPosition = VecAdd(currentPosition, directions[i]);

            // [6-2-12]체크하는 칸이 모눈판의 범위 내인지 판정한다
            if ((currentPosition.x < 0)
                || (currentPosition.x >= BOARD_WIDTH)
                || (currentPosition.y < 0)
                || (currentPosition.y >= BOARD_HEIGHT))
            {
                // [6-2-13]모눈판 바깥쪽으로 나가면 현재 방향의 체크를 빠져나간다
                break;
            }

            // [6-2-14]체크하는 칸에 돌이 있는지 여부를 판정한다
            if (board[currentPosition.y][currentPosition.x] == TURN_NONE)
            {
                break;// [6-2-15]돌이 없으면 현재 방향의 체크를 빠져나간다
            }

            // [6-2-16]체크하는 칸에 자신의 돌이 있으면
            if (board[currentPosition.y][currentPosition.x] == _color)
            {
                // [6-2-17]돌을 놓을 수 있는 것이 확정된다
                canPlace = true;

                // [6-2-18]뒤집기 플래그가 설정되어 있는지 여부를 판정한다
                if (_turnOver)
                {
                    // [6-2-19]뒤집는 좌표를 선언한다
                    VEC2 reversePosition = _position;

                    // [6-2-20]옆 칸으로 이동한다
                    reversePosition = VecAdd(reversePosition, directions[i]);

                    // [6-2-21]현재 턴의 돌을 찾을 때까지 반복한다
                    do
                    {
                        // [6-2-22]상대의 돌을 뒤집는다
                        board[reversePosition.y][reversePosition.x] = _color;

                        // [6-2-23]옆 칸으로 이동한다
                        reversePosition = VecAdd(reversePosition, directions[i]);

                    } while (board[reversePosition.y][reversePosition.x] != _color);
                }
            }
        }
    }

    return canPlace;// [6-2-24]돌을 놓을 수 있는지 여부를 반환한다
}

// [6-3]모눈판 위에 돌을 놓을 수 있는 칸이 있는지 여부를 판정하는 함수를 선언한다
bool CheckCanPlaceAll(int _color)
{
    // [6-3-1]모눈판의 모든 행을 반복한다
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        // [6-3-2]모눈판의 모든 열을 반복한다
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            // [6-3-3]판정하는 좌표를 선언한다
            VEC2 position = { x,y };

            // [6-3-4]대상 좌표에 돌을 놓을 수 있는지 여부를 판정한다
            if (CheckCanPlace(
                _color,     // int _color       돌 색
                position))  // VEC2 _position   좌표
            {
                return true;// [6-3-5]돌을 놓을 수 있는 칸이 있다는 결과를 반환한다
            }
        }
    }

    return false;// [6-3-6]돌을 놓을 수 있는 칸이 없다는 결과를 반환한다
} 

// [6-4]임의의 돌의 개수를 세는 함수를 선언한다
int GetDiskCount(int _color)
{
    int count = 0;// [6-4-1]세는 돌의 개수를 보유하는 변수를 선언한다

    // [6-4-2]모눈판의 모든 행을 반복한다
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        // [6-4-3]모눈판의 모든 열을 반복한다
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            // [6-4-4]대상 칸에 대상의 돌이 있는지 여부를 판정한다
            if (board[y][x] == _color)
            {
                count++;// [6-4-5]돌의 개수를 더한다
            }
        }
    }

    return count;// [6-4-6]센 돌의 개수를 반환한다
}

// [6-5]화면을 그리는 함수를 선언한다
void DrawScreen()
{
    system("clear");// [6-5-1]화면을 클리어한다

    // [6-5-2]모든 행을 반복한다
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        // [6-5-3]모든 열을 반복한다
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            printf("%s", diskAA[board[y][x]]);// [6-5-4]돌을 그린다
        }

        // [6-5-5]플레이어의 담당인지 여부를 판정한다
        if (isPlayer[turn])
        {
            // [6-5-6]대상 행이 커서와 같은 행인지 여부를 판정한다
            if (y == cursorPosition.y)
            {
                printf("<");// [6-5-7]커서를 그린다
            }
        }

        printf("\n");// [6-5-8]행 그리기의 마지막에 줄바꿈한다
    }

    // [6-5-9]플레이어의 담당인지 여부를 판정한다
    if (isPlayer[turn])
    {
        // [6-5-10]모눈판의 열 수만큼 반복한다
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            // [6-5-11]커서와 같은 열인지 여부를 판정한다
            if (x == cursorPosition.x)
            {
                printf("^");    // [6-5-12]^화살표를 표시한다
            }
            else
            {
                printf(" ");    // [6-5-13]공백을 표시한다
            }
        }
    }

    // [6-5-14]커서 그리기가 끝나면 줄바꿈한다
    printf("\n");

    // [6-5-15]승부가 났는지 여부를 판정한다
    if (turn != TURN_NONE)
    {
        // [6-5-16]턴을 표시한다
        printf("%s의 턴입니다\n", turnNames[turn]);
    }
    // [6-5-17]승부가 났다면
    else
    {
        // [6-5-18]검은 돌의 개수를 선언한다
        int blackCount = GetDiskCount(TURN_BLACK);

        // [6-5-19]흰 돌의 개수를 선언한다
        int whiteCount = GetDiskCount(TURN_WHITE);

        // [6-5-20]승자를 보유하는 변수를 선언한다
        int winner;

        // [6-5-21]승자를 판정한다
        if (blackCount > whiteCount)        // [6-5-22]검은 돌이 많으면
        {
            winner = TURN_BLACK;            // [6-5-23]검은 돌 승리
        }
        else if (whiteCount > blackCount)   // [6-5-24]흰 돌이 많으면
        {
            winner = TURN_WHITE;            // [6-5-25]흰 돌 승리
        }
        else                                // [6-5-26]같은 수라면
        {
            winner = TURN_NONE;             // [6-5-27]무승부
        }

        // [6-5-28]양측 돌의 개수를 표시한다
        printf("%s%d―%s%d\n",
            turnNames[TURN_BLACK],      // 검은 돌의 이름
            GetDiskCount(TURN_BLACK),   // 검은 돌의 개수
            turnNames[TURN_WHITE],      // 흰 돌의 이름
            GetDiskCount(TURN_WHITE));  // 흰 돌의 개수

        // [6-5-29]무승부인지 여부를 판정한다
        if (winner == TURN_NONE)
        {
            printf("무승부\n");// [6-5-30]무승부 메시지를 표시한다
        }
        else// [6-5-31]승부가 났다면
        {
            // [6-5-32]승자를 표시한다
            printf("%s의 승리\n", turnNames[winner]);
        }
    }
}

// [6-6]모드 선택 화면의 함수를 선언한다
void SelectMode()
{
    mode = MODE_1P;// [6-6-1]게임 모드를 초기화한다

    // [6-6-2]무한 루프한다
    while (1)
    {
        system("clear");// [6-6-3]화면을 클리어한다

        // [6-6-4]메시지를 표시한다
        printf("모드를 선택하세요\n");

        printf("\n\n");// [6-6-5]2행 비운다

        // [6-6-6]모든 모드를 반복한다
        for (int i = 0; i < MODE_MAX; i++)
        {
            // [6-6-7]현재의 모드에는 커서를, 그 밖에는 공백을 그린다
            printf("%s ", (i == mode) ? ">":"");

            printf("%s\n", modeNames[i]);// [6-6-8]모드의 이름을 그린다

            printf("\n");// [6-6-9]1행 비운다
        }

        // [6-6-10]입력된 키로 분기한다
        switch (getch())
        {
        case 'w':   // [6-6-11]w키를 누르면
            mode--; // [6-6-12]이전 모드로 바꾼다
            break;

        case 's':   // [6-6-13]s키를 누르면
            mode++; // [6-6-14]다음 모드로 바꾼다
            break;

        default:// [6-6-15]그 밖의 키를 누르면

            // [6-6-16]선택된 모드로 분기한다
            switch (mode)
            {
            case MODE_1P:       // [6-6-17]AI와 대전하는 모드라면

                isPlayer[TURN_BLACK] = true;    // [6-6-18]검은 돌을 플레이어로 한다
                isPlayer[TURN_WHITE] = false;   // [6-6-19]흰 돌을 플레이어로 하지 않는다

                break;

            case MODE_2P:       // [6-6-20]사람 간의 대전 모드라면

                // [6-6-21]양쪽을 플레이어의 담당으로 한다
                isPlayer[TURN_BLACK] = isPlayer[TURN_WHITE] = true;

                break;

            case MODE_WATCH:    // [6-6-22]AI간 대결의 관전 모드라면

                // [6-6-23]양쪽을 플레이어의 담당으로 하지 않는다
                isPlayer[TURN_BLACK] = isPlayer[TURN_WHITE] = false;

                break;
            }

            return;// [6-6-24]모드 선택을 빠져나간다
        }

        // [6-6-25]커서를 상하로 루프시킨다
        mode = (MODE_MAX + mode) % MODE_MAX;
    }
}

// [6-7]게임을 초기화하는 함수를 선언한다
void Init()
{
    // [6-7-1]모눈판의 모든 행을 반복한다
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        // [6-7-2]모눈판의 모든 열을 반복한다
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            // [6-7-3]대상 칸을 돌이 놓여 있지 않은 상태로 한다
            board[y][x] = TURN_NONE;
        }
    }

    // [6-7-4]모눈판 중앙에 표준 오델로 초기 배치를 한다 (8x8 보드 중앙)
    // 표준 오델로 초기 배치:
    // [3][3]=흰돌, [3][4]=검은돌
    // [4][3]=검은돌, [4][4]=흰돌
    board[3][3] = TURN_WHITE;   // (3,3) 흰 돌
    board[3][4] = TURN_BLACK;   // (3,4) 검은 돌
    board[4][3] = TURN_BLACK;   // (4,3) 검은 돌
    board[4][4] = TURN_WHITE;   // (4,4) 흰 돌

    turn = TURN_BLACK;// [6-7-6]검은 돌의 턴으로 초기화한다

    cursorPosition = { 3,3 };// [6-7-7]커서의 좌표를 초기화한다

    DrawScreen();// [6-7-8]화면을 그리는 함수를 호출한다
}

// [6-8]돌을 놓는 칸을 선택하는 함수를 선언한다
VEC2 InputPosition()
{
    // [6-8-1]놓는 칸이 선택될 때까지 무한 루프한다
    while (1)
    {
        DrawScreen();// [6-8-2]화면을 그리는 함수를 호출한다

        // [6-8-3]입력된 키에 따라 분기한다
        switch (getch())
        {
        case 'w':               // [6-8-4]w키를 누르면
            cursorPosition.y--; // [6-8-5]커서를 위쪽으로 이동한다
            break;

        case 's':               // [6-8-6]s키를 누르면
            cursorPosition.y++; // [6-8-7]커서를 아래쪽으로 이동한다
            break;

        case 'a':               // [6-8-8]a키를 누르면
            cursorPosition.x--; // [6-8-9]커서를 왼쪽으로 이동한다
            break;

        case 'd':               // [6-8-10]d키를 누르면
            cursorPosition.x++; // [6-8-11]커서를 오른쪽으로 이동한다
            break;

        default:// [6-8-12]이동 이외의 키를 누르면

            // [6-8-13]커서의 좌표에 돌을 놓을 수 있는지 여부를 판정한다
            if (CheckCanPlace(turn, cursorPosition))
            {
                return cursorPosition;// [6-8-14]커서의 좌표를 반환한다
            }
            // [6-8-15]놓을 수 없다면
            else
            {
                // [6-8-16]놓을 수 없다는 메시지를 표시한다
                printf("놓을 수 없는 곳입니다\a");

                getch();// [6-8-17]키보드 입력을 기다린다
            }

            break;
        }

        // [6-8-18]커서를 좌우로 루프시킨다
        cursorPosition.x = (BOARD_WIDTH + cursorPosition.x) % BOARD_WIDTH;

        // [6-8-19]커서를 상하로 루프시킨다
        cursorPosition.y = (BOARD_HEIGHT + cursorPosition.y) % BOARD_HEIGHT;
    }
}

// [6-9]프로그램 실행의 시작점을 선언한다
int main()
{
    // [6-9-0]리눅스에서는 기본적으로 UTF-8을 사용한다
    srand((unsigned int)time(NULL));// [6-9-1]난수를 섞는다

start:  // [6-9-2]시작 라벨
    ;   // [6-9-3]빈 문장

    SelectMode();// [6-9-4]모드를 선택하는 함수를 호출한다

    Init();// [6-9-5]게임을 초기화하는 함수를 호출한다

    // [6-9-6]메인루프
    while (1)
    {
        // [6-9-7]놓을 수 있는 칸이 없는지 여부를 판정한다
        if (!CheckCanPlaceAll(turn))
        {
            turn ^= 1;// [6-9-8]턴을 바꾼다

            // [6-9-9]놓을 수 있는 칸이 없는지 여부를 판정한다
            if (!CheckCanPlaceAll(turn))
            {
                turn = TURN_NONE;// [6-9-10]승부가 난 것으로 한다

                DrawScreen();// [6-9-11]화면을 그리는 함수를 호출한다

                getch();// [6-9-12]키보드 입력을 기다린다

                goto start;// [6-9-13]시작 라벨로 점프한다
            }

            // [6-9-14]상대에게 놓을 수 있는 칸이 있으면
            else
            {
                continue;// [6-9-15]상대의 턴으로 스킵한다
            }
        }

        // [6-9-16]돌을 놓는 칸을 선언한다
        VEC2 placePosition;

        // [6-9-17]현재 턴의 담당이 플레이어인지 여부를 판정한다
        if (isPlayer[turn])
        {
            // [6-9-18]돌을 놓는 칸을 선택하는 함수를 호출한다
            placePosition = InputPosition();
        }
        // [6-9-19]현재 턴의 담당이 플레이어가 아니라면
        else
        {
            DrawScreen();// [6-9-20]모눈판을 그리는 함수를 호출한다

            getch();// [6-9-21]키보드 입력을 기다린다

            // [6-9-22]놓을 수 있는 좌표를 보유하는 벡터를 선언한다
            std::vector<VEC2> positions;

            // [6-9-23]모눈판의 모든 행을 반복한다
            for (int y = 0; y < BOARD_HEIGHT; y++)
            {
                // [6-9-24]모눈판의 모든 열을 반복한다
                for (int x = 0; x < BOARD_WIDTH; x++)
                {
                    // [6-9-25]대상 칸의 좌표를 선언한다
                    VEC2 position = { x, y };

                    // [6-9-26]대상 좌표에 돌을 놓을 수 있는지 여부를 판정한다
                    if (CheckCanPlace(turn, position))
                    {
                        // [6-9-27]벡터에 대상 좌표를 추가한다
                        positions.push_back(position);
                    }
                }
            }

            // [6-9-28]놓을 수 있는 곳을 랜덤으로 얻는다
            placePosition = positions[rand() % positions.size()];
        }

        // [6-9-29]돌을 뒤집는다
        CheckCanPlace(turn, placePosition, true);

        // [6-9-30]현재 턴의 돌을 놓는다
        board[placePosition.y][placePosition.x] = turn;

        turn ^= 1;// [6-9-31]턴을 바꾼다
    }
}