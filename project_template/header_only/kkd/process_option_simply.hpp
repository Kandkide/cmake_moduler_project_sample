/**
 * @file process_option_simply.hpp
 * @author Your Name (you@domain.com)
 * @brief Header file containing functions to process command-line options simply.
 * @version 0.1
 * @date 2024-01-08
 * @copyright Copyright (c) 2024
 */

#ifndef PROCESS_OPTION_SIMPLY_HPP_INCLUDED
#define PROCESS_OPTION_SIMPLY_HPP_INCLUDED

#include <iostream>
#include <span>
#include <string_view>

namespace kkd {
    /**
     * @brief Process the help option.
     * 
     * @tparam unusedT Unused template parameter.
     * @param argc Number of command-line arguments.
     * @param argv Array of command-line arguments.
     * @param helpText Text to display if the help option is found.
     * @param argRequired Boolean indicating whether arguments are required after the help option.
     * @return true if the help option is found or arguments are required but given none, false otherwise.
     */
    template<typename unusedT = char>
    bool process_help(int argc, char* argv[], const std::string_view helpText, bool argRequired = false) {
        if (argRequired && argc <= 1) {
            std::cerr << "Command-line argument is required: " << helpText << std::endl;
            return true;
        }

        std::span<char*> args(argv, argc);

        for (auto& e : args.subspan(1)) {
            if (std::string_view(e) == "-h" || std::string_view(e) == "--help") {
                std::cout << helpText << std::endl;
                return true;
            } 
        }
        return false;
    }

    /**
     * @brief Retrieve the last command-line argument.
     * 
     * @tparam unusedT Unused template parameter.
     * @param argc Number of command-line arguments.
     * @param argv Array of command-line arguments.
     * @return The string_view of the last command-line argument.
     */
    template<typename unusedT = char>
    std::string_view the_last_arg(int argc, char* argv[]) {
        return std::string_view(argv[argc - 1]);
    }

    /**
     * @brief Process simple options.
     * 
     * @tparam FunctorT Type of the functor.
     * @param argc Number of command-line arguments.
     * @param argv Array of command-line arguments.
     * @param func Functor to process each option.
     */
    template<typename FunctorT>
    void process_option_simply(int argc, char* argv[], FunctorT func) {
        std::span<char*> args(argv, argc);

        for (auto& e : args.subspan(1)) {
            func(std::string_view(e));
        }
    }
}

#endif // PROCESS_OPTION_SIMPLY_HPP_INCLUDED

/**
 * @usage
#include <kkd_hpp/process_option_simply.hpp>
int main(int argc, char* argv[]) {
    const char* helpText = "Usage: only the last argument is used as output file name.";
    if (kkd::process_help(argc, argv, helpText, true)) {
        return 0;
    } 
    std::cout << kkd::the_last_arg(argc, argv) << std::endl;
    return 0;
}
 */