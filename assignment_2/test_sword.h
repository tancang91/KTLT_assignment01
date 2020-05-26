#ifndef TEST_SWORD_H_XUNVLOP3
#define TEST_SWORD_H_XUNVLOP3

#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

bool check_prime(int number);
bool check_dragonknight(int number);

//void  game_main(knight& oriKnight, castle arrCastle[], int nCastle, int mode, int nPetal, report *r);
report*  game_main(knight& oriKnight, castle arrCastle[], int nCastle, int mode, int nPetal);

#endif /* end of include guard: TEST_SWORD_H_XUNVLOP3 */
