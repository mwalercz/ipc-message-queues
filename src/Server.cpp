#include "Server.hpp"

Server::Server() {
    //FIXME
}

Server::~Server() {
    //FIXME
}

// FIXME
void Server::serve() {
    /* while (1) {
        pending_queries.removeTimedoutQueries();//i.a. sends wakeup msgs to authors
        timeout = pending_queries.getNextTimeout();//shortest timeout in pending queries
        msg_part = channel_in.recv(timeout); // block if nothing in the channel
        if (!msg_part) { // woke up by timer
            continue;
        }
        process_msg_part(msg_part);
        if (any_msg_complete()) {
            parsed_msg = parse(getCompletedMessage());
            if (Now() - parsed_msg.getSendTime() > parsed_msg.getTimeout()) {
                channel_out.send_wakeup_msg(parsed_msg.getPid());
            } else if (parsed_msg.type == query) {
                result = find(parsed_msg);
                if ( result != null ) {
                    if (parsed_msg.type.rd != query_read_only) {
                        remove(parsed_msg);
                    }
                    channel_out.send(parsed_msg.getPid(), result);
                }
                else {
                    add_to_pending_queries(parsed_msg);
                }
            } else {  //parsed_msg.type == insert
                // remove timed out queries and try to match pending query
                found = iter_over_pending_queries(parsed_msg);
                if found {
                    channel_out.send(parsed_msg);
                } else {
                    insert(parsed_msg);
                }
            }
        }
    } */
}
