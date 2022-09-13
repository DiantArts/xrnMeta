#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// methods
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> template <
    auto function
> constexpr void ::xrn::meta::ForEach<Types...>::run(
    auto&&... args
)
{
    (function.template operator()<Types>(::std::forward<decltype(args)>(args)...), ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> template <
    auto function
> constexpr auto ::xrn::meta::ForEach<Types...>::compareAnd(
    auto&&... args
) -> bool
{
    return (function.template operator()<Types>(::std::forward<decltype(args)>(args)...) && ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> template <
    auto function
> constexpr auto ::xrn::meta::ForEach<Types...>::compareOr(
    auto&&... args
) -> bool
{
    return (function.template operator()<Types>(::std::forward<decltype(args)>(args)...) || ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> template <
    typename Type
> constexpr auto ::xrn::meta::ForEach<Types...>::hasType()
    -> bool
{
    return (::std::is_same<Type, Types>::value || ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> template <
    typename Type
> constexpr auto ::xrn::meta::ForEach<Types...>::contains()
    -> bool
{
    return ForEach::hasType<Type>();
}

///////////////////////////////////////////////////////////////////////////
namespace {

template <
    typename ComparingType,
    typename... Types
> struct ForEachIterator {
    template <
        typename ComparedType,
        ::std::size_t i
    > [[ nodiscard ]] static inline constexpr auto getPosition()
        -> ::std::size_t
    {
        if constexpr (::xrn::meta::constraint::sameAs<ComparingType, ComparedType>) {
            return i;
        } else {
            return ::ForEachIterator<Types...>::template getPosition<ComparedType, i + 1>();
        }
    }
};

} // namespace

template <
    typename... Types
> template <
    typename ComparedType
> constexpr auto ::xrn::meta::ForEach<Types...>::getPosition()
    -> ::std::size_t
{
    static_assert(::xrn::meta::uniqueTypes_v<Types...>, "Types must be unique");
    return ForEachIterator<Types...>::template getPosition<ComparedType, 0>();
}
