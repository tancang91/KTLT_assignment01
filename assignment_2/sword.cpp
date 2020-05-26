#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif


/********* Begin My Implementation ***********/
#define MIN(a,b) ((a)<(b)) ? (a) : (b)
#define MAX(a,b) ((a)>(b)) ? (a) : (b)

// {{{ Data structure
enum Event
{
    // Trivia fighting opponent
    MADBEAR = 1, MOONBRINGER = 2, ELF = 3, SAXON = 4, TROLL = 5, TORNBERRY = 6, QUEENCARDS = 7,
    // Helping event
    NINA = 8, DURIAN = 9, ANTIDOTE = 10, ODIN = 11, MERLIN = 12,
    // Non-trivia fighting opponent
    OMEGAWEAPON = 13, HADES = 14,
    // Special Event
    SCARLET = 15, LOCKEDDOOR = 16,
    // Weapon to defeat ULTIMECIA
    W_PALADIN = 95, W_LANCELOT = 96, W_GUINEVERE = 97, W_EXCALIBUR = 98,
    ULTIMECIA = 99
};

enum Character
{
    ARTHUR = 0, LANCELOT = 1, PALADIN = 2, UNDRAGONKNIGHT = 3,
    DRAGONKNIGHT = 4, GUINEVERE = 5, KNIGHT = 6
};

enum GameState
{
    GAMEOVER = 0,
    RUNNING,
    FINISHED
} Game;

struct ExKnight
{
    int HP; int gil; int level; int antidote;

    int maxHP;
    int odin;
    int lionHeart;

    bool isMythril;
    // Whether obtained weapon of Paladin, Lancelot, Guinevere
    bool isPaladinW, isLancelotW, isGuinevere;
    bool isExcalibur;

    int nWin, nLose;

    Character character;
};
// }}}

// {{{ Check Prime
bool check_prime(int number) {
    if (number < 2)             return false;
    if (number == 2)            return true;
    if ((number & 1UL) ^ 1UL)   return false;

    for (int i = 3; i*i <= number; i+=2) {
        if ((number % i) == 0)
            return false;  
    }
    return true;
}
// }}}
// {{{ Check Dragonknight
bool check_dragonknight(int number) {
    /* -- x^2 + y^2 =z^2
     * |
     * -- x + y + z = number
     * x = m^2 - n^2
     * y = 2*m*n
     * z = m^2 + n^2
     *
     * Solution
     * 0 < (number - m*m)/m < m
     */

    // 3 + 4 + 5 = 12
    if(number < 12 || number > 999)
        return false;
    // Odd number
    if (number & 1UL)
        return false;

    int N = number/2;
    int m = 1;
    for( ; ; m++) {

        // m*m < number
        long long temp = m*m;
        if (N < temp)
            break;

        // check number/m is integer
        if (N % m != 0)
            continue;

        // check number < 2*m*m
        if (N/2 > temp)
            continue;

        return true;
    }
    return false;
}
// }}}
// {{{ Get character
Character get_character(int orignalHP)
{
    if (orignalHP == 999)              return Character::ARTHUR;
    if (orignalHP == 888)              return Character::LANCELOT;
    if (orignalHP == 777)              return Character::GUINEVERE;
    if (check_prime(orignalHP))        return Character::PALADIN;
    if (check_dragonknight(orignalHP)) return Character::UNDRAGONKNIGHT;

    return Character::KNIGHT;
}
// }}}

void handle_fight(struct ExKnight *theKnight, int opponent, int eventNum)
{
    int level = theKnight->level;
    Character character = theKnight->character;
    int b = eventNum % 10;
    int level_oppnent = eventNum>6 ? (b>5?b:5):b;


    // TODO: Check autowin
    bool autowin = (    (theKnight->odin > 0)                   ||
                        (character == Character::ARTHUR)        ||
                        (character == Character::DRAGONKNIGHT)  ||
                        (character == Character::PALADIN)       ||
                        (character == Character::LANCELOT)      ||
                        (level > level_oppnent)
                    );

    switch (opponent) {
        case Event::ULTIMECIA:
            if(theKnight->isExcalibur)
            {
                Game = GameState::FINISHED;
                theKnight->nWin++;
            }
            else
            {
                theKnight->HP = MAX(1, theKnight->HP / 3);
                theKnight->nLose++;
            }
            break;

        default: {
            float basedame = 1.0f;
            int gil = 100;
            if (opponent == Event::MOONBRINGER)
            {
                gil = 150;
                basedame = 1.5f;
            }
            else if (opponent == Event::ELF)
            {
                gil = 450;
                basedame = 4.5f;
            }
            else if (opponent == Event::SAXON)
            {
                gil = 650;
                basedame = 6.5f;
            }
            else if (opponent == Event::TROLL)
            {
                gil = 850;
                basedame = 8.5f;
            }

            if (autowin)
                theKnight->gil = MIN(999, theKnight->gil + gil);
            else if (level < level_oppnent)
            {
                if (!theKnight->isMythril)
                    theKnight->HP =
                        (int)(theKnight->HP - level_oppnent*basedame*10.0f);
            }
        } break;
    }

    // TODO: Check die, Call Phoenix
}

void handle_item(struct ExKnight *theKnight, int event)
{
    switch (event)
    {
        // Event 95
        case Event::W_PALADIN:
            theKnight->isPaladinW = true;
            break;

        // Event 96
        case Event::W_LANCELOT:
            theKnight->isLancelotW = true;
            break;

        // Event 97
        case Event::W_GUINEVERE:
            theKnight->isGuinevere = true;
            break;

        // Event 98
        case Event::W_EXCALIBUR: {
            bool can_get_excalibur = (theKnight->character == Character::ARTHUR) ||
                        (theKnight->isGuinevere && theKnight->isPaladinW && theKnight->isLancelotW);

            if (can_get_excalibur)
                theKnight->isExcalibur = true;
        } break;

        default:
            break;
    }
}


void init_knight(ExKnight* exKnight ,knight& oriKnight)
{
    exKnight->HP = oriKnight.HP;
    exKnight->level = oriKnight.level;
    exKnight->antidote = oriKnight.antidote;
    exKnight->gil = oriKnight.gil;

    exKnight->nWin = exKnight->nLose = 0;
    exKnight->maxHP = oriKnight.HP;
    exKnight->odin = -1;
    exKnight->lionHeart = 0;
    exKnight->isMythril = false;
    exKnight->isPaladinW = exKnight->isLancelotW = exKnight->isGuinevere = false;
    exKnight->isExcalibur = false;

    Character character = get_character(oriKnight.HP);
    exKnight->character = character;

    switch(character)
    {
        case Character::LANCELOT:
            exKnight->isLancelotW = true;
            break;

        case Character::PALADIN:
            exKnight->isPaladinW = true;
            break;

        case Character::GUINEVERE:
            exKnight->isGuinevere = true;
            break;

        default:
            break;
    }
}

report*  game_main(knight& oriKnight, castle arrCastle[], int nCastle, int mode, int nPetal)
//void  game_main(knight& oriKnight, castle arrCastle[], int nCastle, int mode, int nPetal, report *r)
{
    ExKnight theKnight;
    init_knight(&theKnight, oriKnight);

    // Game loop
    Game = GameState::RUNNING;
    while (Game == GameState::RUNNING)
    {
        int i;
        for (i = 0; i < nCastle && Game == GameState::RUNNING; ++i)
        {
            int j;
            int *events = arrCastle[i].arrEvent;
            int nEvent = arrCastle[i].nEvent;
            for (j = 0; j < nEvent; ++j)
            {
                if (events[j] >= 95 && events[j] <= 98)
                    handle_item(&theKnight, events[j]);
                else if ((events[j] >= 1 && events[j] <= 7) || events[j] == 99)
                    handle_fight(&theKnight, events[j], j+1);

                if (--nPetal == 0 && Game != GameState::FINISHED)
                    Game = GameState::GAMEOVER;

                if (Game != GameState::RUNNING)
                    break;
            }

            // Knight got out of castle
            if(j == nEvent)
            {
                theKnight.level = MIN(10, theKnight.level + 1);
                theKnight.maxHP = MIN(999, theKnight.maxHP + 100);
            }
        }
    }

    // Return value to oriKnight
    oriKnight.HP = theKnight.HP;
    oriKnight.antidote = theKnight.antidote;
    oriKnight.gil = theKnight.gil;
    oriKnight.level = theKnight.level;

    if (Game == GameState::FINISHED)
    {
        report *r = new report;
        r->nLose = theKnight.nLose;
        r->nWin = theKnight.nWin;
        r->nPetal = nPetal;
        return r;
    }
    return NULL;
}
/********* End My Implementation ***********/

report*  walkthrough (knight& theKnight, castle arrCastle[], int nCastle, int mode, int nPetal)
{
  report* pReturn;
  int bFlag;
  //fighting for the existence of mankind here

 
  // success or failure?
  pReturn = (bFlag)? new report : NULL;
  return pReturn;
}

