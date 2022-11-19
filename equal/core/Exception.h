#pragma once

//#include "../export.h"
#include <exception>
#include <fmt/format.h>
#include <iostream>
#include <stdexcept>
#include <string>

#ifdef DEBUG
#define EQ_THROW(...)                                                               \
    {                                                                               \
        std::throw_with_nested(std::runtime_error(                                  \
                fmt::format("{} {}  {}:{}", __FUNCTION__, fmt::format(__VA_ARGS__), \
                            __FILE__, __LINE__)));                                  \
    }
#else
#define EQ_THROW(...) \
    { std::throw_with_nested(std::runtime_error(fmt::format(__VA_ARGS__))); }
#endif

namespace eq {

    inline void StackTrace(const std::exception &exception,
                                     int level = 0) {
        std::cerr << std::string(level, ' ') << " exception: " << exception.what()
                  << std::endl;
        try {
            std::rethrow_if_nested(exception);
        } catch (const std::exception &ex) {
            StackTrace(ex, level + 1);
        } catch (...) {
            std::cerr << "unknown error" << std::endl;
        }
    }

}// namespace eq
