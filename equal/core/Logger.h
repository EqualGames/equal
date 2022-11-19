#pragma once

#include <fmt/format.h>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <time.h>

#ifndef EQ_LOGGER_LEVEL
#define EQ_LOGGER_LEVEL 0// VERBOSE
#endif

namespace eq {

    namespace out {

        namespace code {

            const char RESET[7] = "\033[0m";
            const char TEXT_BOLD[7] = "\033[1m";
            const char TEXT_UNDERLINE[7] = "\033[4m";

            const char FG_BLACK[8] = "\033[30m";
            const char FG_RED[8] = "\033[31m";
            const char FG_GREEN[8] = "\033[32m";
            const char FG_YELLOW[8] = "\033[33m";
            const char FG_BLUE[8] = "\033[34m";
            const char FG_MAGENTA[8] = "\033[35m";
            const char FG_CYAN[8] = "\033[36m";
            const char FG_LIGHT_GRAY[8] = "\033[37m";
            const char FG_DEFAULT[8] = "\033[39m";
            const char FG_DARK_GRAY[8] = "\033[90m";
            const char FG_LIGHT_RED[8] = "\033[91m";
            const char FG_LIGHT_GREEN[8] = "\033[92m";
            const char FG_LIGHT_YELLOW[8] = "\033[93m";
            const char FG_LIGHT_BLUE[8] = "\033[94m";
            const char FG_LIGHT_MAGENTA[8] = "\033[95m";
            const char FG_LIGHT_CYAN[8] = "\033[96m";
            const char FG_WHITE[8] = "\033[97m";

            const char BG_BLACK[8] = "\033[40m";
            const char BG_RED[8] = "\033[41m";
            const char BG_GREEN[8] = "\033[42m";
            const char BG_YELLOW[8] = "\033[43m";
            const char BG_BLUE[8] = "\033[44m";
            const char BG_MAGENTA[8] = "\033[45m";
            const char BG_CYAN[8] = "\033[46m";
            const char BG_WHITE[8] = "\033[47m";
            const char BG_DEFAULT[8] = "\033[49m";

        }// namespace code

        inline std::string apply_effect(const char *color, const std::string &text) {
            return fmt::format("{}{}{}", color, text, code::RESET);
        }

        inline std::string BOLD(const std::string &text) { return apply_effect(code::TEXT_BOLD, text); }
        inline std::string UNDERLINE(const std::string &text) { return apply_effect(code::TEXT_UNDERLINE, text); }

        inline std::string BLACK(const std::string &text) { return apply_effect(code::FG_BLACK, text); }
        inline std::string RED(const std::string &text) { return apply_effect(code::FG_RED, text); }
        inline std::string GREEN(const std::string &text) { return apply_effect(code::FG_GREEN, text); }
        inline std::string YELLOW(const std::string &text) { return apply_effect(code::FG_YELLOW, text); }
        inline std::string BLUE(const std::string &text) { return apply_effect(code::FG_BLUE, text); }
        inline std::string MAGENTA(const std::string &text) { return apply_effect(code::FG_MAGENTA, text); }
        inline std::string CYAN(const std::string &text) { return apply_effect(code::FG_CYAN, text); }
        inline std::string LIGHT_GRAY(const std::string &text) { return apply_effect(code::FG_LIGHT_GRAY, text); }
        inline std::string DEFAULT(const std::string &text) { return apply_effect(code::FG_DEFAULT, text); }
        inline std::string DARK_GRAY(const std::string &text) { return apply_effect(code::FG_DARK_GRAY, text); }
        inline std::string LIGHT_RED(const std::string &text) { return apply_effect(code::FG_LIGHT_RED, text); }
        inline std::string LIGHT_GREEN(const std::string &text) { return apply_effect(code::FG_LIGHT_GREEN, text); }
        inline std::string LIGHT_YELLOW(const std::string &text) { return apply_effect(code::FG_LIGHT_YELLOW, text); }
        inline std::string LIGHT_BLUE(const std::string &text) { return apply_effect(code::FG_LIGHT_BLUE, text); }
        inline std::string LIGHT_MAGENTA(const std::string &text) { return apply_effect(code::FG_LIGHT_MAGENTA, text); }
        inline std::string LIGHT_CYAN(const std::string &text) { return apply_effect(code::FG_LIGHT_CYAN, text); }
        inline std::string WHITE(const std::string &text) { return apply_effect(code::FG_WHITE, text); }

        inline std::string BG_BLACK(const std::string &text) { return apply_effect(code::BG_BLACK, text); }
        inline std::string BG_RED(const std::string &text) { return apply_effect(code::BG_RED, text); }
        inline std::string BG_GREEN(const std::string &text) { return apply_effect(code::BG_GREEN, text); }
        inline std::string BG_YELLOW(const std::string &text) { return apply_effect(code::BG_YELLOW, text); }
        inline std::string BG_BLUE(const std::string &text) { return apply_effect(code::BG_BLUE, text); }
        inline std::string BG_MAGENTA(const std::string &text) { return apply_effect(code::BG_MAGENTA, text); }
        inline std::string BG_CYAN(const std::string &text) { return apply_effect(code::BG_CYAN, text); }
        inline std::string BG_WHITE(const std::string &text) { return apply_effect(code::BG_WHITE, text); }
        inline std::string BG_DEFAULT(const std::string &text) { return apply_effect(code::BG_DEFAULT, text); }


    }// namespace out

    namespace Logger {

        enum Level {
            VERBOSE = 0,
            DEVELOPMENT = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            CRITICAL = 5
        };

        inline std::string level_to_str(Level level) {
            switch (level) {
                case Level::VERBOSE:
                    return out::LIGHT_GRAY(out::BOLD("VERBOSE"));
                    break;
                case Level::DEVELOPMENT:
                    return out::CYAN(out::BOLD("DEBUG"));
                    break;
                case Level::INFO:
                    return out::GREEN(out::BOLD("INFO"));
                    break;
                case Level::WARN:
                    return out::YELLOW(out::BOLD("WARN"));
                    break;
                case Level::ERROR:
                    return out::RED(out::BOLD("ERROR"));
                    break;
                case Level::CRITICAL:
                    return out::BG_RED(out::WHITE(out::BOLD("CRITICAL")));
                    break;
                default:
                    return out::DEFAULT(out::BOLD("NONE"));
                    break;
            }
        }

        template<typename... Args>
        inline void log(Level level, Args... args) {
            if (level >= EQ_LOGGER_LEVEL) {
                auto t = std::time(nullptr);
                auto tm = std::localtime(&t);

                std::stringstream ss;
                ss << std::put_time(tm, "%Y/%m/%d %H:%M:%S %z");

                std::cout << "[" << ss.str() << "] [" << level_to_str(level) << "] " << fmt::format(args...) << std::endl;
            }
        }

        template<typename... Args>
        inline void trace(Args... args) {
            log(Level::VERBOSE, args...);
        }

        template<typename... Args>
        inline void debug(Args... args) {
            log(Level::DEVELOPMENT, args...);
        }

        template<typename... Args>
        inline void info(Args... args) {
            log(Level::INFO, args...);
        }

        template<typename... Args>
        inline void warn(Args... args) {
            log(Level::WARN, args...);
        }

        template<typename... Args>
        inline void error(Args... args) {
            log(Level::ERROR, args...);
        }

        template<typename... Args>
        inline void critical(Args... args) {
            log(Level::CRITICAL, args...);
        }
    };// namespace Logger

}// namespace eq
