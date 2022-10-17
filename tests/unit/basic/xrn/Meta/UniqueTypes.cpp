#include <pch.hpp>
#include <catch2/catch.hpp>
#include <xrn/Meta/UniqueTypes.hpp>

///////////////////////////////////////////////////////////////////////////

TEST_CASE(" xrnMeta :: UniqueTypes.Basic01")
{
    REQUIRE(::xrn::meta::UniqueTypes<int>::value);
    REQUIRE(::xrn::meta::UniqueTypes<int, float>::value);
    REQUIRE(::xrn::meta::UniqueTypes<int, float, ::std::string>::value);
    REQUIRE(!::xrn::meta::UniqueTypes<int, int>::value);
    REQUIRE(!::xrn::meta::UniqueTypes<int, float, int>::value);
    REQUIRE(!::xrn::meta::UniqueTypes<int, float, ::std::string, int>::value);
}

TEST_CASE(" xrnMeta :: UniqueTypes.Basic02")
{
    REQUIRE(::xrn::meta::uniqueTypes_v<int>);
    REQUIRE(::xrn::meta::uniqueTypes_v<int, float>);
    REQUIRE(::xrn::meta::uniqueTypes_v<int, float, ::std::string>);
    REQUIRE(!::xrn::meta::uniqueTypes_v<int, int>);
    REQUIRE(!::xrn::meta::uniqueTypes_v<int, float, int>);
    REQUIRE(!::xrn::meta::uniqueTypes_v<int, float, ::std::string, int>);
}
