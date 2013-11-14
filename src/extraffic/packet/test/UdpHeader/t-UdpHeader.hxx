#include <cxxtest/TestSuite.h>


#include "extraffic/packet/UdpHeader.hpp"


using extraffic::packet::UdpHeader;


namespace
{

char test_udp_header_buffer_1[] = {
    0xd1, 0x0f, // source port
    0xee, 0xbd, // destination port
    0x00, 0x54, // length
    0xcb, 0xe1  // checksum
};

char test_udp_header_buffer_2[] = {
    0xc5, 0xf6, // source port
    0xee, 0xbd, // destination port
    0x00, 0x34, // length
    0xf4, 0x26  // checksum
};

} // namespace anonymous


class UdpHeaderTestSuite : public CxxTest::TestSuite
{
    public:
        void test_construction()
        {
            UdpHeader udp_header;

            // Test that the internal state of the ip header is properly initialized.
            TS_ASSERT_EQUALS(udp_header.is_valid(), false);
            TS_ASSERT_EQUALS(udp_header.header(), (struct udphdr*)NULL);
        }

        void test_reset()
        {
            UdpHeader udp_header;

            // Test the first overlay.
            uint32_t offset = udp_header.overlay(test_udp_header_buffer_1,
                                                 sizeof(test_udp_header_buffer_1));

            // Test that the offset to the end of the ip header is correct.
            TS_ASSERT_EQUALS(offset, sizeof(test_udp_header_buffer_1));

            // Test that the internal state of the ip header is properly initialized.
            TS_ASSERT_EQUALS(udp_header.is_valid(), true);
            TS_ASSERT_DIFFERS(udp_header.header(), (struct udphdr*)NULL);

            // Test that we can reset the ethernet header to its default state.
            udp_header.reset();

            TS_ASSERT_EQUALS(udp_header.is_valid(), false);
            TS_ASSERT_EQUALS(udp_header.header(), (struct udphdr*)NULL);
        }

        void test_overlay()
        {
            UdpHeader udp_header;

            // Test the first overlay.
            uint32_t offset = udp_header.overlay(test_udp_header_buffer_1,
                                                 sizeof(test_udp_header_buffer_1));

            // Test that the offset to the end of the ip header is correct.
            TS_ASSERT_EQUALS(offset, sizeof(test_udp_header_buffer_1));

            // Test that the internal state of the ip header is properly initialized.
            TS_ASSERT_EQUALS(udp_header.is_valid(), true);
            TS_ASSERT_DIFFERS(udp_header.header(), (struct udphdr*)NULL);

            // Test that the ip header is correctly overlayed onto the test ip header
            // based on the contents.
            TS_ASSERT_EQUALS(udp_header.source_port(), 0xd10f);
            TS_ASSERT_EQUALS(udp_header.destination_port(), 0xeebd);
            TS_ASSERT_EQUALS(udp_header.length(), 0x0054);
            TS_ASSERT_EQUALS(udp_header.checksum(), 0xcbe1);

            // Test the second overlay.
            offset = udp_header.overlay(test_udp_header_buffer_2,
                                        sizeof(test_udp_header_buffer_2));

            // Test that the offset to the end of the ip header is correct.
            TS_ASSERT_EQUALS(offset, sizeof(test_udp_header_buffer_2));

            // Test that the internal state of the ip header is properly initialized.
            TS_ASSERT_EQUALS(udp_header.is_valid(), true);
            TS_ASSERT_DIFFERS(udp_header.header(), (struct udphdr*)NULL);

            // Test that the ip header is correctly overlayed onto the test ip header
            // based on the contents.
            TS_ASSERT_EQUALS(udp_header.source_port(), 0xc5f6);
            TS_ASSERT_EQUALS(udp_header.destination_port(), 0xeebd);
            TS_ASSERT_EQUALS(udp_header.length(), 0x0034);
            TS_ASSERT_EQUALS(udp_header.checksum(), 0xf426);
        }

        void test_overlay_truncated_buffer()
        {
            UdpHeader udp_header;

            // Test that the overlay fails by passing in a buffer length that is too small.
            uint32_t offset = udp_header.overlay(test_udp_header_buffer_1,
                                                 sizeof(test_udp_header_buffer_1) - 1);

            TS_ASSERT_EQUALS(offset, 0U);

            // Test that the internal state of the udp header is still correctly set to
            // the defaults (i.e. reset).
            TS_ASSERT_EQUALS(udp_header.is_valid(), false);
            TS_ASSERT_EQUALS(udp_header.header(), (struct udphdr*)NULL);
        }
};
