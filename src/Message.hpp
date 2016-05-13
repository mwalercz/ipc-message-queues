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
      Length getIdx() const;
      bool isMatch(const Element& element) const;
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
        QueryParts getParts() const;

    private:
        int pid_;
        Time send_time_;
        TimeDuration timeout_;
        QueryParts parts_;
        /* … */
};

#endif /* ifndef MESSAGE_HPP */
