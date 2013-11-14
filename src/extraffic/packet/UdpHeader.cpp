#include "extraffic/packet/UdpHeader.hpp"


namespace extraffic
{
namespace packet
{


uint32_t UdpHeader::overlay(char* buffer, uint32_t length)
{
    if (is_valid())
    {
        reset();
    }

    if (length < sizeof(struct udphdr))
    {
        return 0;
    }

    m_header = reinterpret_cast<struct udphdr*>(buffer);
    return sizeof(struct udphdr);
}


} // namespace extraffic
} // namespace packet
