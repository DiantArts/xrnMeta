#include <pch.hpp>
#include <catch2/catch.hpp>
#include <xrn/Meta/Constraint.hpp>

///////////////////////////////////////////////////////////////////////////

TEST_CASE(" xrnMeta :: Constraint.run.Basic01")
{
    REQUIRE(::xrn::meta::constraint::sameAs<int, int>);
    REQUIRE(!::xrn::meta::constraint::sameAs<int, float>);

    REQUIRE(::xrn::meta::constraint::sameAs<int&, int>);
    REQUIRE(!::xrn::meta::constraint::sameAs<int&, float>);

    REQUIRE(::xrn::meta::constraint::sameAs<const int&, int>);
    REQUIRE(!::xrn::meta::constraint::sameAs<const int&, float>);

    REQUIRE(::xrn::meta::constraint::sameAs<int*, int>);
    REQUIRE(!::xrn::meta::constraint::sameAs<int*, float>);

    REQUIRE(::xrn::meta::constraint::sameAs<const int*, int>);
    REQUIRE(!::xrn::meta::constraint::sameAs<const int*, float>);

    REQUIRE(::xrn::meta::constraint::isPointer<const int*>);
    REQUIRE(::xrn::meta::constraint::isPointer<int*>);
    REQUIRE(!::xrn::meta::constraint::isPointer<const int&>);

    REQUIRE(::xrn::meta::constraint::isContiguousContainer<::std::vector<int>>);
    REQUIRE(::xrn::meta::constraint::isContiguousContainer<::std::array<int, 1>>);
    REQUIRE(!::xrn::meta::constraint::isContiguousContainer<::std::map<int, int>>);
}

TEST_CASE(" xrnMeta :: Constraint.run.isContainedBy")
{
    REQUIRE(::xrn::meta::constraint::isContainedBy<char, ::std::vector<char>>);
    REQUIRE(::xrn::meta::constraint::isContainedBy<char, ::std::span<char>>);
    REQUIRE(::xrn::meta::constraint::isContainedBy<int, ::std::vector<int>>);
    REQUIRE(::xrn::meta::constraint::isContainedBy<int, ::std::span<int>>);
    REQUIRE(!::xrn::meta::constraint::isContainedBy<char, ::std::vector<int>>);
    REQUIRE(!::xrn::meta::constraint::isContainedBy<char, ::std::span<int>>);
}

TEST_CASE(" xrnMeta :: Constraint.run.isMemoryStr")
{
    REQUIRE(::xrn::meta::constraint::isMemoryStr<char*>);
    REQUIRE(::xrn::meta::constraint::isMemoryStr<::std::string>);
    REQUIRE(::xrn::meta::constraint::isMemoryStr<::std::vector<char>>);
    REQUIRE(::xrn::meta::constraint::isMemoryStr<::std::span<char>>);
    REQUIRE(!::xrn::meta::constraint::isMemoryStr<int*>);
    REQUIRE(!::xrn::meta::constraint::isMemoryStr<::std::vector<int>>);
    REQUIRE(!::xrn::meta::constraint::isMemoryStr<::std::span<int>>);
}
