#ifndef SERVER_SINK_HPP
#define SERVER_SINK_HPP

#include <memory>
#include <string>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#include <vector>
#include <utility>

#include "Queue.hpp"
#include "PendingQueries.hpp"

class ServerSink : public Queue {
   public:
    ServerSink(key_t key, const PendingQueries& pending_queries);
    virtual ~ServerSink();

    /** Creates queue */
    void init();

    /** Collects message
     *  this is one iteration of message colletion
     *  if no message is ready in this step nullptr is returned
     */
    std::unique_ptr<std::pair<Queue::MsgHeader, std::string>> recv();

    /** Sends message */
    void send(pid_t pid, const std::string& msg);

    /** Sends wakeup message */
    void sendWakeup(pid_t pid);

    /** Sends timeout message */
    void sendTimeout(pid_t pid);

    /** Sends parse error message */
    void sendParseError(pid_t pid);

   private:

    /** Destroys queue */
    void close();

    /** gets next header from queue
     *  blocks till header is received or the timeout is expired
     *  returns pointer to MsgHeader or nullptr if timeouted
     */
    std::unique_ptr<MsgHeader> rcvHeader();

    /** gets msg body
     *  doesn't block, returns null if there is no msg with type == pid
     */
    std::unique_ptr<std::string> rcvBody(pid_t pid, int size);

    /** waits for anything in queue
     *  return false if timeouted
     */
    bool checkQueue(unsigned timeout);

    /** SIGALRM handler */
    static void sig_alarm_handler(int signo);
    /** reference to pending querries, to get next timeout */
    const PendingQueries& pending_queries_;
    std::vector<MsgHeader> headers_;
    /**set in sig alarm handler */
    static volatile sig_atomic_t got_alarm_interrupt;
};

#endif
