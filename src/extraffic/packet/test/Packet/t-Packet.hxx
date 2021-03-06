#include <cxxtest/TestSuite.h>


#include "extraffic/packet/Packet.hpp"


using extraffic::packet::Packet;


namespace
{

char test_udp_packet_buffer[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd4, 0xbe, 
    0xd9, 0x9a, 0x76, 0x75, 0x08, 0x00, 0x45, 0x00, 
    0x00, 0x48, 0x2a, 0xac, 0x00, 0x00, 0x80, 0x11, 
    0xf5, 0x10, 0x0a, 0x02, 0x06, 0xe5, 0x0a, 0x02, 
    0xff, 0xff, 0xd1, 0x0f, 0xee, 0xbd, 0x00, 0x34, 
    0x78, 0x49, 0x57, 0x46, 0x42, 0x53, 0x2d, 0x53, 
    0x56, 0x43, 0x00, 0x00, 0x01, 0x09, 0x01, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
    0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x79, 0x8e, 
    0x70, 0x30, 0x3e, 0x7f, 0xc1, 0x03, 0x88, 0xcf, 
    0xa5, 0x04, 0xed, 0xb2, 0x76, 0x84
};

char test_tcp_packet_buffer[] = {
    0x00, 0xe0, 0xed, 0x19, 0x51, 0xa5, 0x5c, 0xf9, 
    0xdd, 0x77, 0xd2, 0xea, 0x08, 0x00, 0x45, 0x00, 
    0x02, 0x17, 0xc8, 0x1f, 0x40, 0x00, 0x40, 0x06, 
    0xdf, 0x3d, 0x0a, 0x02, 0x07, 0x0a, 0x9d, 0xa6, 
    0xe2, 0xd1, 0xc0, 0x09, 0x00, 0x50, 0x1a, 0x01, 
    0xc2, 0x95, 0x3b, 0x5c, 0x07, 0xb1, 0x80, 0x18, 
    0x00, 0x7b, 0x93, 0x8d, 0x00, 0x00, 0x01, 0x01, 
    0x08, 0x0a, 0x3d, 0xce, 0x71, 0x6d, 0xe7, 0xcd, 
    0x07, 0x59, 0x44, 0x3d, 0x31, 0x33, 0x38, 0x30, 
    0x37, 0x34, 0x38, 0x35, 0x33, 0x36, 0x37, 0x35, 
    0x38, 0x32, 0x39, 0x37, 0x34, 0x33, 0x30, 0x30, 
    0x31, 0x32, 0x37, 0x32, 0x33, 0x32, 0x26, 0x74, 
    0x69, 0x6c, 0x65, 0x3d, 0x38, 0x35, 0x38, 0x35, 
    0x33, 0x35, 0x38, 0x34, 0x37, 0x30, 0x38, 0x34, 
    0x33, 0x26, 0x64, 0x6f, 0x6d, 0x49, 0x64, 0x3d, 
    0x39, 0x30, 0x31, 0x39, 0x66, 0x39, 0x34, 0x64, 
    0x33, 0x39, 0x35, 0x61, 0x63, 0x37, 0x63, 0x34, 
    0x26, 0x6b, 0x78, 0x69, 0x64, 0x3d, 0x26, 0x6b, 
    0x78, 0x73, 0x65, 0x67, 0x3d, 0x0d, 0x0a, 0x41, 
    0x63, 0x63, 0x65, 0x70, 0x74, 0x2d, 0x45, 0x6e, 
    0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67, 0x3a, 0x20, 
    0x67, 0x7a, 0x69, 0x70, 0x2c, 0x64, 0x65, 0x66, 
    0x6c, 0x61, 0x74, 0x65, 0x2c, 0x73, 0x64, 0x63, 
    0x68, 0x0d, 0x0a, 0x41, 0x63, 0x63, 0x65, 0x70, 
    0x74, 0x2d, 0x4c, 0x61, 0x6e, 0x67, 0x75, 0x61, 
    0x67, 0x65, 0x3a, 0x20, 0x65, 0x6e, 0x2d, 0x55, 
    0x53, 0x2c, 0x65, 0x6e, 0x3b, 0x71, 0x3d, 0x30, 
    0x2e, 0x38, 0x0d, 0x0a, 0x43, 0x6f, 0x6f, 0x6b, 
    0x69, 0x65, 0x3a, 0x20, 0x6f, 0x70, 0x74, 0x69, 
    0x6d, 0x69, 0x7a, 0x65, 0x6c, 0x79, 0x53, 0x65, 
    0x67, 0x6d, 0x65, 0x6e, 0x74, 0x73, 0x3d, 0x25, 
    0x37, 0x42, 0x25, 0x32, 0x32, 0x31, 0x37, 0x30, 
    0x39, 0x36, 0x32, 0x33, 0x34, 0x30, 0x25, 0x32, 
    0x32, 0x25, 0x33, 0x41, 0x25, 0x32, 0x32, 0x66, 
    0x61, 0x6c, 0x73, 0x65, 0x25, 0x32, 0x32, 0x25, 
    0x32, 0x43, 0x25, 0x32, 0x32, 0x31, 0x37, 0x31, 
    0x36, 0x35, 0x37, 0x39, 0x36, 0x31, 0x25, 0x32, 
    0x32, 0x25, 0x33, 0x41, 0x25, 0x32, 0x32, 0x67, 
    0x63, 0x25, 0x32, 0x32, 0x25, 0x32, 0x43, 0x25, 
    0x32, 0x32, 0x31, 0x37, 0x32, 0x31, 0x34, 0x38, 
    0x36, 0x37, 0x39, 0x25, 0x32, 0x32, 0x25, 0x33, 
    0x41, 0x25, 0x32, 0x32, 0x6e, 0x6f, 0x6e, 0x65, 
    0x25, 0x32, 0x32, 0x25, 0x32, 0x43, 0x25, 0x32, 
    0x32, 0x31, 0x37, 0x32, 0x32, 0x36, 0x35, 0x33, 
    0x32, 0x39, 0x25, 0x32, 0x32, 0x25, 0x33, 0x41, 
    0x25, 0x32, 0x32, 0x64, 0x69, 0x72, 0x65, 0x63, 
    0x74, 0x25, 0x32, 0x32, 0x25, 0x37, 0x44, 0x3b, 
    0x20, 0x6f, 0x70, 0x74, 0x69, 0x6d, 0x69, 0x7a, 
    0x65, 0x6c, 0x79, 0x45, 0x6e, 0x64, 0x55, 0x73, 
    0x65, 0x72, 0x49, 0x64, 0x3d, 0x6f, 0x65, 0x75, 
    0x31, 0x33, 0x38, 0x30, 0x37, 0x34, 0x38, 0x35, 
    0x33, 0x36, 0x30, 0x37, 0x35, 0x72, 0x30, 0x2e, 
    0x37, 0x30, 0x32, 0x35, 0x34, 0x36, 0x35, 0x38, 
    0x32, 0x30, 0x39, 0x31, 0x35, 0x39, 0x39, 0x37, 
    0x3b, 0x20, 0x6f, 0x70, 0x74, 0x69, 0x6d, 0x69, 
    0x7a, 0x65, 0x6c, 0x79, 0x42, 0x75, 0x63, 0x6b, 
    0x65, 0x74, 0x73, 0x3d, 0x25, 0x37, 0x42, 0x25, 
    0x37, 0x44, 0x3b, 0x20, 0x53, 0x65, 0x6c, 0x65, 
    0x63, 0x74, 0x65, 0x64, 0x45, 0x64, 0x69, 0x74, 
    0x69, 0x6f, 0x6e, 0x3d, 0x77, 0x77, 0x77, 0x3b, 
    0x20, 0x73, 0x5f, 0x63, 0x63, 0x3d, 0x74, 0x72, 
    0x75, 0x65, 0x3b, 0x20, 0x73, 0x5f, 0x73, 0x71, 
    0x3d, 0x25, 0x35, 0x42, 0x25, 0x35, 0x42, 0x42, 
    0x25, 0x35, 0x44, 0x25, 0x35, 0x44, 0x3b, 0x20,
    0x6f, 0x70, 0x74, 0x69, 0x6d, 0x69, 0x7a, 0x65,
    0x6c, 0x79, 0x50, 0x65, 0x6e, 0x64, 0x69, 0x6e,
    0x67, 0x4c, 0x6f, 0x67, 0x45, 0x76, 0x65, 0x6e,
    0x74, 0x73, 0x3d, 0x25, 0x35, 0x42, 0x25, 0x35,
    0x44, 0x0d, 0x0a, 0x0d, 0x0a
};

} // namespace anonymous


class PacketTestSuite : public CxxTest::TestSuite
{
    public:
        void test_construction()
        {
            Packet packet;

            // Test that the internal state of the packet
            // is properly initialized.
            TS_ASSERT_EQUALS(packet.is_valid(), false);

            // Test that the underlying headers are also
            // properly initialized.
            TS_ASSERT_EQUALS(packet.ether_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.ip_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.udp_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.tcp_header().is_valid(), false);
        }

        void test_reset()
        {
            Packet packet;

            // Test that the internal state of the packet
            // is properly initialized.
            TS_ASSERT_EQUALS(packet.is_valid(), false);

            // Test that the underlying headers are also
            // properly initialized.
            TS_ASSERT_EQUALS(packet.ether_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.ip_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.udp_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.tcp_header().is_valid(), false);

            TS_ASSERT_EQUALS(packet.overlay(test_tcp_packet_buffer,
                                            sizeof(test_tcp_packet_buffer)), true);

            // Test that the underlying headers are also
            // properly initialized.
            TS_ASSERT_EQUALS(packet.ether_header().is_valid(), true);
            TS_ASSERT_EQUALS(packet.ip_header().is_valid(), true);
            TS_ASSERT_EQUALS(packet.udp_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.tcp_header().is_valid(), true);

            // Test that a reset restores the packet and underlying
            // headers to a default state.
            packet.reset();

            TS_ASSERT_EQUALS(packet.is_valid(), false);
            TS_ASSERT_EQUALS(packet.ether_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.ip_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.udp_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.tcp_header().is_valid(), false);
        }

        void test_overlay_udp()
        {
            Packet packet;

            TS_ASSERT_EQUALS(packet.overlay(test_udp_packet_buffer,
                                            sizeof(test_udp_packet_buffer)), true);

            // Test that the internal state of the packet
            // is properly initialized.
            TS_ASSERT_EQUALS(packet.is_valid(), true);

            // Test that the underlying headers are also
            // properly initialized.
            TS_ASSERT_EQUALS(packet.ether_header().is_valid(), true);
            TS_ASSERT_EQUALS(packet.ip_header().is_valid(), true);
            TS_ASSERT_EQUALS(packet.udp_header().is_valid(), true);
            TS_ASSERT_EQUALS(packet.tcp_header().is_valid(), false);
        }

        void test_overlay_tcp()
        {
            Packet packet;

            TS_ASSERT_EQUALS(packet.overlay(test_tcp_packet_buffer,
                             sizeof(test_tcp_packet_buffer)), true);

            // Test that the internal state of the packet
            // is properly initialized.
            TS_ASSERT_EQUALS(packet.is_valid(), true);

            // Test that the underlying headers are also
            // properly initialized.
            TS_ASSERT_EQUALS(packet.ether_header().is_valid(), true);
            TS_ASSERT_EQUALS(packet.ip_header().is_valid(), true);
            TS_ASSERT_EQUALS(packet.udp_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.tcp_header().is_valid(), true);
        }

        void test_double_overlay()
        {
            Packet packet;

            TS_ASSERT_EQUALS(packet.overlay(test_udp_packet_buffer,
                                            sizeof(test_udp_packet_buffer)), true);

            // Test that the internal state of the packet
            // is properly initialized.
            TS_ASSERT_EQUALS(packet.is_valid(), true);

            // Test that the underlying headers are also
            // properly initialized.
            TS_ASSERT_EQUALS(packet.ether_header().is_valid(), true);
            TS_ASSERT_EQUALS(packet.ip_header().is_valid(), true);
            TS_ASSERT_EQUALS(packet.udp_header().is_valid(), true);
            TS_ASSERT_EQUALS(packet.tcp_header().is_valid(), false);

            // Test now that overlaying the packet on top of
            // another buffer yields the expected result.
            TS_ASSERT_EQUALS(packet.overlay(test_tcp_packet_buffer,
                             sizeof(test_tcp_packet_buffer)), true);

            // Test that the internal state of the packet
            // is properly initialized.
            TS_ASSERT_EQUALS(packet.is_valid(), true);

            // Test that the underlying headers are also
            // properly initialized.
            TS_ASSERT_EQUALS(packet.ether_header().is_valid(), true);
            TS_ASSERT_EQUALS(packet.ip_header().is_valid(), true);
            TS_ASSERT_EQUALS(packet.udp_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.tcp_header().is_valid(), true);
        }

        void test_overlay_truncated_udp_buffer()
        {
            Packet packet;

            TS_ASSERT_EQUALS(packet.overlay(test_udp_packet_buffer,
                                            sizeof(test_udp_packet_buffer) - 1), false);

            // Test that the internal state of the packet is properly set to default
            // values (i.e. reset).
            TS_ASSERT_EQUALS(packet.is_valid(), false);
            TS_ASSERT_EQUALS(packet.ether_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.ip_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.udp_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.tcp_header().is_valid(), false);
        }

        void test_overlay_truncated_tcp_buffer()
        {
            Packet packet;

            TS_ASSERT_EQUALS(packet.overlay(test_tcp_packet_buffer,
                             sizeof(test_tcp_packet_buffer) - 1), false);

            // Test that the internal state of the packet is properly set to default
            // values (i.e. reset).
            TS_ASSERT_EQUALS(packet.is_valid(), false);
            TS_ASSERT_EQUALS(packet.ether_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.ip_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.udp_header().is_valid(), false);
            TS_ASSERT_EQUALS(packet.tcp_header().is_valid(), false);
        }
};
