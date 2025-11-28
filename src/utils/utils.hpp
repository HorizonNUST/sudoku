#pragma once
#include <functional>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>

#include "__macros.hpp"

namespace utils
{
    /// @brief Get Random `int` in given range
    /// @param minInclusive from Inclusive
    /// @param maxInclusive to Inclusive
    inline int getRandomInt(int minInclusive, int maxInclusive)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(minInclusive, maxInclusive);
        return distrib(gen);
    }

    /// @brief Get Random `float` in given range
    /// @param minInclusive from Inclusive
    /// @param maxInclusive to Inclusive
    inline float getRandomFloat(float minInclusive, float maxInclusive)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distrib(minInclusive, maxInclusive);
        return distrib(gen);
    }

    /// @brief Get Random Bool
    inline bool getRandomBool()
    {
        return getRandomInt(0, 1);
    }

    /// @brief get random float between 0 and 1
    inline float getRandom01()
    {
        return getRandomFloat(0, 1);
    }

    /// @brief Get random sfml `sf::Vector2f` with given magnitude
    /// @param magnitude the magnitude
    inline sf::Vector2f getRandomVector2f(float magnitude)
    {
        return {magnitude * getRandomFloat(0, 1), magnitude * getRandomFloat(0, 1)};
    }

    /// @brief Get random sfml `sf::Vector2i` with given magnitude
    /// @param magnitude the magnitude
    inline sf::Vector2i getRandomVector2i(float magnitude)
    {
        sf::Vector2f vec = getRandomVector2f(magnitude);
        return sf::Vector2i(
            static_cast<int>(vec.x),
            static_cast<int>(vec.y));
    }

    struct printConfig
    {
        static constexpr bool printLineNum = true;
        static constexpr bool functionName = true;
        static constexpr bool fileName = true;

        static inline constexpr bool hasDebugPrefix()
        {
            return printLineNum || functionName || fileName;
        }
    };

    /// @brief ### !Use MACRO `PRINT(message)` or `DEBUG_PRINT(message)`
    inline void printLine(const std::string &fileName, const std::string &functionName, int lineNum, const std::string &message, const std::string &prefix = "")
    {
        using cf = printConfig;

        std::stringstream debugPrefix;
        if (cf::hasDebugPrefix())
        {
            debugPrefix << "["
                        << (cf::fileName ? fileName : "")
                        << (cf::printLineNum ? (" : " + std::to_string(lineNum)) : "")
                        << (cf::functionName ? (" @ " + functionName) : "")
                        << "] ";
        }

        std::cout << prefix << debugPrefix.str() << message << "\n";
    }
}

// static to limit scope to this file
static inline std::string file_name(const char* path) {
    return std::filesystem::path(path).filename().string();
}

#define PRINT(message) \
    utils::printLine(file_name(__FILE__).c_str(), __func__, __LINE__, message)

#if DEBUG == 1
#define DEBUG_PRINT(message) \
    utils::printLine(file_name(__FILE__).c_str(), __func__, __LINE__, message, "* ")
#else
#define DEBUG_PRINT(message)
#endif