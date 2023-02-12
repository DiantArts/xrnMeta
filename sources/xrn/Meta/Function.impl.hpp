#pragma once

namespace xrn::meta {

///////////////////////////////////////////////////////////////////////////
/// \brief Contains information about the function
///
///////////////////////////////////////////////////////////////////////////
template <
    typename func
> struct FunctionType
    : public ::xrn::meta::FunctionType<decltype(&func::operator())>
{};

///////////////////////////////////////////////////////////////////////////
/// \brief Information from function pointers
///
///////////////////////////////////////////////////////////////////////////
template <
    typename RetType,
    typename... ArgTypes
> struct FunctionType<RetType(*)(ArgTypes...)>
    : public ::xrn::meta::FunctionType<RetType(ArgTypes...)>
{};

///////////////////////////////////////////////////////////////////////////
/// \brief Information from ::std::function
///
///////////////////////////////////////////////////////////////////////////
template <
    typename RetType,
    typename... ArgTypes
> struct FunctionType<::std::function<RetType(ArgTypes...)>>
    : public ::xrn::meta::FunctionType<RetType(ArgTypes...)>
{};

///////////////////////////////////////////////////////////////////////////
/// \brief Information from class operator()
///
///////////////////////////////////////////////////////////////////////////
template <
    typename ClassType,
    typename RetType,
    typename... ArgTypes
>struct FunctionType<RetType(ClassType::*)(ArgTypes...) const>
    : public ::xrn::meta::FunctionType<RetType(ArgTypes...)>
{};

} // namespace xrn::meta

namespace xrn::meta {

template <
    auto func
> struct Function
    : public ::xrn::meta::FunctionType<decltype(func)>
{};

} // namespace xrn::meta
