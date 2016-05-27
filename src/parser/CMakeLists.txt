add_library(Parser lex.cc Scanner.ih Scannerbase.h Scanner.h
        parse.cc Parser.ih Parserbase.h Parser.h
        ../Message.cpp ../Message.hpp
        ../Element.hpp ../Element.cpp
        ../Tuple.cpp ../Tuple.hpp)