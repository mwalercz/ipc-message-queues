#ifndef SERVER_SINK_HPP
#define SERVER_SINK_HPP
#include <memory>
#include <string>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <vector>

#include "Queue.hpp"
#include "PendingQueries.hpp"


class ServerSink : public Queue {
   public:
    ServerSink(key_t key, const PendingQueries& pending_queries)
        : Queue(key), pending_queries_(pending_queries) {}

    /** Collects message */
    std::unique_ptr<std::string> recv();

   private:
    /** gets next header from queue
     *  blocks till header is received or the timeout is expired
     *  returns pointer to MsgHeader or nullptr if timeouted
     */
    std::unique_ptr<MsgHeader> rcvHeader(unsigned timeout);

    /** gets msg body
     *  doesn't block, returns null if there is no msg with type == pid
     */
    std::unique_ptr<MsgBody> rcvBody(pid_t pid, int size);

    /** reference to pending querries, to get next timeout */
    const PendingQueries& pending_queries_;
    std::vector<MsgHeader> headers_;

};

#endif
