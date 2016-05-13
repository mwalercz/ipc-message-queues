#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include "Element.hpp"
#include <vector>
#include <map>
#include <ctime>

typedef int Length;
typedef long Types;
typedef std::map<std::pair<Length, Types>, Elements> Storage;
typedef time_t Time;
typedef double TimeDuration;

class Message { // abstract class
    // virtual ~Message() = delete;
};

class Insert : Message {
/* … */
};

class QueryPart : Message {
   public:
      bool isMatch(Element element) {
          return reference_point_.compare(element) == expected_;
      }
      Length getIdx();
      /* … */
   private:
       Length idx_; // element index in tuple
       Element reference_point_;
       Element::Comparison expected_;
      /* … */
};

class Query : Message {
    public:
        typedef std::vector<QueryPart> QueryParts;
        /* … */
        QueryParts getParts();

    private:
        int pid_;
        Time send_time_;
        TimeDuration timeout_;
        QueryParts parts_;
        /* … */
};

#endif /* ifndef MESSAGE_HPP */
