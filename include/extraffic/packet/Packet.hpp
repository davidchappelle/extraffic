#ifndef EXTRAFFIC_PACKET_PACKET_HPP
#define EXTRAFFIC_PACKET_PACKET_HPP


#include <cstddef>
#include <assert.h>
#include <iostream>


#include "extraffic/packet/IpHeader.hpp"
#include "extraffic/packet/UdpHeader.hpp"
#include "extraffic/packet/TcpHeader.hpp"
#include "extraffic/packet/EtherHeader.hpp"


namespace extraffic
{
namespace packet
{


class Packet
{
    private:
        EtherHeader m_ether_header;
        IpHeader m_ip_header;
        UdpHeader m_udp_header;
        TcpHeader m_tcp_header;

        char* m_payload;
        uint32_t m_payload_length;

    private:
        inline uint32_t overlay_l2_header(char* buffer, uint32_t length)
        {
            uint32_t header_length = m_ether_header.overlay(buffer, length);

            if (header_length > 0)
            {
                if (m_ether_header.ether_type() != ETHERTYPE_IP)
                {
                    //std::cerr << "ERROR: unsupported ethertype: "
                    //          << m_ether_header.ether_type() << std::endl;
                    return 0;
                }
            }

            return header_length;
        }

        inline uint32_t overlay_l3_header(char* buffer, uint32_t length)
        {
            uint32_t header_length = m_ip_header.overlay(buffer, length);

            if (header_length > 0)
            {
                // Currently we only deal with TCP/UDP. In addition, we also
                // need to validate that the reported length in the ip header
                // matches the actual length.
                uint8_t protocol = m_ip_header.protocol();
                if ((protocol != IPPROTO_UDP) && (protocol != IPPROTO_TCP))
                {
                    //std::cerr << "ERROR: unsupported network protocol: "
                    //          << m_ip_header.protocol() << std::endl;
                    return 0;
                }
                else if (m_ip_header.total_length() != length)
                {
                    //std::cerr << "ERROR: detected malformed ip/buffer length" << std::endl;
                    //std::cerr << "        ip:" << m_ip_header.total_length() << std::endl;
                    //std::cerr << "    length:" << length << std::endl;
                    return 0;
                }
            }

            return header_length;
        }

        inline uint32_t overlay_l4_header(char* buffer, uint32_t length, uint8_t protocol)
        {
            uint32_t header_length = 0;

            if (protocol == IPPROTO_UDP)
            {
                header_length = m_udp_header.overlay(buffer, length);
                if (header_length > 0)
                {
                    if (m_udp_header.length() != length)
                    {
                        //std::cerr << "ERROR: detected malformed udp/buffer length" << std::endl;
                        return 0;
                    }
                }
            }
            else if (protocol == IPPROTO_TCP)
            {
                header_length = m_tcp_header.overlay(buffer, length);
                if (header_length > 0)
                {
                    // Determine what the expected length of the tcp header and
                    // payload is so that we can validate it.
                    uint32_t expected_length = m_ip_header.total_length() -
                                               (m_ip_header.header_length() * 4);

                    // Now validate that the expected length mathces the actual.
                    if (expected_length != length)
                    {
                        //std::cerr << "ERROR: detected malformed tcp/buffer length" << std::endl;
                        return 0;
                    }
                }
            }
            else
            {
                //std::cerr << "ERROR: unsupported network protocol: "
                //          << protocol << std::endl;
                return 0;
            }

            return header_length;
        }

    public:
        Packet() :
            m_payload(NULL),
            m_payload_length(0)
        {
        }

        ~Packet()
        {
        }

        inline bool is_valid() const
        {
            return m_payload != NULL;
        }

        inline void reset()
        {
            m_ether_header.reset();
            m_ip_header.reset();
            m_udp_header.reset();
            m_tcp_header.reset();

            m_payload = NULL;
            m_payload_length = 0;
        }

        bool overlay(char* buffer, uint32_t length);

        inline EtherHeader& ether_header()
        {
            return m_ether_header;
        }

        inline const EtherHeader& ether_header() const
        {
            return m_ether_header;
        }

        inline IpHeader& ip_header()
        {
            return m_ip_header;
        }

        inline const IpHeader& ip_header() const
        {
            return m_ip_header;
        }

        inline UdpHeader& udp_header()
        {
            return m_udp_header;
        }

        inline const UdpHeader& udp_header() const
        {
            return m_udp_header;
        }

        inline TcpHeader& tcp_header()
        {
            return m_tcp_header;
        }

        inline const TcpHeader& tcp_header() const
        {
            return m_tcp_header;
        }
};


} // namespace packet
} // namespace extraffic


#endif // EXTRAFFIC_PACKET_PACKET_HPP
