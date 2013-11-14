#include "extraffic/packet/IpHeader.hpp"


namespace extraffic
{
namespace packet
{


uint32_t IpHeader::overlay(char* buffer, uint32_t length)
{
    if (is_valid())
    {
        reset();
    }

    // Check first that we even have enough room to overlay the basic
    // ip header structure. We have to do this as a separate check before
    // extracting the ip header as we need to use a field in the header
    // to determine the true length.
    if (length < sizeof(struct iphdr))
    {
        return 0;
    }

    m_header = reinterpret_cast<struct iphdr*>(buffer);

    // Now check the true header length to ensure that there was in fact
    // enough room in the buffer.
    uint32_t header_length = m_header->ihl * 4;
    if (length < header_length)
    {
        return 0;
    }

    return header_length;
}


} // namespace extraffic
} // namespace packet
