#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "Element.hpp"

#include <vector>
#include <map>
#include <ctime>
#include <set>

typedef int Length;
typedef long Types;
typedef time_t Time;
typedef double TimeDuration;
typedef unsigned MsgPid;

class Message { // abstract class
    public:
        enum Type {
            kQuery,
            kOutput,
            kInvalid,
        };

        virtual ~Message() = 0;

        bool isExpired() const;
        MsgPid getPid() const;
        Type getType() const;

    private:
        MsgPid pid_;
        Time send_time_;
        TimeDuration timeout_;
        Type type_;
};

class Output : public Message {
/* … */
};

class QueryPart : public Message {
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

class Query : public Message {
    public:
        typedef std::vector<QueryPart> QueryParts;
        Query();
        explicit Query(bool r);
        /* … */
        QueryParts getParts() const;
        bool isReadOnly() const;

    private:
        QueryParts parts_;
        bool read_only_;
        /* … */
};

class MessageSet {
    public:
        MessageSet();
        virtual ~MessageSet();

    private:
        std::set<Message> message_set_;
};

#endif /* MESSAGE_HPP */
