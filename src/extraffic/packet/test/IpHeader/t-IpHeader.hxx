#include <cxxtest/TestSuite.h>


#include "extraffic/packet/IpHeader.hpp"


using extraffic::packet::IpHeader;


namespace
{
char test_ip_header_buffer_1[] = {
    0x45, 0x00, 0x00, 0x3c,
    0xb5, 0x21, 0x40, 0x00,
    0x40, 0x06, 0x68, 0x03,
    0x0a, 0x02, 0x07, 0x0a,
    0x0a, 0x14, 0x02, 0x78
};

char test_ip_header_buffer_2[] = {
    0x45, 0x00, 0x00, 0x24,
    0x0b, 0x15, 0x00, 0x00,
    0x01, 0x11, 0x14, 0xa5,
    0x0a, 0x02, 0x06, 0xbd,
    0xe0, 0xa8, 0xa8, 0xa8
};

} // namespace anonymous


class IpHeaderTestSuite : public CxxTest::TestSuite
{
    public:
        void test_construction()
        {
            IpHeader ip_header;

            // Test that the internal state of the ip header is properly initialized.
            TS_ASSERT_EQUALS(ip_header.is_valid(), false);
            TS_ASSERT_EQUALS(ip_header.header(), (struct iphdr*)NULL);
        }

        void test_reset()
        {
            IpHeader ip_header;

            // Test the first overlay.
            uint32_t offset = ip_header.overlay(test_ip_header_buffer_1,
                                                sizeof(test_ip_header_buffer_1));

            // Test that the offset to the end of the ip header is correct.
            TS_ASSERT_EQUALS(offset, sizeof(test_ip_header_buffer_1));

            // Test that the internal state of the ip header is properly initialized.
            TS_ASSERT_EQUALS(ip_header.is_valid(), true);
            TS_ASSERT_DIFFERS(ip_header.header(), (struct iphdr*)NULL);

            // Test that we can reset the ethernet header to its default state.
            ip_header.reset();

            TS_ASSERT_EQUALS(ip_header.is_valid(), false);
            TS_ASSERT_EQUALS(ip_header.header(), (struct iphdr*)NULL);
        }

        void test_overlay()
        {
            IpHeader ip_header;

            // Test the first overlay.
            uint32_t offset = ip_header.overlay(test_ip_header_buffer_1,
                                                sizeof(test_ip_header_buffer_1));

            // Test that the offset to the end of the ip header is correct.
            TS_ASSERT_EQUALS(offset, sizeof(test_ip_header_buffer_1));

            // Test that the internal state of the ip header is properly initialized.
            TS_ASSERT_EQUALS(ip_header.is_valid(), true);
            TS_ASSERT_DIFFERS(ip_header.header(), (struct iphdr*)NULL);

            // Test that the ip header is correctly overlayed onto the test ip header
            // based on the contents.
            TS_ASSERT_EQUALS(ip_header.header_length(), 5U);
            TS_ASSERT_EQUALS(ip_header.version(), 4U);
            TS_ASSERT_EQUALS(ip_header.type_of_service(), 0U);
            TS_ASSERT_EQUALS(ip_header.total_length(), 60U);
            TS_ASSERT_EQUALS(ip_header.identifier(), 46369U);
            TS_ASSERT_EQUALS(ip_header.fragment_flags(), IP_DF);
            TS_ASSERT_EQUALS(ip_header.fragment_offset(), 0U);
            TS_ASSERT_EQUALS(ip_header.time_to_live(), 64U);
            TS_ASSERT_EQUALS(ip_header.protocol(), 6U);
            TS_ASSERT_EQUALS(ip_header.checksum(), 0x6803);
            TS_ASSERT_EQUALS(ip_header.source_ip_address(), 167905034U);
            TS_ASSERT_EQUALS(ip_header.destination_ip_address(), 169083512U);
            TS_ASSERT_EQUALS(ip_header.source_ip_address_string(), "10.2.7.10");
            TS_ASSERT_EQUALS(ip_header.destination_ip_address_string(), "10.20.2.120");

            // Test the second overlay.
            offset = ip_header.overlay(test_ip_header_buffer_2,
                                       sizeof(test_ip_header_buffer_2));

            // Test that the offset to the end of the ip header is correct.
            TS_ASSERT_EQUALS(offset, sizeof(test_ip_header_buffer_2));

            // Test that the internal state of the ip header is properly initialized.
            TS_ASSERT_EQUALS(ip_header.is_valid(), true);
            TS_ASSERT_DIFFERS(ip_header.header(), (struct iphdr*)NULL);

            // Test that the ip header is correctly overlayed onto the test ip header
            // based on the contents.
            TS_ASSERT_EQUALS(ip_header.header_length(), 5U);
            TS_ASSERT_EQUALS(ip_header.version(), 4U);
            TS_ASSERT_EQUALS(ip_header.type_of_service(), 0U);
            TS_ASSERT_EQUALS(ip_header.total_length(), 36U);
            TS_ASSERT_EQUALS(ip_header.identifier(), 2837U);
            TS_ASSERT_EQUALS(ip_header.fragment_flags(), 0U);
            TS_ASSERT_EQUALS(ip_header.fragment_offset(), 0U);
            TS_ASSERT_EQUALS(ip_header.time_to_live(), 1U);
            TS_ASSERT_EQUALS(ip_header.protocol(), 17U);
            TS_ASSERT_EQUALS(ip_header.checksum(), 0x14a5);
            TS_ASSERT_EQUALS(ip_header.source_ip_address(), 167904957U);
            TS_ASSERT_EQUALS(ip_header.destination_ip_address(), 3769149608U);
            TS_ASSERT_EQUALS(ip_header.source_ip_address_string(), "10.2.6.189");
            TS_ASSERT_EQUALS(ip_header.destination_ip_address_string(), "224.168.168.168");
        }

        void test_overlay_truncated_buffer()
        {
            IpHeader ip_header;

            // Test that the overlay fails by passing in a buffer length that is too small.
            uint32_t offset = ip_header.overlay(test_ip_header_buffer_1,
                                                sizeof(test_ip_header_buffer_1) - 1);
            
            TS_ASSERT_EQUALS(offset, 0U);

            // Test that the internal state of the ip header is still correctly set to the
            // defaults (i.e. reset).
            TS_ASSERT_EQUALS(ip_header.is_valid(), false);
            TS_ASSERT_EQUALS(ip_header.header(), (struct iphdr*)NULL);
        }
};
