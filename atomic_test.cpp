#include <atomic>
#include "catch.hpp"
#include "serializer.h"
#include "config.hpp"

#ifdef HOST_LITTLE_ENDIAN
TEST_CASE("Test single atomic read/write operation", "[serializer]") {
    std::vector<uint8_t> data;
    binser::memory_output_archive<> out(data);
    binser::memory_input_archive<> in(data);
    std::atomic<int> a{ 0x12345678 };
    std::atomic<int> b{ 0 };
    out(a);
    in(b);
    REQUIRE(a == b);
}

TEST_CASE("Test mixed atomic read/write operations", "[serializer]") {
    std::vector<uint8_t> data;
    binser::memory_output_archive<> out(data);
    binser::memory_input_archive<> in(data);
    std::atomic<int> a{ 0x12345678 };
    int b = 1234;
    out(a, b);
    a = 0; b = 0;
    in(a, b);
    REQUIRE(a == 0x12345678);
    REQUIRE(b == 1234);
}
#endif