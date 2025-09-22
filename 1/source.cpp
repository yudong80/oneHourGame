// [1]헤더를 인클루드하는 곳

#include <stdio.h>  // [1-1]표준 입출력 헤더를 인클루드한다
#include <stdlib.h> // [1-2]표준 라이브러리 헤더를 인클루드한다
#include <string.h>	// [1-3]문자열 조작 헤더를 인클루드한다
#include <time.h>   // [1-4]시간 관리 헤더를 인클루한다
#include <termios.h> // [1-5]터미널 I/O 헤더를 인클루드한다
#include <unistd.h>  // [1-6]유닉스 표준 헤더를 인클루드한다

// [2]상수를 정의하는 곳

#define SPELL_COST  (3) // [2-1]주문의 소비 MP를 정의한다 

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
    int command;            // [4-1-8]명령
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

// [6-1]게임을 초기화하는 함수를 선언한다
void Init()
{
    // [6-1-1]플레이어의 상태를 초기화한다
    characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];
}

// [6-2]전투 장면의 화면을 그리는 함수를 선언한다
void DrawBattleScreen()
{
    // [6-2-1]화면을 클리어한다
    system("clear");

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
        switch (getch())
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
    getch();

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
                getch();

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
                getch();

                break;
            }
            case COMMAND_SPELL: // [6-4-22]주문

                // [6-4-23]MP가 충분한지 여부를 판정한다
                if (characters[i].mp < SPELL_COST)
                {
                    // [6-4-24]MP가 부족한 메시지를 표시한다
                    printf("MP가 부족하다!\n");

                    // [6-4-25]키보드 입력을 기다린다
                    getch();

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
                getch();

                // [6-4-31]HP를 회복시킨다
                characters[i].hp = characters[i].maxHp;

                // [6-4-32]전투 장면의 화면을 다시 그린다
                DrawBattleScreen();

                // [6-4-33]HP가 회복된 메시지를 표시한다 
                printf("%s의 상처가 회복되었다!\n", characters[i].name);

                // [6-4-34]키보드 입력을 기다린다
                getch();

                break;

            case COMMAND_RUN:   // [6-4-35]도망친다

                // [6-4-36]도망친 메시지를 표시한다
                printf("%s은(는) 도망쳤다!\n", characters[i].name);

                // [6-4-37]키보드 입력을 기다린다
                getch();

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
                    strcpy(characters[characters[i].target].aa, "\n");

                    // [6-4-45]전투 장면의 화면을 다시 그리는 함수를 호출한다
                    DrawBattleScreen();

                    // [6-4-46]몬스터를 쓰러뜨린 메시지를 표시한다
                    printf("%s을(를) 쓰러뜨렸다!\n", characters[characters[i].target].name);

                    break;
                }

                // [6-4-47]키보드 입력을 기다린다
                getch();

                // [6-4-48]전투 장면의 함수를 빠져나간다
                return;
            }
        }
    }
}

// [6-6]프로그램의 실행 시작점을 선언한다
int main()
{
   // [6-6-0]리눅스에서는 기본적으로 UTF-8을 사용한다
    
   // [6-6-1]난수를 섞는다
    srand((unsigned int)time(NULL));

    // [6-6-2]게임을 초기화하는 함수를 호출한다
    Init();

    // [6-6-3]전투 장면의 함수를 호출한다
    Battle(MONSTER_BOSS);
}