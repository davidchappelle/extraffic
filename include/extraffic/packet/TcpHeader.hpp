#ifndef EXINDA_PACKET_TCP_HEADER_HPP
#define EXINDA_PACKET_TCP_HEADER_HPP


#include <cstddef>
#include <assert.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>


namespace extraffic
{
namespace packet
{


// This class provides a wrapper around an underlying C style definition
// of an tcp header. It helps simplify the overlay of the tcp header over
// top of packetized data buffers to facilitate in the extraction and
// modification of fields contained within the header.
class TcpHeader
{
    private:
        struct tcphdr* m_header;

    public:
        TcpHeader() :
            m_header(NULL)
        {
        }

        ~TcpHeader()
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

        inline struct tcphdr* header()
        {
            return m_header;
        }

        inline const struct tcphdr* header() const
        {
            return m_header;
        }

        inline uint16_t source_port() const
        {
            assert(m_header != NULL);
            return htons(m_header->source);
        }

        inline uint16_t destination_port() const
        {
            assert(m_header != NULL);
            return htons(m_header->dest);
        }

        inline uint32_t sequence_number() const
        {
            assert(m_header != NULL);
            return htonl(m_header->seq);
        }

        inline uint32_t acknowledgement_number() const
        {
            assert(m_header != NULL);
            return htonl(m_header->ack_seq);
        }

        inline uint8_t data_offset() const
        {
            assert(m_header != NULL);
            return m_header->doff;
        }

        inline uint8_t fin_flag() const
        {
            assert(m_header != NULL);
            return m_header->fin;
        }

        inline uint8_t syn_flag() const
        {
            assert(m_header != NULL);
            return m_header->syn;
        }

        inline uint8_t rst_flag() const
        {
            assert(m_header != NULL);
            return m_header->rst;
        }

        inline uint8_t psh_flag() const
        {
            assert(m_header != NULL);
            return m_header->psh;
        }

        inline uint8_t ack_flag() const
        {
            assert(m_header != NULL);
            return m_header->ack;
        }

        inline uint8_t urg_flag() const
        {
            assert(m_header != NULL);
            return m_header->urg;
        }

        inline uint16_t window_size() const
        {
            assert(m_header != NULL);
            return ntohs(m_header->window);
        }

        inline uint16_t checksum() const
        {
            assert(m_header != NULL);
            return ntohs(m_header->check);
        }

        inline uint16_t urgent_pointer() const
        {
            assert(m_header != NULL);
            return ntohs(m_header->urg_ptr);
        }
};


} // namespace packet
} // namespace extraffic


#endif // EXINDA_PACKET_TCP_HEADER_HPP
