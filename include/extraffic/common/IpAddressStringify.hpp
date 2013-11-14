#ifndef EXTRAFFIC_COMMON_IP_ADDRESS_STRINGIFY_HPP
#define EXTRAFFIC_COMMON_IP_ADDRESS_STRINGIFY_HPP


#include </usr/include/netinet/in.h>


#include "extraffic/common/Stringify.hpp"


namespace extraffic
{
namespace common
{


// Converts an ip address from its integer form given in network
// byte order to a string in standard dotted decimal notation
// in host network order. For example the ip address defined by:
//
//     3769149608 (0xE0A8A8A8)
//
// is converted to the string:
//
//    "224.168.168.168"
//
// Note that the 0x00 is converted to a single digit in the string output.
class IpAddressStringify : public Stringify<struct in_addr, INET_ADDRSTRLEN>
{
    protected:
        virtual const char* stringify(const struct in_addr* addr)
        {
            return inet_ntop(AF_INET, addr, storage(), storage_size());
        }
};


} // namesapce common
} // namespace extraffic


#endif // EXTRAFFIC_COMMON_IP_ADDRESS_STRINGIFY_HPP
