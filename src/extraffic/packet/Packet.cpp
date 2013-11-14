#include "extraffic/packet/Packet.hpp"


namespace extraffic
{
namespace packet
{


bool Packet::overlay(char* buffer, uint32_t length)
{
    uint32_t offset = 0;

    // If this is a successive attempt to overlay the packet
    // onto a buffer we need to first reset the state.
    if (is_valid())
    {
        reset();
    }

    uint32_t l2_header_length = overlay_l2_header(buffer, length);
    if (l2_header_length == 0)
    {
        //std::cerr << "ERROR: failed to overlay L2 header" << std::endl;
        // No accumulated state to cleanup at this point.
        return false;
    }
    offset += l2_header_length;

    // Packet is just an empty ethernet packet.
    if (offset < length)
    {
        uint32_t l3_header_length = overlay_l3_header(buffer + offset, length - offset);
        if (l3_header_length == 0)
        {
            //std::cerr << "ERROR: failed to overlay L3 header" << std::endl;
            // Cleanup all accumulated state so far.
            reset();
            return false;
        }
        offset += l3_header_length;

        // Packet is just an empty l3 packet.
        if (offset < length)
        {
            uint32_t l4_header_length = overlay_l4_header(
                buffer + offset, length - offset, m_ip_header.protocol());
            if (l4_header_length == 0)
            {
                //std::cerr << "ERROR: failed to overlay L4 header" << std::endl;
                // Cleanup all accumulated state so far.
                reset();
                return false;
            }
            offset += l4_header_length;
        }
    }

    assert(length >= offset);

    m_payload = buffer + offset;
    m_payload_length = length - offset;

    return true;
}


} // namespace extraffic
} // namespace packet
