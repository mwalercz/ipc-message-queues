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
//    scanner.lex();
//    scanner.lex();
//    scanner.lex();
//    scanner.lex();
    std::string out;
    output >> out;
    std::cout << out;

}

BOOST_AUTO_TEST_CASE(ParserSimpleInput) {
    std::string in = "input 1, 2, mama";
    Parser parser;
    int result = parser.parse__(in);
    BOOST_CHECK_EQUAL(result, 0);
}

BOOST_AUTO_TEST_CASE(ParserSimpleQuery) {
    std::string in = "read integer: *, float :>2. , string:=ma jka";
    Parser parser;
    BOOST_CHECK_EQUAL(parser.parse__(in), 0);
    BOOST_CHECK_EQUAL(parser.parse__(in), 0);

}