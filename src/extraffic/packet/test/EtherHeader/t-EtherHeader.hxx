#include <cxxtest/TestSuite.h>


#include "extraffic/packet/EtherHeader.hpp"


using extraffic::packet::EtherHeader;


namespace
{
char test_ether_header_buffer_1[] = { 
    0x00, 0xe0, 0xed, 0x19, 0x51, 0xa5, // dst:  00:e0:ed:19:51:a5
    0x5c, 0xf9, 0xdd, 0x77, 0xd2, 0xea, // src:  5c:f9:dd:77:d2:ea 
    0x08, 0x00                          // type: IP
};

char test_ether_header_buffer_2[] = { 
    0x10, 0xec, 0xed, 0x1a, 0x51, 0xb5, // dst:  10:ec:ed:1a:51:b5
    0xcc, 0xf9, 0xdd, 0x57, 0xd2, 0x1a, // src:  cc:f9:dd:57:d2:1a 
    0x08, 0x06                          // type: IP
};

} // namespace anonymous


class EtherHeaderTestSuite : public CxxTest::TestSuite
{
    public:
        void test_construction()
        {
            EtherHeader ether_header;

            // Test that the internal state of the ethernet header
            // is properly initialized.
            TS_ASSERT_EQUALS(ether_header.is_valid(), false);
            TS_ASSERT_EQUALS(ether_header.header(), (struct ether_header*)NULL);
        }

        void test_reset()
        {
            EtherHeader ether_header;

            // Test that the internal state of the ethernet header
            // is properly initialized.
            TS_ASSERT_EQUALS(ether_header.is_valid(), false);
            TS_ASSERT_EQUALS(ether_header.header(), (struct ether_header*)NULL);

            uint32_t offset = ether_header.overlay(test_ether_header_buffer_1,
                                                   sizeof(test_ether_header_buffer_1));

            // Test that the offset to the end of the ethernet header
            // is correct.
            TS_ASSERT_EQUALS(offset, sizeof(test_ether_header_buffer_1));

            // Test that the internal state of the ethernet header is
            // properly initialized.
            TS_ASSERT_EQUALS(ether_header.is_valid(), true);
            TS_ASSERT_DIFFERS(ether_header.header(), (struct ether_header*)NULL);

            // Test that we can reset the ethernet header to its
            // default state.
            ether_header.reset();

            TS_ASSERT_EQUALS(ether_header.is_valid(), false);
            TS_ASSERT_EQUALS(ether_header.header(), (struct ether_header*)NULL);

        }

        void test_overlay()
        {
            EtherHeader ether_header;

            // Test the first overlay.
            uint32_t offset = ether_header.overlay(test_ether_header_buffer_1,
                                                   sizeof(test_ether_header_buffer_1));

            // Test that the offset to the end of the ethernet header
            // is correct.
            TS_ASSERT_EQUALS(offset, sizeof(test_ether_header_buffer_1));

            // Test that the internal state of the ethernet header
            // is properly initialized.
            TS_ASSERT_EQUALS(ether_header.is_valid(), true);
            TS_ASSERT_DIFFERS(ether_header.header(), (struct ether_header*)NULL);

            // Test that the ethernet header is correctly overlayed onto the test
            // ethernet header based on the contents.
            TS_ASSERT_EQUALS(ether_header.ether_type(), ETHERTYPE_IP);
            TS_ASSERT_DIFFERS(ether_header.source_ether_address(), (struct ether_addr*)NULL);
            TS_ASSERT_DIFFERS(ether_header.destination_ether_address(), (struct ether_addr*)NULL);
            TS_ASSERT_EQUALS(ether_header.source_ether_address_string().c_str(), "5c:f9:dd:77:d2:ea");
            TS_ASSERT_EQUALS(ether_header.destination_ether_address_string().c_str(), "0:e0:ed:19:51:a5");

            // Test the second overlay.
            offset = ether_header.overlay(test_ether_header_buffer_2,
                                          sizeof(test_ether_header_buffer_2));

            // Test that the offset to the end of the ethernet header
            // is correct.
            TS_ASSERT_EQUALS(offset, sizeof(test_ether_header_buffer_2));

            // Test that the internal state of the ethernet header
            // is properly initialized.
            TS_ASSERT_EQUALS(ether_header.is_valid(), true);
            TS_ASSERT_DIFFERS(ether_header.header(), (struct ether_header*)NULL);

            // Test that the ethernet header is correctly overlayed onto the test
            // ethernet header based on the contents.
            TS_ASSERT_EQUALS(ether_header.ether_type(), ETHERTYPE_ARP);
            TS_ASSERT_DIFFERS(ether_header.source_ether_address(), (struct ether_addr*)NULL);
            TS_ASSERT_DIFFERS(ether_header.destination_ether_address(), (struct ether_addr*)NULL);
            TS_ASSERT_EQUALS(ether_header.source_ether_address_string().c_str(), "cc:f9:dd:57:d2:1a");
            TS_ASSERT_EQUALS(ether_header.destination_ether_address_string().c_str(), "10:ec:ed:1a:51:b5");
        }

        void test_overlay_truncated_buffer()
        {
            EtherHeader ether_header;

            // Test that the overlay fails.
            uint32_t offset = ether_header.overlay(test_ether_header_buffer_1,
                                                   sizeof(test_ether_header_buffer_1) - 1);

            TS_ASSERT_EQUALS(offset, 0U);

            // Test that the internal state of the ether header is
            // still correctly set to the defaults (i.e. reset).
            TS_ASSERT_EQUALS(ether_header.is_valid(), false);
            TS_ASSERT_EQUALS(ether_header.header(), (struct ether_header*)NULL);
        }
};
