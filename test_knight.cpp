//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "knight.h"

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

TEST_CASE("Check next fib", "[get_fib]") {
    REQUIRE(get_fib(12) == 13);
    REQUIRE(get_fib(300) == 377);
    REQUIRE(get_fib(610) == 987);
    REQUIRE(get_fib(1) == 2);
    REQUIRE(get_fib(50) == 55);
}

struct knight theKnight;
void set_knight(struct knight *theKnight, int HP, int level, int remedy, int maidenkiss, int phoenixdown) {
    theKnight->HP = HP;
    theKnight->level = level;
    theKnight->remedy = remedy;
    theKnight->maidenkiss = maidenkiss;
    theKnight->phoenixdown = phoenixdown;

    theKnight->numCursed = 0;
    theKnight->previousLevel = 0;
    theKnight->sword = Item::NORMALSWORD; 
    theKnight->armor = Item::NORMALARMOR; 
}

TEST_CASE("Example", "[example]")
{
    // Check Dwarf - event 0 - ex 2
    {   set_knight(&theKnight, 172, 2, 0, 1, 0);
        int events[] = {0};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 175); }

    // Check Dwarf - event 0 - ex 3
    {   set_knight(&theKnight, 172, 2, 0, 1, 0);
        int events[] = {0,10,5,15,21,99};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 175); }

    // Check Dwarf - event 1...5 - ex 4
    {   set_knight(&theKnight, 172, 2, 0, 1, 0);
        int events[1] = {5};
        REQUIRE(game_main(&theKnight, events, 1) == 176); }

    // Check Dwarf - event 1...5 - ex 5
    {   set_knight(&theKnight, 172, 1, 0, 1, 0);
        int events[2] = {5,2};
        REQUIRE(game_main(&theKnight, events, 2) == 144); }

    // Check Dwarf - event 1...5 - ex 6
    {   set_knight(&theKnight, 152, 1, 0, 1, 0);
        int events[3] = {3,5,7};
        REQUIRE(game_main(&theKnight, events, 3) == -1); }

    // Check Dwarf - event 1...5 - ex 7
    {   set_knight(&theKnight, 152, 1, 0, 1, 1);
        int events[2] = {3,5};
        REQUIRE(game_main(&theKnight, events, 2) == 154); }

    // Check Dwarf - event 6 - ex 8
    {   set_knight(&theKnight, 152, 1 , 0, 0, 0);
        int events[3] = {4,6,5};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == -1); }

    // Check Dwarf - event 6 - ex 9
    {   set_knight(&theKnight, 998, 1 , 0, 0, 0);
        int events[] = {4,6,1,1,1};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 396); }

    // Check Dwarf - event 6 - ex 10
    {   set_knight(&theKnight, 998, 1 , 2, 0, 0);
        int events[] = {4,6,1};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 967); }

    // EXCALIBUR - event 8 - ex 11
    {   set_knight(&theKnight, 172, 1, 2, 0, 0);
        int events[] = {8,5};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 176); }

    // MYTHRIL armor - event 9 - ex 12
    {   set_knight(&theKnight, 172, 1, 2, 0, 0);
        int events[] = {9,5,8,4};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 176); }

    // EXCALIPOOR - event 10 - ex 13
    {   set_knight(&theKnight, 172, 4, 2, 0, 0);
        int events[] = {8,9,10,5};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 178); }

    // MUSHMARIO - event 11 - ex 14
    {   set_knight(&theKnight, 172, 4, 2, 0, 0);
        int events[] = {10,1,11};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 178); }

    // MUSHKNIGHT - event 14 - ex 15
    {   set_knight(&theKnight, 172, 4, 2, 0, 0);
        int events[] = {10,1,14};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 228); }

    // GUINEVERE - event 20 - ex 16
    {   set_knight(&theKnight, 172, 4, 2, 0, 0);
        int events[] = {1,4,20,3,4,5,6,7,8,9,10,11};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 182); }

    // LIGHTWING - event 21 - ex 17
    {   set_knight(&theKnight, 172, 4, 2, 0, 0);
        int events[] = {21,4,18,3,2};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 103); }

    // LIGHTWING - event 21 - ex 18
    {   set_knight(&theKnight, 172, 4, 2, 0, 0);
        int events[] = {21,99,99};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 178); }

    // LIGHTWING - event 21 - ex 19
    {   set_knight(&theKnight, 172, 4, 2, 0, 0);
        int events[] = {21,99,20,99,16,20,12};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 178); }

    // Arthur - ex 20
    {   set_knight(&theKnight, 999, 6, 2, 0, 0);
        int events[] = {6,19};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 1009); }

    // Arthur - ex 21
    {   set_knight(&theKnight, 999, 6, 2, 0, 0);
        int events[] = {19};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == -1); }

    // Lancelot - ex 22
    {   set_knight(&theKnight, 888, 1, 2, 0, 0);
        int events[] = {10,1,10,7,5};
        REQUIRE_FALSE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 892); }

    // ex 23
    CHECK(check_dragonknight(234));
}

TEST_CASE("Check fight", "[fight]")
{
    // Check Frog
    {   set_knight(&theKnight, 998, 1 , 0, 0, 0);
        int events[] = {4,6,7};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 200); }

    // Check BOWSER
    {   set_knight(&theKnight, 998, 1 , 0, 0, 0);
        int events[] = {4,99};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == -1); }

    {   set_knight(&theKnight, 999, 1 , 0, 0, 0); // Arthur
        int events[] = {4,99};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 1009); }

    {   set_knight(&theKnight, 888, 2, 0, 0, 0); // Lancelot, even number
        int events[] = {4,99};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 898); }

    {   set_knight(&theKnight, 888, 3, 0, 0, 0); // Lancelot, odd number
        int events[] = {4,99};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 898); }

    {   set_knight(&theKnight, 11, 8, 0, 0, 0);
        int events[] = {4,99};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 21); }

    {   set_knight(&theKnight, 12, 10, 0, 0, 0);
        int events[] = {99};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 22); }

    {   set_knight(&theKnight, 100, 9, 0, 0, 0);
        int events[] = {99};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == -1); }
}

TEST_CASE("Test item", "[item]") {
    // Phoenixdown
    {   set_knight(&theKnight, 10, 1, 0, 0, 1);
        int events[] = {5,5};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 11); }

    {   set_knight(&theKnight, 172, 4, 2, 0, 0);
        int events[] = {10,1,14,15,16,17};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 231); }

    // MUSHFIB
    {   set_knight(&theKnight, 172, 4, 2, 0, 0);
        int events[] = {10,1,11,12};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 178); }

    // MUSHFGHOST
    {   set_knight(&theKnight, 172, 4, 2, 0, 0);
        int events[] = {10,1,11,12,13};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 128); }

    {   set_knight(&theKnight, 50, 0, 0, 0, 0);
        int events[] = {13};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 1); }

    // MUSHFGHOST (event 9) and Mysthril (event 13)
    {   set_knight(&theKnight, 100, 1, 0, 0, 0);
        int events[] = {9,13};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 101); }
}

TEST_CASE("Test Abyss vuc tham","[abyss][character]") {
    // event 19
    {   set_knight(&theKnight, 9, 7, 2, 0, 0);
        int events[] = {19};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 18); }

    {   set_knight(&theKnight, 999, 1, 10, 10, 10);
        int events[] = {99, 19};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 1039); }

    SECTION("Odin help")
    {
        // Odin -> Abyss -> MushGhost -> EXCALIPOOR
        {   set_knight(&theKnight, 81, 4, 0, 0, 0);
            int events[] = {22, 19, 13, 10};
            REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 85); }

        // Odin ->  EXCALIPOOR -> Troll
        {   set_knight(&theKnight, 81, 0, 0, 0, 0);
            int events[] = {22, 10, 5};
            REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 82); }
    }

    SECTION("King Arthur")
    {
        {   set_knight(&theKnight, 999, 6, 2, 0, 0);
            int events[] = {19};
            REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == -1); }
    }

    SECTION("Dragon")
    {
        {   set_knight(&theKnight, 12, 6, 2, 0, 0);
            int events[] = {19};
            REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == -1); }

        {   set_knight(&theKnight, 12, 6, 2, 0, 0);
            int events[] = {23, 19};
            REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 20); }
    }

    SECTION("Paladin")
    {
        set_knight(&theKnight, 41, 6, 2, 0, 0);
        int events[] = {19};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == -1);
    }

    SECTION("Lancelot")
    {
        set_knight(&theKnight, 888, 5, 2, 0, 0);
        int events[] = {19};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == -1);
    }
}

/*
 *TEST_CASE( "Final Result", "[prob_calculator_main]" ) {
 *    Catch::StringMaker<float>::precision = 2;
 *    // Normal rule when wp < 2
 *    REQUIRE( prob_calculator_main(450, 1, 150, 1, 302) == Approx(0.65f).epsilon(0.01));
 *    REQUIRE( prob_calculator_main(807, 0, 750, 1, 156) == Approx(0.16f).margin(0.01));
 *    REQUIRE( prob_calculator_main(417, 1, 416, 0, 417) == Approx(0.71f).epsilon(0.01));
 *    REQUIRE( prob_calculator_main(235, 1, 624, 0, 624) == Approx(0.58f).epsilon(0.01));
 *    REQUIRE( prob_calculator_main(998, 1, 517, 1, 998) == Approx(0.74f).epsilon(0.01));
 *
 *    // wp = 2
 *    REQUIRE( prob_calculator_main(238, 2, 114, 1, 145) == Approx(0.56f).epsilon(0.01));
 *    REQUIRE( prob_calculator_main(738, 1, 45, 2, 26) == Approx(0.50f).epsilon(0.01));
 *
 *    // King arthur
 *    REQUIRE( prob_calculator_main(999, 0, 800, 2, 444) == Approx(1).epsilon(0.01));
 *    REQUIRE( prob_calculator_main(998, 3, 888, 2, 444) == Approx(0.00f).epsilon(0.01));
 *}
 */
