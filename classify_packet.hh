#ifndef CLICK_CLASSIFY_PACKETS_HH
#define CLICK_CLASSIFY_PACKETS_HH
#include <string>
#include <vector>

struct hello_packet {

        uint8_t type;
        uint16_t src_address;
        uint8_t seq_num;
};

struct ack_packet {
        struct hello_packet hello;
        uint16_t dst_address;
};

struct data_packet {
        uint8_t type;
        uint16_t src_address;
        uint8_t seq_num;
        uint8_t k_value;
        uint16_t path1;
        uint16_t path2;
        uint16_t path3;
        uint16_t path4;
        uint16_t dst1_address;
        uint16_t dst2_address;
        uint16_t dst3_address;
        std::vector<int> data_path;
        std::string payload;
};
/* RREQ packet format */
struct rreq_packet {
                uint8_t type;
                uint16_t src_address;
                uint8_t seq_num;
                std::vector<int> RREQ_path;
                uint16_t dst_R1_address;
                uint16_t dst_R2_address;
                uint16_t dst_R3_address;
};
/* RREP packet format */
struct rrep_packet {
        uint8_t type;
        uint16_t src_address;
        uint8_t seq_num;
        std::vector<int> RREP_path;
        uint16_t dst_RREP_address;

};

#endif
