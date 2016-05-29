add_library(Parser Scanner.cpp Scanner.ih Scannerbase.h Scanner.h
        Parser.cpp Parser.ih Parserbase.h Parser.h
        ../Message.hpp ../Message.cpp
        ../Element.hpp ../Element.cpp
        ../Tuple.cpp ../Tuple.hpp)