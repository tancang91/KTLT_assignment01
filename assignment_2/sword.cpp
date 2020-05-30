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
    HAKAMA = 15, LOCKEDDOOR = 16,
    // Weapon to defeat ULTIMECIA
    W_PALADIN = 95, W_LANCELOT = 96, W_GUINEVERE = 97, W_EXCALIBUR = 98,
    ULTIMECIA = 99
};

enum Character { ARTHUR = 0, LANCELOT, PALADIN, DRAGONKNIGHT, GUINEVERE, KNIGHT };

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

    int odin, lionHeart, poison;

    bool isMythril, winOmega, hakama;
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
    if (check_dragonknight(orignalHP)) return Character::DRAGONKNIGHT;

    return Character::KNIGHT;
}
// }}}
// {{{ Check friendly number
bool is_friendly_number(int a, int b)
{
    return false;
}
// }}}
// {{{ Helper function
void copy_knight(ExKnight& exKnight, knight& oriKnight, bool reverse)
{
    /* Copy from exKnight to oriKnight */

    if (!reverse) {
        oriKnight.HP        = exKnight.HP;
        oriKnight.gil       = exKnight.gil;
        oriKnight.level     = exKnight.level;
        oriKnight.antidote  = exKnight.antidote;
    }
    else {
        exKnight.HP        =   oriKnight.HP;
        exKnight.gil       =   oriKnight.gil;
        exKnight.level     =   oriKnight.level;
        exKnight.antidote  =   oriKnight.antidote;
    }
}

int custom_callPhoenix(ExKnight &exKnight)
{
    // Get rid of poison from body
    exKnight.poison = 0;

    knight oriKnight;
    copy_knight(exKnight, oriKnight, false);
    int i = callPhoenix(oriKnight, exKnight.maxHP);
    copy_knight(exKnight, oriKnight, true);
    return i;
}

void increase_level(ExKnight &exKnight)
{
    exKnight.level = MIN(10, exKnight.level + 1);
    exKnight.maxHP = MIN(999, exKnight.maxHP + 100);
}

void init_knight(ExKnight* exKnight ,knight& oriKnight)
{
    // Original attribute of knight
    exKnight->HP = oriKnight.HP;
    exKnight->level = oriKnight.level;
    exKnight->antidote = oriKnight.antidote;
    exKnight->gil = oriKnight.gil;

    exKnight->maxHP = oriKnight.HP;
    exKnight->nWin = exKnight->nLose = 0;

    // Event with countdown.
    exKnight->odin = 0;
    exKnight->lionHeart = exKnight->poison = 0;

    // Special item
    exKnight->isMythril = exKnight->hakama= false;
    exKnight->winOmega = false;
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
// }}}

// {{{ Handle fight
void handle_fight(ExKnight& theKnight, int opponent, int eventNum)
{
    int level = theKnight.level;
    const Character character = theKnight.character;
    int b = eventNum % 10;
    const int level_oppnent = eventNum>6 ? (b>5?b:5):b;

    bool autowin = (    (theKnight.odin > 0)                    ||
                        (theKnight.lionHeart > 0)               ||
                        (character == Character::ARTHUR)        ||
                        (character == Character::LANCELOT)      ||
                        (level >= level_oppnent)
                    );

    switch (opponent) {
        case Event::ULTIMECIA:
            if (theKnight.isExcalibur || theKnight.lionHeart > 0)
            {
                if (theKnight.poison > 0)
                    theKnight.HP = MAX(1, theKnight.HP / 3);

                Game = GameState::FINISHED;
                theKnight.nWin++;
            }
            else
            {
                if ( !theKnight.isMythril && (character != Character::GUINEVERE) )
                    theKnight.HP = MAX(1, theKnight.HP / 3);
                theKnight.nLose++;
            }
            break;

        case Event::HADES: {
            if (theKnight.odin > 0 && character != Character::DRAGONKNIGHT)
                theKnight.odin = -1;

            bool eternalLove = ( !theKnight.isExcalibur && theKnight.isLancelotW && theKnight.isGuinevere) ||
                                ( theKnight.isGuinevere && character == Character::ARTHUR ) ||
                                ( theKnight.isGuinevere && character == Character::LANCELOT ) ||
                                ( theKnight.isLancelotW && character == Character::GUINEVERE );

            bool win =  eternalLove                 ||
                        (level >= level_oppnent)    ||
                        (theKnight.lionHeart > 0)   ||
                        (theKnight.odin > 0 && character == Character::DRAGONKNIGHT);
            if (win)
            {
                theKnight.isMythril = true;
                theKnight.nWin++;
            }
            else
            {
                if (!theKnight.isMythril)
                    theKnight.HP = 0;
                theKnight.nLose++;
            }
        } break;

        case Event::OMEGAWEAPON:
            if (!theKnight.winOmega)
            {
                bool win = (theKnight.isExcalibur && theKnight.level == 10) ||
                            (character == Character::DRAGONKNIGHT && theKnight.lionHeart > 0);
                if (win)
                {
                    while (theKnight.level != 10)
                        increase_level(theKnight);

                    theKnight.gil = 999;
                    theKnight.winOmega = true;
                    theKnight.nWin++;
                }
                else
                {
                    if (!theKnight.isMythril)
                        theKnight.HP = 0;
                    theKnight.nLose++;
                }

            }
            break;

        case Event::QUEENCARDS:
            if (autowin)
            {
                theKnight.gil = MIN(999, theKnight.gil*2);
                theKnight.nWin++;
            }
            else if (level < level_oppnent)
            {
                bool notDecrease = (theKnight.hakama) || (character == Character::GUINEVERE);
                if (!notDecrease)
                    theKnight.gil = MAX(1, theKnight.gil / 2);
                theKnight.nLose++;
            }
            break;

        case Event::TORNBERRY:
            // 5 + 1 = 6
            if (theKnight.poison > 0)
                break;

            if (autowin)
            {
                increase_level(theKnight);
                theKnight.nWin++;
            }
            else if (level < level_oppnent)
            {
                if (character != Character::PALADIN && character != Character::DRAGONKNIGHT)
                    theKnight.poison = 6;
                if (theKnight.poison > 0 && theKnight.antidote > 0)
                    theKnight.antidote--;

                theKnight.nLose++;
            }
            break;

        default: {
            float basedame = 1.0f;
            int gil = 100;
            if (opponent == Event::MOONBRINGER)
            {
                gil = 150;
                basedame = (character == Character::GUINEVERE) ? 0.0f : 1.5f;
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

            if (autowin || character == Character::PALADIN)
            {
                theKnight.gil = MIN(999, theKnight.gil + gil);
                theKnight.nWin++;

                if(theKnight.poison > 0)
                    theKnight.HP = (int)(theKnight.HP - level_oppnent*basedame*10.0f);
            }
            else if (level < level_oppnent)
            {
                if (!theKnight.isMythril)
                    theKnight.HP = (int)(theKnight.HP - level_oppnent*basedame*10.0f);
                theKnight.nLose++;
            }
        } break;
    }

    // Check die, Call Phoenix
    if (theKnight.HP <= 0)
        custom_callPhoenix(theKnight);
}
// }}}

void handle_event(ExKnight& theKnight, int event)
{
    switch (event)
    {
        // Event 8
        // TODO: Implement Friend number function
        case Event::NINA: {
            bool isFriendly = is_friendly_number(theKnight.HP, theKnight.gil);
            bool free_lunch =   (theKnight.character == Character::GUINEVERE) || 
                                (theKnight.character == Character::PALADIN)   ||
                                (theKnight.hakama);

            if (free_lunch)
            {
                theKnight.HP = theKnight.maxHP;
                theKnight.poison = 0;
                if (theKnight.character == Character::GUINEVERE)
                    theKnight.gil = MIN(999, theKnight.gil + 50);
            }
            if (isFriendly)
            {
                theKnight.HP = theKnight.maxHP;
                theKnight.poison = 0;

                // Paladin will carry lion heart forever (999)
                theKnight.lionHeart = theKnight.character == Character::PALADIN ? 999 : 6;
            }
            else if (theKnight.gil >= 50)
            {
                if (!free_lunch)
                {
                    if (theKnight.poison > 0)
                    {
                        theKnight.poison = 0;
                        theKnight.gil -= 50;
                    }

                    int temp = MIN(theKnight.maxHP - theKnight.HP, theKnight.gil);
                    theKnight.gil -= temp;
                    theKnight.HP += temp;
                }
            }
        } break;

        // Event 9
        case Event::DURIAN:
            theKnight.poison = 0;
            theKnight.HP = theKnight.maxHP;
            break;

        // Event 10
        case Event::ANTIDOTE:
            theKnight.antidote = MIN(99, theKnight.antidote+1);
            if (theKnight.poison > 0)
            {
                theKnight.poison = 0;
                theKnight.antidote = MAX(0, theKnight.antidote-1);
            }
            break;

        // Event 11
        case Event::ODIN:
            // -1 mean odin already dead.
            theKnight.odin = (theKnight.odin == -1) ? -1 : 6;
            break;

        // Event 12
        case Event::MERLIN:
            theKnight.poison = 0;
            increase_level(theKnight);
            theKnight.HP = theKnight.maxHP;
            break;

        // Event 15
        case Event::HAKAMA:
            theKnight.hakama = true;
            break;

        // Event 16
        //case Event::LOCKEDDOOR:
            //break;

        default:
            break;
    }
}

// {{{ Handle item
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
// }}}


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
                theKnight.poison -= theKnight.poison > 0 ? 1 : 0;
                theKnight.odin -= theKnight.odin > 0 ? 1 : 0;
                //theKnight.lionHeart -= theKnight.lionHeart > 0 ? 1 : 0;
                if (theKnight.lionHeart > 0 && theKnight.lionHeart <= 6)
                    theKnight.lionHeart--;

                int event = events[j];
                if (event >= 95 && event <= 98)
                    handle_item(&theKnight, event);
                else if ((event >= 1 && event <= 7) || event == 99 || event == 13 || event == 14)
                    handle_fight(theKnight, event, j+1);
                else
                {
                    handle_event(theKnight, event);

                    if (event == Event::DURIAN)
                        nPetal = theKnight.hakama ? 99 : MIN(99, nPetal+5);
                    else if (event == Event::LOCKEDDOOR)
                    {
                        bool isPass = (theKnight.level > ((j+1)%10))                    ||
                                        (theKnight.character == Character::LANCELOT)    ||
                                        (theKnight.character == Character::DRAGONKNIGHT);
                        if (!isPass)
                            j = nEvent - 1;
                    }
                }

                nPetal = MAX(0, nPetal-1);
                if ((nPetal == 0 && theKnight.character != Character::ARTHUR) && Game != GameState::FINISHED)
                    Game = GameState::GAMEOVER;

                if (Game != GameState::RUNNING) break;
            }

            // Knight got out of castle
            if(j == nEvent)
                increase_level(theKnight);
        }
    }

    // Return value to oriKnight
    copy_knight(theKnight, oriKnight, false);

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

