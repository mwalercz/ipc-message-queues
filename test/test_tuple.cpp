// somethign
#define BOOST_TEST_MODULE TupleTest

#include <boost/test/unit_test.hpp>
#include <boost/utility/binary.hpp>

// because i can
#define private public

#include "../src/Tuple.hpp"
#include "../src/Message.hpp"


BOOST_AUTO_TEST_SUITE(test_tuple)

BOOST_AUTO_TEST_CASE( TestTupleCalcTypeTooLong )
{
    Elements es;
    for ( int i = 0; i < 40; ++i ) {
        es.push_back(Element(i));
    }
    BOOST_CHECK_THROW(Tuple::calculateType(es), std::domain_error);
}

BOOST_AUTO_TEST_CASE( TestTupleCalcType )
{
    Elements es1;
    es1.push_back(Element(int(1)));
    es1.push_back(Element(float(1)));
    es1.push_back(Element("a"));
    Tuple::Type type1 = BOOST_BINARY_L(011011);
    BOOST_CHECK_EQUAL(Tuple::calculateType(es1), type1);

    Elements es2;
    es2.push_back(Element(int(1)));
    es2.push_back(Element(int(1)));
    es2.push_back(Element("a"));
    Tuple::Type type2 = BOOST_BINARY_L(010111);
    BOOST_CHECK_EQUAL(Tuple::calculateType(es2), type2);

    Elements es3;
    es3.push_back(Element("z"));
    es3.push_back(Element("x"));
    es3.push_back(Element("a"));
    Tuple::Type type3 = BOOST_BINARY_L(111111);
    BOOST_CHECK_EQUAL(Tuple::calculateType(es3), type3);

    Elements es4;
    es4.push_back(Element(float(1)));
    es4.push_back(Element(float(0)));
    es4.push_back(Element(float(-1)));
    es4.push_back(Element(float(-0.5)));
    Tuple::Type type4 = BOOST_BINARY_L(10101010);
    BOOST_CHECK_EQUAL(Tuple::calculateType(es4), type4);
}

BOOST_AUTO_TEST_CASE( TestTupleIsMatch )
{
    Elements es3;
    es3.push_back(Element("z"));
    es3.push_back(Element("x"));
    es3.push_back(Element("a"));
    Tuple t = Tuple(es3);
    Query q(0, 0, 0, t.getType());
    q.appendPart(QueryPart(0, Element("z"), Element::Comparison::kEqual));
    BOOST_CHECK(t.isMatch(q));
}

BOOST_AUTO_TEST_CASE( TestTupleNoMatch )
{
    Elements es3;
    es3.push_back(Element("z"));
    es3.push_back(Element("x"));
    es3.push_back(Element("a"));
    Tuple t = Tuple(es3);
    Query q(0, 0, 0, t.getType());
    q.appendPart(QueryPart(0, Element("x"), Element::Comparison::kEqual));
    BOOST_CHECK(!t.isMatch(q));
}

BOOST_AUTO_TEST_CASE( TestTupleToString )
{
    Elements es1;
    es1.push_back(Element(int(1234)));
    es1.push_back(Element(float(1987.587646)));
    es1.push_back(Element("\"aasdklfj.,haskdfu!\""));
    Tuple t = Tuple(es1);
    BOOST_CHECK_EQUAL(t.toString(), "1234,1987.587646,\"aasdklfj.,haskdfu!\"");
}

BOOST_AUTO_TEST_SUITE_END()
