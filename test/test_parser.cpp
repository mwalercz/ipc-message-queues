#define BOOST_TEST_MODULE ParserTests

#include <boost/test/unit_test.hpp>
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
    Message* msg_ptr = parser.parse(in, 1, 1, 1);
    Output * out_ptr = dynamic_cast<Output*>(msg_ptr);
    delete out_ptr;
//    BOOST_CHECK_EQUAL(result, 0);
}

BOOST_AUTO_TEST_CASE(ParserSimpleOutputTwo) {
    std::string in = "output 6, 8.0, jacek, 12";
    Parser parser;
    Message* msg_ptr = parser.parse(in, 1, 1, 1);
    Output * out_ptr = dynamic_cast<Output*>(msg_ptr);
    delete out_ptr;
//    BOOST_CHECK_EQUAL(result, 0);
}

BOOST_AUTO_TEST_CASE(ParserSimpleQuery) {
    std::string in = "input integer:=5, float :>2., string:=majka";
    Parser parser;
    Message* msg_ptr = parser.parse(in, 1, 1, 1);

    Query* query_ptr = dynamic_cast<Query*>(msg_ptr);
    delete query_ptr;

}

BOOST_AUTO_TEST_CASE(ParserSimpleQueryTwo) {
    std::string in = "read integer:*, float :>8., string:=majka, string:*";
    Parser parser;
    Message* msg_ptr = parser.parse(in, 1, 1, 1);

    Query* query_ptr = dynamic_cast<Query*>(msg_ptr);
    delete query_ptr;
//    BOOST_CHECK_EQUAL(parser.parse__(in), 0);

}