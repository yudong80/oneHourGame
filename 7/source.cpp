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
#define TROOP_UNIT      (1000)  // [2-3]병력 수 단위를 정의한다
#define START_YEAR      (1570)  // [2-4]시작 연도를 정의한다
#define CHRONOLOGY_MAX  (1024)  // [2-5]연표의 최대 문자 수를 정의한다

// [3]열거 상수를 정의하는 곳 

// [3-1]다이묘의 종류를 정의한다
enum
{
    LORD_DATE,      // [3-1- 1]다테 테루무네
    LORD_UESUGI,    // [3-1- 2]우에스기 겐신
    LORD_TAKEDA,    // [3-1- 3]다케다 신겐
    LORD_HOJO,      // [3-1- 4]호조 우지마사
    LORD_TOKUGAWA,  // [3-1- 5]도쿠가와 이에야스
    LORD_ODA,       // [3-1- 6]오다 노부나가
    LORD_ASHIKAGA,  // [3-1- 7]아시카가 요시아키
    LORD_MORI,      // [3-1- 8]모리 모토나리
    LORD_CHOSOKABE, // [3-1- 9]조소카베 모토치카
    LORD_SIMAZU,    // [3-1-10]시마즈 요시히사
    LORD_MAX        // [3-1-11]종류의 개수
};

// [3-2]성의 종류를 정의한다
enum
{
    CASTLE_YONEZAWA,        // [3-2- 1]요네자와성
    CASTLE_KASUGAYAMA,      // [3-2- 2]가스가야마성
    CASTLE_TSUTSUJIGASAKI,  // [3-2- 3]쓰쓰지가사키관
    CASTLE_ODAWARA,         // [3-2- 4]오다와라성
    CASTLE_OKAZAKI,         // [3-2- 5]오카자키성
    CASTLE_GIFU,            // [3-2- 6]기후성
    CASTLE_NIJO,            // [3-2- 7]니조성
    CASTLE_YOSHIDAKORIYAMA, // [3-2- 8]요시다고리야마성
    CASTLE_OKO,             // [3-2- 9]오코성
    CASTLE_UCHI,            // [3-2-10]우찌성
    CASTLE_MAX              // [3-2-11]종류의 개수
};

// [4]구조체를 선언하는 곳

// [4-1]다이묘 구조체를 선언한다
typedef struct {
    char familyName[16];    // [4-1-1]성
    char firstName[16];     // [4-1-2]이름
} LORD;

// [4-2]성 구조체를 선언한다
typedef struct {
    const char* name;               // [4-2-1]이름
    int                 owner;              // [4-2-2]성주
    int                 troopCount;         // [4-2-3]병력 수
    std::vector<int>    connectedCastles;   // [4-2-4]연결된 성 리스트
} CASTLE;

// [5]변수를 선언하는 곳

// [5-1]다이묘 배열을 선언한다
LORD lords[LORD_MAX] =
{
    {"다테",    "테루무네"},    // [5-1- 1]LORD_DATE        다테 테루무네
    {"우에스기",    "겐신"},    // [5-1- 2]LORD_UESUGI      우에스기 겐신
    {"다케다",      "신겐"},    // [5-1- 3]LORD_TAKEDA      다케다 신겐
    {"호조",    "우지마사"},    // [5-1- 4]LORD_HOJO        호조 우지마사
    {"도쿠가와","이에야스"},    // [5-1- 5]LORD_TOKUGAWA    도쿠가와 이에야스
    {"오다",    "노부나가"},    // [5-1- 6]LORD_ODA         오다 노부나가
    {"아시카가","요시아키"},    // [5-1- 7]LORD_ASHIKAGA    아시카가 요시아키
    {"모리",    "모토나리"},    // [5-1- 8]LORD_MORI        모리 모토나리
    {"조소카베","모토치카"},    // [5-1- 9]LORD_CHOSOKABE   조소카베 모토치카
    {"시마즈",  "요시히사"}     // [5-1-10]LORD_SIMAZU      시마즈 요시히사
};

// [5-2]성 배열을 선언한다
CASTLE castles[CASTLE_MAX] =
{
    // [5-2-1]CASTLE_YONEZAWA   요네자와성
    {
        "요네자와성",   // const char* name         이름
        LORD_DATE,  // int owner                성주
        TROOP_BASE, // int troopCount           병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_KASUGAYAMA,  // 가스가야마성
            CASTLE_ODAWARA      // 오다와라성
        }
    },

    // [5-2-2]CASTLE_KASUGAYAMA 가스가야마성
    {
        "가스가야마성",     // const char* name     이름
        LORD_UESUGI,    // int owner            성주
        TROOP_BASE,     // int troopCount       병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_YONEZAWA,        // 요네자와성
            CASTLE_TSUTSUJIGASAKI,  // 쓰쓰지가사키관
            CASTLE_GIFU             // 기후성
        }
    },

    // [5-2-3]CASTLE_TSUTSUJIGASAKI 쓰쓰지가사키관
    {
        "쓰쓰지가사키관",   // const char* name     이름
        LORD_TAKEDA,    // int owner            성주
        TROOP_BASE,     // int troopCount       병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_KASUGAYAMA,  // 가스가야마성
            CASTLE_ODAWARA,     // 오다와라성
            CASTLE_OKAZAKI      // 오카자키성
        }
    },

    // [5-2-4]CASTLE_ODAWARA    오다와라성
    {
        "오다와라성", // const char* name         이름
        LORD_HOJO,  // int owner                성주
        TROOP_BASE, // int troopCount           병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_YONEZAWA,        // 요네자와성
            CASTLE_TSUTSUJIGASAKI,  // 쓰쓰지가사키관
            CASTLE_OKAZAKI          // 오카자키성
        }
    },

    // [5-2-5]CASTLE_OKAZAKI    오카자키성
    {
        "오카자키성",       // const char* name     이름
        LORD_TOKUGAWA,  // int owner            성주
        TROOP_BASE,     // int troopCount       병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_TSUTSUJIGASAKI,  // 쓰쓰지가사키관
            CASTLE_ODAWARA,         // 오다와라성
            CASTLE_GIFU             // 기후성
        }
    },

    // [5-2-6]CASTLE_GIFU   기후성
    {
        "기후성",   // const char* name         이름
        LORD_ODA,   // int owner                성주
        TROOP_BASE, // int troopCount           병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_KASUGAYAMA,  // 가스가야마성
            CASTLE_OKAZAKI,     // 오카자키성
            CASTLE_NIJO         // 니조성
        }
    },

    // [5-2-7]CASTLE_NIJO   니조성
    {
        "니조성",       // const char* name     이름
        LORD_ASHIKAGA,  // int owner            성주
        TROOP_BASE,     // int troopCount       병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_GIFU,            // 기후성
            CASTLE_YOSHIDAKORIYAMA, // 요시다고리야마성
            CASTLE_OKO              // 오코성
        }
    },

    // [5-2-8]CASTLE_YOSHIDAKORIYAMA    요시다고리야마성
    {
        "요시다고리야마성",   // const char* name     이름
        LORD_MORI,      // int owner            성주
        TROOP_BASE,     // int troopCount       병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_NIJO,    // 니조성
            CASTLE_OKO,     // 오코성
            CASTLE_UCHI     // 우찌성
        }
    },

    // [5-2-9]CASTLE_OKO    오코성
    {
        "오코성",       // const char* name     이름
        LORD_CHOSOKABE, // int owner            성주
        TROOP_BASE,     // int troopCount       병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_NIJO,            // 니조성
            CASTLE_YOSHIDAKORIYAMA, // 요시다고리야마성
            CASTLE_UCHI             // 우찌성
        }
    },

    // [5-2-10]CASTLE_UCHI  우찌성
    {
        "우찌성",         // const char* name     이름
        LORD_SIMAZU,    // int owner            성주
        TROOP_BASE,     // int troopCount       병력 수

        // std::vector<int> connectedCastles    연결된 성 리스트
        {
            CASTLE_YOSHIDAKORIYAMA, // 요시다고리야마성
            CASTLE_OKO              // 오코성
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
            "1570년　～～～～～～～～～～～～～～～～　　　　　　～\n"      // 01
            "　　　　　～～～～～～～～～～～～～～～～　0요네5　～\n"      // 02
            "～～～～～～～～～～～～～～～～～～1가스5　다테　～～\n"      // 03
            "～～～～～～～～～～～～～～～　～～우에　　　　　～～\n"      // 04
            "～～～～～～～～～～～～～～～　～　　　　　　　　～～\n"      // 05
            "～～～～～～～～～～～～～～　　　　　2쓰쓰5　　　～～\n"      // 06
            "～～～～～～～～～～～～～　　　　　　다케　　　～～～\n"      // 07
            "～～～～～～　　　　　　　5기후5　　　　　　　　～～～\n"      // 08
            "～～～～　7요시5　6니조5　오다　4오카5　3오다5　～～～\n"      // 09
            "～～～　　모리　　아시　　　　　토쿠　　호조～～～～～\n"      // 10
            "～～　～～～～～～～　　　～～～～～～～～～～～～～～\n"      // 11
            "～　　　～　8오코5～～　～～～～～～～～～～～～～～～\n"      // 12
            "～　　　～～조소～～～～～～～～～～～～～～～～～～～\n"      // 13
            "～9우찌5～～～～～～～～～～～～～～～～～～～～～～～\n"      // 14
            "～시마～～～～～～～～～～～～～～～～～～～～～～～～\n"      // 15
            "～～～～～～～～～～～～～～～～～～～～～～～～～～～\n");    // 16
    */
    // [6-2-2]지도의 1번째 행을 그린다
    printf("%d년　　～～～～～～～～～～～～～～～～　　　　　～\n",
        year);  // 년

    // [6-2-3]지도의 2번째 행을 그린다
    printf("　　　　　～～～～～～～～～～～～～～～～　%d%.4s%d　～\n",

        // 요네자와성의 성 번호
        CASTLE_YONEZAWA,

        // 요네자와성의 이름
        castles[CASTLE_YONEZAWA].name,

        // 요네자와성의 병력 수
        castles[CASTLE_YONEZAWA].troopCount);

    // [6-2-4]지도의 3번째 행을 그린다
    printf("～～～～～～～～～～～～～～～～～～%d%.4s%d　%.4s　～～\n",

        // 가스가야마성의 성 번호
        CASTLE_KASUGAYAMA,

        // 가스가야마성의 이름
        castles[CASTLE_KASUGAYAMA].name,

        // 가스가야마성의 병력 수
        castles[CASTLE_KASUGAYAMA].troopCount,

        // 요네자와성의 성씨
        lords[castles[CASTLE_YONEZAWA].owner].familyName);

    // [6-2-5]지도의 4번째 행을 그린다
    printf("～～～～～～～～～～～～～～～　～～%.4s　　　　　～～\n",

        // 가스가야마성의 성씨
        lords[castles[CASTLE_KASUGAYAMA].owner].familyName);

    // [6-2-6]지도의 5번째 행을 그린다
    printf("～～～～～～～～～～～～～～～　～　　　　　　　　～～\n");

    // [6-2-7]지도의 6번째 행을 그린다
    printf("～～～～～～～～～～～～～～　　　　　%d%.4s%d　　　～～\n",

        // 쓰쓰지가사키관의 성 번호
        CASTLE_TSUTSUJIGASAKI,

        // 쓰쓰지가사키관의 이름
        castles[CASTLE_TSUTSUJIGASAKI].name,

        // 쓰쓰지가사키관의 병력 수
        castles[CASTLE_TSUTSUJIGASAKI].troopCount);

    // [6-2-8]지도의 7번째 행을 그린다
    printf("～～～～～～～～～～～～～　　　　　　%.4s　　　～～～\n",

        // 쓰쓰지가사키관의 성주의 성씨
        lords[castles[CASTLE_TSUTSUJIGASAKI].owner].familyName);

    // [6-2-9]지도의 8번째 행을 그린다
    printf("～～～～～～　　　　　　　%d%.4s%d　　　　　　　　～～～\n",

        // 기후성의 성 번호
        CASTLE_GIFU,

        // 기후성의 이름
        castles[CASTLE_GIFU].name,

        // 기후성의 병력 수
        castles[CASTLE_GIFU].troopCount);

    // [6-2-10]지도의 9번째 행을 그린다
    printf("～～～～　%d%.4s%d　%d%.4s%d　%.4s　　　　　%d%.4s%d　～～～\n",

        // 요시다고리야마성의 성 번호
        CASTLE_YOSHIDAKORIYAMA,

        // 요시다고리야마성의 이름
        castles[CASTLE_YOSHIDAKORIYAMA].name,

        // 요시다고리야마성의 병력 수
        castles[CASTLE_YOSHIDAKORIYAMA].troopCount,

        // 니조성의 성 번호
        CASTLE_NIJO,

        // 니조성의 이름
        castles[CASTLE_NIJO].name,

        // 니조성의 병력 수
        castles[CASTLE_NIJO].troopCount,

        // 기후성 성주의 성
        lords[castles[CASTLE_GIFU].owner].familyName,

        // 오다와라성의 성 번호
        CASTLE_ODAWARA,

        // 오다와라성의 이름
        castles[CASTLE_ODAWARA].name,

        // 오다와라성의 병력 수
        castles[CASTLE_ODAWARA].troopCount);

    // [6-2-11]지도의 10번째 행을 그린다
    printf("～～～　　%.4s　　%.4s　～　　　%d%.4s%d　%.4s～～～～～\n",

        // 요시다고리야마성의 성주의 성씨
        lords[castles[CASTLE_YOSHIDAKORIYAMA].owner].familyName,

        // 니조성 성주의 성씨
        lords[castles[CASTLE_NIJO].owner].familyName,

        // 오카자키성의 성 번호
        CASTLE_OKAZAKI,

        // 오카자키성의 이름
        castles[CASTLE_OKAZAKI].name,

        // 오카자키성의 병력 수
        castles[CASTLE_OKAZAKI].troopCount,

        // 오다와라성 성주의 성씨
        lords[castles[CASTLE_ODAWARA].owner].familyName);

    // [6-2-12]지도의 11번째 행을 그린다
    printf("～～　～～～～～～～　　　　～～%.4s～　～　～～～～～\n",

        // 오카자키성 성주의 성씨
        lords[castles[CASTLE_OKAZAKI].owner].familyName);

    // [6-2-13]지도의 12번째 행을 그린다
    printf("～　　　～　%d%.4s%d　～　　　　～～～～～～～～～～～～\n",

        // 오코성의 성 번호
        CASTLE_OKO,

        // 오코성의 이름
        castles[CASTLE_OKO].name,

        // 오코성의 병력 수
        castles[CASTLE_OKO].troopCount);

    // [6-2-14]지도의 13번째 행을 그린다
    printf("～　　　～　%.4s　～～　　～～～～～～～～～～～～～～\n",

        // 오코성 성주의 성씨
        lords[castles[CASTLE_OKO].owner].familyName);

    // [6-2-15]지도의 14번째 행을 그린다
    printf("～%d%.4s%d～～～～～～～～～～～～～～～～～～～～～～～\n",

        // 우찌성의 성 번호
        CASTLE_UCHI,

        // 우찌성의 이름
        castles[CASTLE_UCHI].name,

        // 우찌성의 병력 수
        castles[CASTLE_UCHI].troopCount);

    // [6-2-16]지도의 15번째 행을 그린다
    printf("～%.4s～～～～～～～～～～～～～～～～～～～～～～～～\n",

        // 우찌성 성주의 성씨
        lords[castles[CASTLE_UCHI].owner].familyName);

    // [6-2-17]지도의 16번째 행을 그린다
    printf("～～～～～～～～～～～～～～～～～～～～～～～～～～～\n");

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
    printf("주군님, 우리 성은\n"
        "이 지도의 어디에 있습니까？！（0～%d）\n",
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
    printf("～%s 전투～\n", castles[_castle].name);

    printf("\n");// [6-4-3]1행 비운다

    // [6-4-4]공격당한 다이묘를 선언한다
    int defensiveLord = castles[_castle].owner;

    // [6-4-5]무한 루프한다
    while (1)
    {
        // [6-4-6]전투의 경과를 표시한다
        printf("%s군(%4d명)　Ｘ　%s군(%4d명)\n",

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
        printf("%s은(는)　%s 가문의 것이 됩니다\n",
            castles[_castle].name,
            lords[_offensiveLord].familyName);

        printf("\n");// [6-4-21]1행 비운다

        // [6-4-22]수비 측의 다이묘가 성을 모두 잃었는지 여부를 판정한다
        if (GetCastleCount(defensiveLord) <= 0)
        {
            char str[128];  // [6-4-23]추가하는 문자열을 선언한다

            // [6-4-24]추가하는 문자열을 작성한다
            sprintf_s(str, "%d년　%s%s이(가)　%s에서　%s%s을(를)　멸망시키다\n",
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
                printf("%s님, 어디로 진군하시겠습니까?\n",
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
                        isConnected = true;// [6-5-30]연결의 유무 플래그를 true로 설정한다

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
                printf("%s에 몇 명 진군하시겠습니까?（0～%d）\n",
                    castles[targetCastle].name,	// 진군 목적지 성의 이름
                    troopMax);					// 진군 병력 수

                // [6-5-41]진군 병력 수를 선언한다
                int troopCount;

                // [6-5-42]범위 내의 병력 수가 입력될 때까지 반복한다
                do {
                    troopCount = _getch() - '0';// [6-5-43]진군 병력 수를 입력한다
                } while ((troopCount < 0) || (troopCount > troopMax));

                // [6-5-44]현재 성의 병력 수를 이동하는 만큼 뺀다
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
                    : "으로 출진이다~！！");  // 적의 성이면

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

                        // 그리고 그중에서 가장 병력 수가 적은 성보다도 병력 수가 많은 성이 있으면
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
                        printf("%s의　%s%s이(가)　%s에　공격해 들어갔습니다！\n",
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

                    // [6-5-83]병력을 보내는 목적지의 성이 전선이 아닌 아군의 성이면
                    else
                    {
                        // [6-5-84]보내는 목적지의 빈 병력 수와 보내는 곳의 병력 수 중, 적은 병력 수를 설정한다
                        sendTroopCount = std::min(

                            // 보내는 목적지의 빈 병력 수
                            sendTroopCount,

                            // 보내는 곳의 병력 수
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
                        printf("%s에서　%s로　%d명 이동했습니다\n",
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
                printf("%d년　%s%s이(가)　정이대장군에 임명된다\n"
                    "%d년　%s%s이(가)　%s막부를 연다\n"
                    "\n"
                    "ＴＨＥ　ＥＮＤ",
                    year + 3,                       // 정이대장군이 된 연도
                    lords[playerLord].familyName,   // 플레이어의 다이묘 성씨
                    lords[playerLord].firstName,    // 플레이어의 다이묘 이름
                    year + 3,                       // 막부를 연 연도
                    lords[playerLord].familyName,   // 플레이어의 다이묘 성씨
                    lords[playerLord].firstName,    // 플레이어의 다이묘 이름
                    lords[playerLord].familyName);  // 막부 이름

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

        // [6-5-109]「혼노지의 변」이벤트가 발생하는 조건을 마족하고 있는지 여부를 판정한다
        if (
            // 1582년이다
            (year == 1582)

            // 그리고 오다 가문이 니조성을 소유하고 있다
            && (castles[CASTLE_NIJO].owner == LORD_ODA))
        {
            // [6-5-110]오다 가문 다이묘의 성을「하시바」로 변경한다
            strcpy_s(lords[LORD_ODA].familyName, "하시바");

            // [6-5-111]오다 가문 다이묘의 이름을「히데요시」로 변경한다
            strcpy_s(lords[LORD_ODA].firstName, "히데요시");

            DrawScreen();// [6-5-112]화면을 다시 그린다

            // [6-5-113]「혼노지의 변」이벤트의 메시지를 표시한다
            printf(
                "아케치 미쓰히데 「적은 혼노지에 있다！\n"
                "\n"
                "아케치 미쓰히데가 혼노지의 오다노부나가를 습격했다！\n"
                "\n"
                "오다 노부나가「할 수 없이…\n"
                "\n"
                "오다 노부나가는 혼노지에서 자결했다！\n"
                "\n"
                "후일, 하시바 히데요시가 야마자키 전투에서 아케치 미쓰히데를 물리치고, \n"
                "오다 가문 후계의 영토를 찬탈했다！\n");

            _getch();// [6-5-114]키보드 입력을 기다린다
        }
    }
}