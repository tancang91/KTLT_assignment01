#ifndef TEST_SWORD_H_XUNVLOP3
#define TEST_SWORD_H_XUNVLOP3

#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

bool check_prime(int number);
bool check_dragonknight(int number);

report*  game_main(knight& oriKnight, castle arrCastle[], int nCastle, int mode, int nPetal);

int callPhoenix(knight& woundedKnight, int MaxHP)
{
	static int nTimes = 0;
	woundedKnight.HP = MaxHP/2;
	woundedKnight.gil = woundedKnight.gil<100? 0: woundedKnight.gil-100;
	return ++nTimes;
}

int hash(int eventCode)
{
    return eventCode;
}
int sum_of_diviors(int N);
int gcd(int a, int b);
bool is_friendly_number(int a, int b);

// {{{ Helper
void set_knight(struct knight *theKnight, int HP, int level, int antidote, int gil)
{
    theKnight->HP = HP;
    theKnight->level = level;
    theKnight->antidote = antidote;
    theKnight->gil = gil;
}

void print_knight(knight *theKnight)
{
    std::cout << "---Knight info---\n";
    std::cout << "HP: " << theKnight->HP << ", ";
    std::cout << "Level:" << theKnight->level << ", ";
    std::cout << "Antidote:" << theKnight->antidote << ", ";
    std::cout << "Gil: " << theKnight->gil << "\n";
    std::cout << "---------------\n";
}

void print_report(report *r)
{
    std::cout << "---Report info---\n";
    if (!r)
        std::cout << "NULL value" << "\n";
    else {
        std::cout << "nPetal: " << r->nPetal << ", ";
        std::cout << "nWin: " << r->nWin << ", ";
        std::cout << "nLose: " << r->nLose << "\n";
    }
    std::cout << "---------------\n";
}

bool compare_knight(struct knight *theKnight, int HP, int level, int antidote, int gil)
{

    return theKnight->HP == HP &&
            theKnight->level == level &&
            theKnight->antidote == antidote &&
            theKnight->gil == gil;
}

bool compare_report(report *r, int nPetal, int nWin, int nLose)
{
    if(!r) return false;
    return r->nPetal == nPetal &&
            r->nWin == nWin &&
            r->nLose == nLose;
}
// }}}

#endif /* end of include guard: TEST_SWORD_H_XUNVLOP3 */

