#pragma once

namespace xrn::meta::detail {

///////////////////////////////////////////////////////////////////////////
/// \brief Contains information about the function
///
///////////////////////////////////////////////////////////////////////////
template <
    typename func
> struct InformationImpl
    : public ::xrn::meta::detail::InformationImpl<decltype(&func::operator())>
{};

///////////////////////////////////////////////////////////////////////////
/// \brief Information from function pointers
///
///////////////////////////////////////////////////////////////////////////
template <
    typename RetType,
    typename... ArgTypes
> struct InformationImpl<RetType(*)(ArgTypes...)>
    : public ::xrn::meta::detail::InformationImpl<RetType(ArgTypes...)>
{};

///////////////////////////////////////////////////////////////////////////
/// \brief Information from ::std::function
///
///////////////////////////////////////////////////////////////////////////
template <
    typename RetType,
    typename... ArgTypes
> struct InformationImpl<::std::function<RetType(ArgTypes...)>>
    : public ::xrn::meta::detail::InformationImpl<RetType(ArgTypes...)>
{};

///////////////////////////////////////////////////////////////////////////
/// \brief Information from class operator()
///
///////////////////////////////////////////////////////////////////////////
template <
    typename ClassType,
    typename RetType,
    typename... ArgTypes
>struct InformationImpl<RetType(ClassType::*)(ArgTypes...) const>
    : public ::xrn::meta::detail::InformationImpl<RetType(ArgTypes...)>
{};

} // namespace xrn::meta::detail

namespace xrn::meta {

template <
    auto func
> struct Function
    : public ::xrn::meta::detail::InformationImpl<decltype(func)>
{};

} // namespace xrn::meta
