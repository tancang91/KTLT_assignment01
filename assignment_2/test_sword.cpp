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

TEST_CASE("Check sum divisors", "[sum]")
{
    REQUIRE(sum_of_diviors(1) == 1);
    REQUIRE(sum_of_diviors(30) == 72);
    REQUIRE(sum_of_diviors(81) == 121);
    REQUIRE(sum_of_diviors(17) == 18);
    REQUIRE(sum_of_diviors(100) == 217);
    REQUIRE(sum_of_diviors(108) == 280);
    REQUIRE(sum_of_diviors(144) == 403);
}

TEST_CASE("Greatest common divisor", "[gcd]")
{
    REQUIRE(gcd(6, 18) == 6);
    REQUIRE(gcd(17, 17) == 17);
    REQUIRE(gcd(17, 13) == 1);
    REQUIRE(gcd(54, 24) == 6);
    REQUIRE(gcd(180, 48) == 12);
}

TEST_CASE("Friend Number", "[friend]")
{
    REQUIRE(is_friendly_number(30, 140));
    REQUIRE(is_friendly_number(2480, 6200));
    REQUIRE(is_friendly_number(135, 819));
    REQUIRE(is_friendly_number(42, 544635));
    REQUIRE(is_friendly_number(40640, 6200));
}

#if 0
TEST_CASE("Stack", "[stack]")
{
    testing::Stack s;
    REQUIRE(s.isEmpty());

    for (int i = 1; i <= 4; ++i)
        s.push(i);

    REQUIRE(!s.isFull());
    s.push(5);
    REQUIRE(s.isFull());

    SECTION("Pop Stack")
    {
        for (int i = 5; i > 0; --i)
        {
            REQUIRE(s.pop() == i);
        }

        REQUIRE(s.isEmpty());
        REQUIRE(s.top() == -999);
    }
}

TEST_CASE("Sorting", "[sort]")
{
    int temp[3];
    temp[0] = 11;
    temp[1] = 56;
    temp[2] = 12;
    for (int i = 1; i < 3; ++i)
    {
        int t = temp[i];
        int j = i;
        while (j != 0 && temp[j-1] < t)
        {
            temp[j] = temp[j-1];
            j--;
        }
        temp[j] = t;
    }

    for (int i = 1; i < 3; ++i)
        REQUIRE(temp[i-1] >= temp[i]);
}
#endif

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

    // Example 6b
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

    // Example 7
    {
        int nPetal = 12;
        set_knight(&theKnight, 172, 1, 0, 100);
        castle arrCastle[] = { {{14,95,96,97,98,14,6,99}, 8} };
        m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
        REQUIRE(compare_knight(&theKnight, 57, 1, 0, 100));
        REQUIRE(compare_report(m_report, 4, 2, 2));
        delete m_report;
    }

    // Example 8
    {
        int nPetal = 12;
        set_knight(&theKnight, 172, 3, 0, 100);
        castle arrCastle[] = { {{11,14,95,96,97,98,11,1,99}, 9} };
        m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
        REQUIRE(compare_knight(&theKnight, 172, 3, 0, 100));
        REQUIRE(compare_report(m_report, 3, 2, 1));
        delete m_report;
    }

    // Example 9 (LOCKEDDOOR)
    {
        int nPetal = 12;
        set_knight(&theKnight, 172, 2, 0, 100);
        castle arrCastle[] = { {{95,16,96,97,98,99}, 6}};
        m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
        REQUIRE(compare_knight(&theKnight, 172, 3, 0, 100));
        REQUIRE(compare_report(m_report, 4, 1, 0));
        delete m_report;
    }

    // Example 9 (Arthur)
    {
        int nPetal = 1;
        set_knight(&theKnight, 999, 2, 0, 100);
        castle arrCastle[] = { {{10,98,99,95,96,97}, 6} };
        m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
        REQUIRE(compare_knight(&theKnight, 999, 2, 1, 100));
        REQUIRE(compare_report(m_report, 0, 1, 0));
        delete m_report;
    }

    // Example 10 (mode 1)
    {
        int nPetal = 12;
        set_knight(&theKnight, 4, 1, 0, 100);
        castle arrCastle[] = { {{95,96,97,98,99}, 5} };
        m_report = game_main(theKnight, arrCastle, 1, 1, nPetal);
        REQUIRE(compare_knight(&theKnight, 1, 2, 0, 100));
        REQUIRE(compare_report(m_report, 2, 1, 1));
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

    // Test OMEGAWEAPON
    {
        int nPetal = 12;
        set_knight(&theKnight, 100, 10, 0, 50);
        castle arrCastle[] = { {{95,96,97,13,98,99}, 6}};
        m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
        REQUIRE(compare_knight(&theKnight, 50, 10, 0, 0));
        REQUIRE(compare_report(m_report, 6,1,1));
        delete m_report;
    }
}

TEST_CASE("Check event", "[event]")
{
    int mode = 0;
    SECTION("NINA") {
        int nPetal = 20;
        set_knight(&theKnight, 30, 1, 0, 140);

        SECTION("Friendly number") {
            castle arrCastle[] = { {{8, 95, 96, 97, 1, 99}, 6} };
            m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
            REQUIRE(compare_knight(&theKnight, 30, 1, 0, 240));
            REQUIRE(compare_report(m_report, 14, 2, 0));
        }

        SECTION("Friendly number expire") {
            castle arrCastle[] = { {{8, 95, 96, 97, 2, 98, 1, 99}, 8} };
            m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
            REQUIRE(compare_knight(&theKnight, 15, 1, 0, 190));
            REQUIRE(compare_report(m_report, 12, 2, 1));
        }

        SECTION("Basic: Not enough gil") {
            set_knight(&theKnight, 200, 1, 0, 50);
            castle arrCastle[] = { {{95, 96, 97, 98, 10, 1, 8, 99}, 8} };
            m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
            REQUIRE(compare_knight(&theKnight, 190, 1, 1, 0));
            REQUIRE(compare_report(m_report, 12, 1, 1));
        }

        SECTION("Basic: Enough gil") {
            set_knight(&theKnight, 200, 1, 0, 160);
            castle arrCastle[] = { {{95, 96, 97, 98, 1, 8, 99}, 7} };
            m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
            REQUIRE(compare_knight(&theKnight, 200, 1, 0, 110));
            REQUIRE(compare_report(m_report, 13, 1, 1));
        }
        delete m_report;
    }

    // Event Odin 11
    {
        int nPetal = 12;
        set_knight(&theKnight, 172, 1, 0, 100);
        castle arrCastle[] = { {{11, 95, 96, 97, 98, 3, 1}, 7},
                    {{1, 99}, 2},
        };
        m_report = game_main(theKnight, arrCastle, 3, mode, nPetal);
        REQUIRE(theKnight.HP == 102); REQUIRE(theKnight.gil == 650);
        REQUIRE(compare_report(m_report, 3, 3, 1));
        delete m_report;
    }

    // Event Merlin 12
    {
        int nPetal = 12;
        set_knight(&theKnight, 172, 1, 0, 100);
        castle arrCastle[] = { {{11, 95, 96, 97, 98, 6, 12, 99}, 8} };
        m_report = game_main(theKnight, arrCastle, 3, mode, nPetal);
        REQUIRE(compare_knight(&theKnight, 372, 3, 0, 100));
        REQUIRE(compare_report(m_report, 4, 2, 0));
        delete m_report;
    }

    // Event LOCKEDDOOR & LANCELOT
    {
        int nPetal = 12;
        set_knight(&theKnight, 888, 2, 0, 100);
        castle arrCastle[] = { {{95,16,96,97,98,99}, 6}};
        m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
        REQUIRE(compare_knight(&theKnight, 888, 2, 0, 100));
        REQUIRE(compare_report(m_report, 6, 1, 0));
        delete m_report;
    }

    // Event Hakama & Durian
    {
        int nPetal = 12;
        set_knight(&theKnight, 14, 2, 0, 100);
        castle arrCastle[] = { {{10,95,96,97,98,15,7,9,99}, 9}};
        m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
        REQUIRE(compare_knight(&theKnight, 14, 2, 1, 100));
        REQUIRE(compare_report(m_report, 97, 1, 1));
        delete m_report;
    }

    // Lose to Hades
    {
        int nPetal = 12;
        set_knight(&theKnight, 120, 1, 0, 140);
        castle arrCastle[] = { {{95,96,97,98,14,99}, 6} };
        m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
        REQUIRE(compare_knight(&theKnight, 60, 1, 0, 40));
        REQUIRE(compare_report(m_report, 6, 1, 1));
        delete m_report;
    }
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
    }

    SECTION("DRAGONKNIGHT") {
        int nPetal = 12;
        set_knight(&theKnight, 12, 3, 0, 100);

        SECTION("Odin does not die") {
            castle arrCastle[] = { {{11,14,95,96,97,98,11,5,99}, 9} };
            m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
            REQUIRE(compare_knight(&theKnight, 12, 3, 0, 950));
            REQUIRE(compare_report(m_report, 3, 3, 0));
        }

        SECTION("Odin win hades") {
            castle arrCastle[] = { {{11,95,96,97,98,14,5,99}, 8} };
            m_report = game_main(theKnight, arrCastle, 1, mode, nPetal);
            REQUIRE(compare_knight(&theKnight, 12, 3, 0, 100));
            REQUIRE(compare_report(m_report, 4, 2, 1));
        }
    }
    delete m_report;
}
