// [1]헤더를 인클루드하는 곳

#include <stdio.h>  // [1-1]표준 입출력 헤더를 인클루드한다
#include <stdlib.h> // [1-2]표준 라이브러리 헤더를 인클루드한다
#include <string.h> // [1-3]문자열 조작 헤더를 인클루드한다
#include <time.h>   // [1-4]시간 관리 헤더를 인클루드한다
#include <stdbool.h> // [1-5]bool 타입을 위한 헤더를 인클루드한다

// [2]상수를 정의하는 곳

#define FIELD_WIDTH     (40)            // [2-1]필드의 너비를 정의한다 (터미널 크기에 맞게 조정)
#define FIELD_HEIGHT    (20)            // [2-2]필드의 높이를 정의한다 (터미널 크기에 맞게 조정)

#define FPS             (2)             // [2-3]1초당 갱신 횟수를 정의한다 (느리게 조정)
#define INTERVAL        (CLOCKS_PER_SEC/FPS) // [2-4]갱신 간격(clock ticks)을 정의한다

// [3]변수를 선언하는 곳

// [3-1]필드를 선언한다
bool field[FIELD_HEIGHT][FIELD_WIDTH] =
{
    /*
        {0,1,0},
        {0,0,1},
        {1,1,1}
    */
};

// [4]함수를 선언하는 곳

// [4-1]필드를 그리는 함수를 선언한다
void DrawField()
{
    system("clear");// [4-1-1]그리기 전에 화면을 클리어한다

    // [4-1-2]필드의 모든 행을 반복한다
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        // [4-1-3]필드의 모든 열을 반복한다
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            // [4-1-4]셀이 살아 있으면「*」를, 죽어 있으면「 」를 그립니다 (리눅스 터미널 호환성)
            printf("%s", field[y][x] ? "*" : " ");
        }

        printf("\n");// [4-1-5]1행 그릴 때마다 줄바꿈한다
    }
}

// [4-2]대상 셀과 인접하는 살아 있는 셀의 수를 가져오는 함수를 선언한다
int GetLivingCellsCount(int _x, int _y)
{
    int count = 0;// [4-2-1]살아 있는 셀을 세는 카운터를 선언한다

    // [4-2-2]대상 셀의 상하 1칸을 반복한다
    for (int y = _y - 1; y <= _y + 1; y++)
    {
        /*
                // [4-2-3]상하로 루프시키지 않는 경우는 행이 범위 내인지 여부를 판정한다
                if ((y < 0) || (y >= FIELD_HEIGHT))
                {
                    continue;// [4-2-4]범위 밖의 행이므로 스킵한다
                }
        */
        // [4-2-5]상하로 루프한 Y좌표를 선언한다
        int roopedY = (FIELD_HEIGHT + y) % FIELD_HEIGHT;

        // [4-2-6]대상 셀의 좌우 1칸을 반복한다 
        for (int x = _x + -1; x <= _x + 1; x++)
        {
            /*
                        // [4-2-7]좌우로 루프시키지 않는 경우는 열이 범위 내인지 여부를 판정한다
                        if ((x < 0) || (x >= FIELD_WIDTH))
                        {
                            continue;// [4-2-8]범위 밖의 열이므로 스킵한다
                        }
            */
            // [4-2-9]좌우로 루프한 X좌표를 선언한다
            int roopedX = (FIELD_WIDTH + x) % FIELD_WIDTH;

            // [4-2-10]대상 좌표가 중심 셀과 같은지 여부를 판정한다
            if ((roopedX == _x) && (roopedY == _y))
            {
                continue;// [4-2-11]대상 좌표를 스킵한다
            }

            // [4-2-12]대상 셀이 살아 있으면 1을, 죽어 있으면 0을 가산한다
            count += field[roopedY][roopedX];
        }
    }

    return count;// [4-2-13]살아 있는 셀의 수를 반환한다
}

// [4-3]1스텝만큼의 시뮬레이션을 실행하는 함수를 선언한다
void StepSimulation()
{
    // [4-3-1]다음 세대의 필드를 선언한다
    bool nextField[FIELD_HEIGHT][FIELD_WIDTH] = {};

    // [4-3-2]모든 행을 반복한다
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        //  [4-3-3]모든 열을 반복한다
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            // [4-3-4]대상 셀과 인접하는 살아 있는 셀의 수를 선언한다
            int livingCellCount = GetLivingCellsCount(x, y);

            // [4-3-5]인접하는 살아 있는 셀의 수로 분기한다
            if (livingCellCount <= 1)// [4-3-5]1개면
            {
                // [4-3-6]대상 셀을 사멸시킨다
                nextField[y][x] = false;
            }
            else if (livingCellCount == 2)// [4-3-7]2개면
            {
                // [4-3-8]현상 유지
                nextField[y][x] = field[y][x];
            }
            else if (livingCellCount == 3)// [4-3-9]3개면
            {
                // [4-3-10]대상 셀을 탄생/생존시킨다
                nextField[y][x] = true;
            }
            else// [4-3-11]4개 이상이면
            {
                // [4-3-12]대상 셀을 사멸시킨다
                nextField[y][x] = false;
            }
        }
    }

    // [4-3-13]다음 스텝의 필드를 현재 필드에 복사한다
    memcpy(field, nextField, sizeof field);
}

// [4-4]패턴을 필드에 복사하는 함수를 선언한다
void PatternTransfer(
    int _destX, int _destY,
    int _srcWidth, int _srcHeight,
    bool* _pPattern)
{
    // [4-4-1]패턴 내의 모든 행을 반복한다
    for (int y = 0; y < _srcHeight; y++)
    {
        // [4-4-2]패턴 내의 모든 열을 반복한다
        for (int x = 0; x < _srcWidth; x++)
        {
            // [4-4-3]패턴을 필드에 복사한다
            field[_destY + y][_destX + x] = _pPattern[y * _srcWidth + x];
        }
    }
}

// [4-5]프로그램 실행의 시작점을 선언한다
int main()
{
    const int patternWidth = 10;// [4-5-1]패턴의 너비를 선언한다
    const int patternHeight = 8;// [4-5-2]패턴의 높이를 선언한다

    // [4-5-3]패턴을 선언한다
    bool pattern[patternHeight][patternWidth] =
    {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,1,0,1,1,0},
        {0,0,0,0,0,1,0,1,0,0},
        {0,0,0,0,0,1,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0},
        {0,1,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
    };

    // [4-5-4]패턴을 필드의 중심에 복사한다 
    PatternTransfer(
        FIELD_WIDTH / 2 - patternWidth / 2,     // int _destX
        FIELD_HEIGHT / 2 - patternHeight / 2,   // int _destY
        patternWidth,                           // int _srcWidth
        patternHeight,                          // int _srcHeight
        (bool*)pattern);                        // bool* _pPattern

    clock_t lastClock = clock();// [4-5-5]이전 회의 경과 시간을 선언한다

    // [4-5-6]메인 루프
    while (1)
    {
        clock_t newClock = clock();// [4-5-7]현재의 경과 시간을 선언한다

        // [4-5-8]이전 회의 경과 시간에서 대기 시간이 경과하지 않으면
        if (newClock < lastClock + INTERVAL)
        {
            continue;// [4-5-9]대기 상태로 돌아간다
        }

        // [4-5-10]이전 회 경과 시간을 현재의 경과 시간으로 갱신한다
        lastClock = newClock;

        DrawField();// [4-5-11]필드를 그리는 함수를 호출한다

        //      _getch();// [4-5-12]키보드 입력을 기다린다

        StepSimulation();// [4-5-13]시뮬레이션을 진행한다
    }
}