#include "catch.hpp"
#include "serializer.h"
#include "config.hpp"

struct A {
    int v;
};

template <typename Archive>
void serialize(Archive& archive, A& adl)
{
    archive(adl.v);
}

class B {
    int v = 0x01020304;
public:
    int get() { return v; }
    void clear() { v = 0; }

    friend binser::access;
    template <typename Archive, typename Self>
    static void serialize(Archive& archive, Self& self)
    {
        archive(self.v);
    }
};

#ifdef HOST_LITTLE_ENDIAN
TEST_CASE("Test struct test1", "[serializer]") {
    std::vector<uint8_t> data;
    binser::memory_output_archive<> out(data);
    binser::memory_input_archive<> in(data);
    A a{ 0x12345678 };
    out(a);
    REQUIRE(data.size() == 4);
    REQUIRE(data[0] == 0x78);
    REQUIRE(data[1] == 0x56);
    REQUIRE(data[2] == 0x34);
    REQUIRE(data[3] == 0x12);
    a.v = 0;
    in(a);
    REQUIRE(a.v == 0x12345678);
}
TEST_CASE("Test struct test2", "[serializer]") {
    std::vector<uint8_t> data;
    binser::memory_output_archive<> out(data);
    binser::memory_input_archive<> in(data);
    A a{ 0x12345678 };
    B b;
    out(a, b);
    REQUIRE(data.size() == 8);
    REQUIRE(data[0] == 0x78);
    REQUIRE(data[1] == 0x56);
    REQUIRE(data[2] == 0x34);
    REQUIRE(data[3] == 0x12);
    REQUIRE(data[4] == 0x04);
    REQUIRE(data[5] == 0x03);
    REQUIRE(data[6] == 0x02);
    REQUIRE(data[7] == 0x01);
    a.v = 0;
    b.clear();
    in(a, b);
    REQUIRE(a.v == 0x12345678);
    REQUIRE(b.get() == 0x01020304);
}
#endif