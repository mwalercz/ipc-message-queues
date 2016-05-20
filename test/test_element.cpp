/**
 * \file test_asymetry_contours.cpp
 * \brief Calc library tests. Tests contours asymetry calculation.
 */

/** \def Allows building dynamic library */
#define BOOST_TEST_MODULE ElementTest

#include "../src/Element.hpp"

#include <boost/test/unit_test.hpp>



BOOST_AUTO_TEST_SUITE(test_element)

/** Tests correctness of attributes standard deviations */
BOOST_AUTO_TEST_CASE( TestElementCreation )
{
    int a = rand();
    Element i = Element(a);
    BOOST_CHECK( i.getType() == Element::Type::Int );

    float b = float(rand());
    Element f = Element(b);
    BOOST_CHECK( f.getType() == Element::Type::Float );
}

BOOST_AUTO_TEST_SUITE_END()
