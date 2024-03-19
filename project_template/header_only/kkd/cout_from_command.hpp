/**
 * @file cout_from_command.hpp
 * @author Your Name (you@domain.com)
 * @brief Header file containing functions to execute shell commands and capture output.
 * @version 0.1
 * @date 2023-12-23
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef COUT_FROM_COMMAND_HPP_DEFINED
#define COUT_FROM_COMMAND_HPP_DEFINED

#include <iostream>
#include <stdio.h>
#include <array>

namespace kkd {
    
    template<typename Unused=char>
    /**
     * Executes a command in the shell and captures the output.
     * @param cmd The command to execute.
     * @return The output of the command as a string.
     */
    std::string cout_from_command(const char* cmd) {
        std::array<char, 128> buffer;
        std::string result;
        FILE* pipe = popen(cmd, "r");
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
            result += buffer.data();
        }
        pclose(pipe);
        return result;
    }

    template<typename Unused=char>
    /**
     * Overloaded function to execute a command in the shell by accepting a string.
     * @param cmd The command to execute as a string.
     * @return The output of the command as a string.
     */
    std::string cout_from_command(const std::string cmd) {
        return cout_from_command(cmd.c_str());
    }

    /**
     * Converts a command into a PowerShell command.
     * @param cmd The command to convert to a PowerShell command.
     * @return The PowerShell command as a string.
     */
    std::string to_powershell(const auto cmd) {
        std::string result = "powershell -Command \"";
        return result + cmd + "\"";
    }

    template<typename Unused=char>
    /**
     * Executes a command using PowerShell and captures the output.
     * @param cmd The command to execute using PowerShell.
     * @return The output of the PowerShell command as a string.
     */
    std::string cout_from_powershell_command(const auto cmd) {
        return cout_from_command(to_powershell(cmd));
    }
}

#endif

/**
 * @usage
const char* command = "kkd_manage_path.exe -s";

std::string output = kkd::cout_from_command(command);
std::cout << "cout_from_command(command):\n" << output << std::endl;

std::string outputPowershell = kkd::cout_from_powershell_command(command);
std::cout << "cout_from_powershell_command(command):\n" << outputPowershell << std::endl;
 */