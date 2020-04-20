#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

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

TEST_CASE( "Real HP are computed", "[realHP_calculator]" ) {
    REQUIRE( realHP_calculator(105, 0, 1, true) == 10 );
    REQUIRE( realHP_calculator(105, 1, 1, true) == 105 );
    REQUIRE( realHP_calculator(105, 2, 1, true) == 105 );
    REQUIRE( realHP_calculator(105, 3, 1, true) == 210 );

    REQUIRE( realHP_calculator(500, 3, 1, true) == 999 );
    REQUIRE( realHP_calculator(500, 3, 1, false) == 500 );
    REQUIRE_FALSE( realHP_calculator(100, 3, 1, true) == 300 );
}

TEST_CASE( "Final Result", "[prob_calculator_main]" ) {
    Catch::StringMaker<float>::precision = 2;
    // Normal rule when wp < 2
    REQUIRE( prob_calculator_main(450, 1, 150, 1, 302) == Approx(0.65f).epsilon(0.01));
    REQUIRE( prob_calculator_main(807, 0, 750, 1, 156) == Approx(0.16f).margin(0.01));
    REQUIRE( prob_calculator_main(417, 1, 416, 0, 417) == Approx(0.71f).epsilon(0.01));
    REQUIRE( prob_calculator_main(235, 1, 624, 0, 624) == Approx(0.58f).epsilon(0.01));
    REQUIRE( prob_calculator_main(998, 1, 517, 1, 998) == Approx(0.74f).epsilon(0.01));

    // wp = 2
    REQUIRE( prob_calculator_main(238, 2, 114, 1, 145) == Approx(0.56f).epsilon(0.01));
    REQUIRE( prob_calculator_main(738, 1, 45, 2, 26) == Approx(0.50f).epsilon(0.01));

    // wp == 3
    REQUIRE( prob_calculator_main(414, 1, 415, 3, 199) == Approx(0.50f).epsilon(0.01));
    REQUIRE( prob_calculator_main(221, 3, 600, 1, 221) == Approx(0.44f).epsilon(0.01));
    REQUIRE( prob_calculator_main(612, 3, 800, 1, 800) == Approx(0.56f).epsilon(0.01));
    REQUIRE( prob_calculator_main(189, 3, 517, 2, 444) == Approx(0.43f).epsilon(0.01));

    // King arthur
    REQUIRE( prob_calculator_main(999, 0, 800, 2, 444) == Approx(1).epsilon(0.01));
    REQUIRE( prob_calculator_main(998, 3, 888, 2, 444) == Approx(0.00f).epsilon(0.01));

    // Paladin
    REQUIRE( prob_calculator_main(31, 0, 880, 2, 444) == Approx(0.99f).epsilon(0.01));
    REQUIRE( prob_calculator_main(97, 3, 41, 1, 444) == Approx(0.99f).margin(0.01));
    REQUIRE( prob_calculator_main(998, 3, 41, 1, 444) == Approx(0.01f).margin(0.01));
    REQUIRE( prob_calculator_main(41, 3, 41, 1, 444) == Approx(0.05f).margin(0.01));
    REQUIRE( prob_calculator_main(41, 3, 97, 1, 444) == Approx(0.01f).margin(0.01));
    REQUIRE_FALSE( prob_calculator_main(25, 1, 886, 1, 444) == Approx(0.99f).margin(0.01));
    REQUIRE_FALSE( prob_calculator_main(800, 1, 25, 1, 444) == Approx(0.01f).margin(0.01));
}
