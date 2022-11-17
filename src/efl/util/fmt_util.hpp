#pragma once


#include "fmt/format.h"

#include "efl/date.h"
#include "efl/book.hpp"

namespace fmt
{
    template <>
    struct formatter<date::year_month_day>
    {
        template <typename ParseContext>
        constexpr ParseContext::iterator parse(ParseContext &ctx)
        {
            return ctx.begin();
        }

        template <typename FormatContext>
        FormatContext::iterator format(date::year_month_day const &ymd, FormatContext &ctx)
        {
            return fmt::format_to(ctx.out(), "{0}/{1}/{2}",
                                  int(ymd.year()),
                                  static_cast<unsigned>(ymd.month()),
                                  static_cast<unsigned>(ymd.day()));
        }
    };

    template <>
    struct formatter<efl::book_row_t>
    {
        template <typename ParseContext>
        constexpr ParseContext::iterator parse(ParseContext &ctx)
        {
            return ctx.begin();
        }

        template <typename FormatContext>
        FormatContext::iterator format(efl::book_row_t const &row, FormatContext &ctx)
        {
            return fmt::format_to(ctx.out(), "{0}@{1}[{2}]",
                row.qty, row.price, row.date);
        }
    };
}
