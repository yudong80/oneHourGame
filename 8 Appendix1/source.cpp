// [1]헤더를 인클루드하는 곳

#include <stdio.h>      // [1-1]표준 입출력 헤더를 인클루드한다
#include <stdlib.h>     // [1-2]표준 라이브러리 헤더를 인클루드한다
#include <time.h>       // [1-3]시간 관리 헤더를 인클루드한다
#include <conio.h>      // [1-4]콘솔 입출력 헤더를 인클루드한다
#include <vector>       // [1-5]벡터 헤더를 인클루드한다
#include <algorithm>    // [1-6]알고리즘 헤더를 인클루드한다

// [2]상수를 정의하는 곳

#define TROOP_BASE      (5)     // [2-1]기본 병력 수를 정의한다
#define TROOP_MAX       (9)     // [2-2]최대 병력 수를 정의한다
#define TROOP_UNIT      (10000) // [2-3]병력 수 단위를 정의한다
#define START_YEAR      (227)   // [2-4]시작 년도를 정의한다
#define CHRONOLOGY_MAX  (1024)  // [2-5]연표의 최대 문자 수를 정의한다

// [3]열거 상수를 정의하는 곳

// [3-1]다이묘의 종류를 정의한다
enum
{
    LORD_IGAK,        // [3-1- 1]이각
    LORD_YUBI,        // [3-1- 2]유비
    LORD_WONSO,       // [3-1- 3]원소
    LORD_JOJO,        // [3-1- 4]조조
    LORD_YEOPO,       // [3-1- 5]여포
    LORD_YUPYO,       // [3-1- 6]유표
    LORD_SONCHAEK,    // [3-1- 7]손책
    LORD_YUJANG,      // [3-1- 8]유장
    LORD_MADEUNG,     // [3-1- 9]마등
    LORD_GONGSONCHAN, // [3-1-10]공손찬
    LORD_MAX          // [3-1-11]종류의 개수
};

// [3-2]성의 종류를 정의한다
enum
{
    CASTLE_SAYE,     // [3-2- 1]사예
    CASTLE_YEJU,     // [3-2- 2]예주
    CASTLE_GIJU,     // [3-2- 3]기주
    CASTLE_YEONJU,   // [3-2- 4]연주
    CASTLE_SEOJU,    // [3-2- 5]서주
    CASTLE_HYEONGJU, // [3-2- 6]형주
    CASTLE_YANGJU,   // [3-2- 7]양주
    CASTLE_IKJU,     // [3-2- 8]익주
    CASTLE_RYANGJU,  // [3-2- 9]량주
    CASTLE_YUJU,     // [3-2-10]유주
    CASTLE_MAX       // [3-2-11]종류의 개수
};

// [4]구조체를 선언하는 곳

// [4-1]다이묘 구조체를 선언한다
typedef struct {
    char familyName[16];    // [4-1-1]성
    char firstName[16];     // [4-1-2]이름
} LORD;

// [4-2]성 구조체를 선언한다
typedef struct {
    const char* name;                       // [4-2-1]이름
    int                 owner;              // [4-2-2]성주
    int                 troopCount;         // [4-2-3]병력 수
    std::vector<int>    connectedCastles;   // [4-2-4]연결된 성 리스트
} CASTLE;

// [5]변수를 선언하는 곳

// [5-1]다이묘 배열을 선언한다
LORD lords[LORD_MAX] =
{
    {"이각",      "치연",},   // [5-1- 1]LORD_IGAK    이각
    {"유비",      "현덕",},   // [5-1- 2]LORD_YUBI     유비
    {"원소",      "본초",},   // [5-1- 3]LORD_WONSO     원소
    {"조조",      "맹덕",},   // [5-1- 4]LORD_JOJO      조조
    {"여포",      "봉선",},   // [5-1- 5]LORD_YEOPO     여포
    {"유표",      "경승",},   // [5-1- 6]LORD_YUPYO    유표
    {"손책",      "백부",},   // [5-1- 7]LORD_SONCHAEK   손책
    {"유장",      "계옥",},   // [5-1- 8]LORD_YUJANG    유장
    {"마등",      "수성",},   // [5-1- 9]LORD_MADEUNG      마등
    {"공손찬",    "백규",},   // [5-1-10]LORD_GONGSONCHAN  공손찬
};

// [5-2]성 배열을 선언한다
CASTLE castles[CASTLE_MAX] =
{
    // [5-2-1]CASTLE_SAYE 사예
    {
        "사예",         // const char* name     이름
        LORD_IGAK,      // int owner            성주
        TROOP_BASE,     // int troopCount       병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_YEJU,     // 예주
            CASTLE_GIJU,     // 기주
            CASTLE_YEONJU,   // 연주
            CASTLE_HYEONGJU, // 형주
            CASTLE_IKJU,     // 익주
            CASTLE_RYANGJU   // 량주
        }
    },

    // [5-2-2]CASTLE_YEJU  예주
    {
        "예주",     // const char* name 이름
        LORD_YUBI,  // int owner        성주
        TROOP_BASE, // int troopCount   병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_SAYE,     // 사예
            CASTLE_YEONJU,   // 연주
            CASTLE_SEOJU,    // 서주
            CASTLE_HYEONGJU, // 형주
            CASTLE_YANGJU    // 양주
        }
    },

    // [5-2-3]CASTLE_GIJU  기주
    {
        "기주",     // const char* name 이름
        LORD_WONSO, // int owner        성주
        TROOP_BASE, // int troopCount   병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_SAYE,   // 사예
            CASTLE_YEONJU, // 연주
            CASTLE_SEOJU,  // 서주
            CASTLE_YUJU    // 유주
        }
    },

    // [5-2-4]CASTLE_YEONJU  연주
    {
        "연주",     // const char* name 이름
        LORD_JOJO,  // int owner        성주
        TROOP_BASE, // int troopCount   병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_SAYE,  // 사예
            CASTLE_YEJU,  // 예주
            CASTLE_GIJU,  // 기주
            CASTLE_SEOJU  // 서주
        }
    },

    // [5-2-5]CASTLE_SEOJU  서주
    {
        "서주",     // const char* name 이름
        LORD_YEOPO, // int owner        성주
        TROOP_BASE, // int troopCount   병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_YEJU,   // 예주
            CASTLE_GIJU,   // 기주
            CASTLE_YEONJU, // 연주
            CASTLE_YANGJU  // 양주
        }
    },

    // [5-2-6]CASTLE_HYEONGJU 형주
    {
        "형주",        // const char* name 이름
        LORD_YUPYO,    // int owner        성주
        TROOP_BASE,    // int troopCount   병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_SAYE,   // 사예
            CASTLE_YEJU,   // 예주
            CASTLE_YANGJU, // 양주
            CASTLE_IKJU    // 익주
        }
    },

    // [5-2-7]CASTLE_YANGJU 양주
    {
        "양주",         // const char* name 이름
        LORD_SONCHAEK,  // int owner        성주
        TROOP_BASE,     // int troopCount   병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_YEJU,     // 예주
            CASTLE_SEOJU,    // 서주
            CASTLE_HYEONGJU  // 형주
        }
    },

    // [5-2-8]CASTLE_IKJU 익주
    {
        "익주",         // const char* name 이름
        LORD_YUJANG,    // int owner        성주
        TROOP_BASE,     // int troopCount   병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_SAYE,    // 사예
            CASTLE_HYEONGJU // 형주
        }
    },

    // [5-2-9]CASTLE_RYANGJU 량주
    {
        "량주",       // const char* name 이름
        LORD_MADEUNG, // int owner        성주
        TROOP_BASE,   // int troopCount   병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_SAYE   // 사예
        }
    },

    // [5-2-10]CASTLE_YUJU 유주
    {
        "유주",           // const char* name 이름
        LORD_GONGSONCHAN, // int owner        성주
        TROOP_BASE,       // int troopCount   병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_GIJU  // 기주
        }
    }
};

int year;  // [5-3]현재 연도를 선언한다

int playerLord;// [5-4]플레이어의 다이묘를 선언한다

char chronology[CHRONOLOGY_MAX];// [5-5]연표를 선언한다

// [6]함수를 선언하는 곳

// [6-1]성의 개수를 세는 함수를 선언한다
int GetCastleCount(int _lord)
{
    // [6-1-1]성의 개수를 선언한다
    int castleCount = 0;

    // [6-1-2]모든 성을 반복한다
    for (int i = 0; i < CASTLE_MAX; i++)
    {
        // [6-1-3]대상 성의 성주가 대상 다이묘인지 여부를 판정한다
        if (castles[i].owner == _lord)
        {
            // [6-1-4]성의 개수를 더한다
            castleCount++;
        }
    }

    // [6-1-5]성의 개수를 반환한다
    return castleCount;
}

// [6-2]기본 정보를 그리는 함수를 선언한다
void DrawScreen()
{
    system("cls");// [6-2-1]화면을 클리어한다
    /*
        // [6-2-1.5]지도 샘플을 그린다
        printf("%s",
            " 196년　　　　　　　　　　9유주5　　　  \n"    // 01
            "　　　　　　　　　　　　　공손　　～　～\n"    // 02
            "8량주5　　　　　　2기주5　　　～～～～～\n"    // 03
            "마등　　　　　　　원소　　～～～～～～～\n"    // 04
            "　　　　　　　　　　　　　　～～　　～～\n"    // 05
            "　　　　　　　　　3연주5　　　　　～～～\n"    // 06
            "　　　0사예5　　　조조　　4서주5　～～～\n"    // 07
            "　　　이각　　　　　　　　여포　～～～～\n"    // 08
            "　　　　　　　　　1예주5　　　　　～～～\n"    // 09
            "　　　　　　　　　유비　　　　　　　～～\n"    // 10
            "7익주5　　5형주5　　　　6양주5　　　～～\n"    // 11
            "유장　　　유표　　　　　손책　　　　～～\n"    // 12
            "　　　　　　　　　　　　　　　　　～～～\n"    // 13
            "　　　　　　　　　　　　　　　　　～～～\n"    // 14
            "　　　　　　　　　　　　　　　～～～～～\n"    // 15
            "　　　　　　　　　～～～～～～～～～～～\n"    // 16
        );*/
    
    // [6-2-2]지도의 1번째 행을 그린다
    
    printf(" %d년  　　　　　　　　　　%d%.4s%d　　　\n",
        year,                              // 연도
        CASTLE_YUJU,                       // 유주의 주 번호
        castles[CASTLE_YUJU].name,         // 유주의 이름
        castles[CASTLE_YUJU].troopCount);  // 유주의 병력 수

    // [6-2-3]지도의 2번째 행을 그린다
    printf("　　　　　　　　　　　　　　%.4s　～　～\n",
        lords[castles[CASTLE_YUJU].owner].familyName); // 유주 주목의 성명

    // [6-2-4]지도의 3번째 행을 그린다
    printf("%d%.4s%d　　　　　　%d%.4s%d　　　～～～～～\n",
        CASTLE_RYANGJU,                      // 량주의 주 번호
        castles[CASTLE_RYANGJU].name,        // 량주의 이름
        castles[CASTLE_RYANGJU].troopCount,  // 량주의 병력 수
        CASTLE_GIJU,                       // 기주의 주 번호
        castles[CASTLE_GIJU].name,         // 기주의 이름
        castles[CASTLE_GIJU].troopCount);  // 기주의 병력 수

    // [6-2-5]지도의 4번째 행을 그린다
    printf("%.4s　　　　　　　%.4s　　～～～～～～～\n",
        lords[castles[CASTLE_RYANGJU].owner].familyName,     // 량주 주목의 성명
        lords[castles[CASTLE_GIJU].owner].familyName);     // 기주 주목의 성명

    // [6-2-6]지도의 5번째 행을 그린다
    printf("　　　　　　　　　　　　　　～～　　～～\n");

    // [6-2-7]지도의 6번째 행을 그린다
    printf("　　　　　　　　　%d%.4s%d　　　　　～～～\n",
        CASTLE_YEONJU,                       // 연주의 주 번호
        castles[CASTLE_YEONJU].name,         // 연주의 이름
        castles[CASTLE_YEONJU].troopCount);  // 연주의 병력 수

    // [6-2-8]지도의 7번째 행을 그린다
    printf("　　　%d%.4s%d　　　%.4s　　%d%.4s%d　～～～\n",
        CASTLE_SAYE,                                    // 사예의 주 번호
        castles[CASTLE_SAYE].name,                      // 사예의 이름
        castles[CASTLE_SAYE].troopCount,                // 사예의 병력 수
        lords[castles[CASTLE_YEONJU].owner].familyName, // 연주 주목의 성명
        CASTLE_SEOJU,                                   // 서주의 주 번호
        castles[CASTLE_SEOJU].name,                     // 서주의 이름
        castles[CASTLE_SEOJU].troopCount);              // 서주의 병력 수

    // [6-2-9]지도의 8번째 행을 그린다
    printf("　　　%.4s　　　　　　　　%.4s　～～～～\n",
        lords[castles[CASTLE_SAYE].owner].familyName,   // 사예 주목의 성명
        lords[castles[CASTLE_SEOJU].owner].familyName); // 서주 주목의 성명

    // [6-2-10]지도의 9번째 행을 그린다
    printf("　　　　　　　　　%d%s%d　　　　～～～～\n",
        CASTLE_YEJU,                       // 예주의 주 번호
        castles[CASTLE_YEJU].name,         // 예주의 이름
        castles[CASTLE_YEJU].troopCount);  // 예주의 병력 수

    // [6-2-11]지도의 10번째 행을 그린다
    printf("　　　　　　　　　%.4s　　　　　　～～～\n",
        lords[castles[CASTLE_YEJU].owner].familyName); // 예주 주목의 성명

    // [6-2-12]지도의 11번째 행을 그린다
    printf("　　　　　%d%.4s%d　　　　　　%d%.4s%d　～～\n",
        CASTLE_HYEONGJU,                      // 형주의 주 번호
        castles[CASTLE_HYEONGJU].name,        // 형주의 이름
        castles[CASTLE_HYEONGJU].troopCount,  // 형주의 병력 수
        CASTLE_YANGJU,                        // 양주의 주 번호
        castles[CASTLE_YANGJU].name,          // 양주의 이름
        castles[CASTLE_YANGJU].troopCount);   // 양주의 병력 수

    // [6-2-13]지도의 12번째 행을 그린다
    printf("%d%.4s%d　　%.4s　　　　　　　%.4s　　～～\n",
        CASTLE_IKJU,                                      // 익주의 주 번호
        castles[CASTLE_IKJU].name,                        // 익주의 이름
        castles[CASTLE_IKJU].troopCount,                  // 익주의 병력 수
        lords[castles[CASTLE_HYEONGJU].owner].familyName, // 형주 주목의 성명
        lords[castles[CASTLE_YANGJU].owner].familyName);  // 양주 주목의 성명

    // [6-2-14]지도의 13번째 행을 그린다
    printf("%.4s　　　　　　　　　　　　　　　　～～\n",
        lords[castles[CASTLE_IKJU].owner].familyName);    // 익주 주목의 성명

    // [6-2-15]지도의 14번째 행을 그린다
    printf("　　　　　　　　　　　　　　　　　　～～\n");

    // [6-2-16]지도의 15번째 행을 그린다
    printf("　　　　　　　　　　　　　　　　～～～～\n");

    // [6-2-17]지도의 16번째 행을 그린다
    printf("　　　　　　　　　～～～～～～～～～～～\n");
    
    // [6-2-18]1행 비워둔다
    printf("\n");
}

// [6-3]게임을 초기화하는 함수를 선언한다
void Init()
{
    year = START_YEAR;// [6-3-1]연도를 리셋한다

    // [6-3-2]모든 성을 반복한다
    for (int i = 0; i < CASTLE_MAX; i++)
    {
        // [6-3-3]성주를 초기화한다
        castles[i].owner = i;

        // [6-3-4]병력 수를 초기화한다
        castles[i].troopCount = TROOP_BASE;
    }

    // [6-3-5]연표를 클리어한다
    sprintf_s(chronology, "");

    DrawScreen();// [6-3-6]기본 정보를 그리는 화면을 호출한다

    // [6-3-7]다이묘 선택을 촉구하는 메시지를 표시한다
    printf("폐하, 우리 성은\n"
        "이 지도의 어디에 있습니까？！（0~%d）\n",
        CASTLE_MAX - 1);    // 성 번호의 최댓값

    printf("\n");// [6-3-8]1행 비운다

    // [6-3-9]선택된 성을 보유하는 변수를 선언한다
    int selectedCastle;

    // [6-3-10]범위 내의 성 번호가 입력될 때까지 반복한다
    do {
        selectedCastle = _getch() - '0';// [6-3-11]성 번호를 입력한다
    } while ((selectedCastle < 0) || (selectedCastle >= CASTLE_MAX));

    // [6-3-12]선택한 성의 성주를 플레이어 다이묘로 한다
    playerLord = castles[selectedCastle].owner;

    // [6-3-13]결정한 다이묘를 통지하는 메시지를 표시한다
    printf("%s님, %s에서 천하 통일을\n 목표로 합시다！\n",
        lords[playerLord].firstName,    // 선택된 다이묘의 이름
        castles[playerLord].name);      // 선택된 성의 이름

    _getch();// [6-3-14]키보드 입력을 기다린다
}

// [6-4]공성전의 함수를 선언한다
void Siege(
    int _offensiveLord,         // 공격한 다이묘
    int _offensiveTroopCount,   // 공격한 병력 수
    int _castle)                // 공격당한 성
{
    system("cls");// [6-4-1]화면을 클리어한다

    // [6-4-2]공성전의 이름을 표시한다
    printf("～%s전투～\n", castles[_castle].name);

    printf("\n");// [6-4-3]1행 비운다

    // [6-4-4]공격당한 다이묘를 선언한다
    int defensiveLord = castles[_castle].owner;

    // [6-4-5]무한 루프한다
    while (1)
    {
        // [6-4-6]전투의 경과를 표시한다
        printf("%s군(%5d명)　Ｘ　%s군(%5d명)\n",

            // 공격한 다이묘의 성씨
            lords[_offensiveLord].familyName,

            // 공격한 병력 수
            _offensiveTroopCount * TROOP_UNIT,

            // 공격당한 다이묘의 성씨
            lords[defensiveLord].familyName,

            // 공격당한 성의 병력 수
            castles[_castle].troopCount * TROOP_UNIT);

        _getch();// [6-4-7]키보드 입력을 기다린다

        // [6-4-8]공격과 수비 중 어느 한쪽의 병력 수가 0이하인지 여부를 판정한다
        if ((_offensiveTroopCount <= 0) || (castles[_castle].troopCount <= 0))
        {
            break;// [6-4-9]루프를 빠져나간다
        }

        // [6-4-10]0~2의 난수가 0인지 여부를 판정한다
        if (rand() % 3 == 0)
        {
            castles[_castle].troopCount--;// [6-4-11]수비 측의 병력을 줄인다
        }

        // [6-4-12]0~2의 난수가 1이나 2면
        else
        {
            _offensiveTroopCount--;// [6-4-13]공격 측의 병력을 줄인다
        }
    }

    printf("\n");// [6-4-14]1행 비운다

    // [6-4-15]수비 측의 병력이 전멸했는지 여부를 판정한다
    if (castles[_castle].troopCount <= 0)
    {
        // [6-4-16]성이 함락되었다는 메시지를 표시한다
        printf("%s　함락！！\n", castles[_castle].name);

        printf("\n");// [6-4-17]1행 비운다

        // [6-4-18]공격 측의 다이묘 성으로 한다
        castles[_castle].owner = _offensiveLord;

        // [6-4-19]공격 측의 병력을 입성시킨다
        castles[_castle].troopCount = _offensiveTroopCount;

        // [6-4-20]성주가 공격한 다이묘로 바뀐 메시지를 표시한다
        printf("%s는　%s 가문의 것이 됩니다\n",
            castles[_castle].name,
            lords[_offensiveLord].familyName);

        printf("\n");// [6-4-21]1행 비운다

        // [6-4-22]수비 측의 다이묘가 성을 모두 잃었는지 여부를 판정한다
        if (GetCastleCount(defensiveLord) <= 0)
        {
            char str[128];  // [6-4-23]추가하는 문자열을 선언한다

            // [6-4-24]24]추가하는 문자열을 작성한다
            sprintf_s(str, "%d년　%s（%s）이(가)　%s에서　%s（%s）을　멸망시키다\n",
                year,                               // 멸망시킨 연도
                lords[_offensiveLord].familyName,   // 멸망시킨 다이묘의 성씨
                lords[_offensiveLord].firstName,    // 멸망시킨 다이묘의 이름
                castles[_castle].name,              // 전장의 이름
                lords[defensiveLord].familyName,    // 멸망한 다이묘의 성씨
                lords[defensiveLord].firstName);    // 멸망한 다이묘의 이름

            // [6-4-25]연표에 문자열을 추가한다
            strcat_s(chronology, str);
        }
    }

    // [6-4-26]수비 측의 병력이 전멸하지 않았다면
    else
    {
        // [6-4-27]공격 측이 전멸한 메시지를 표시한다 
        printf("%s군　전멸！！\n"
            "\n"
            "%s군이　%s을(를) 지켜냈습니다！\n",
            lords[_offensiveLord].familyName,
            lords[defensiveLord].familyName,
            castles[_castle].name);
    }
}

// [6-5]프로그램 실행의 시작점을 선언한다
int main()
{

    srand((unsigned int)time(NULL));// [6-5-1]난수를 섞는다

start:  // [6-5-2]게임 시작 라벨
    ;   // [6-5-3]빈 문장

    Init();// [6-5-4]게임을 리셋하는 함수를 호출한다

    // [6-5-5]메인 루프
    while (1)
    {
        int turnOrder[CASTLE_MAX];  // [6-5-6]턴 순서의 테이블을 선언한다

        // [6-5-7]턴 순서를 초기화한다
        for (int i = 0; i < CASTLE_MAX; i++)
        {
            turnOrder[i] = i;// [6-5-8]턴 순서를 초기화한다
        }

        // [6-5-9]모든 성을 반복한다
        for (int i = 0; i < CASTLE_MAX; i++)
        {
            // [6-5-10]턴을 랜덤으로 바꾼다
            std::swap(turnOrder[i], turnOrder[rand() % CASTLE_MAX]);
        }

        // [6-5-11]모든 턴을 반복한다
        for (int i = 0; i < CASTLE_MAX; i++)
        {
            DrawScreen();// [6-5-12]기본 정보 화면을 그린다

            // [6-5-13]모든 턴을 반복한다
            for (int j = 0; j < CASTLE_MAX; j++)
            {
                // [6-5-14]현재 턴의 성에 커서를 그린다
                printf("%s", (j == i) ? "＞" : "　");

                // [6-5-15]각 턴의 성 이름을 그린다
                printf("%.4s", castles[turnOrder[j]].name);
            }

            // [6-5-16]줄바꿈하여 1행 비운다
            printf("\n\n");

            // [6-5-17]현재 턴의 성 번호를 선언한다
            int currentCastle = turnOrder[i];

            // [6-5-18]메시지를 표시한다
            printf("%s 가문의　%s　전략 회의…\n",
                lords[castles[currentCastle].owner].familyName, // 성주의 성씨
                castles[currentCastle].name);                   // 성의 이름

            printf("\n");// [6-5-19]1행 비운다

            // [6-5-20]현재 성의 성주가 플레이어인지 여부를 판정한다
            if (castles[currentCastle].owner == playerLord)
            {
                // [6-5-21]진군할 성의 지정을 촉구하는 메시지를 표시한다
                printf("%s님, 어디로 진군하시겠습니까？\n",
                    lords[castles[currentCastle].owner].firstName);

                printf("\n");// [6-5-22]1행 비운다

                // [6-5-23]모든 연결된 성을 반복한다
                for (int j = 0; j < (int)castles[currentCastle].connectedCastles.size(); j++)
                {
                    // [6-5-24]연결된 성 번호와 이름을 표시한다
                    printf("%d %s\n",
                        castles[currentCastle].connectedCastles[j],
                        castles[castles[currentCastle].connectedCastles[j]].name);
                }

                printf("\n");// [6-5-25]1행 비운다

                // [6-5-26]진군 목표의 성을 입력하여 선언한다
                int targetCastle = _getch() - '0';

                // [6-5-27]현재 성과 대상 성이 연결되어 있는지 여부를 보유하는 플래그를 선언한다
                bool isConnected = false;

                // [6-5-28]현재 성과 연결된 모든 성을 반복한다
                for (int castle : castles[currentCastle].connectedCastles)
                {
                    // [6-5-29]대상 성과 연결이 확인되면
                    if (castle == targetCastle)
                    {
                        isConnected = true;// [6-5-30]연결의 유무 플래그를 설정한다

                        break;// [6-5-31]반복을 빠져나온다
                    }
                }

                // [6-5-32]연결된 성이 선택되지 않으면
                if (!isConnected)
                {
                    // [6-5-33]진군을 취소하는 메시지를 표시한다
                    printf("진군을 취소했습니다\n");

                    _getch();// [6-5-34]키보드 입력을 기다린다

                    continue;// [6-5-35]다음 국가의 전략 회의로 스킵한다
                }

                // [6-5-36]현재 성의 병력 수를 최대 진군 수로 선언한다
                int troopMax = castles[currentCastle].troopCount;

                // [6-5-37]진군 목적지가 플레이어의 성인지 여부를 판정한다
                if (castles[targetCastle].owner == playerLord)
                {
                    // [6-5-38]진군 목적지 성의 빈 병력 수를 선언한다
                    int targetCapacity = TROOP_MAX - castles[targetCastle].troopCount;

                    // [6-5-39]현재 성의 병력 수나 진군 목적지의 빈 병력 수 중에서 적은 쪽을 최대 진군 병력 수로 한다
                    troopMax = std::min(troopMax, targetCapacity);
                }

                // [6-5-40]입력된 성을 통지하고, 이동하는 병력 수의 입력을 촉구하는 메시지를 표시한다
                printf("%s에 몇 만명 진군하시겠습니까?(0～%d)\n",
                    castles[targetCastle].name,	// 진군 목적지 성의 이름
                    troopMax);					// 진군 병력 수

                // [6-5-41]진군 병력 수를 선언한다
                int troopCount;
                
                // [6-5-42]범위 내의 병력 수가 입력될 때까지 반복한다
                do {
                    troopCount = _getch() - '0';// [6-5-43]진군 병력 수를 입력한다
                } while ((troopCount < 0) || (troopCount > troopMax));

                // [6-5-44]현재 성의 병력 수를 이동하는 만큼 뺀다 여기
                castles[currentCastle].troopCount -= troopCount;

                // [6-5-45]이동 목적지가 플레이어의 성이면
                if (castles[targetCastle].owner == playerLord)
                {
                    // [6-5-46]진군 목적지의 성 병력 수에 이동 병력 수를 더한다
                    castles[targetCastle].troopCount += troopCount;
                }

                // [6-5-47]줄바꿈한다
                printf("\n");

                // [6-5-48]입력된 진군 병력 수를 통지한다
                printf("%s에　%d명%s",
                    castles[targetCastle].name, // 진군 목적지 성의 이름
                    troopCount * TROOP_UNIT,	// 진군 병력 수

                    // 진군 목적지 성의 성주가 플레이어인지 여부를 판정한다
                    (castles[targetCastle].owner == playerLord)
                    ? "　이동했습니다"          // 플레이어의 성이면
                    : "으로 출진이다～！！");  // 적의 성이면

                // [6-5-49]진군 목적지가 적의 성인지 여부를 판정한다
                if (castles[targetCastle].owner != playerLord)
                {
                    _getch();// [6-5-50]키보드 입력을 기다린다

                    // [6-5-51]공성전 함수를 호출한다
                    Siege(
                        playerLord,     // int _offensiveLord       공격한 다이묘
                        troopCount,     // int _offensiveTroopCount 공격한 병력 수
                        targetCastle);  // int _castle              공격당한 성
                }
            }

            // [6-5-52]현재 성의 성주가 플레이어가 아니면
            else
            {
                // [6-5-53]연결된 적의 성 리스트를 선언한다
                std::vector<int> connectedEnemyCastles;

                // [6-5-54]모든 연결된 성을 반복한다
                for (int j = 0;
                    j < (int)castles[currentCastle].connectedCastles.size();
                    j++)
                {
                    // [6-5-55]적의 성인지 여부를 판정한다
                    if (castles[castles[currentCastle].connectedCastles[j]].owner
                        != castles[currentCastle].owner)
                    {
                        // [6-5-56]연결된 적의 성 리스트에 더한다
                        connectedEnemyCastles.push_back(
                            castles[currentCastle].connectedCastles[j]);
                    }
                }

                // [6-5-57]연결된 적의 성이 있는지 여부를 판정한다
                if (connectedEnemyCastles.size() > 0)
                {
                    // [6-5-58]병력이 적은 순으로 정렬한다
                    sort(connectedEnemyCastles.begin(), connectedEnemyCastles.end(),
                        // 2개의 성을 비교하는 람다
                        [](int _castle0, int _castle1)
                        {
                            // 리스트 뒤의 성쪽이 병력이 많은지 여부를 판정하여 반환한다
                            return castles[_castle0].troopCount < castles[_castle1].troopCount;
                        }
                    );

                    // [6-5-59]가장 병력이 적은 성만 남을 때까지 반복한다
                    while (
                        // 인접하는 적의 성이 2성 이상이다
                        (connectedEnemyCastles.size() > 1)

                        // 그리고 그 중에서 가장 병력 수가 적은 성보다도 병력 수가 많은 성이 있으면
                        && (castles[connectedEnemyCastles.front()].troopCount
                            < castles[connectedEnemyCastles.back()].troopCount))
                    {
                        // [6-5-60]리스트에서 맨 끝을 삭제한다 
                        connectedEnemyCastles.pop_back();
                    }

                    // [6-5-61]공격하는 성을 선언한다
                    int targetCastle =
                        connectedEnemyCastles[rand() % connectedEnemyCastles.size()];

                    // [6-5-62]공격할지 여부를 판정한다
                    if (
                        // 병력 수가 기준치 이상인가
                        (castles[currentCastle].troopCount >= TROOP_BASE)

                        // 이쪽의 병력 수가 수비병을 제하고 상대의 2배이상이면
                        || (castles[currentCastle].troopCount - 1
                            >= castles[targetCastle].troopCount * 2))
                    {
                        // [6-5-63]공격하는 병력 수를 선언한다
                        int troopCount = std::max(castles[currentCastle].troopCount - 1, 0);

                        // [6-5-64]현재 성의 병력 수에서 공격하는 병력 수를 뺀다
                        castles[currentCastle].troopCount -= troopCount;

                        // [6-5-65]공격하는 메시지를 표시한다
                        printf("%s의　%s（%s）가　%s에　공격해 들어갔습니다！\n",
                            castles[currentCastle].name,
                            lords[castles[currentCastle].owner].familyName,
                            lords[castles[currentCastle].owner].firstName,
                            castles[targetCastle].name);

                        _getch();// [6-5-66]키보드 입력을 기다린다

                        // [6-5-67]공성전 함수를 호출한다
                        Siege(

                            // int _offensiveLord       공격한 다이묘
                            castles[currentCastle].owner,

                            // int _offensiveTroopCount 공격한 병력 수
                            troopCount,

                            // int _castle              공격한 성
                            targetCastle);
                    }
                }

                // [6-5-68]연결된 적의 성이 없으면
                else
                {
                    // [6-5-69]연결된 전선의 성 리스트를 선언한다
                    std::vector<int> frontCastles;

                    // [6-5-70]모든 연결된 성을 반복한다
                    for (int neighbor : castles[currentCastle].connectedCastles)
                    {
                        // [6-5-71]인접하는 성에 연결된 모든 성을 반복한다
                        for (int neighborNeighbor : castles[neighbor].connectedCastles)
                        {
                            // [6-5-72]대상 성이 적의 성에 인접하고 있는지 여부를 판정한다
                            if (castles[neighborNeighbor].owner != castles[neighbor].owner)
                            {
                                frontCastles.push_back(neighbor);// [6-5-73]전선의 성 리스트에 추가한다

                                break;// [6-5-74]반복을 빠져나간다
                            }
                        }
                    }

                    // [6-5-75]병력을 보내는 성 리스트를 선언한다
                    std::vector<int> destCastles =

                        // 전선이 성이 없는지 여부를 판정한다
                        frontCastles.empty()

                        // 없으면 연결된 성 리스트를 설정한다
                        ? castles[currentCastle].connectedCastles

                        // 있으면 전선의 성 리스트를 설정한다
                        : frontCastles;

                    // [6-5-76]병력이 적은 순으로 정렬한다
                    sort(destCastles.begin(), destCastles.end(),
                        [](int _castle0, int _castle1)
                        {
                            return castles[_castle0].troopCount < castles[_castle1].troopCount;
                        }
                    );

                    // [6-5-77]가장 병력이 적은 성만 남을 때까지 반복한다
                    while (
                        // 병력을 보내는 목적지 성의 후보가 여러 개 있다
                        (destCastles.size() > 1)

                        // 그리고 그 중에서 가장 병력 수가 적은 성보다도 병력 수가 많은 성이 있으면
                        && (castles[destCastles.front()].troopCount
                            < castles[destCastles.back()].troopCount))
                    {
                        // [6-5-78]리스트에서 맨 끝을 삭제한다
                        destCastles.pop_back();
                    }

                    // [6-5-79]병력을 보내는 성을 선언한다
                    int targetCastle = destCastles[rand() % destCastles.size()];

                    // [6-5-80]보내는 병력 수를 선언한다
                    int sendTroopCount = TROOP_MAX - castles[targetCastle].troopCount;

                    // [6-5-81]병력을 보내는 목적지의 성이 전선인지 여부를 판정한다
                    if (!frontCastles.empty())
                    {
                        // [6-5-82]보내는 목적지의 빈 병력 수와 보내는 곳의 병력 수 중, 적은 병력 수를 설정한다
                        sendTroopCount = std::min(

                            // 보내는 목적지의 빈 병력 수
                            sendTroopCount,

                            // 보내는 곳의 병력 수
                            castles[currentCastle].troopCount);
                    }

                    // [6-5-83]兵を送る先の城が前線でない味方の城なら
                    else
                    {
                        // [6-5-84]送り先の空き병력 수と送り元の余剰병력 수のうち、少ない병력 수を設定する
                        sendTroopCount = std::min(

                            // 送り先の空き병력 수
                            sendTroopCount,

                            // 送り元の병력 수
                            castles[currentCastle].troopCount - (TROOP_BASE - 1));
                    }

                    // [6-5-85]보내는 병력이 있는지 여부를 판정한다
                    if (sendTroopCount > 0)
                    {
                        // [6-5-86]보내는 곳의 병력 수를 뺀다
                        castles[currentCastle].troopCount -= sendTroopCount;

                        // [6-5-87]보내는 곳의 병력 수를 늘린다
                        castles[targetCastle].troopCount += sendTroopCount;

                        // [6-5-88]병사가 이동한 메시지를 표시한다
                        printf("%s에서　%s로　%d명　이동했습니다\n",
                            castles[currentCastle].name,
                            castles[targetCastle].name,
                            sendTroopCount * TROOP_UNIT);
                    }
                }
            }

            _getch();// [6-5-89]키보드 입력을 기다린다

            // [6-5-90]플레이어의 성이 없는지 여부를 판정한다
            if (GetCastleCount(playerLord) <= 0)
            {
                DrawScreen();// [6-5-91]화면을 그린다

                printf("%s", chronology);// [6-5-92]연표를 표시한다

                printf("\n");// [6-5-93]1행 비운다

                // [6-5-94]게임 오버 메시지를 표시한다
                printf("ＧＡＭＥ　ＯＶＥＲ\n");

                _getch();// [6-5-95]키보드 입력을 기다린다

                goto start;// [6-5-96]게임 시작 라벨로 점프한다
            }

            // [6-5-97]플레이어가 모든 성을 소유하고 있는지 여부를 판정한다
            else if (GetCastleCount(playerLord) >= CASTLE_MAX)
            {
                DrawScreen();// [6-5-98]화면을 그린다

                printf("%s", chronology);// [6-5-99]연표를 표시한다

                // [6-5-100]엔딩 메시지를 표시한다
                printf("%d년　%s (%s)이(가)　천하를 통일한다\n"
                    "\n"
                    "ＴＨＥ　ＥＮＤ",
                    year,                       // 천하 통일한 연도
                    lords[playerLord].familyName,   // 플레이어의 군주 성명
                    lords[playerLord].firstName);    // 플레이어의 군주 자

                _getch();// [6-5-101]키보드 입력을 기다린다

                goto start;// [6-5-102]게임 시작 라벨로 점프한다
            }
        }

        year++;// [6-5-103]연도를 진행한다

        // [6-5-104]모든 성을 반복한다
        for (int i = 0; i < CASTLE_MAX; i++)
        {
            // [6-5-105]대상 성의 병력 수가 기본 병력 수 미만인지 여부를 판정한다
            if (castles[i].troopCount < TROOP_BASE)
            {
                castles[i].troopCount++;// [6-5-106]병력 수를 늘린다
            }

            // [6-5-107]대상 성의 병력 수가 기본 병력 수보다 많은지 여부를 판정한다
            else if (castles[i].troopCount > TROOP_BASE)
            {
                castles[i].troopCount--;// [6-5-108]병력 수를 줄인다
            }
        }
    }
}