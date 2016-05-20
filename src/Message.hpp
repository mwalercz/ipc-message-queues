#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <ctime>
#include <set>
#include <vector>

#include "Element.hpp"
#include "Tuple.hpp"

typedef int Length;
typedef time_t Time;
typedef double TimeDuration;
typedef unsigned MsgPid;

class Output;
class Query;

class MessageVisitor {
    public:
        virtual void visit(Output&) = 0;
        virtual void visit(Query&) = 0;
};

class Message { // abstract class
    public:
        virtual ~Message() {};
        virtual void accept(MessageVisitor& v) = 0;

        bool isExpired() const;
        MsgPid getPid() const;
        Tuple::Type getType() const;
        Time getEstimatedTimeout() const;
        TimeDuration getLeftTimeout() const;
        bool compareTimes(Time l, Time r) const;
        friend bool operator<(const Message& lhs, const Message& rhs);

    private:
        MsgPid pid_;
        Time send_time_;
        TimeDuration timeout_;
        Tuple::Type type_;
};

class Output : public Message {
    public:
        Output(const Tuple& tuple);
        virtual ~Output() = default;
        virtual void accept(MessageVisitor& v);
        Tuple getTuple() const;
    private:
        Tuple tuple_;
};

class QueryPart {
   public:
    QueryPart(Length idx, const Element& reference_point,
              Element::Comparison expected);
      Length getIdx() const;
      bool isMatch(const Element& element) const;
   private:
       Length idx_; // element index in tuple
       Element reference_point_;
       Element::Comparison expected_;
};

class Query : public Message {
    public:
        typedef std::vector<QueryPart> QueryParts;

        Query();
        explicit Query(bool r);
        virtual ~Query() = default;
        virtual void accept(MessageVisitor& v);

        QueryParts getParts() const;
        bool isReadOnly() const;

    private:
        QueryParts parts_;
        bool read_only_;
};

class MessageSet {
    public:
        MessageSet();
        virtual ~MessageSet();

    private:
        std::set<Message> message_set_;
};

#endif /* MESSAGE_HPP */
