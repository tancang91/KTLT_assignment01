//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "test_sword.h"
//#include "defs.h"

#define sum(a,b,c) (a+b+c)
knight theKnight;
report *m_report;

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

// {{{ [example]
TEST_CASE("Run example", "[example]")
{
    int mode = 0;

    // Example 2
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

    // Example 3
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

    // Example 4
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

    // Example 5
    {
        int nPetal = 12;
        set_knight(&theKnight, 4, 1, 0, 100);
        castle arrCastle[] = { {{95}, 1},
                    {{96, 97, 98, 2, 99}, 5}
        };
        m_report = game_main(theKnight, arrCastle, 2, mode, nPetal);
        REQUIRE(m_report != NULL);
        REQUIRE(compare_knight(&theKnight, 52, 2, 0, 0));
        REQUIRE(compare_report(m_report, 6, 1, 1));
        delete m_report;
    }

    // Example 6
    {
        int nPetal = 12;
        set_knight(&theKnight, 172, 1, 0, 100);
        castle arrCastle[] = { {{95}, 1},
                    {{96, 97, 98, 6}, 4},
                    {{1, 99}, 2},
        };
        m_report = game_main(theKnight, arrCastle, 3, mode, nPetal);
        REQUIRE(m_report != NULL);
        REQUIRE(compare_knight(&theKnight, 54, 3, 0, 200));
        REQUIRE(compare_report(m_report, 5, 2, 1));
        delete m_report;
    }

    // Example 7
    {
        int nPetal = 12;
        set_knight(&theKnight, 172, 1, 0, 100);
        castle arrCastle[] = { {{95,96,97,98,1,8,99}, 7} };
        m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);

        REQUIRE(m_report != NULL);
        REQUIRE(compare_knight(&theKnight, 172, 1, 0, 50));
        REQUIRE(compare_report(m_report, 5, 1, 1));
        delete m_report;
    }

}


// }}}

TEST_CASE("Check fight", "[fight]")
{
    int mode = 0;

    // Test Fight event 7
    // Event Durican 9, Antidote 10
    {
        int nPetal = 12;
        set_knight(&theKnight, 172, 1, 0, 50);
        castle arrCastle[] = { {{95, 96, 97, 98, 7, 9, 10, 99}, 8} };
        m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
        REQUIRE(compare_knight(&theKnight, 172, 1, 1, 25));
        REQUIRE(compare_report(m_report, 9,1,1));
        delete m_report;
    }

    // Test GUINEVERE
    {
        int nPetal = 12;
        set_knight(&theKnight, 777, 1, 0, 50);
        castle arrCastle[] = { {{95,96,97,2}, 4},
            {{99, 98}, 2} };
        m_report = game_main(theKnight, arrCastle, 2, mode, nPetal);
        REQUIRE(compare_knight(&theKnight, 777, 4, 0, 50));
        delete m_report;
    }
}

TEST_CASE("Check event", "[event]")
{
    int mode = 0;
    // TODO: NINA
}

TEST_CASE("Check character", "[character]")
{
    int mode = 0;
    // Arthur do not care Canh Hoa Hong
    {
        int nPetal = 1;
        set_knight(&theKnight, 999, 1, 0, 50);
        castle arrCastle[] = { {{95,98,99},3}};
        m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
        REQUIRE(m_report != NULL);
        REQUIRE(compare_report(m_report, 0,1,0));
        delete m_report;
    }

}
