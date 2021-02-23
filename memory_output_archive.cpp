#include "catch.hpp"
#include "serializer.h"
#include "config.hpp"

#ifdef HOST_LITTLE_ENDIAN
TEST_CASE("Test host memory_output_archive", "[serializer]") {
    std::vector<uint8_t> data;
    binser::memory_output_archive<> out(data);
    uint32_t value = 0x12345678;
    out(value);
    REQUIRE(data.size() == 4);
    REQUIRE(data[0] == 0x78);
    REQUIRE(data[1] == 0x56);
    REQUIRE(data[2] == 0x34);
    REQUIRE(data[3] == 0x12);
}
TEST_CASE("Test little endian memory_output_archive", "[serializer]") {
    std::vector<uint8_t> data;
    binser::memory_output_archive<binser::EndiannessType::LittleEndian> out(data);
    uint32_t value = 0x12345678;
    out(value);
    REQUIRE(data.size() == 4);
    REQUIRE(data[0] == 0x78);
    REQUIRE(data[1] == 0x56);
    REQUIRE(data[2] == 0x34);
    REQUIRE(data[3] == 0x12);
}
TEST_CASE("Test big endian memory_output_archive", "[serializer]") {
    std::vector<uint8_t> data;
    binser::memory_output_archive<binser::EndiannessType::BigEndian> out(data);
    uint32_t value = 0x12345678;
    out(value);
    REQUIRE(data.size() == 4);
    REQUIRE(data[0] == 0x12);
    REQUIRE(data[1] == 0x34);
    REQUIRE(data[2] == 0x56);
    REQUIRE(data[3] == 0x78);
}
#else
#endif