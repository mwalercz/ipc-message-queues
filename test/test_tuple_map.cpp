// somethign
#define BOOST_TEST_MODULE TupleMapTest

#include <boost/test/unit_test.hpp>
#include <boost/utility/binary.hpp>

#include <memory>

#include "../src/Tuple.hpp"
#include "../src/Message.hpp"
// because i can
#define private public
#include "../src/TupleMap.hpp"


BOOST_AUTO_TEST_SUITE(test_tuple_map)

BOOST_AUTO_TEST_CASE( TestTupleMapInsert )
{
    const std::vector<Tuple> tuples = {
        Tuple({{"qwerty"}, {"xyz"}, {"asd"}}),
        Tuple({{"a"}, {"b"}, {"c"}}),
        Tuple({{1}, {1.0f}, {3.1459f}}),
        Tuple({{1}, {2}, {3}}),
        Tuple({{1}, {2}, {3}}),
    };
    TupleMap tmap;
    for (auto tuple : tuples) {
        tmap.insert(tuple);
    }
    TupleMap::TypeMap expected = {
        { BOOST_BINARY_L(111111),
          { Tuple({{"qwerty"}, {"xyz"}, {"asd"}}), Tuple({{"a"}, {"b"}, {"c"}}) }
        },
        { BOOST_BINARY_L(011010),
          { Tuple({{1}, {1.0f}, {3.1459f}}) }
        },
        { BOOST_BINARY_L(010101),
          { Tuple({{1}, {2}, {3}}), Tuple({{1}, {2}, {3}})}
        },
    };
    BOOST_CHECK_EQUAL(tmap.type_map_.size(), expected.size());
    for (auto e : expected) {
        Tuple::Type type = e.first;
        auto it = tmap.type_map_.find(type);
        BOOST_REQUIRE( it != tmap.type_map_.end() );
        //  check only if size of vectors are equal
        BOOST_CHECK_EQUAL(it->second.size(), e.second.size());
    }
}

BOOST_AUTO_TEST_CASE( TestTupleMapFind )
{
    const std::vector<Tuple> tuples = {
        Tuple({{"qwerty"}, {"xyz"}, {"asd"}}),
        Tuple({{"a"}, {"b"}, {"c"}}),
        Tuple({{1}, {1.0f}, {3.1459f}}),
    };
    TupleMap tmap;
    for (auto tuple : tuples) {
        tmap.insert(tuple);
    }
    Query q0(1, 1, 1, BOOST_BINARY_L(111111));
    q0.appendPart(QueryPart(2, Element("baca"), Element::Comparison::kLower));
    Query q1(1, 1, 1, BOOST_BINARY_L(111111));
    q1.appendPart(QueryPart(1, Element("b"), Element::Comparison::kEqual));
    q1.appendPart(QueryPart(0, Element("a"), Element::Comparison::kEqual));
    Query q2(1, 1, 1, BOOST_BINARY_L(011010));
    q2.appendPart(QueryPart(0, Element(1), Element::Comparison::kEqual));
    q2.appendPart(QueryPart(1, Element(2.0f), Element::Comparison::kLower));
    q2.appendPart(QueryPart(2, Element(2.0f), Element::Comparison::kGreater));

    std::unique_ptr<Tuple> tuple = tmap.find(q0);
    BOOST_REQUIRE(tuple != nullptr);
    BOOST_CHECK(*tuple == tuples[0]);
    //deleting and checking againg
    tuple.release();
    tuple = tmap.find(q0);
    BOOST_REQUIRE(tuple != nullptr);
    BOOST_CHECK(*tuple == tuples[0]);

    tuple = tmap.find(q1);
    BOOST_REQUIRE(tuple != nullptr);
    BOOST_CHECK(*tuple == tuples[1]);
    tuple = tmap.find(q2);
    BOOST_REQUIRE(tuple != nullptr);
    BOOST_CHECK(*tuple == tuples[2]);
}

BOOST_AUTO_TEST_CASE( TestTupleMapFetch )
{
    const std::vector<Tuple> tuples = {
        Tuple({{"qwerty"}, {"xyz"}, {"asd"}}),
        Tuple({{"a"}, {"b"}, {"c"}}),
        Tuple({{1}, {1.0f}, {3.1459f}}),
    };
    TupleMap tmap;
    for (auto tuple : tuples) {
        tmap.insert(tuple);
    }
    Query q0(1, 1, 1, BOOST_BINARY_L(111111));
    q0.appendPart(QueryPart(2, Element("baca"), Element::Comparison::kLower));
    Query q1(1, 1, 1, BOOST_BINARY_L(111111));
    q1.appendPart(QueryPart(1, Element("b"), Element::Comparison::kEqual));
    q1.appendPart(QueryPart(0, Element("a"), Element::Comparison::kEqual));
    Query q2(1, 1, 1, BOOST_BINARY_L(011010));
    q2.appendPart(QueryPart(0, Element(1), Element::Comparison::kEqual));
    q2.appendPart(QueryPart(1, Element(2.0f), Element::Comparison::kLower));
    q2.appendPart(QueryPart(2, Element(2.0f), Element::Comparison::kGreater));

    std::unique_ptr<Tuple> tuple = tmap.fetch(q0);
    BOOST_REQUIRE(tuple != nullptr);
    BOOST_CHECK(*tuple == tuples[0]);
    //deleting result and checking again
    tuple.release();
    tuple = tmap.fetch(q0);
    BOOST_CHECK(tuple == nullptr);

    tuple = tmap.fetch(q1);
    BOOST_REQUIRE(tuple != nullptr);
    BOOST_CHECK(*tuple == tuples[1]);
    //deleting result and checking again
    tuple.release();
    tuple = tmap.fetch(q1);
    BOOST_CHECK(tuple == nullptr);

    tuple = tmap.fetch(q2);
    BOOST_REQUIRE(tuple != nullptr);
    BOOST_CHECK(*tuple == tuples[2]);
    //deleting result and checking again
    tuple.release();
    tuple = tmap.fetch(q2);
    BOOST_CHECK(tuple == nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
