#define BOOST_TEST_MODULE ParserTests

#include <boost/test/unit_test.hpp>
#include <HelperFuns.hpp>
#include "parser/Scanner.h"
#include "parser/Parser.h"



BOOST_AUTO_TEST_CASE(ParseSimpleOutput) {
    std::string in = "output 1, 2.0, \"mama\"";
    Parser parser;
    auto realOutputPtr = dynamic_unique_ptr_cast<Output>(parser.parse(in, 1, 1, 1));
    Tuple realTuple = realOutputPtr.get()->getTuple();
    Elements elements;
    elements.push_back(Element(1));
    elements.push_back(Element(float(2.0)));
    elements.push_back(Element("\"mama\""));
    Tuple expectedTuple(elements);
    BOOST_CHECK(expectedTuple == realTuple);
}

BOOST_AUTO_TEST_CASE(ParseSimpleOutputTwo) {
    std::string in = "output 6, 8.0, \"jacek-placek i janek,.\", 12";
    Parser parser;
    auto realOutputPtr = dynamic_unique_ptr_cast<Output>(parser.parse(in, 1, 1, 1));
    Tuple realTuple = realOutputPtr.get()->getTuple();
    Elements elements;
    elements.push_back(Element(6));
    elements.push_back(Element(float(8.0)));
    elements.push_back(Element("\"jacek-placek i janek,.\""));
    elements.push_back(Element(12));
    Tuple expectedTuple(elements);
    BOOST_CHECK(expectedTuple == realTuple);

}

BOOST_AUTO_TEST_CASE(ParseSimpleQuery) {
    std::string in = "input integer:=5, float :>2., string:=\"majka i jej pies reksio. lubimy jesc\"";
    Parser parser;
    auto realQueryPtr = dynamic_unique_ptr_cast<Query>(parser.parse(in, 1, 1, 1));
    Query realQuery = *realQueryPtr.get();
    BOOST_CHECK(!realQuery.isReadOnly());
    Elements elements;
    elements.push_back(Element(5));
    elements.push_back(Element(float(8.0)));
    elements.push_back(Element("\"majka i jej pies reksio. lubimy jesc\""));
    Tuple expectedTuple(elements);
    BOOST_CHECK(expectedTuple.isMatch(realQuery));
    elements.push_back(Element(1));
    Tuple differentTuple(elements);
    BOOST_CHECK(!differentTuple.isMatch(realQuery));

}

BOOST_AUTO_TEST_CASE(ParseTwoSimpleQueries) {
    std::string in = "read integer:*, float :>8., string:=\"majka lubi placki\", string:*";
    Parser parser;
    auto realQueryPtr = dynamic_unique_ptr_cast<Query>(parser.parse(in, 1, 2, 3));
    Query realQuery = *realQueryPtr.get();
    BOOST_CHECK(realQuery.isReadOnly());
    BOOST_CHECK(realQuery.getPid() == 3);
    BOOST_CHECK(realQuery.getEstimatedTimeout() == (1 + 2));

    Elements elements;
    elements.push_back(Element(1));
    elements.push_back(Element(float(7.0)));
    elements.push_back(Element("\"majka lubi placki\""));
    elements.push_back(Element("\"ha\""));
    Tuple differentTuple(elements);
    BOOST_CHECK(!differentTuple.isMatch(realQuery));
    elements[1] = Element(float(8.1));
    Tuple expectedTuple(elements);
    BOOST_CHECK(expectedTuple.isMatch(realQuery));

    std::string in2 = "input float:>5., string:*";
    auto realQueryPtr2 = dynamic_unique_ptr_cast<Query>(parser.parse(in2, 1, 1, 1));
    Elements elements2;
    elements2.push_back(Element(float(6.0)));
    elements2.push_back(Element("\"Ala ma kota\""));
    Tuple expectedTuple2(elements2);
    BOOST_CHECK(expectedTuple2.isMatch(*realQueryPtr2.get()));

}

bool is_parsing_error(std::domain_error const &ex) {
    return true;
}

BOOST_AUTO_TEST_CASE(ParseFails) {
    std::string in = "read integer:*, float :>8., string:*,";
    Parser parser;
    BOOST_CHECK_EXCEPTION(parser.parse(in, 1, 1, 1);, std::domain_error, is_parsing_error);

}
