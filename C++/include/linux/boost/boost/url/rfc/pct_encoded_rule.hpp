//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/url
//

#ifndef BOOST_URL_RFC_PCT_ENCODED_RULE_HPP
#define BOOST_URL_RFC_PCT_ENCODED_RULE_HPP

#include <boost/url/detail/config.hpp>
#include <boost/url/error_types.hpp>
#include <boost/url/pct_string_view.hpp>
#include <boost/url/grammar/charset.hpp>

namespace boost {
namespace urls {

/** Rule for a string with percent-encoded escapes

    This function returns a rule which matches
    a percent-encoded string, permitting characters
    in the string which are also in the specified
    character set to be used unescaped.
   
    @par Value Type
    @code
    using value_type = pct_string_view;
    @endcode

    @par Example
    Rules are used with the function @ref grammar::parse.
    @code
    //  pchar         = unreserved / pct-encoded / sub-delims / ":" / "@"

    system::result< pct_string_view > rv = grammar::parse( "Program%20Files", pct_encoded_rule( pchars ) );
    @endcode

    @par BNF
    @code
    pct-encoded   = "%" HEXDIG HEXDIG
    @endcode

    @param cs The character set indicating
    which characters are allowed without escapes.
    Any character which is not in this set must be
    escaped, or else parsing returns an error.

    @par Specification
    @li <a href="https://datatracker.ietf.org/doc/html/rfc3986#section-2.1">
        2.1. Percent-Encoding (rfc3986)</a>

    @see
        @ref grammar::parse,
        @ref pchars,
        @ref pct_string_view.
*/
#ifdef BOOST_URL_DOCS
/**@{*/
template<class CharSet>
constexpr
__implementation_defined__
pct_encoded_rule( CharSet const& cs ) noexcept;
/**@}*/
#else
namespace implementation_defined {
template<class CharSet>
struct pct_encoded_rule_t
{
    using value_type = pct_string_view;

    system::result<value_type>
    parse(
        char const*& it,
        char const* end) const noexcept;

    constexpr
    pct_encoded_rule_t(
        CharSet const& cs) noexcept
        : cs_(cs)
    {
    }

private:
    CharSet cs_;
};
} // implementation_defined

/** Rule for a string with percent-encoded escapes

    This function returns a rule which matches
    a percent-encoded string, permitting characters
    in the string which are also in the specified
    character set to be used unescaped.

    @par Value Type
    @code
    using value_type = pct_string_view;
    @endcode

    @par Example
    Rules are used with the function @ref grammar::parse.
    @code
    //  pchar         = unreserved / pct-encoded / sub-delims / ":" / "@"

    system::result< pct_string_view > rv = grammar::parse( "Program%20Files", pct_encoded_rule( pchars ) );
    @endcode

    @par BNF
    @code
    pct-encoded   = "%" HEXDIG HEXDIG
    @endcode

    @param cs The character set indicating
    which characters are allowed without escapes.
    Any character which is not in this set must be
    escaped, or else parsing returns an error.

    @return A rule object.

    @par Specification
    @li <a href="https://datatracker.ietf.org/doc/html/rfc3986#section-2.1">
        2.1. Percent-Encoding (rfc3986)</a>

    @see
        @ref grammar::parse,
        @ref pchars,
        @ref pct_string_view.
*/
template<BOOST_URL_CONSTRAINT(grammar::CharSet) CS>
constexpr
auto
pct_encoded_rule(CS const& cs) noexcept ->
    implementation_defined::pct_encoded_rule_t<CS>
{
    // If an error occurs here it means that
    // the value of your type does not meet
    // the requirements. Please check the
    // documentation!
    static_assert(
        grammar::is_charset<CS>::value,
        "CharSet requirements not met");

    return implementation_defined::pct_encoded_rule_t<CS>(cs);
}

#endif

} // urls
} // boost

#include <boost/url/rfc/impl/pct_encoded_rule.hpp>

#endif
