#ifndef EXINDA_PACKET_ETHER_HEADER_HPP
#define EXINDA_PACKET_ETHER_HEADER_HPP


#include <string>
#include <cstddef>
#include <stdint.h>
#include <assert.h>
#include <arpa/inet.h>
#include <net/ethernet.h>


#include "extraffic/common/EtherAddressStringify.hpp"


namespace extraffic
{
namespace packet
{


// This class provides a wrapper around an underlying C style definition
// of an ethernet header. It helps simplify the overlay of the ethernet
// header over top of packetized data buffers to facilitate in the
// extraction and modification of fields contained within the header.
class EtherHeader
{
    private:
        struct ether_header* m_header;

    public:
        EtherHeader() :
            m_header(NULL)
        {
        }

        ~EtherHeader()
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

        inline struct ether_header* header()
        {
            return m_header;
        }

        inline const struct ether_header* header() const
        {
            return m_header;
        }

        inline uint16_t ether_type() const
        {
            assert(m_header != NULL);
            return ntohs(m_header->ether_type);
        }

        inline struct ether_addr* source_ether_address()
        {
            assert(m_header != NULL);
            return reinterpret_cast<struct ether_addr*>(m_header->ether_shost);
        }

        inline const struct ether_addr* source_ether_address() const
        {
            assert(m_header != NULL);
            return reinterpret_cast<const struct ether_addr*>(m_header->ether_shost);
        }

        inline struct ether_addr* destination_ether_address()
        {
            assert(m_header != NULL);
            return reinterpret_cast<struct ether_addr*>(m_header->ether_dhost);
        }

        inline const struct ether_addr* destination_ether_address() const
        {
            assert(m_header != NULL);
            return reinterpret_cast<const struct ether_addr*>(m_header->ether_dhost);
        }

        inline const std::string source_ether_address_string() const
        {
            return std::string(
                common::EtherAddressStringify().to_string(source_ether_address()));
        }

        inline const std::string destination_ether_address_string() const
        {
            return std::string(
                common::EtherAddressStringify().to_string(destination_ether_address()));
        }
};


} // namespace packet
} // namespace extraffic


#endif // EXINDA_PACKET_ETHER_HEADER_HPP
