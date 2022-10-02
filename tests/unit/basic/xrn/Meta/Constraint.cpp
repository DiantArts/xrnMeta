#include <pch.hpp>
#include <catch2/catch.hpp>
#include <xrn/Meta/Constraint.hpp>

///////////////////////////////////////////////////////////////////////////

TEST_CASE("Constraint.run.Basic01")
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
