#include "catch.hpp"
#include "serializer.h"
#include "config.hpp"

#ifdef HOST_LITTLE_ENDIAN
TEST_CASE("Test host memory_input_archive", "[serializer]") {
    std::vector<uint8_t> data{ 0x78, 0x56, 0x34, 0x12 };
    binser::memory_input_archive<> in(data);
    uint32_t value;
    in(value);
    REQUIRE(value == 0x12345678);
}
TEST_CASE("Test little endian memory_input_archive", "[serializer]") {
    std::vector<uint8_t> data{ 0x78, 0x56, 0x34, 0x12 };
    binser::memory_input_archive<binser::EndiannessType::LittleEndian> in(data);
    uint32_t value;
    in(value);
    REQUIRE(value == 0x12345678);
}
TEST_CASE("Test big endian memory_input_archive", "[serializer]") {
    std::vector<uint8_t> data{ 0x78, 0x56, 0x34, 0x12 };
    binser::memory_input_archive<binser::EndiannessType::BigEndian> in(data);
    uint32_t value;
    in(value);
    REQUIRE(value == 0x78563412);
}
#endif