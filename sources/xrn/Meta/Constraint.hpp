#pragma once

#include <xrn/Meta/Detail/Constraint.hpp>
#include <xrn/Meta/Function.hpp>

namespace xrn::meta::constraint {

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the two types given as template parameter are the
///        same
///
/// The comparison ignores cv-qualifiers, references (compares the type
/// referenced) and pointers (compares the type pointed)
///
/// \tparam Type to check
///
/// \return True if the types given as template parameter are the same.
///         False otherwise
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type1,
    typename Type2
> concept sameAs = ::std::same_as<
        ::std::remove_cvref_t<::std::remove_pointer_t<Type1>>,
        ::std::remove_cvref_t<::std::remove_pointer_t<Type2>>
    >;

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether a type is present into the template parameter
///        pack
///
/// The comparison ignores cv-qualifiers, references (compares the type
/// referenced) and pointers (compares the type pointed)
///
/// \tparam ComparedType to check
/// \tparam ComparingTypes parameter pack that must contain the comapred type to work
///
/// \return True if the compared type is present within the comparing types
///
///////////////////////////////////////////////////////////////////////////
template <
    typename ComparedType,
    typename... ComparingTypes
> concept contains = ::std::disjunction_v<::std::is_same<
    ::std::remove_cvref_t<::std::remove_pointer_t<ComparedType>>,
    ::std::remove_cvref_t<::std::remove_pointer_t<ComparingTypes>>
>...>;

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the Type given as template parameter is const
///
/// The comparison ignores cv-qualifiers and references (compares the type
/// referenced).
///
/// \tparam Type to check
///
/// \return True if the Type given as template parameter is constant
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> concept isConst = ::std::is_const_v<::std::remove_reference_t<::std::remove_pointer_t<Type>>>;

///////////////////////////////////////////////////////////////////////////
/// \brief Oposite of ::xrn::meta::constraint::isConst
///
/// \see ::xrn::meta::constraint::isConst
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> concept isNotConst = !::xrn::meta::constraint::isConst<Type>;

///////////////////////////////////////////////////////////////////////////
/// \brief Is the value given to a function or method mutates the original
/// variable
///
/// Opposite of ::xrn::meta::constraint::isConst.
///
/// \tparam Type to check
///
/// \return True if the Type given as template parameter is mutable
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> concept isMutable = (::std::is_pointer_v<Type> && !::std::is_const_v<::std::remove_pointer_t<Type>>)
    || (::std::is_reference_v<Type> && !::std::is_const_v<::std::remove_reference_t<Type>>);

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the Type given as template parameter is a pointer
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> concept isPointer = ::std::is_pointer_v<Type>;

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the Type given as template parameter has .data()
/// and .size() methods
///
///////////////////////////////////////////////////////////////////////////
template <
    typename T
> concept isContiguousContainer = requires{
    ::std::declval<T>().data() && ::std::declval<T>().size() && ::std::declval<T>().operator[](0);
};

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the Type given as template parameter is the type
/// contained by the template class given as second template parameter
///
/// E.G.: ::std::vector<int> will contain ints.
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type1,
    typename Type2
> concept isContainedBy = ::xrn::meta::constraint::sameAs<
        ::std::remove_cvref_t<::std::remove_pointer_t<Type1>>,
        ::std::remove_cvref_t<::std::remove_pointer_t<
            ::xrn::meta::constraint::detail::TemplateParameter_t<Type2>
        >>
    >;

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the Type given as template parameter is a
/// suitable str
///
/// suitable strs are ::xrn::meta::constraint::isContiguousContainer with
/// chars or csstrings or ::std::string
///
///////////////////////////////////////////////////////////////////////////
template <
    typename T
> concept isMemoryStr = (::xrn::meta::constraint::isContainedBy<char, T> &&
    ::xrn::meta::constraint::isContiguousContainer<T>) ||
    ::std::same_as<::std::remove_cvref_t<T>, char*> ||
    ::std::same_as<::std::remove_cvref_t<T>, ::std::string>;

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the callable passed as first template parameter
/// has the other types given as template parammeter
///
///////////////////////////////////////////////////////////////////////////
template <
    typename CallableType
    , typename... Types
> concept doesCallableHasParameters =
    ::std::is_same<
        typename ::xrn::meta::template FunctionType<CallableType>::Arguments::Type
        , ::std::tuple<Types...>
    >::value;

} // namespace xrn::meta::constraint
