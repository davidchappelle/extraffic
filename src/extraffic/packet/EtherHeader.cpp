#include "extraffic/packet/EtherHeader.hpp"


namespace extraffic
{
namespace packet
{


uint32_t EtherHeader::overlay(char* buffer, uint32_t length)
{
    if (is_valid())
    {
        reset();
    }

    if (length < sizeof(struct ether_header))
    {
        return 0;
    }

    // TODO: Add handling for vlan tagged ethernet packets
    m_header = reinterpret_cast<struct ether_header*>(buffer);
    return sizeof(struct ether_header);
}


} // namespace extraffic
} // namespace packet
