#ifndef EXTRAFFIC_COMMON_ETHER_ADDRESS_STRINGIFY_HPP
#define EXTRAFFIC_COMMON_ETHER_ADDRESS_STRINGIFY_HPP


#include <net/ethernet.h>
#include <netinet/ether.h>


#include "extraffic/common/Stringify.hpp"


namespace extraffic
{
namespace common
{

// The ehternet address string length consists of 2 characters per octet
// plus 5 colons and a null terminator totalling 18 characters.
#define ETHER_ADDRSTRLEN ((ETHER_ADDR_LEN * 2) + 5 + 1)


// Converts an ethernet address from its binary hexadecimal form given in
// network byte order to a string in standard hex-digits-and-colons notation,
// omitting  leading  zeros. For example the ethernet address defined by:
//
//    struct ether_addr addr = { { 0x00, 0x09, 0xed, 0x19, 0x51, 0xa5} };
//
// is converted to the string:
//
//    "0:9:ed:19:51:a5"
//
// Note that the 0x00 is converted to a single digit in the string output.
class EtherAddressStringify : public Stringify<struct ether_addr, ETHER_ADDRSTRLEN>
{
    protected:
        virtual const char* stringify(const struct ether_addr* addr)
        {
            return ether_ntoa_r(addr, storage());
        }
};


} // namesapce common
} // namespace extraffic


#endif // EXTRAFFIC_COMMON_ETHER_ADDRESS_STRINGIFY_HPP
