//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "test_sword.h"


#define sum(a,b,c) (a+b+c)

TEST_CASE( "Check Prime", "[check_prime]" ) {
    REQUIRE( check_prime(11) );
    REQUIRE( check_prime(41) );
    REQUIRE( check_prime(2) );
    REQUIRE( check_prime(3) );

    REQUIRE_FALSE(check_prime(-1));
    REQUIRE_FALSE(check_prime(0));
    REQUIRE_FALSE(check_prime(1));
    REQUIRE_FALSE( check_prime(25) );
    REQUIRE_FALSE( check_prime(14) );
}

TEST_CASE("Check dragon knight", "[check_dragonknight]") {
    REQUIRE(check_dragonknight(sum(3,4,5)));
    REQUIRE(check_dragonknight(sum(5,12,13)));
    REQUIRE(check_dragonknight(sum(6,8,10)));
    REQUIRE(check_dragonknight(sum(7,24,25)));
    REQUIRE(check_dragonknight(sum(8,15,17)));
    REQUIRE(check_dragonknight(sum(30,40,50)));

    REQUIRE_FALSE(check_dragonknight(6));
    REQUIRE_FALSE(check_dragonknight(8));
    REQUIRE_FALSE(check_dragonknight(111));
    REQUIRE_FALSE(check_dragonknight(1000));
    REQUIRE_FALSE(check_dragonknight(sum(9999,200,10001)));
}

/*
 *struct knight theKnight;
 *void set_knight(struct knight *theKnight, int HP, int level, int remedy, int maidenkiss, int phoenixdown) {
 *    theKnight->HP = HP;
 *    theKnight->level = level;
 *    theKnight->remedy = remedy;
 *    theKnight->maidenkiss = maidenkiss;
 *    theKnight->phoenixdown = phoenixdown;
 *
 *    theKnight->numCursed = 0;
 *    theKnight->previousLevel = 0;
 *    theKnight->sword = Item::NORMALSWORD; 
 *    theKnight->armor = Item::NORMALARMOR; 
 *}
 *
 *TEST_CASE("Check fight", "[fight]")
 *{
 *    // Check Frog
 *    {   set_knight(&theKnight, 998, 1 , 0, 0, 0);
 *        int events[] = {4,6,7};
 *        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 200); }
 *
 *    // Check BOWSER
 *    {   set_knight(&theKnight, 998, 1 , 0, 0, 0);
 *        int events[] = {4,99};
 *        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == -1); }
 *
 *    {   set_knight(&theKnight, 999, 1 , 0, 0, 0); // Arthur
 *        int events[] = {4,99};
 *        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 1009); }
 *
 *    {   set_knight(&theKnight, 888, 2, 0, 0, 0); // Lancelot, even number
 *        int events[] = {4,99};
 *        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 898); }
 *
 *    {   set_knight(&theKnight, 888, 3, 0, 0, 0); // Lancelot, odd number
 *        int events[] = {4,99};
 *        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 898); }
 *
 *    {   set_knight(&theKnight, 11, 8, 0, 0, 0);
 *        int events[] = {4,99};
 *        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 21); }
 *
 *    {   set_knight(&theKnight, 12, 10, 0, 0, 0);
 *        int events[] = {99};
 *        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 22); }
 *
 *    {   set_knight(&theKnight, 100, 9, 0, 0, 0);
 *        int events[] = {99};
 *        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == -1); }
 *}
 */
