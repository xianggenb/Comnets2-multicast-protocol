 #ifndef ROUTING_MAP_HH
#define ROUTING_MAP_HH

#include <algorithm>
#include <utility>
#include <set>
#include <map>
#include <click/element.hh>
#include <click/timer.hh>
#include <vector>
#include <string>
#include <cstring>
#include <stdlib.h>
CLICK_DECLS
 class Routing_Map : public Element{
public:
        Routing_Map();
        ~Routing_Map();

        const char *class_name() const { return "routing_map";}
        const char *port_count() const { return "-/-"; }
        const char *processing() const { return PUSH; }

        //int configure(Vector<String>&, ErrorHandler*);
        //int initialize(ErrorHandler*);

        typedef std::map<int, int> length_type;
        typedef std::vector<int> path;
        typedef std::map<int,std::vector<int> > routing_type;
        void update_length_table(int dest_num, int path_length, path new_path);
        void update_routing_table(int dest_num, path new_path);
        std::map <int, std::vector<int> > get_map(int k);
        void info_trans(int dest_num,std::string string_path);
private:
        length_type path_table;
        routing_type routing_table;
        routing_type result_table;
};
CLICK_ENDDECLS
#endif

