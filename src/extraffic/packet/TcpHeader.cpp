#include "extraffic/packet/TcpHeader.hpp"


namespace extraffic
{
namespace packet
{


uint32_t TcpHeader::overlay(char* buffer, uint32_t length)
{
    if (is_valid())
    {
        reset();
    }

    // Check first that we even have enough room to overlay the basic
    // tcp header structure. We have to do this as a separate check before
    // extracting the tcp header as we need to use a field in the header
    // to determine the true length.
    if (length < sizeof(struct tcphdr))
    {
        return 0;
    }

    m_header = reinterpret_cast<struct tcphdr*>(buffer);

    // Now check the true header length to ensure that there was in fact
    // enough room in the buffer.
    uint32_t header_length = m_header->doff * 4;
    if (length < header_length)
    {
        return 0;
    }

    return header_length;
}


} // namespace extraffic
} // namespace packet
