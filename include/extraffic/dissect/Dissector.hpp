#ifndef EXTRAFFIC_DISSECT_DISSECTOR_HPP
#define EXTRAFFIC_DISSECT_DISSECTOR_HPP


#include <pcap.h>
#include <string>
#include <string.h>
#include <iostream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>


#include "extraffic/packet/Packet.hpp"
#include "extraffic/packet/IpHeader.hpp"
#include "extraffic/packet/UdpHeader.hpp"
#include "extraffic/packet/TcpHeader.hpp"
#include "extraffic/packet/EtherHeader.hpp"


namespace extraffic
{
namespace dissect
{


class Dissector
{
    private:
        Json::Value m_json_root;
        std::string m_capture_file_name;

    private:
        void dissect_packet(packet::Packet& packet)
        {
            Json::Value json_packet(Json::objectValue);

            json_packet["layer_2"] = dissect_layer_2(packet);
            json_packet["layer_3"] = dissect_layer_3(packet);
            json_packet["layer_4"] = dissect_layer_4(packet);
            //json_packet["payload"] = packet.payload();

            m_json_root.append(json_packet);
        }

        Json::Value dissect_layer_2(packet::Packet& packet)
        {
            Json::Value layer_2(Json::objectValue);
            packet::EtherHeader& ether_header = packet.ether_header();

            if (ether_header.is_valid())
            {
                layer_2["destination_ether_address"] =
                    ether_header.destination_ether_address_string();

                layer_2["source_ether_address"] =
                    ether_header.source_ether_address_string();

                layer_2["ether_type"] = ether_header.ether_type();
            }
            else
            {
                std::cerr << "ERROR: failed to parse the layer 2 header" << std::endl;
            }

            return layer_2;
        }

        Json::Value dissect_layer_3(packet::Packet& packet)
        {
            Json::Value layer_3(Json::objectValue);
            packet::IpHeader& ip_header = packet.ip_header();

            if (ip_header.is_valid())
            {
                layer_3["header_length"] = ip_header.header_length();
                layer_3["version"] = ip_header.version();
                layer_3["type_of_service"] = ip_header.type_of_service();
                layer_3["total_length"] = ip_header.total_length();
                layer_3["identifier"] = ip_header.identifier();
                layer_3["fragment_flags"] = ip_header.fragment_flags();
                layer_3["fragment_offset"] = ip_header.fragment_offset();
                layer_3["time_to_live"] = ip_header.time_to_live();
                layer_3["protocol"] = ip_header.protocol();
                layer_3["checksum"] = ip_header.checksum();
                layer_3["source_ip_address"] = ip_header.source_ip_address_string();
                layer_3["destination_ip_address"] = ip_header.destination_ip_address_string();
                layer_3["options"] = Json::Value(Json::arrayValue);
                // TODO: deal with ip options
            }
            else
            {
                std::cerr << "ERROR: failed to parse the layer 3 header" << std::endl;
            }

            return layer_3;
        }

        Json::Value dissect_layer_4(packet::Packet& packet)
        {
            Json::Value layer_4(Json::objectValue);
            packet::UdpHeader& udp_header = packet.udp_header();
            packet::TcpHeader& tcp_header = packet.tcp_header();

            if (udp_header.is_valid())
            {
                layer_4["source_port"] = udp_header.source_port();
                layer_4["destination_port"] = udp_header.destination_port();
                layer_4["length"] = udp_header.length();
                layer_4["checksum"] = udp_header.checksum();
            }
            else if (tcp_header.is_valid())
            {
                layer_4["source_port"] = tcp_header.source_port();
                layer_4["destination_port"] = tcp_header.destination_port();
                layer_4["sequence_number"] = tcp_header.sequence_number();
                layer_4["acknowledgement_number"] = tcp_header.acknowledgement_number();
                layer_4["data_offset"] = tcp_header.data_offset();
                layer_4["fin_flag"] = tcp_header.fin_flag();
                layer_4["syn_flag"] = tcp_header.syn_flag();
                layer_4["rst_flag"] = tcp_header.rst_flag();
                layer_4["psh_flag"] = tcp_header.psh_flag();
                layer_4["ack_flag"] = tcp_header.ack_flag();
                layer_4["urg_flag"] = tcp_header.urg_flag();
                layer_4["window_size"] = tcp_header.window_size();
                layer_4["checksum"] = tcp_header.checksum();
                layer_4["urgent_pointer"] = tcp_header.urgent_pointer();
                layer_4["options"] = Json::Value(Json::arrayValue);
                // TODO: deal with tcp options
            }
            else
            {
                std::cerr << "ERROR: failed to parse the layer 4 header" << std::endl;
            }

            return layer_4;
        }

    public:
        Dissector(const std::string& capture_file_name) :
            m_json_root(Json::arrayValue),
            m_capture_file_name(capture_file_name)
        {
        }

        ~Dissector()
        {
        }

        bool dissect()
        {
            char error_buffer[PCAP_ERRBUF_SIZE];
            pcap_t* pcap = pcap_open_offline(m_capture_file_name.c_str(), error_buffer);
            if(!pcap)
            {
                std::cerr << "ERROR: can't open " << m_capture_file_name << "(" << error_buffer << ")" << std::endl;
                printf("Can't open file '%s': %s\n",
                       m_capture_file_name.c_str(), error_buffer);
                return false;
            }

            int status;
            packet::Packet packet;
            const u_char* packet_buffer;
            struct pcap_pkthdr* packet_header;

            std::cerr << "Starting to dissect packets from " << m_capture_file_name << std::endl;
            while ((status = pcap_next_ex(pcap, &packet_header, &packet_buffer)) > 0)
            {
                std::cerr << "processing packet" << std::endl;
                char* buffer = new char[packet_header->len];
                memcpy(buffer, packet_buffer, packet_header->len);
                if (packet.overlay(buffer, packet_header->len))
                {
                    dissect_packet(packet);
                }
                else
                {
                    std::cerr << "failed to overlay packet!!!" << std::endl;
                }

                delete [] buffer;
            }
            std::cerr << "Finished dissecting packets" << std::endl;

            if (status == -1)
            {
                std::cerr << "ERROR: failed to read entire capture file" << std::endl;
            }
            else
            {
                std::cerr << "outputing json" << std::endl;
                Json::StyledWriter writer;
                std::cerr << writer.write(m_json_root) << std::endl;
            }

            return status == -2;
        }
};


} // namespace dissect
} // namespace extraffic


#endif // EXTRAFFIC_DISSECT_DISSECTOR_HPP
