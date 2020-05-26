//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "test_sword.h"
//#include "defs.h"


#define sum(a,b,c) (a+b+c)

// {{{ Check prime
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
// }}}
// {{{ Check Dragon Knight
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
// }}}

knight theKnight;
report *m_report;
void set_knight(struct knight *theKnight, int HP, int level, int antidote, int gil)
{
    theKnight->HP = HP;
    theKnight->level = level;
    theKnight->antidote = antidote;
    theKnight->gil = gil;
}

bool compare_knight(struct knight *theKnight, int HP, int level, int antidote, int gil)
{
    //std::cout << theKnight->HP << " ";
    //std::cout << theKnight->level << " ";
    //std::cout << theKnight->antidote << " ";
    //std::cout << theKnight->gil << "\n";

    return theKnight->HP == HP &&
            theKnight->level == level &&
            theKnight->antidote == antidote &&
            theKnight->gil == gil;
}

bool compare_report(report *r, int nPetal, int nWin, int nLose)
{
    if(!r) return false;
    //std::cout << r->nPetal << " ";
    //std::cout << r->nWin << " ";
    //std::cout << r->nLose << " ";

    return r->nPetal == nPetal &&
            r->nWin == nWin &&
            r->nLose == nLose;
}

TEST_CASE("Check fight", "[fight]")
{
    int mode = 0;

    {
        int nPetal = 1;
        set_knight(&theKnight, 172, 4, 0, 100);
        castle arrCastle[] = { {{95,96,97}, 3},
                    {{98,99}, 2}
        };
        m_report = game_main(theKnight, arrCastle, 2, mode, nPetal);
        CHECK(m_report == NULL);
        delete m_report;
    }

    {
        int nPetal = 12;
        set_knight(&theKnight, 172, 4, 0, 100);
        castle arrCastle[] = { {{95,96,97}, 3},
                    {{98,99}, 2}
        };
        m_report = game_main(theKnight, arrCastle, 2, mode, nPetal);
        REQUIRE(compare_knight(&theKnight, 172, 5, 0, 100));
        REQUIRE(m_report != NULL);
        REQUIRE(compare_report(m_report, 7, 1, 0));
        delete m_report;
    }

    {
        int nPetal = 8;
        set_knight(&theKnight, 172, 4, 0, 100);
        castle arrCastle[] = { {{96,98,99}, 3},
                    {{97, 95}, 2}
        };
        m_report = game_main(theKnight, arrCastle, 2, mode, nPetal);
        REQUIRE(m_report != NULL);
        REQUIRE(compare_knight(&theKnight, 57, 6, 0, 100));
        REQUIRE(compare_report(m_report, 0, 1, 1));
        delete m_report;
    }
}
