#ifndef CLICK_FORWARDER_HH
#define CLICK_FORWARDER_HH

#include <click/hashmap.hh>
#include <click/element.hh>
#include <click/timer.hh>
#include <vector>
#include <string>

CLICK_DECLS

class Forwarder: public Element {

    public:

        Forwarder();
        ~Forwarder();
        const char *class_name() const { return "Forwarder";}
        const char *port_count() const { return "-/-";}
        const char *processing() const { return PUSH; }

        void push(int port, Packet *packet);
        int initialize(ErrorHandler*);
        int configure(Vector<String>&, ErrorHandler*);
        void pass_hello(uint8_t src_addr);
        void pass_ack(uint8_t dest_addr);
        void pass_data(uint8_t src_addr,std::string payload,std::vector data_path);
        void pass_RREQ(uint8_t dest_addr,std::vector RREQ_path);
        void pass_RREP(uint8_t dest_addr, uint8_t src_addr)
    private:
        uint8_t current_addr;
        uint8_t source_addr;
        uint8_t dest_addr;
        int seq_num;
        std::string payload;
        std::vector RREQ_path;
        std::vector data_path;



};

CLICK_ENDDECLS
#endif

