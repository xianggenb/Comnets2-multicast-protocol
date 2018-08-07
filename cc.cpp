#include <click/error.hh>
#include <clicknet/ether.h>
#include <clicknet/ip.h>
#include <click/packet.hh>
#include "Routing_Map.hh"
#include <utility>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <stdlib.h>
CLICK_DECLS

Routing_Map::Routing_Map(){
std::vector<int> a;
std::vector<int> b;
std::vector<int> c;
path_table.insert(std::pair<int, int>(1,100));
path_table.insert(std::pair<int, int>(2,100));
path_table.insert(std::pair<int, int>(3,100));
routing_table.insert(std::pair<int,path>(1, a));
routing_table.insert(std::pair<int,path>(2, b));
routing_table.insert(std::pair<int,path>(3, c));
}
Routing_Map::~Routing_Map(){}

void Routing_Map::update_routing_table(int dest_num, path new_path){
routing_table[dest_num]=new_path;
click_chatter("dest %d path updated",dest_num);
}

void Routing_Map::update_length_table(int dest_num, int path_length,path new_path){

if(dest_num>3 || dest_num<1){
click_chatter("invalid destination");
}
else{
if(path_table[dest_num]>path_length){
path_table[dest_num]=path_length;
update_routing_table(dest_num, new_path);
click_chatter("path to %d | length change to %d",dest_num,path_length);
}
}
}

std::map<int, std::vector<int> > Routing_Map::get_map(int k){
int common_path_key=32;
if(k==1 ){
        result_table.insert(std::pair<int,path>(1,routing_table[1]));
}
else if (k==2){
 int dis_path_index=0;
 path common_path;
 path path1;
 path path2;
 path dis_path1;
 path dis_path2;
 path1=routing_table[1];
 path2=routing_table[2];
 int size=path1.size();
 for(int i=0;i<size;i++){
 if(path1[i]==path2[i]){
  common_path.push_back(path1[i]);
  dis_path_index=i+1;
}
 else{break;}
}
 for(int j=dis_path_index;j<path1.size();j++){
 dis_path1.push_back(path1[j]);
}
 for(int j=dis_path_index;j<path2.size();j++){
 dis_path2.push_back(path2[j]);
}
result_table.insert(std::pair<int, path>(1, dis_path1));
result_table.insert(std::pair<int, path>(2, dis_path2));
result_table.insert(std::pair<int, path>(common_path_key,common_path));
}
else if (k==3){
 int dis_path_index;
 path common_path;
 path path1;
 path path2;
 path path3;
 path dis_path1;
 path dis_path2;
 path dis_path3;
 path1=routing_table[1];
 path2=routing_table[2];
 path3=routing_table[3];
 for(int i=0;i<path1.size();i++){
 if(path1[i]==path2[i] && path2[i]==path3[i]){
  common_path.push_back(path1[i]);
  dis_path_index=i+1;
}
 else{break;}
}
 for(int j=dis_path_index;j<path1.size();j++){
 dis_path1.push_back(path1[j]);
}
 for(int j=dis_path_index;j<path2.size();j++){
 dis_path2.push_back(path2[j]);
}
  for(int j=dis_path_index;j<path3.size();j++){
 dis_path3.push_back(path3[j]);
}
result_table.insert(std::pair<int, path>(1, dis_path1));
result_table.insert(std::pair<int, path>(2, dis_path2));
result_table.insert(std::pair<int, path>(3, dis_path3));
result_table.insert(std::pair<int, path>(common_path_key,common_path));
}
return result_table;
}
void Routing_Map::info_trans(int dest_num,std::string string_path){
std::vector<int> path_trans;
int path_len=(int)string_path.length();
for(int i=0;i<path_len;i++){
path_trans.push_back((int)string_path[i]);
}
update_length_table(dest_num,path_len,path_trans);
}
CLICK_ENDDECLS
EXPORT_ELEMENT(Routing_Map)

