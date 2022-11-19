#pragma once

#include "../export.h"
#include <string>
#include <string_view>
#include <utility>

namespace eq {

    EQ_EXPORT void replace(std::string &text, const std::string &search,
                           const std::string &replace);

    EQ_EXPORT void ltrim(std::string &s);

    EQ_EXPORT void rtrim(std::string &s);

    EQ_EXPORT void trim(std::string &s);

    EQ_EXPORT std::string ltrim_copy(std::string s);

    EQ_EXPORT std::string rtrim_copy(std::string s);

    EQ_EXPORT std::string trim_copy(std::string s);

    EQ_EXPORT std::pair<std::string, std::string>
    split_pair(const std::string &text, char delimiter, bool remove_spaces = true);

}// namespace eq
