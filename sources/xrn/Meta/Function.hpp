#pragma once

#include <xrn/Meta/Function.impl.hpp>

namespace xrn::meta {

///////////////////////////////////////////////////////////////////////////
/// \brief Fetch meta information about callables
/// \ingroup meta
///
/// \include Function.hpp <xrn/Meta/Function.hpp>
///
/// This class is a part of the ::xrn::meta Library designed to facilitate
/// usage of template metaprgramming.
///
/// \code
/// auto lambda{ [](int){} };
/// using Types = typename ::xrn::meta::template Function<lambda>::Arguments::Type;
/// bool value{ ::std::is_same<Types, ::std::tuple<int>>::value };
/// ::fmt::print("{}\n", value); // true
/// \endcode
///
/// \tparam Types Types to execute actions on
///
///////////////////////////////////////////////////////////////////////////
template <
    typename RetType,
    typename... ArgTypes
> struct FunctionType<RetType(ArgTypes...)> {

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Contains the return type
    ///
    ///////////////////////////////////////////////////////////////////////////
    struct Return {
        using Type = RetType;
    };

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Contains the argument types
    ///
    ///////////////////////////////////////////////////////////////////////////
    struct Arguments {

        ///////////////////////////////////////////////////////////////////////////
        /// \brief Tuple of all the types
        ///
        ///////////////////////////////////////////////////////////////////////////
        using Type = ::std::tuple<ArgTypes...>;

        ///////////////////////////////////////////////////////////////////////////
        /// \brief Are all the arguments modifying the original value passed as
        ///        argument (mutable ref or ptr).
        ///
        ///////////////////////////////////////////////////////////////////////////
        static constexpr const auto areConst{ ((
            ::std::is_const<::std::remove_reference_t<ArgTypes>>::value ||
            !::std::is_reference<ArgTypes>::value
        ) && ...) };
    };

};

} // namespace xrn::meta
