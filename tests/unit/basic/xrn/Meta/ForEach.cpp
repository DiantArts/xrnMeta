#include <pch.hpp>
#include <catch2/catch.hpp>
#include <xrn/Meta/ForEach.hpp>

///////////////////////////////////////////////////////////////////////////

TEST_CASE("ForEach.run.Basic01")
{
    int value{ 0 };
    ::xrn::meta::ForEach<int, float>::run<[]<typename>(int& value){ ++value; }>(value);
    REQUIRE(value == 2);
    ::xrn::meta::ForEach<int, float, int>::run<[]<typename>(int& value){ ++value; }>(value);
    REQUIRE(value == 5);
    ::xrn::meta::ForEach<int>::run<[]<typename>(int& value){ ++value; }>(value);
    REQUIRE(value == 6);
    ::xrn::meta::ForEach<>::run<[]<typename>(int& value){ ++value; }>(value);
    REQUIRE(value == 6);
}

///////////////////////////////////////////////////////////////////////////

TEST_CASE("ForEach.compareAnd.Basic01")
{
    bool value;

    value = ::xrn::meta::ForEach<int, short, long>::compareAnd<[]<typename T>(){
        return ::std::is_integral<T>();
    }>();
    REQUIRE(value);

    value = ::xrn::meta::ForEach<float, int, ::std::string>::compareAnd<[]<typename T>(){
        return ::std::is_integral<T>();
    }>();
    REQUIRE(!value);

    value = ::xrn::meta::ForEach<int, float, ::std::string>::compareAnd<[]<typename T>(){
        return ::std::is_integral<T>();
    }>();
    REQUIRE(!value);
}

///////////////////////////////////////////////////////////////////////////

TEST_CASE("ForEach.compareOr.Basic02")
{
    bool value;

    value = ::xrn::meta::ForEach<int, short, long>::compareOr<[]<typename T>(){
        return ::std::is_integral<T>();
    }>();
    REQUIRE(value);

    value = ::xrn::meta::ForEach<float, int, ::std::string>::compareOr<[]<typename T>(){
        return ::std::is_integral<T>();
    }>();
    REQUIRE(value);

    value = ::xrn::meta::ForEach<int, float, ::std::string>::compareOr<[]<typename T>(){
        return ::std::is_integral<T>();
    }>();
    REQUIRE(value);

    value = ::xrn::meta::ForEach<::std::string, ::std::string>::compareOr<[]<typename T>(){
        return ::std::is_integral<T>();
    }>();
    REQUIRE(!value);
}

///////////////////////////////////////////////////////////////////////////

TEST_CASE("ForEach.contains/hasType.Basic01")
{
    REQUIRE((::xrn::meta::ForEach<int>::hasType<int>()));
    REQUIRE(!(::xrn::meta::ForEach<int>::hasType<float>()));
    REQUIRE((::xrn::meta::ForEach<int>::contains<int>()));
    REQUIRE(!(::xrn::meta::ForEach<int>::contains<float>()));
}

TEST_CASE("ForEach.contains/hasType.Basic02")
{
    REQUIRE((::xrn::meta::ForEach<int, float>::hasType<int>()));
    REQUIRE((::xrn::meta::ForEach<int, float>::hasType<float>()));
    REQUIRE(!(::xrn::meta::ForEach<int, float>::hasType<::std::string>()));
    REQUIRE((::xrn::meta::ForEach<int, float>::contains<int>()));
    REQUIRE((::xrn::meta::ForEach<int, float>::contains<float>()));
    REQUIRE(!(::xrn::meta::ForEach<int, float>::contains<::std::string>()));
}

///////////////////////////////////////////////////////////////////////////

TEST_CASE("ForEach.getPosition.Basic01")
{
    REQUIRE((::xrn::meta::ForEach<int>::getPosition<int>() == 0));
}

TEST_CASE("ForEach.getPosition.Basic02")
{
    REQUIRE((::xrn::meta::ForEach<int, float>::getPosition<int>() == 0));
    REQUIRE((::xrn::meta::ForEach<int, float>::getPosition<float>() == 1));
    REQUIRE((::xrn::meta::ForEach<float, int>::getPosition<float>() == 0));
    REQUIRE((::xrn::meta::ForEach<float, int>::getPosition<int>() == 1));
}

TEST_CASE("ForEach.getPosition.Basic03")
{
    REQUIRE((::xrn::meta::ForEach<int, float, ::std::string>::getPosition<int>() == 0));
    REQUIRE((::xrn::meta::ForEach<int, float, ::std::string>::getPosition<float>() == 1));
    REQUIRE((::xrn::meta::ForEach<int, float, ::std::string>::getPosition<::std::string>() == 2));
}
