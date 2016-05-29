#define BOOST_TEST_MODULE ParserTests

#include <boost/test/unit_test.hpp>
#include <HelperFuns.hpp>
#include "parser/Scanner.h"
#include "parser/Parser.h"


BOOST_AUTO_TEST_CASE(ScannerSimpleTest) {
    std::string in = "o 1, 2, mama";
    std::stringstream input;
    std::stringstream output;
    input << in;
    Scanner scanner(input, output);
    scanner.lex();
    scanner.lex();
    scanner.lex();
    scanner.lex();
    std::string out;
    output >> out;
    std::cout << out;

}

BOOST_AUTO_TEST_CASE(ParserSimpleOutput) {
    std::string in = "output 1, 2.0, mama";
    Parser parser;
    auto realOutputPtr = dynamic_unique_ptr_cast<Output>(parser.parse(in, 1, 1, 1));
    Tuple realTuple = realOutputPtr.get()->getTuple();
    Elements elements;
    elements.push_back(Element(1));
    elements.push_back(Element(float(2.0)));
    elements.push_back(Element("mama"));
    Tuple expectedTuple(elements);
    BOOST_CHECK(expectedTuple == realTuple);
}

BOOST_AUTO_TEST_CASE(ParserSimpleOutputTwo) {
    std::string in = "output 6, 8.0, jacek, 12";
    Parser parser;
    auto realOutputPtr = dynamic_unique_ptr_cast<Output>(parser.parse(in, 1, 1, 1));
    Tuple realTuple = realOutputPtr.get()->getTuple();
    Elements elements;
    elements.push_back(Element(6));
    elements.push_back(Element(float(8.0)));
    elements.push_back(Element("jacek"));
    elements.push_back(Element(12));
    Tuple expectedTuple(elements);
    BOOST_CHECK(expectedTuple == realTuple);

}

BOOST_AUTO_TEST_CASE(ParserSimpleQuery) {
    std::string in = "input integer:=5, float :>2., string:=majka";
    Parser parser;
    auto realQueryPtr = dynamic_unique_ptr_cast<Query>(parser.parse(in, 1, 1, 1));
    Elements elements;
    elements.push_back(Element(5));
    elements.push_back(Element(float(8.0)));
    elements.push_back(Element("majka"));
    Tuple expectedTuple(elements);
    BOOST_CHECK(expectedTuple.isMatch(*realQueryPtr.get()));
    elements.push_back(Element(1));
    Tuple differentTuple(elements);
    BOOST_CHECK(!differentTuple.isMatch(*realQueryPtr.get()));

}

BOOST_AUTO_TEST_CASE(ParserSimpleQueryTwo) {
    std::string in = "read integer:*, float :>8., string:=majka, string:*";
    Parser parser;
    auto realQueryPtr = dynamic_unique_ptr_cast<Query>(parser.parse(in, 1, 1, 1));
    Elements elements;
    elements.push_back(Element(1));
    elements.push_back(Element(float(7.0)));
    elements.push_back(Element("majka"));
    elements.push_back(Element("ha"));
    Tuple expectedTuple(elements);
    BOOST_CHECK(!expectedTuple.isMatch(*realQueryPtr.get()));
//    elements.push_back(Element(1));
//    Tuple differentTuple(elements);
//    BOOST_CHECK(!differentTuple.isMatch(*realQueryPtr.get()));



}