#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include <clicknet/ether.h>
#include <clicknet/ip.h>
#include <click/packet.hh>
#include <iostream>
#include "forwarder.hh"
#include "classify_packet.hh"

#define HELLO_TYPE 1
#define ACKNOWLEDGMENT_TYPE 2
#define MULTICAST_DATA_TYPE 3
#define RREQ_TYPE 4
#define RREP_TYPE 5

CLICK_DECLS


Forwarder::Forwarder(){}
Forwarder::~Forwarder{}

int Forwarder::initialize(ErrorHandler *errh){
    return 0;
}

void Forwarder::push(int port, Packet *packet) {// push is only for assigning the values for data members private

        assert(packet);
       if(header->type ==1){
         struct hello_package *header=(struct hello_header* ) packet->data();
               click_chater("hello arrives");
               pass_hello(header->src_address);



       }
       else if (header->type == 2){
               struct ack_package *header=(struct ack_header* ) packet->data();
               click_chater("Ack arrives");
               pass_ack(header->dst_address);

        }
       else if (header->type == 3){
               struct data_package *header=(struct data_header* ) packet->data();
               click_chater("data arrives");
               pass_data(header->payload,header->data_path);

}

      else if(header->type == 4){
       struct rreq_package *header=(struct rreq_header* ) packet->data();
               click_chater("RReq arrives");
               pass_RREQ(header->src_address,header->dst_address,header->RREQ_path);

}
     else if (header->type==5){
       struct rrep_package *header=(struct rrep_header* ) packet->data();
               click_chater("rrep arrives");
               pass_ack(header->dst_address, header->src_address);
}
}

void Forwarder::pass_hello(uint8_t src_addr){
  output(0),push("hello");

}
void Forwarder::pass_ack(uint8_t dest_addr){
     if(dest_addr== current_addr){
     click_chatter("ACK received");
     packet->kill();
}
else(){
  output(0),push(packet);
}
}

void Forwarder::pass_data(uint8_t src_addr,std::string payload, std::vector data_path){

        header->dest_address= (uint8_t)data_path.pop_front();
        output(0),push(packet);
        std::cout<<payload<<endl;//check data content
        struct ack=new ack_packaget;
        ack->set_dest_addr(src_addr);
        output(0),push(ack)
        click-chatter("package to src sent");
        delete ack;
}

void Forwarder:: pass_RREQ(uint8_t src_addr, uint8_t dest_addr, std::vector<int>){

                        std:map<int, int> ports_table = get_port();
                        typedef std::map<int, int>::const_iterator MapIterator;
                        for (MapIterator iter = ports_table.begin(); iter != ports_table.end(); iter++) {
                                Packet *clone = packet->clone();
                                (clone->RREQ_path)->push_back(iter->second);
                                clone->cost = clone->cost + 1;
                                rreqJudge = 1;
                                output(0).push(clone);


}
}
void Forwarder:: pass_RREP(uint8_t dest_addr, uint8_t src_addr){

output(0),push(packet);

}

CLICK_ENDDECLS
EXPORT_ELEMENT(Forwarder)


