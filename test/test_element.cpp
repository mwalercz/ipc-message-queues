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
BOOST_AUTO_TEST_CASE( TestElementInt )
{
    int a = rand();
    Element i = Element(a);
    BOOST_CHECK_EQUAL( i.getType(), Element::Type::kInt );
    BOOST_CHECK_EQUAL( *i.getInt(), a );
    BOOST_CHECK( i.getFloat() == nullptr );
    BOOST_CHECK( i.getString() == nullptr );

}

BOOST_AUTO_TEST_CASE( TestElementFloat )
{
    float a = float(rand());
    Element e = Element(a);
    BOOST_CHECK_EQUAL( e.getType(), Element::Type::kFloat );
    BOOST_CHECK( e.getInt() == nullptr );
    BOOST_CHECK_EQUAL( *e.getFloat(), a );
    BOOST_CHECK( e.getString() == nullptr );
}

BOOST_AUTO_TEST_CASE( TestElementString )
{
    std::string a = "test";
    Element e = Element(a);
    BOOST_CHECK_EQUAL( e.getType(), Element::Type::kString );
    BOOST_CHECK( e.getInt() == nullptr );
    BOOST_CHECK( e.getFloat() == nullptr );
    BOOST_CHECK_EQUAL( *e.getString(), a );
}


BOOST_AUTO_TEST_CASE( TestElementCompareDiffTypes )
{
    std::string s = "test";
    int i = rand();
    Element a0 = Element(s);
    Element a1 = Element(i);
    BOOST_CHECK_THROW(a0.compare(a1), std::domain_error);
}

BOOST_AUTO_TEST_CASE( TestElementCompareStrings )
{
    std::string x = "x";
    std::string x_ = "x";
    std::string y = "y";
    Element a0 = Element(x);
    Element a1 = Element(x_);
    Element b = Element(y);
    // positive
    BOOST_CHECK(Element::fulfills(a0.compare(a0), Element::Comparison::kLowerOrEqual));
    BOOST_CHECK(Element::fulfills(a0.compare(a0), Element::Comparison::kEqual));
    BOOST_CHECK(Element::fulfills(a0.compare(a0), Element::Comparison::kGreaterOrEqual));

    BOOST_CHECK(Element::fulfills(a0.compare(a1), Element::Comparison::kLowerOrEqual));
    BOOST_CHECK(Element::fulfills(a0.compare(a1), Element::Comparison::kEqual));
    BOOST_CHECK(Element::fulfills(a0.compare(a1), Element::Comparison::kGreaterOrEqual));

    BOOST_CHECK(Element::fulfills(a0.compare(b), Element::Comparison::kLower));
    BOOST_CHECK(Element::fulfills(a0.compare(b), Element::Comparison::kLowerOrEqual));

    BOOST_CHECK(Element::fulfills(b.compare(a0), Element::Comparison::kGreater));
    BOOST_CHECK(Element::fulfills(b.compare(a0), Element::Comparison::kGreaterOrEqual));

    //negative
    BOOST_CHECK(!Element::fulfills(a0.compare(a0), Element::Comparison::kLower));
    BOOST_CHECK(!Element::fulfills(a0.compare(a0), Element::Comparison::kGreater));

    BOOST_CHECK(!Element::fulfills(a0.compare(a1), Element::Comparison::kLower));
    BOOST_CHECK(!Element::fulfills(a0.compare(a1), Element::Comparison::kGreater));

    BOOST_CHECK(!Element::fulfills(a0.compare(b), Element::Comparison::kEqual));
    BOOST_CHECK(!Element::fulfills(a0.compare(a1), Element::Comparison::kGreater));
    BOOST_CHECK(!Element::fulfills(a0.compare(b), Element::Comparison::kGreaterOrEqual));

    BOOST_CHECK(!Element::fulfills(b.compare(a0), Element::Comparison::kLowerOrEqual));
    BOOST_CHECK(!Element::fulfills(b.compare(a0), Element::Comparison::kLower));
    BOOST_CHECK(!Element::fulfills(b.compare(a0), Element::Comparison::kEqual));
}

BOOST_AUTO_TEST_CASE( TestElementCompareInts )
{
    int x = -5;
    int x_ = -5;
    int y = 3;
    Element a0 = Element(x);
    Element a1 = Element(x_);
    Element b = Element(y);
    // positive
    BOOST_CHECK(Element::fulfills(a0.compare(a0), Element::Comparison::kLowerOrEqual));
    BOOST_CHECK(Element::fulfills(a0.compare(a0), Element::Comparison::kEqual));
    BOOST_CHECK(Element::fulfills(a0.compare(a0), Element::Comparison::kGreaterOrEqual));

    BOOST_CHECK(Element::fulfills(a0.compare(a1), Element::Comparison::kLowerOrEqual));
    BOOST_CHECK(Element::fulfills(a0.compare(a1), Element::Comparison::kEqual));
    BOOST_CHECK(Element::fulfills(a0.compare(a1), Element::Comparison::kGreaterOrEqual));

    BOOST_CHECK(Element::fulfills(a0.compare(b), Element::Comparison::kLower));
    BOOST_CHECK(Element::fulfills(a0.compare(b), Element::Comparison::kLowerOrEqual));

    BOOST_CHECK(Element::fulfills(b.compare(a0), Element::Comparison::kGreater));
    BOOST_CHECK(Element::fulfills(b.compare(a0), Element::Comparison::kGreaterOrEqual));

    //negative
    BOOST_CHECK(!Element::fulfills(a0.compare(a0), Element::Comparison::kLower));
    BOOST_CHECK(!Element::fulfills(a0.compare(a0), Element::Comparison::kGreater));

    BOOST_CHECK(!Element::fulfills(a0.compare(a1), Element::Comparison::kLower));
    BOOST_CHECK(!Element::fulfills(a0.compare(a1), Element::Comparison::kGreater));

    BOOST_CHECK(!Element::fulfills(a0.compare(b), Element::Comparison::kEqual));
    BOOST_CHECK(!Element::fulfills(a0.compare(a1), Element::Comparison::kGreater));
    BOOST_CHECK(!Element::fulfills(a0.compare(b), Element::Comparison::kGreaterOrEqual));

    BOOST_CHECK(!Element::fulfills(b.compare(a0), Element::Comparison::kLowerOrEqual));
    BOOST_CHECK(!Element::fulfills(b.compare(a0), Element::Comparison::kLower));
    BOOST_CHECK(!Element::fulfills(b.compare(a0), Element::Comparison::kEqual));
}

BOOST_AUTO_TEST_CASE( TestElementCompareFloats )
{
    float x = -1.75;
    float x_ = -1.75;
    float y = 3.0;
    Element a0 = Element(x);
    Element a1 = Element(x_);
    Element b = Element(y);
    // positive
    BOOST_CHECK(Element::fulfills(a0.compare(a0), Element::Comparison::kLowerOrEqual));
    BOOST_CHECK(Element::fulfills(a0.compare(a0), Element::Comparison::kEqual));
    BOOST_CHECK(Element::fulfills(a0.compare(a0), Element::Comparison::kGreaterOrEqual));

    BOOST_CHECK(Element::fulfills(a0.compare(a1), Element::Comparison::kLowerOrEqual));
    BOOST_CHECK(Element::fulfills(a0.compare(a1), Element::Comparison::kEqual));
    BOOST_CHECK(Element::fulfills(a0.compare(a1), Element::Comparison::kGreaterOrEqual));

    BOOST_CHECK(Element::fulfills(a0.compare(b), Element::Comparison::kLower));
    BOOST_CHECK(Element::fulfills(a0.compare(b), Element::Comparison::kLowerOrEqual));

    BOOST_CHECK(Element::fulfills(b.compare(a0), Element::Comparison::kGreater));
    BOOST_CHECK(Element::fulfills(b.compare(a0), Element::Comparison::kGreaterOrEqual));

    //negative
    BOOST_CHECK(!Element::fulfills(a0.compare(a0), Element::Comparison::kLower));
    BOOST_CHECK(!Element::fulfills(a0.compare(a0), Element::Comparison::kGreater));

    BOOST_CHECK(!Element::fulfills(a0.compare(a1), Element::Comparison::kLower));
    BOOST_CHECK(!Element::fulfills(a0.compare(a1), Element::Comparison::kGreater));

    BOOST_CHECK(!Element::fulfills(a0.compare(b), Element::Comparison::kEqual));
    BOOST_CHECK(!Element::fulfills(a0.compare(a1), Element::Comparison::kGreater));
    BOOST_CHECK(!Element::fulfills(a0.compare(b), Element::Comparison::kGreaterOrEqual));

    BOOST_CHECK(!Element::fulfills(b.compare(a0), Element::Comparison::kLowerOrEqual));
    BOOST_CHECK(!Element::fulfills(b.compare(a0), Element::Comparison::kLower));
    BOOST_CHECK(!Element::fulfills(b.compare(a0), Element::Comparison::kEqual));
}

BOOST_AUTO_TEST_SUITE_END()
