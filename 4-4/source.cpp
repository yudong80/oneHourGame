// [1]헤더를 인클루드하는 곳

#include <stdio.h>  // [1-1]표준 입출력 헤더를 인클루드한다
#include <stdlib.h> // [1-2]표준 라이브러리 헤더를 인클루드한다
#include <string.h> // [1-3]문자열 조작 헤더를 인클루드한다
#include <time.h>   // [1-4]시간 관리 헤더를 인클루드한다
#include <conio.h>  // [1-5]콘솔 입출력 헤더를 인클루드한다

// [2]상수를 정의하는 곳

#define FIELD_WIDTH         (12)            // [2-1]필드의 너비를 정의한다
#define FIELD_HEIGHT        (18)            // [2-2]필드의 높이를 정의한다

#define BLOCK_WIDTH_MAX     (4)             // [2-3]블록의 최대 너비를 정의한다
#define BLOCK_HEIGHT_MAX    (4)             // [2-4]블록의 최대 높이를 정의한다

#define FPS                 (1)             // [2-5]1초당 그리기 빈도를 정의한다
#define INTERVAL            (1000 / FPS)    // [2-6]그리기 간격(밀리초)을 정의한다

// [3]열거 상수를 정의하는 곳

// [3-1]블록의 종류를 정의한다
enum
{
    BLOCK_NONE, // [3-1-1]블록 없음
    BLOCK_HARD, // [3-1-2]지울 수 없는 블록
    BLOCK_SOFT, // [3-1-3]지울 수 있는 블록
    BLOCK_FALL, // [3-1-4]낙하 블록
    BLOCK_MAX   // [3-1-5]블록 종류의 개수
};

// [3-2]낙하 블록의 종류를 정의한다
enum
{
    BLOCK_SHAPE_I,  // [3-2-1]I형
    BLOCK_SHAPE_L,  // [3-2-2]L형
    BLOCK_SHAPE_MAX // [3-2-3]낙하 블록 종류의 개수
};

// [4]구조체를 선언하는 곳

// [4-1]낙하 블록 형태의 구조체를 선언한다
typedef struct {
    int size;                                           // [4-1-1]너비와 높이
    bool pattern[BLOCK_HEIGHT_MAX][BLOCK_WIDTH_MAX];    // [4-1-2]형태
} BLOCKSHAPE;

// [4-2]낙하 블록의 구조체를 선언한다
typedef struct {
    int x, y;           // [4-2-1]좌표
    BLOCKSHAPE shape;   // [4-2-2]형태
} BLOCK;

// [5]변수를 선언하는 곳

// [5-1]낙하 블록의 형태를 선언한다
const BLOCKSHAPE blockShapes[BLOCK_SHAPE_MAX] =
{
    // [5-1-1]BLOCK_SHAPE_I I형
    {
        3,// [5-1-2]int size    너비와 높이

        // [5-1-3]bool pattern[BLOCK_HEIGHT_MAX][BLOCK_WIDTH_MAX]   형태
        {
            {0,1,0},
            {0,1,0},
            {0,1,0}
        }
    },

    // [5-1-4]BLOCK_SHAPE_L L형
    {
        3,// [5-1-5]int size    너비와 높이

        // [5-1-6]bool pattern[BLOCK_HEIGHT_MAX][BLOCK_WIDTH_MAX]   형태
        {
            {0,1,0},
            {0,1,1},
            {0,0,0}
        }
    },
};

// [5-2]필드를 선언한다
int field[FIELD_HEIGHT][FIELD_WIDTH];

// [5-3]필드의 초기 상태를 선언한다
int defaultField[FIELD_HEIGHT][FIELD_WIDTH] =
{
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,1,1},
    {1,1,1,0,0,0,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,1,1,1},
    {1,1,1,1,0,0,0,0,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1}
};

BLOCK block;// [5-4]낙하 블록을 선언한다

// [6]함수를 선언하는 곳

// [6-1]낙하 블록과 필드의 충돌 판정을 실시하는 함수를 선언한다
bool BlockIntersectField()
{
    // [6-1-1]낙하 블록의 모든 행을 반복한다
    for (int y = 0; y < block.shape.size; y++)
    {
        // [6-1-2]낙하 블록의 모든 열을 반복한다
        for (int x = 0; x < block.shape.size; x++)
        {
            // [6-1-3]대상 칸에 블록이 있는지 여부를 판정한다
            if (block.shape.pattern[y][x])
            {
                // [6-1-4]블록의 필드 위 열을 선언한다
                int globalX = block.x + x;

                // [6-1-5]블록의 필드 위 행을 선언한다
                int globalY = block.y + y;

                // [6-1-6]블록과 필드의 충돌 판정을 실시한다
                if ((globalX < 0)                   // 열이 왼쪽 밖인지 여부
                    || (globalX >= FIELD_WIDTH)     // 열이 오른쪽 밖인지 여부
                    || (globalY < 0)                // 행이 위쪽 밖인지 여부
                    || (globalY >= FIELD_HEIGHT)    // 행이 아래쪽 밖인지 여부

                    // 필드 위에 블록이 있는지 여부
                    || (field[globalY][globalX] != BLOCK_NONE))
                {
                    return true;// [6-1-7]충돌했다는 결과를 반환한다
                }
            }
        }
    }

    return false;// [6-1-8]충돌하지 않았다는 결과를 반환한다
}

// [6-2]채워진 행의 블록을 삭제하는 함수를 선언한다
void EraseLine()
{
    // [6-2-1]모든 행을 반복한다
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        // [6-2-2]그 행이 채워졌는지 여부의 플래그를 선언한다
        bool completed = true;

        // [6-2-3]모든 열을 반복한다
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            // [6-2-4]대상 칸에 블록이 있는지 여부를 판정한다
            if (field[y][x] == BLOCK_NONE)
            {
                completed = false;// [6-2-5]채워지지 않았다

                break;// [6-2-6]그 행의 체크를 빠져나간다
            }
        }

        // [6-2-7]그 행이 채워졌는지 여부를 판정한다 
        if (completed)
        {
            // [6-2-8]모든 열을 반복한다
            for (int x = 0; x < FIELD_WIDTH; x++)
            {
                // [6-2-9]대상 칸이 지울 수 있는 블록이면
                if (field[y][x] == BLOCK_SOFT)
                {
                    // [6-2-10]대상 칸의 블록을 지운다
                    field[y][x] = BLOCK_NONE;
                }
            }

            // [6-2-11]모든 열을 반복한다
            for (int x = 0; x < FIELD_WIDTH; x++)
            {
                // [6-2-12]지워진 행부터 맨 앞의 행까지 반복한다
                for (int y2 = y; y2 >= 0; y2--)
                {
                    // [6-2-13]지울 수 없는 블록을 찾으면 반복을 빠져나간다
                    if (field[y2][x] == BLOCK_HARD)
                        break;

                    // [6-2-14]맨 앞의 행인지 여부를 판정한다
                    if (y2 == 0)
                    {
                        // [6-2-15]블록을 지운다
                        field[y2][x] = BLOCK_NONE;
                    }

                    // [6-2-16]맨 앞의 행이 아니면
                    else
                    {
                        // [6-2-17]위 칸이 지울 수 없는 블록이 아닌지 여부를 판정하다
                        if (field[y2 - 1][x] != BLOCK_HARD)
                        {
                            // [6-2-18]위 칸을 아래 칸으로 복사한다
                            field[y2][x] = field[y2 - 1][x];
                        }
                    }
                }
            }
        }
    }
}

// [6-3]화면을 그리는 함수를 선언한다
void DrawScreen()
{
    // [6-3-1]화면 버퍼를 선언한다
    int screen[FIELD_HEIGHT][FIELD_WIDTH];

    // [6-3-2]필드를 화면 버퍼에 복사한다
    memcpy(screen, field, sizeof field);

    // [6-3-3]필드의 모든 행을 반복한다
    for (int y = 0; y < BLOCK_HEIGHT_MAX; y++)
    {
        // [6-3-4]필드의 모든 열을 반복한다
        for (int x = 0; x < BLOCK_WIDTH_MAX; x++)
        {
            // [6-3-5]블록이 있는지 여부를 판정한다
            if (block.shape.pattern[y][x])
            {
                // [6-3-6]화면 버퍼에 낙하 블록을 써넣는다
                screen[block.y + y][block.x + x] = BLOCK_FALL;
            }
        }
    }

    // [6-3-7]화면을 클리어한다
    system("cls");

    // [6-3-8]필드의 모든 행을 반복한다
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        // [6-3-9]필드의 모든 열을 반복한다
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            // [6-3-10]블록의 종류로 분기한다
            switch (screen[y][x])
            {
            case BLOCK_NONE: printf("  ");    break;// [6-3-11]블록 없음
            case BLOCK_HARD: printf("＋");    break;// [6-3-12]지울 수 없는 블록
            case BLOCK_SOFT: printf("◆");    break;// [6-3-13]지울 수 있는 블록
            case BLOCK_FALL: printf("◇");    break;// [6-3-14]낙하 블록
            }
        }

        printf("\n");// [6-3-15]줄바꿈한다
    }
}

// [6-4]낙하 블록을 회전시키는 함수를 선언한다
void RotateBlock()
{
    // [6-4-1]회전 후의 블록을 선언한다
    BLOCK rotatedBlock = block;

    // [6-4-2]낙하 블록의 모든 행을 반복한다
    for (int y = 0; y < block.shape.size; y++)
    {
        // [6-4-3]낙하 블록의 모든 열을 반복한다
        for (int x = 0; x < block.shape.size; x++)
        {
            // [6-4-4]회전 후의 블록 형태를 작성한다
            rotatedBlock.shape.pattern[block.shape.size - 1 - x][y] =
                block.shape.pattern[y][x];
        }
    }

    // [6-4-5]회전 후의 블록을 적용한다
    block = rotatedBlock;
}

// [6-5]낙하 블록을 초기화하는 함수를 선언한다
void InitBlock()
{
    // [6-5-1]낙하 블록의 형태를 랜덤으로 설정한다
    block.shape = blockShapes[rand() % BLOCK_SHAPE_MAX];

    // [6-5-2]낙하 블록의 열을 중심으로 한다
    block.x = FIELD_WIDTH/2 - block.shape.size/2;

    block.y = 0;// [6-5-3]낙하 블록의 행을 맨 앞으로 한다

    // [6-5-4]낙하 블록을 회전시키는 횟수를 선언한다
    int rotateCount = rand() % 4;

    // [6-5-5]낙하 블록을 회전시키는 횟수만큼 반복한다
    for (int i = 0; i < rotateCount; i++)
    {
        // [6-5-6]낙하 블록을 회전시킨다
        RotateBlock();
    }
}

// [6-6]게임을 초기화하는 함수를 선언한다
void Init()
{
    // [6-6-1]필드에 초기 상태를 복사한다
    memcpy(field, defaultField, sizeof field);

    InitBlock();// [6-6-2]블록을 초기화하는 함수를 호출한다

    DrawScreen();// [6-6-3]화면을 그리는 함수를 호출한다
}

// [6-7]낙하 블록을 떨어뜨리는 함수를 선언한다
void FallBlock()
{
    BLOCK lastBlock = block;// [6-7-1]블록 이동 전의 상태를 선언한다

    block.y++;// [6-7-2]블록을 떨어뜨린다

    // [6-7-3]블록과 필드가 겹쳤는지 여부를 판정한다
    if (BlockIntersectField())
    {
        // [6-7-4]낙하 블록을 이동 전의 상태로 되돌린다
        block = lastBlock;

        // [6-7-5]낙하 블록의 모든 행을 반복한다
        for (int y = 0; y < BLOCK_HEIGHT_MAX; y++)
        {
            // [6-7-6]낙하 블록의 모든 열을 반복한다
            for (int x = 0; x < BLOCK_WIDTH_MAX; x++)
            {
                // [6-7-7]블록이 있는 칸인지 여부를 판정한다 
                if (block.shape.pattern[y][x])
                {
                    // [6-7-8]필드에 지울 수 있는 블록을 써넣는다
                    field[block.y + y][block.x + x] = BLOCK_SOFT;
                }
            }
        }

        // [6-7-9]채워진 블록을 삭제하는 함수를 호출한다
        EraseLine();

        // [6-7-10]블록을 초기화하는 함수를 호출한다
        InitBlock();

        // [6-7-11]블록과 필드가 겹쳤는지 여부를 판정한다
        if (BlockIntersectField())
        {
            Init();// [6-7-12]게임을 초기화한다
        }
    }

    DrawScreen();// [6-7-13]화면을 그리는 함수를 호출한다
}

// [6-8]프로그램 실행의 시작점을 선언한다
int main()
{
    srand((unsigned int)time(NULL));// [6-8-1]난수를 섞는다

    // [6-8-2]게임을 초기화하는 함수를 호출한다
    Init();

    clock_t lastClock = clock();// [6-8-3]이전 회의 갱신 시각을 보유하는 변수를 선언한다

    // [6-8-4]메인 루프
    while (1)
    {
        clock_t newClock = clock();// [6-8-5]현재 시각을 선언한다

        // [6-8-6]대기 시간을 경과하면
        if (newClock >= lastClock + INTERVAL)
        {
            lastClock = newClock;// [6-8-7]이전 회의 갱신 시각을 현재 시각으로 갱신한다

            FallBlock();// [6-8-8]낙하 블록을 떨어뜨리는 함수를 호출한다
        }

        // [6-8-9]키보드 입력이 있었는지 여부를 판정한다
        if (_kbhit())
        {
            // [6-8-10]블록 이동 전의 상태를 선언한다
            BLOCK lastBlock = block;

            // [6-8-11]입력된 키에 따라 분기한다
            switch (_getch())
            {
            case 'w':       // [6-8-12]w키를 누르면
                break;

            case 's':       // [6-8-13]s키를 누르면
                block.y++;  // [6-8-14]블록을 아래로 이동한다
                break;

            case 'a':       // [6-8-15]a키를 누르면
                block.x--;  // [6-8-16]블록을 왼쪽으로 이동한다
                break;

            case 'd':       // [6-8-17]d키를 누르면
                block.x++;  // [6-8-18]블록을 오른쪽으로 이동한다
                break;

            default:// [6-8-19]이동 이외의 키를 누르면

                // [6-8-20]낙하 블록을 회전시키는 함수를 호출한다
                RotateBlock();

                break;
            }

            // [6-8-21]블록과 필드가 겹쳤는지 여부를 판정한다
            if (BlockIntersectField())
            {
                // [6-8-22]블록을 이동 전의 상태로 되돌린다
                block = lastBlock;
            }
            // [6-8-23]블록과 필드가 겹치지 않으면
            else
            {
                // [6-8-24]화면을 그리는 함수를 호출한다
                DrawScreen();
            }
        }
    }
}