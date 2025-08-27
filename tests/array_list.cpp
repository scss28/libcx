#include <cx/array_list.h>

TEST_CASE("ArrayList 'push' works", "[array_list]") {
    cx::ArrayList<u8> list;
    list.push(1);
    list.push(2);

    REQUIRE(list.items.len == 2);
    REQUIRE(list.items[0] == 1);
    REQUIRE(list.items[1] == 2);
}

TEST_CASE("ArrayList 'pop' works", "[array_list]") {
    cx::ArrayList<u8> list;
    list.push(1);
    auto popped = list.pop();

    REQUIRE(popped == 1);
    REQUIRE(list.items.len == 0);
}
