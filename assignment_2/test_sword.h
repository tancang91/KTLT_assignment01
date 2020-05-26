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

#endif /* end of include guard: TEST_SWORD_H_XUNVLOP3 */
