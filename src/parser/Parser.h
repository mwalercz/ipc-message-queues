// Generated by Bisonc++ V4.10.01 on Thu, 19 May 2016 00:43:22 +0200

#ifndef Parser_h_included
#define Parser_h_included

#include "Parserbase.h"
#include "Scanner.h"
#include "../Message.hpp"
#include "../Element.hpp"
#include "../Tuple.hpp"


#undef Parser

class Parser : public ParserBase {

public:
    Parser();
    std::unique_ptr<Message> parse(std::string input);

    int parse__(std::string input);
    std::unique_ptr<Message> result;



private:
    Scanner d_scanner;


    void switchStreams(std::istream &in, std::ostream &out);

    int parse();

    void error(char const *msg);

    int lex();

    void print();

    void executeAction(int ruleNr);

    void errorRecovery();

    int lookup(bool recovery);

    void nextToken();

    void print__();

    void exceptionHandler__(std::exception const &exc);
};


#endif
