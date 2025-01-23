// [1]헤더를 인클루드하는 곳

#include <stdio.h>  // [1-1]표준 입출력 헤더를 인클루드한다
#include <stdlib.h> // [1-2]표준 라이브러리 헤더를 인클루드한다
#include <string.h>	// [1-3]문자열 조작 헤더를 인클루드한다
#include <time.h>   // [1-4]시간 관리 헤더를 인클루한다
#include <conio.h>  // [1-5]콘솔 입출력 헤더를 인클루드한다

// [2]상수를 정의하는 곳

#define SPELL_COST  (3) // [2-1]주문의 소비 MP를 정의한다 
#define MAP_WIDTH       (16)    // [2-2]맵의 너비를 정의한다
#define MAP_HEIGHT      (16)    // [2-3]맵의 높이를 정의한다

#define SCREEN_WIDTH    (16)    // [2-4]스크롤 화면의 너비를 정의한다
#define SCREEN_HEIGHT   (12)    // [2-5]스크롤 화면의 높이를 정의한다

// [3]열거 상수를 정의하는 곳

// [3-1]몬스터의 종류를 정의한다
enum
{
    MONSTER_PLAYER, // [3-1-1]플레이어
    MONSTER_SLIME,  // [3-1-2]슬라임
    MONSTER_BOSS,   // [3-1-3]마왕
    MONSTER_MAX     // [3-1-4]몬스터 종류의 수
};

// [3-2]캐릭터의 종류를 정의한다
enum
{
    CHARACTER_PLAYER,   // [3-2-1]플레이어
    CHARACTER_MONSTER,  // [3-2-2]몬스터
    CHARACTER_MAX       // [3-2-3]캐릭터 종류의 수
};

// [3-3]명령의 종류를 정의한다
enum
{
    COMMAND_FIGHT,  // [3-3-1]싸운다
    COMMAND_SPELL,  // [3-3-2]주문
    COMMAND_RUN,    // [3-3-3]도망친다
    COMMAND_MAX     // [3-3-4]명령의 종류 수
};

// [3-4]맵의 종류를 정의한다
enum {
    MAP_FIELD,          // [3-4-1]필드
    MAP_KING_CASTLE,    // [3-4-2]왕의 성
    MAP_BOSS_CASTLE,    // [3-4-3]마왕의 성
    MAP_MAX           // [3-4-4]맵 종류의 개수
};


// [4]구조체를 선언하는 곳

// [4-1]캐릭터의 구조체를 선언한다
typedef struct {
    int hp;                 // [4-1-1]HP
    int maxHp;              // [4-1-2]최대 HP
    int mp;                 // [4-1-3]MP
    int maxMp;              // [4-1-4]최대 MP
    int attack;             // [4-1-5]공격력
    char name[4 * 3 + 1];   // [4-1-6]이름
    char aa[256];           // [4-1-7]아스키아트
    int command;            // [4-1-8]명령어
    int target;             // [4-1-9]공격 대상
}CHARACTER;

// [5]변수를 선언하는 곳

// [5-1]몬스터 상태의 배열을 선언한다
CHARACTER monsters[MONSTER_MAX] =
{
    // [5-1-1]MONSTER_PLAYER    플레이어
    {
        100,        // [5-1-2]int hp                HP
        100,        // [5-1-3]int maxHp             최대 HP
        15,         // [5-1-4]int mp                MP
        15,         // [5-1-5]int maxMp             최대 MP
        30,         // [5-1-6]int attack            공격력
        "용사",     // [5-1-7]char name[4 * 3 + 1]  이름
    },

    // [5-1-8]MONSTER_SLIME 슬라임
    {
        3,          // [5-1-9]int hp                HP
        3,          // [5-1-10]int maxHp            최대 HP
        0,          // [5-1-11]int mp               MP
        0,          // [5-1-12]int maxMp            최대 MP
        2,          // [5-1-13]int attack           공격력
        "슬라임",   // [5-1-14]char name[4 * 3 + 1] 이름

        // [5-1-15]char aa[256] 아스키아트
        "／・Д・＼\n"
        "～～～～～"
    },

    // [5-1-16]MONSTER_BOSS 마왕
    {
        255,        // [5-1-17]int hp               HP
        255,        // [5-1-18]int maxHp            최대 HP
        0,          // [5-1-19]int mp               MP
        0,          // [5-1-20]int maxMp            최대 MP
        50,         // [5-1-21]int attack           공격력
        "마왕",     // [5-1-22]char name[4 * 3 + 1] 이름

        // [5-1-23]char aa[256] 아스키아트
         "　　Ａ＠Ａ\n"
        "ψ（▼皿▼）ψ"
    }
};

// [5-2]캐릭터의 배열을 선언한다
CHARACTER characters[CHARACTER_MAX];

// [5-3]명령의 이름을 선언한다
char commandNames[COMMAND_MAX][4 * 3 + 1] = {
    "싸운다", // [5-3-1]COMMAND_FIGHT 싸운다
    "주문", // [5-3-2]COMMAND_SPELL 주문
    "도망친다"    // [5-3-3]COMMAND_RUN   도망친다
};

// [5-4]맵의 지형 데이터를 선언한다
char map[MAP_MAX][MAP_HEIGHT][MAP_WIDTH + 1] =
{
    // [5-4-1]MAP_FIELD 필드
    {
        "~~~~~~~~~~~~~~~~",
        "~~MMMMM~~MMMM.~~",
        "~M...M.##..M...~",
        "~M.M.M.~~M.M.M.~",
        "~M.M...~~M...M.~",
        "~M.MMMM~~MMMM..~",
        "~M..MM.~~~~~~#~~",
        "~~M.M.~~~~~~~#~~",
        "~~M.MM~~~~BMM..~",
        "~~...MM~~M.MMM.~",
        "~...~~M~~M...M.~",
        "~..~~~K~~MMM.M.~",
        "~..~~~.~~M...M.~",
        "~......~~M.MM..~",
        "~~....~~~~....~~",
        "~~~~~~~~~~~~~~~~"
    },

        // [5-4-2]MAP_KING_CASTLE   왕의 성
    {
        "HHH.......HHH",
        "H.H.......H.H",
        "HHHHHHHHHHHHH",
        ".H.........H.",
        ".H.HHH.HHH.H.",
        ".H.H0H.H1H.H.",
        ".H.........H.",
        ".HW.......WH.",
        ".HY.......YH.",
        "HHHHHH.HHHHHH",
        "H.H~~~#~~~H.H",
        "HHH~~~#~~~HHH",
        ".............."
    },

    // [5-4-3]MAP_BOSS_CASTLE   마왕의 성
    {
        "HHH.......HHH",
        "H.H.......H.H",
        "HHHHHHHHHHHHH",
        ".H....H....H.",
        ".H..WHHHW..H.",
        ".H..YH2HY..H.",
        ".H.........H.",
        ".H..W...W..H.",
        ".H..Y...Y..H.",
        ".H.........H.",
        "HHHHHH.HHHHHH",
        "H.H~~~#~~~H.H",
        "HHH~~~#~~~HHH",
        "~~~~~~#~~~~~~",
        "~~~~~~#~~~~~~",
        "............."
    }
};

int currentMap; // [5-5]현재 맵을 선언한다
int playerX = 6;    // [5-6]플레이어의 X좌표
int playerY = 12;   // [5-7]플레이어의 Y좌표

// [6]함수를 선언하는 곳

// [6-1]게임을 초기화하는 함수를 선언한다
void Init()
{
    // [6-1-1]플레이어의 상태를 초기화한다
    characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];

    // [6-1-2]현재 맵을 초기화한다
    currentMap = MAP_KING_CASTLE;

    playerX = 4;    // [6-1-3]플레이어의 X좌표를 초기화한다
    playerY = 6;    // [6-1-4]플레이어의 Y좌표를 초기화한다
}

// [6-2]전투 장면의 화면을 그리는 함수를 선언한다
void DrawBattleScreen()
{
    // [6-2-1]화면을 클리어한다
    system("cls");

    // [6-2-2]플레이어의 이름을 표시한다
    printf("%s\n", characters[CHARACTER_PLAYER].name);

    // [6-2-3]플레이어의 상태를 표시한다
    printf("HP: %d/%d　MP: %d/%d\n",
        characters[CHARACTER_PLAYER].hp,
        characters[CHARACTER_PLAYER].maxHp,
        characters[CHARACTER_PLAYER].mp,
        characters[CHARACTER_PLAYER].maxMp);

    // [6-2-4]1행 비운다
    printf("\n");

    // [6-2-5]몬스터의 아스키아트를 그린다
    printf("%s", characters[CHARACTER_MONSTER].aa);

    // [6-2-6]몬스터의 HP를 표시한다
    printf("(HP: %d/%d)\n",
        characters[CHARACTER_MONSTER].hp,
        characters[CHARACTER_MONSTER].maxHp);

    // [6-2-7]1행 비운다
    printf("\n");
}

// [6-3]명령을 선택하는 함수를 선언한다
void SelectCommand()
{
    // [6-3-1]플레이어의 명령을 초기화한다
    characters[CHARACTER_PLAYER].command = COMMAND_FIGHT;

    // [6-3-2]명령이 결정될 때까지 루프한다
    while (1)
    {
        // [6-3-3]전투 화면을 그리는 함수를 호출한다 
        DrawBattleScreen();

        // [6-3-4]명령 목록을 표시한다
        for (int i = 0; i < COMMAND_MAX; i++)
        {
            // [6-3-5]선택 중인 명령이라면 
            if (i == characters[CHARACTER_PLAYER].command)
            {
                // [6-3-6]커서를 그린다
                printf("＞");
            }
            // [6-3-7]선택 중인 명령이 아니면
            else
            {
                // [6-3-8]전각 공백을 넣는다
                printf("　");
            }

            // [6-3-9]명령의 이름을 표시한다
            printf("%s\n", commandNames[i]);
        }

        // [6-3-10]입력된 키에 따라 분기한다
        switch (_getch())
        {
        case 'w':   // [6-3-11]w키를 누르면

            // [6-3-12]위의 명령으로 바꾼다
            characters[CHARACTER_PLAYER].command--;

            break;

        case 's':   // [6-3-13]s키를 누르면

            // [6-3-14]아래의 명령으로 바꾼다
            characters[CHARACTER_PLAYER].command++;

            break;

        default:    // [6-3-15]상기 이외의 키를 누르면
            return; // [6-3-16]함수를 빠져나간다
        }

        // [6-3-17]커서를 상하로 루프시킨다
        characters[CHARACTER_PLAYER].command =
            (COMMAND_MAX + characters[CHARACTER_PLAYER].command) % COMMAND_MAX;
    }
}

// [6-4]전투 장면의 함수를 선언한다
void Battle(int _monster)
{
    // [6-4-1]몬스터의 상태를 초기화한다
    characters[CHARACTER_MONSTER] = monsters[_monster];

    // [6-4-2]플레이어의 공격 대상을 몬스터로 설정한다
    characters[CHARACTER_PLAYER].target = CHARACTER_MONSTER;

    // [6-4-3]몬스터의 공격 대상을 플레이어로 설정한다
    characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

    // [6-4-4]전투 장면의 화면을 그리는 함수를 호출한다
    DrawBattleScreen();

    // [6-4-5]전투 장면의 첫 메시지를 표시한다
    printf("%s이(가) 나타났다!\n", characters[CHARACTER_MONSTER].name);

    // [6-4-6]키보드 입력을 기다린다
    _getch();

    // [6-4-7]전투가 끝날 때까지 루프한다
    while (1)
    {
        // [6-4-8]명령을 선택하는 함수를 호출한다
        SelectCommand();

        // [6-4-9]각 캐릭터를 반복한다
        for (int i = 0; i < CHARACTER_MAX; i++)
        {
            // [6-4-10]전투 장면의 화면을 그리는 함수를 호출한다
            DrawBattleScreen();

            // [6-4-11]선택된 명령에 따라 분기한다
            switch (characters[i].command)
            {
            case COMMAND_FIGHT: // [6-4-12]싸운다
            {
                // [6-4-13]공격을 하는 메시지를 표시한다
                printf("%s의 공격!\n", characters[i].name);

                // [6-4-14]키보드 입력을 기다린다
                _getch();

                // [6-4-15]적에게 주는 대미지를 계산한다
                int damage = 1 + rand() % characters[i].attack;

                // [6-4-16]적에게 대미지를 준다
                characters[characters[i].target].hp -= damage;

                // [6-4-17]적의 HP가 음의 값이 되었는지를 판정한다
                if (characters[characters[i].target].hp < 0)
                {
                    // [6-4-18]적의 HP를 0으로 한다
                    characters[characters[i].target].hp = 0;
                }

                // [6-4-19]전투 장면의 화면을 다시 그리는 함수를 호출한다
                DrawBattleScreen();

                // [6-4-20]적에게 대미지를 준 메시지를 표시한다
                printf("%s에게 %d의 대미지!\n",
                    characters[characters[i].target].name,
                    damage);

                // [6-4-21]키보드 입력을 기다린다
                _getch();

                break;
            }
            case COMMAND_SPELL: // [6-4-22]주문

                // [6-4-23]MP가 충분한지 여부를 판정한다
                if (characters[i].mp < SPELL_COST)
                {
                    // [6-4-24]MP가 부족한 메시지를 표시한다
                    printf("MP가 부족하다!\n");

                    // [6-4-25]키보드 입력을 기다린다
                    _getch();

                    // [6-4-26]주문을 외우는 처리를 빠져나온다
                    break;
                }

                // [6-4-27]MP를 소비시킨다
                characters[i].mp -= SPELL_COST;

                // [6-4-28]화면을 다시 그린다
                DrawBattleScreen();

                // [6-4-29]주문을 외운 메시지를 표시한다
                printf("%s은(는) 주문을 외웠다!\n", characters[i].name);

                // [6-4-30]키보드 입력을 기다린다
                _getch();

                // [6-4-31]HP를 회복시킨다
                characters[i].hp = characters[i].maxHp;

                // [6-4-32]전투 장면의 화면을 다시 그린다
                DrawBattleScreen();

                // [6-4-33]HP가 회복된 메시지를 표시한다 
                printf("%s의 상처가 회복되었다!\n", characters[i].name);

                // [6-4-34]키보드 입력을 기다린다
                _getch();

                break;

            case COMMAND_RUN:   // [6-4-35]도망친다

                // [6-4-36]도망친 메시지를 표시한다
                printf("%s은(는) 도망쳤다!\n", characters[i].name);

                // [6-4-37]키보드 입력을 기다린다
                _getch();

                // [6-4-38]전투 처리를 빠져나간다
                return;

                break;
            }

            // [6-4-39]공격 대상을 쓰러뜨렸는지 여부를 판정한다
            if (characters[characters[i].target].hp <= 0)
            {
                // [6-4-40]공격 대상에 따라 처리를 분기시킨다
                switch (characters[i].target)
                {
                    // [6-4-41]플레이어라면
                case CHARACTER_PLAYER:

                    // [6-4-42]플레이어가 사망한 메시지를 표시한다
                    printf("당신은 사망했습니다.");

                    break;

                    // [6-4-43]몬스터라면
                case CHARACTER_MONSTER:

                    // [6-4-44]몬스터의 아스키아트를 아무것도 표시하지 않게 다시 작성한다
                    strcpy_s(characters[characters[i].target].aa, "\n");

                    // [6-4-45]전투 장면의 화면을 다시 그리는 함수를 호출한다
                    DrawBattleScreen();

                    // [6-4-46]몬스터를 쓰러뜨린 메시지를 표시한다
                    printf("%s을(를) 쓰러뜨렸다!\n", characters[characters[i].target].name);

                    break;
                }

                // [6-4-47]키보드 입력을 기다린다
                _getch();

                // [6-4-48]전투 장면의 함수를 빠져나간다
                return;
            }
        }
    }
}

// [6-5]맵을 그리는 처리를 기술하는 함수를 선언한다
void DrawMap()
{
    // [6-5-1]화면을 클리어한다
    system("cls");

    // [6-5-2]그리는 모든 행을 반복한다
    for (int y = playerY - SCREEN_HEIGHT / 2; y < playerY + SCREEN_HEIGHT / 2; y++)
    {
        // [6-5-3]그리는 모든 열을 반복한다
        for (int x = playerX - SCREEN_WIDTH / 2; x < playerX + SCREEN_WIDTH / 2; x++)
        {
            // [6-5-4]대상 좌표가 플레이어의 좌표와 같은지 여부를 판정한다
            if ((x == playerX) && (y == playerY))
            {
                // [6-5-5]플레이어의 아스키아트를 그린다
                printf("勇");
            }

            // [6-5-6]대상 좌표가 맵 데이터의 범위인지 여부를 판정한다
            else if ((x < 0) || (x >= MAP_WIDTH)    // X좌표가 맵의 범위 밖
                || (y < 0) || (y >= MAP_HEIGHT)     // Y좌표가 맵의 범위 밖
                || (map[currentMap][y][x] == '\0')) // 대상 칸이 설정되어 있지 않다
            {
                // [6-5-7]맵 종류에 따라 분기한다
                switch (currentMap)
                {
                case MAP_FIELD:         printf("～");   break;  // [6-5-8]필드 밖은 바다
                case MAP_KING_CASTLE:   printf("．");   break;  // [6-5-9]왕의 성 밖은 평지
                case MAP_BOSS_CASTLE:   printf("．");   break;  // [6-5-10]마왕의 성 밖은 평지
                }
            }

            // [6-5-11]상기의 상태가 아니면
            else
            {
                // [6-5-12]칸의 종류에 따라 분기한다
                switch (map[currentMap][y][x])
                {
                case '~': printf("〜"); break; // [6-5-13]바다
                case '.': printf("．"); break; // [6-5-14]평지
                case 'M': printf("Ｍ"); break; // [6-5-15]산
                case '#': printf("＃"); break; // [6-5-16]다리
                case 'K': printf("王"); break; // [6-5-17]왕의 성
                case 'B': printf("魔"); break; // [6-5-18]마왕의 성
                case 'H':   printf("□");   break;  // [6-5-19]벽
                case 'W':   printf("炎");   break;  // [6-5-20]불
                case 'Y':   printf("Ｙ");   break;  // [6-5-21]촛대
                case '0':   printf("王");   break;  // [6-5-22]왕
                case '1':   printf("姫");   break;  // [6-5-23]공주님
                case '2':   printf("魔");   break;  // [6-5-24]마왕
                }
            }
        }
        // [6-5-25]1행 그릴 때마다 줄바꿈한다
        printf("\n");
    }

    // [6-5-26]1행 비운다
    printf("\n");
    
    // [6-5-27]플레이어의 이름을 표시한다
    printf("%s\n", characters[CHARACTER_PLAYER].name);

    // [6-5-28]플레이어의 상태를 표시한다
    printf("ＨＰ：%d／%d ＭＰ：%d／%d\n",
        characters[CHARACTER_PLAYER].hp,
        characters[CHARACTER_PLAYER].maxHp,
        characters[CHARACTER_PLAYER].mp,
        characters[CHARACTER_PLAYER].maxMp);

    // [6-5-29]1행 비운다
    printf("\n");
}


// [6-6]프로그램의 실행 시작점을 선언한다
int main()
{
   system("chcp 65001 > nul");// [6-6-0]콘솔의 문자 세트를 UTF-8로 설정한다
    
   // [6-6-1]난수를 셔플한다
    srand((unsigned int)time(NULL));

    // [6-6-2]게임을 초기화하는 함수를 호출한다
    Init();

    // [6-6-3]메인 루프
    while (1)
    {
        // [6-6-4]맵을 그리는 함수를 호출한다
        DrawMap();
        int lastPlayerX = playerX;// [6-6-5]플레이어의 이동 전 X좌표를 선언한다
        int lastPlayerY = playerY;// [6-6-6]플레이어의 이동 전 Y좌표를 선언한다

        // [6-6-7]입력된 키로 분기한다
        switch (_getch())
        {
        case 'w':   playerY--;  break;  // [6-6-8]w키로 위쪽 이동
        case 's':   playerY++;  break;  // [6-6-9]s키로 아랫쪽 위동
        case 'a':   playerX--;  break;  // [6-6-10]a키로 왼쪽 이동
        case 'd':   playerX++;  break;  // [6-6-11]d키로 오른쪽 이동
        }

        // [6-6-12]맵의 밖으로 나갔는지 여부를 판정한다
        if ((playerX < 0) || (playerX >= MAP_WIDTH)         // X좌표가 맵의 범위 밖
            || (playerY < 0) || (playerY >= MAP_HEIGHT)     // Y좌표가 맵의 범위 밖
            || (map[currentMap][playerY][playerX] == '\0')) // 미설정 칸
        {
            // [6-6-13]현재 맵에 따라 분기한다
            switch (currentMap)
            {
            case MAP_KING_CASTLE:   // [6-6-14]왕의 성
                // [6-6-15]필드 맵으로 전환한다フィールドマップに切り替える
                currentMap = MAP_FIELD;

                playerX = 6;    // [6-6-16]플레이어의 X좌표를 설정한다
                playerY = 12;   // [6-6-17]플레이어의 Y좌표를 설정한다

                break;

            case MAP_BOSS_CASTLE:   // [6-6-18]마왕의 성

                // [6-6-19]필드 맵으로 전환한다
                currentMap = MAP_FIELD;

                playerX = 10;   // [6-6-20]플레이어의 X좌표를 설정한다
                playerY = 9;    // [6-6-21]플레이어의 Y좌표를 설정한다

                break;
            }
        }

        // [6-6-22]이동 목적지 칸의 종류에 따라 분기시킨다
        switch (map[currentMap][playerY][playerX])
        {
        case 'K':   // [6-6-23]왕의 성

            // [6-6-24]왕의 성으로 맵을 전환한다
            currentMap = MAP_KING_CASTLE;

            playerX = 6;    // [6-6-25]플레이어의 X좌표를 설정한다
            playerY = 12;   // [6-6-26]플레이어의 Y좌표를 설정한다

            break;

        case '0':   // [6-6-31]왕

            // [6-6-32]왕의 대화 메시지를 표시한다
            printf("＊ 오, 용사여!\n"
                "동쪽 마성의 마왕을\n"
                "물리치고 세상을 구해줘!\n"
            );

            _getch();// [6-6-33]키보드 입력 대기 상태로 한다

            break;

        case '1':   // [6-6-34]공주

            // [6-6-35]공주의 대화 메시지를 표시한다
            printf("＊신께 기도드립니다.\n"
                "오, 신이시여!\n"
                "용사님에게 축복을!\n"
            );

            // [6-6-36]키보드 입력 대기 상태로 한다
            _getch();

            // [6-6-37]플레이어의 HP를 회복시킨다
            characters[CHARACTER_PLAYER].hp = characters[CHARACTER_PLAYER].maxHp;

            // [6-6-38]플레이어의 MP를 회복시킨다
            characters[CHARACTER_PLAYER].mp = characters[CHARACTER_PLAYER].maxMp;

            break;

        case 'B':   // [6-6-27]마왕의 성

            // [6-6-28]마왕의 성으로 맵을 전환한다
            currentMap = MAP_BOSS_CASTLE;

            playerX = 6;    // [6-6-29]플레이어의 X좌표를 설정한다
            playerY = 15;   // [6-6-30]플레이어의 Y좌표를 설정한다

            break;

        case '2':   // [6-6-39]마왕

            // [6-6-40]마왕의 대화 메시지를 표시한다
            printf("＊어리석은 인간이여!\n"
                "나의 야망을 방해하는 자는\n"
                "이 세상에서 사라지게 될 것이다!\n"
            );

            // [6-6-41]키보드 입력 대기 상태로 한다
            _getch();

            // [6-6-42]마왕과의 전투를 발생시킨다
            Battle(MONSTER_BOSS);

            // [6-6-43]마왕이 죽었는지 여부를 판정한다
            if (characters[CHARACTER_MONSTER].hp <= 0)
            {
                // [6-6-44]화면을 클리어한다
                system("cls");

                // [6-6-45]엔딩 메시지를 표시한다
                printf("　　　마왕은 사라지고 세상은\n"
                    "　　멸망의 위기에서 구원되었다！\n"
                    "\n"
                    "　　왕은 포고령을 내리고 용사를\n"
                    "　　　찾아 헤맸지만, 본 사람은\n"
                    "　　아무도 없었다고 전해진다…\n"
                    "\n"
                    "\n"
                    "　　　　ＴＨＥ　ＥＮＤ");

                // [6-6-46]키보드 입력 대기 상태로 한다
                _getch();
                // [6-6-47]게임을 종료한다
                return 0;
            }
            break;
        }

        // [6-6-48]이동 목적지 칸의 종류에 따라 분기시킨다
        switch (map[currentMap][playerY][playerX])
        {
        case '.':   // [6-6-49]평지
        case '#':   // [6-6-50]다리
            
            // [6-6-51]적과 조우했는지 여부를 판정한다
            if ((currentMap == MAP_FIELD) && (rand() % 16 == 0))
            {
                // [6-6-52]잡어 몬스터와의 전투를 발생시킨다
                Battle(MONSTER_SLIME);
            }

            break;

        default:    // [6-6-53]상기 이외의 칸
            playerX = lastPlayerX;// [6-6-54]플레이어의 X좌표를 이동 전으로 되돌린다
            playerY = lastPlayerY;// [6-6-55]플레이어의 Y좌표를 이동 전으로 되돌린다
            break;
        }

        // [6-6-56]플레이어가 사망했는지 여부를 판정한다
        if (characters[CHARACTER_PLAYER].hp <= 0)
        {
            // [6-6-57]게임을 초기화하는 함수를 호출한다
            Init();

            // [6-6-58]화면을 다시 그린다
            DrawMap();

            // [6-6-59]왕의 메시지를 표시한다
            printf("＊ 오, 용사여!\n"
                "신이 그대를 구원하셨다!\n"
                "용사에게 영광을!\n");

            // [6-6-60]키보드 입력 대기 상태로 한다
            _getch();
        }
    }
}