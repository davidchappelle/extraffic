#include <cxxtest/TestSuite.h>


#include "extraffic/common/EtherAddressStringify.hpp"


using extraffic::common::EtherAddressStringify;


namespace
{

struct ether_addr test_ether_addr_1 = {
    // string:  00:e0:ed:19:51:a5
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

struct ether_addr test_ether_addr_2 = {
    // string:  00:e0:ed:19:51:a5
    { 0x00, 0xe0, 0xed, 0x19, 0x51, 0xa5 }
};

struct ether_addr test_ether_addr_3 = {
    // string:  5c:f9:dd:77:d2:ea
    { 0x5c, 0xf9, 0xdd, 0x77, 0xd2, 0xea }
};

} // namespace anonymous


class EtherAddressStringifyTestSuite : public CxxTest::TestSuite
{
    public:
        void test_stringify_1()
        {
            EtherAddressStringify stringify;
            TS_ASSERT_EQUALS("0:0:0:0:0:0", stringify.to_string(test_ether_addr_1));
        }

        void test_stringify_2()
        {
            EtherAddressStringify stringify;
            TS_ASSERT_EQUALS("0:e0:ed:19:51:a5", stringify.to_string(test_ether_addr_2));
        }

        void test_stringify_3()
        {
            EtherAddressStringify stringify;
            TS_ASSERT_EQUALS("5c:f9:dd:77:d2:ea", stringify.to_string(test_ether_addr_3));
        }
};
