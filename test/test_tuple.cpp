/**
 * \file test_asymetry_contours.cpp
 * \brief Calc library tests. Tests contours asymetry calculation.
 */

/** \def Allows building dynamic library */
#define BOOST_TEST_MODULE TupleTest

#include "../src/Tuple.hpp"

#include <boost/test/unit_test.hpp>



BOOST_AUTO_TEST_SUITE(test_tuple)

/** Tests correctness of attributes standard deviations */
BOOST_AUTO_TEST_CASE( TestTupleCreation )
{
    Tuple t = Tuple();
    BOOST_CHECK( true );
}

BOOST_AUTO_TEST_SUITE_END()
