#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <iostream>

using namespace boost::interprocess;
namespace sc = boost::statechart;

// State machine states
struct Idle;
struct Processing;

// State machine events
struct RequestEvent : sc::event<RequestEvent> {
    std::string data;
};

struct ResponseEvent : sc::event<ResponseEvent> {
    std::string data;
};

// State machine definition
struct ServerStateMachine : sc::state_machine<ServerStateMachine, Idle> {
    std::string request_data;
    std::string response_data;
};

struct Idle : sc::simple_state<Idle, ServerStateMachine> {
    typedef sc::transition<RequestEvent, Processing> reactions;

    Idle() {
        std::cout << "Server is idle." << std::endl;
    }

    sc::result react(const RequestEvent& event) {
        context<ServerStateMachine>().request_data = event.data;
        return transit<Processing>();
    }
};

struct Processing : sc::simple_state<Processing, ServerStateMachine> {
    typedef sc::transition<ResponseEvent, Idle> reactions;

    Processing(const RequestEvent& event) {
        std::cout << "Processing request: " << event.data << std::endl;
        // Process the request and generate a response
        context<ServerStateMachine>().response_data = "Response to: " + event.data;
        ResponseEvent response_event;
        response_event.data = context<ServerStateMachine>().response_data;
        post_event(response_event);
    }

    Processing() {
        std::cout << "Processing request: " << context<ServerStateMachine>().request_data << std::endl;
        // Process the request and generate a response
        context<ServerStateMachine>().response_data = "Response to: " + context<ServerStateMachine>().request_data;
        post_event(ResponseEvent());
    }
};

int main() {
    BOOST_TRY {
        message_queue::remove("request_queue");
        message_queue::remove("response_queue");
        message_queue request_queue(create_only, "request_queue", 100, 1024);
        message_queue response_queue(create_only, "response_queue", 100, 1024);

        ServerStateMachine server;
        server.initiate();

        while (true) {
            // Receive request from the request queue
            char request[1024];
            size_t recvd_size;
            unsigned int priority;
            request_queue.receive(request, sizeof(request), recvd_size, priority);

            // Process the request using the state machine
            server.request_data = std::string(request, recvd_size);
            RequestEvent request_event;
            request_event.data = server.request_data;
            server.process_event(request_event);

            // Send response to the response queue
            std::string response = server.response_data;
            response_queue.send(response.data(), response.size(), 0);
        }
    }
    BOOST_CATCH (std::exception& e) {
        std::cerr << e.what() << std::endl;
    } BOOST_CATCH_END

    return 0;
}