#ifndef EXINDA_PACKET_IP_HEADER_HPP
#define EXINDA_PACKET_IP_HEADER_HPP


#include <string>
#include <cstddef>
#include <assert.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <netinet/ip.h>


#include "extraffic/common/IpAddressStringify.hpp"


namespace extraffic
{
namespace packet
{


// This class provides a wrapper around an underlying C style definition
// of an ip header. It helps simplify the overlay of the ip header over
// top of packetized data buffers to facilitate in the extraction and
// modification of fields contained within the header.
class IpHeader
{
    private:
        struct iphdr* m_header;

    public:
        IpHeader() :
            m_header(NULL)
        {
        }

        ~IpHeader()
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

        inline struct iphdr* header()
        {
            return m_header;
        }

        inline const struct iphdr* header() const
        {
            return m_header;
        }

        inline uint8_t header_length() const
        {
            assert(m_header != NULL);
            return m_header->ihl;
        }

        inline uint8_t version() const
        {
            assert(m_header != NULL);
            return m_header->version;
        }

        inline uint8_t type_of_service() const
        {
            assert(m_header != NULL);
            return m_header->tos;
        }

        inline uint16_t total_length() const
        {
            assert(m_header != NULL);
            return ntohs(m_header->tot_len);
        }

        inline uint16_t identifier() const
        {
            assert(m_header != NULL);
            return ntohs(m_header->id);
        }

        inline uint16_t fragment_flags() const
        {
            assert(m_header != NULL);
            return ntohs(m_header->frag_off) & (IP_RF | IP_DF | IP_MF);
        }

        inline uint16_t fragment_offset() const
        {
            assert(m_header != NULL);
            //return ntohs(m_header->frag_off) & IP_OFFMASK;
            return ntohs(m_header->frag_off) & IP_OFFMASK;
        }

        inline uint8_t time_to_live() const
        {
            assert(m_header != NULL);
            return m_header->ttl;
        }

        inline uint8_t protocol() const
        {
            assert(m_header != NULL);
            return m_header->protocol;
        }

        inline uint16_t checksum() const
        {
            assert(m_header != NULL);
            return ntohs(m_header->check);
        }

        inline uint32_t source_ip_address() const
        {
            assert(m_header != NULL);
            return ntohl(m_header->saddr);
        }

        inline uint32_t destination_ip_address() const
        {
            assert(m_header != NULL);
            return ntohl(m_header->daddr);
        }

        inline std::string source_ip_address_string() const
        {
            assert(m_header != NULL);
            struct in_addr addr;
            addr.s_addr = m_header->saddr;
            return std::string(
                common::IpAddressStringify().to_string(addr));
        }

        inline std::string destination_ip_address_string() const
        {
            assert(m_header != NULL);
            struct in_addr addr;
            addr.s_addr = m_header->daddr;
            return std::string(
                common::IpAddressStringify().to_string(addr));
        }
};


} // namespace packet
} // namespace extraffic


#endif // EXINDA_PACKET_IP_HEADER_HPP
