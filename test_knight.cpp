#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
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
    REQUIRE(check_dragonknight(sum(21,28,35)));

    REQUIRE_FALSE(check_dragonknight(6));
    REQUIRE_FALSE(check_dragonknight(111));
    REQUIRE_FALSE(check_dragonknight(1000));
    REQUIRE_FALSE(check_dragonknight(sum(9999,200,10001)));
}

void set_knight(struct knight *theKnight, int HP, int level, int remedy, int maidenkiss, int phoenixdown) {
    theKnight->HP = HP;
    theKnight->level = level;
    theKnight->remedy = remedy;
    theKnight->maidenkiss = maidenkiss;
    theKnight->phoenixdown = phoenixdown;
}

TEST_CASE("Check fight", "[handle_fight]") {
    struct knight theKnight;
    {   set_knight(&theKnight, 172, 2, 0, 1, 0);
        int events[1] = {5};
        REQUIRE(game_main(&theKnight, events, 1) == 176); }

    {   set_knight(&theKnight, 172, 1, 0, 1, 0);
        int events[2] = {5,2};
        REQUIRE(game_main(&theKnight, events, 2) == 144); }

    {   set_knight(&theKnight, 152, 1, 0, 1, 0);
        int events[3] = {3,5,7};
        REQUIRE(game_main(&theKnight, events, 3) == -1); }

    {   set_knight(&theKnight, 152, 1, 0, 1, 1);
        int events[2] = {3,5};
        REQUIRE(game_main(&theKnight, events, 2) == 154); }

    {   set_knight(&theKnight, 152, 1 , 0, 0, 0);
        int events[3] = {4,6,5};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == -1); }

    // Check Dwarf
    {   set_knight(&theKnight, 998, 1 , 0, 0, 0);
        int events[] = {4,6,1,1,1};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 396); }

    {   set_knight(&theKnight, 998, 1 , 2, 0, 0);
        int events[] = {4,6,1};
        REQUIRE(game_main(&theKnight, events, sizeof(events)/sizeof(int)) == 967); }

    // Check Frog
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
