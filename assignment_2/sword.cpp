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

void handle_fight(struct ExKnight *theKnight, Event opponent, int eventNum)
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


void init_knight(ExKnight* exKnight ,knight& oriKnight)
{
    exKnight->HP = oriKnight.HP;
    exKnight->level = oriKnight.level;
    exKnight->antidote = oriKnight.antidote;
    exKnight->gil = oriKnight.gil;

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
{
    ExKnight theKnight;
    init_knight(&theKnight, oriKnight);

    int petal_count, win_count, lose_count;
    petal_count = win_count = lose_count = 0;

    int i;
    for (i = 0; i < nCastle; ++i)
    {
        int *events = arrCastle[i].arrEvent;
        int nEvent = arrCastle[i].nEvent;
        for (int j = 0; j < nEvent; ++j)
        {

        }
    }

    oriKnight.HP = theKnight.HP;
    oriKnight.antidote = theKnight.antidote;
    oriKnight.gil = theKnight.gil;
    oriKnight.level = theKnight.level;

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

