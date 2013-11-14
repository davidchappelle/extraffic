#ifndef EXINDA_PACKET_UDP_HEADER_HPP
#define EXINDA_PACKET_UDP_HEADER_HPP


#include <cstddef>
#include <assert.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <netinet/udp.h>


namespace extraffic
{
namespace packet
{


// This class provides a wrapper around an underlying C style definition
// of an udp header. It helps simplify the overlay of the udp header over
// top of packetized data buffers to facilitate in the extraction and
// modification of fields contained within the header.
class UdpHeader
{
    private:
        struct udphdr* m_header;

    public:
        UdpHeader() :
            m_header(NULL)
        {
        }

        ~UdpHeader()
        {
        }

        inline bool is_valid() const
        {
            return m_header != NULL;
        }

        inline void reset()
        {
            m_header = NULL;
        }

        uint32_t overlay(char* buffer, uint32_t length);

        inline struct udphdr* header()
        {
            return m_header;
        }

        inline const struct udphdr* header() const
        {
            return m_header;
        }

        inline uint16_t source_port() const
        {
            assert(m_header != NULL);
            return ntohs(m_header->source);
        }

        inline uint16_t destination_port() const
        {
            assert(m_header != NULL);
            return ntohs(m_header->dest);
        }

        inline uint16_t length() const
        {
            assert(m_header != NULL);
            return ntohs(m_header->len);
        }

        inline uint16_t checksum() const
        {
            assert(m_header != NULL);
            return ntohs(m_header->check);
        }
};


} // namespace packet
} // namespace extraffic


#endif // EXINDA_PACKET_UDP_HEADER_HPP
