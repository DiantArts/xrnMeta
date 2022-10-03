#pragma once

namespace xrn::meta::constraint::detail {

template <typename T>
struct TemplateParameter;

template <template <typename ...> class C, typename T>
struct TemplateParameter<C<T>>
{
    using type = T;
};

template <template <typename, ::std::size_t> class C, typename T, ::std::size_t size>
struct TemplateParameter<C<T, size>>
{
    using type = T;
};

template <
    typename T
> using TemplateParameter_t = typename ::xrn::meta::constraint::detail::TemplateParameter<T>::type;

} // namespace xrn::meta::constraint::detail
