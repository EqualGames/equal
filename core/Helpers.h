#ifndef EQUAL_HELPERS_H
#define EQUAL_HELPERS_H

#include <string>
#include <string_view>
#include <utility>

void replace(std::string &text, const std::string &search, const std::string &replace);

void ltrim(std::string &s);

void rtrim(std::string &s);

void trim(std::string &s);

std::string ltrim_copy(std::string s);

std::string rtrim_copy(std::string s);

std::string trim_copy(std::string s);

std::pair<std::string, std::string> split_pair(const std::string &text, char delimiter, bool remove_spaces = true);

#endif //EQUAL_HELPERS_H
