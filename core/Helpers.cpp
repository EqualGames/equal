#include "Helpers.h"

void replace(std::string &text, const std::string &search,
             const std::string &replace) {
  size_t f = text.find(search);
  text = text.replace(f, f + search.size(), replace);
}

void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                  [](int ch) { return !std::isspace(ch); }));
}

void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](int ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

std::string ltrim_copy(std::string s) {
  ltrim(s);
  return s;
}

std::string rtrim_copy(std::string s) {
  rtrim(s);
  return s;
}

std::string trim_copy(std::string s) {
  trim(s);
  return s;
}

std::pair<std::string, std::string>
split_pair(const std::string &text, char delimiter, bool remove_spaces) {
  std::string_view v{text};

  if (v.find(delimiter) == std::string_view::npos) {
    if (remove_spaces) {
      return std::make_pair(trim_copy(std::string(v)), "");
    } else {
      return std::make_pair(text, "");
    }
  }

  std::string_view a = v.substr(0, v.find_first_of(delimiter));
  std::string_view b = v.substr(v.find_first_of(delimiter) + 1, v.length());

  if (remove_spaces) {
    return std::make_pair(trim_copy(std::string(a)), trim_copy(std::string(b)));
  } else {
    return std::make_pair(std::string(a), std::string(b));
  }
}
