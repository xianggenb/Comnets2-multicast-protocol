# Comnets2 multicast protocol
1 Introduction
In computer networks, multicasting is sending data to multiple users in a single transmission.
The multiple recipients are usually part of a multicast group. The clients subscribe to a particular
multicast session and are given an ID. Clients with the same ID are part of a Multicast group.
1.1 Purpose
In this document, we detail a method to implement multicast to achieve best case delivery. That
is if the number of recipients are n, we try to deliver to a best destinations of k out of n. In our
case, we limited the number of destinations to 3 and k can take a value of 1,2 or 3, which is
provided by the user.
1.2 Definitions
1.2.1 Router
A Router is a network layer device which implements the routing protocols. It reads the
incoming packets for the destination address and then forwards them to the output port through
which the output port can be reached.
1.2.2 Node
In computer networks, the term “node” usually refers to general-purpose computers, like a
desktop workstation, a multiprocessor, or a PC. In our multicast context, a node can be either a
source or destination terminal.
1.2.3 Multi-casting
Multicasting is method of simultaneously transmitting to multiple users with only single
transmission.
1.2.4 Reliability
It is the quality of a transmission from origin to client. We define reliability in terms of errors in
a packet and delivery of the packet. A reliable network should successfully deliver the packet
from the origin without any errors in it.
1.2.5 Routing Table
Routing table is the data a router has that specifies the cost, next hop for a particular destination.
Routers using routing table to decide if they can reach a particular host and if they can, the next
destination it needs to forward the packet to.
A Routing table is built after routers in a network share their available routes with immediate
neighbours.
1.3 Assumptions
For the convenience of the implementation, we follow the following assumptions:
1. The maximum number of nodes in a network topology is small, e.g., 50.
2. Each node in the network can act as a source or client.
3. All the links in the network topology has the same characteristics, for example, the cost
of every link is 1, and the MTU is 1500 bytes.
4. Each end node is attached to only one routers.
5. Every link of the network has the same loss probability p = 0.2
2 BOOTSTRAP AND DISCOVERY
2.1 Addressing Scheme
● Using 16 digital address.
● Using 3 digital bits to identify routers in the same layer.
2.2 Procedure
When a new network element is added in, we give it a address based on its hierarchy. For
example, we add a new router which in the same class with R1. Then its address should be
010xxxxx.xxxxxxxx/(13). If we add a new D4 connect with R3, then it should 001 001 00.1 001
0010 when address of D1 is 001 001 00.1 001 0001.
In conclusion, we use 3 digital bits to identify routers in the same layer and leave last 4 digital bit
to identify hosts which means each single end router can connect to 16 hosts.
2.3 Packet Format
Type (Hello) Seq Num SRC addr
Type (Ack) Seq Num SRC addr Dest add
Type
(update)
Seq Num SRC addr Dest add Length Payload(routing table)
Type(data) SRC addr Seq Num Dest add 1 Dest add 2 Dest add 3 K Length Payload
3 ROUTING AND MULTICASTING
3.1 Algorithm and Routing
We make use of Distance Vector Routing
● For k=1 ; it will choose the path with the least cost and deliver the packet as normal
unicast routing
● For k=2 ; The router has multiple routes to the same destination i.e.it knows how to reach
D1 via R3, D2 via R5 and D3 via R7.
● This is helpful in deciding when the router has to split the packets.
● The router does not split the packet if there exists a common path for multiple
destinations
● For every split the k value in the header is updated.
● Assume that for same cost it selects the routers will the lowest router number
● Hence it can now reach D1 and D2 via R2, R3 and R5
● It reaches router R3 and then splits the packet since now there is no common path for the
packets.
● For k=3; Similarly, router will have multiple paths to every destination and hence for the
given example it will again split at R3 and R5 to reach all the 3 destinations
● For k=2; the router R3 will know that it has to split the packet if it wants to reach D1 and
D2.
● But to reach D2 and D3 it has a common path upto R6 and hence at R3 it will not split
but pass the packet to R5.
● For k=3; router R1 would have to split the packet if it wanted to reach D1 through R2.
But instead it routes through R3 and then splits to as to reach all the destinations and split
the packet only when its absolutely necessary.
4 Reliability Scheme
4.1 Procedure
Stop and Wait ARQ protocol will be implemented for our project.
Advantages for stop and wait:
1. It can be applied for noisy channel
2. Flow control and error control can be both achieved.
3. Timer implementation is included
Description:
1.Stop and wait ARQ sender sends one packages at a time
2. After sending each packages, sender will not send more packages until it receives an ACK
3. The receiver will send ACK after receive a good package
4. If ACK does not reach the sender in a certain time period(timeout), the sender send the
frame again
5. It can be regarded as a special case for sliding window protocol with both transmit and
receive window size equals to 1
Propagation Delay: Amount of time taken by a packet to make a physical journey from one
router to another router.
Propagation Delay = (Distance between routers) / (Velocity of propagation)
Round Trip Time ( RTT ) = 2* Propagation Delay
TimeOut = 2* RTT
Time To Live ( TTL ) = 2* TimeOut.
Graph view:
4.2 Estimated Efficiency
The Efficiency of Stop and Wait protocol is the channel utilization, which is the fraction
of the transmission capacity of a communication channel that contains data transmissions
The following pattern is repeated while transmitting
Based on the model above, we can come to a conclusion that:
Efficiency= t_data/(t_data+t_ack+2t_prop)
Assumption 1:
Supposed our modem have a data rate of transmission = 50kbps
The length of the link is 10km
The size of data package is 1k Bytes
Ignore the t_ack
Then we have the following :
t_data =8000 bits/50kbps=0.16sec
t_prop=10000/2*10^8m/s=5*10^-5s=50us
And the efficiency is around 0.16s/0.16s+2^0.5us=99.94%
Assumption 2:
Suppose we now have a high speed network with following features:
data rate of transmission like = 300Mbps
The length of the link is 10km
The size of data package is 1k Bytes
Ignore the t_ack
The new t_data=2.67*10^-5s=26.7us
Thus the efficiency now is 26.7/26.7+2*50=21.07%
Finally we come to a conclusion that the Stop and Wait has a good efficiency for low speed
links,but now good enough for high speed network
