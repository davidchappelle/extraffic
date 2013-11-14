#include <cxxtest/TestSuite.h>


#include "extraffic/packet/TcpHeader.hpp"


using extraffic::packet::TcpHeader;


namespace
{

char test_tcp_header_buffer_1[] = {
    0x00, 0x16, 0xe8, 0x61,
    0x19, 0xce, 0x5e, 0x83,
    0x7e, 0x15, 0x8b, 0x53,
    0x50, 0x10, 0x03, 0xfc,
    0x6f, 0xbb, 0x00, 0x00
};

char test_tcp_header_buffer_2[] = {
    0xe8, 0x61, 0x00, 0x16,
    0x7e, 0x15, 0x8b, 0x53,
    0x19, 0xce, 0x5e, 0x84,
    0x50, 0x10, 0x01, 0xf5,
    0x24, 0xa0, 0x00, 0x00
};

} // namespace anonymous


class TcpHeaderTestSuite : public CxxTest::TestSuite
{
    public:
        void test_construction()
        {
            TcpHeader tcp_header;

            // Test that the internal state of the ip header is properly initialized.
            TS_ASSERT_EQUALS(tcp_header.is_valid(), false);
            TS_ASSERT_EQUALS(tcp_header.header(), (struct tcphdr*)NULL);
        }

        void test_reset()
        {
            TcpHeader tcp_header;

            // Test the first overlay.
            uint32_t offset = tcp_header.overlay(test_tcp_header_buffer_1,
                                                 sizeof(test_tcp_header_buffer_1));

            // Test that the offset to the end of the ip header is correct.
            TS_ASSERT_EQUALS(offset, sizeof(test_tcp_header_buffer_1));

            // Test that the internal state of the ip header is properly initialized.
            TS_ASSERT_EQUALS(tcp_header.is_valid(), true);
            TS_ASSERT_DIFFERS(tcp_header.header(), (struct tcphdr*)NULL);

            // Test that we can reset the ethernet header to its default state.
            tcp_header.reset();

            TS_ASSERT_EQUALS(tcp_header.is_valid(), false);
            TS_ASSERT_EQUALS(tcp_header.header(), (struct tcphdr*)NULL);
        }

        void test_overlay()
        {
            TcpHeader tcp_header;

            // Test the first overlay.
            uint32_t offset = tcp_header.overlay(test_tcp_header_buffer_1,
                                                 sizeof(test_tcp_header_buffer_1));

            // Test that the offset to the end of the ip header is correct.
            TS_ASSERT_EQUALS(offset, sizeof(test_tcp_header_buffer_1));

            // Test that the internal state of the ip header is properly initialized.
            TS_ASSERT_EQUALS(tcp_header.is_valid(), true);
            TS_ASSERT_DIFFERS(tcp_header.header(), (struct tcphdr*)NULL);

            // Test that the ip header is correctly overlayed onto the test ip header
            // based on the contents.
            TS_ASSERT_EQUALS(tcp_header.source_port(), 0x0016);
            TS_ASSERT_EQUALS(tcp_header.destination_port(), 0xe861);
            TS_ASSERT_EQUALS(tcp_header.sequence_number(), 0x19ce5e83);
            TS_ASSERT_EQUALS(tcp_header.acknowledgement_number(), 0x7e158b53);
            TS_ASSERT_EQUALS(tcp_header.data_offset(), 0x5);
            TS_ASSERT_EQUALS(tcp_header.fin_flag(), 0x0);
            TS_ASSERT_EQUALS(tcp_header.syn_flag(), 0x0);
            TS_ASSERT_EQUALS(tcp_header.rst_flag(), 0x0);
            TS_ASSERT_EQUALS(tcp_header.psh_flag(), 0x0);
            TS_ASSERT_EQUALS(tcp_header.ack_flag(), 0x1);
            TS_ASSERT_EQUALS(tcp_header.urg_flag(), 0x0);
            TS_ASSERT_EQUALS(tcp_header.window_size(), 0x03fc);
            TS_ASSERT_EQUALS(tcp_header.checksum(), 0x6fbb);
            TS_ASSERT_EQUALS(tcp_header.urgent_pointer(), 0x0000);

            // Test the second overlay.
            offset = tcp_header.overlay(test_tcp_header_buffer_2,
                                        sizeof(test_tcp_header_buffer_2));

            // Test that the offset to the end of the ip header is correct.
            TS_ASSERT_EQUALS(offset, sizeof(test_tcp_header_buffer_2));

            // Test that the internal state of the ip header is properly initialized.
            TS_ASSERT_EQUALS(tcp_header.is_valid(), true);
            TS_ASSERT_DIFFERS(tcp_header.header(), (struct tcphdr*)NULL);

            // Test that the ip header is correctly overlayed onto the test ip header
            // based on the contents.
            TS_ASSERT_EQUALS(tcp_header.source_port(), 0xe861);
            TS_ASSERT_EQUALS(tcp_header.destination_port(), 0x0016);
            TS_ASSERT_EQUALS(tcp_header.sequence_number(), 0x7e158b53);
            TS_ASSERT_EQUALS(tcp_header.acknowledgement_number(), 0x19ce5e84);
            TS_ASSERT_EQUALS(tcp_header.data_offset(), 0x5);
            TS_ASSERT_EQUALS(tcp_header.fin_flag(), 0x0);
            TS_ASSERT_EQUALS(tcp_header.syn_flag(), 0x0);
            TS_ASSERT_EQUALS(tcp_header.rst_flag(), 0x0);
            TS_ASSERT_EQUALS(tcp_header.psh_flag(), 0x0);
            TS_ASSERT_EQUALS(tcp_header.ack_flag(), 0x1);
            TS_ASSERT_EQUALS(tcp_header.urg_flag(), 0x0);
            TS_ASSERT_EQUALS(tcp_header.window_size(), 0x01f5);
            TS_ASSERT_EQUALS(tcp_header.checksum(), 0x24a0);
            TS_ASSERT_EQUALS(tcp_header.urgent_pointer(), 0x0000);
        }

        void test_overlay_truncated_buffer()
        {
            TcpHeader tcp_header;

            // Test that the overlay fails by passing in a buffer length that is too small.
            uint32_t offset = tcp_header.overlay(test_tcp_header_buffer_1,
                                                 sizeof(test_tcp_header_buffer_1) - 1);

            TS_ASSERT_EQUALS(offset, 0U);

            // Test that the internal state of the ip header is still correctly set to the
            // defaults (i.e. reset).
            TS_ASSERT_EQUALS(tcp_header.is_valid(), false);
            TS_ASSERT_EQUALS(tcp_header.header(), (struct tcphdr*)NULL);
        }
};
