#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

namespace Parser
{

extern const char DELIMITERS[];

std::vector<std::string> SplitLine(std::string const& line, std::string del = " ");
ssize_t FindOpeningDelimiter(std::string const& s);
ssize_t FindClosingDelimiter(std::string const& s);

template<typename T>
T Parse(std::string const& str)
{
        std::stringstream ss;
        T val;

        ss << str;
        ss >> val;

        return val;
}

template<typename T>
std::vector<T> ParseArray(std::string const& str)
{
        std::vector<T> arr;
        std::string str_cp = str;

        // Locate indices of brackets
        ssize_t openBracket = FindOpeningDelimiter(str_cp);
        if (openBracket > -1)
                str_cp.replace(openBracket, 1, "");
        ssize_t closeBracket = FindClosingDelimiter(str_cp); // is called after replace, as the index is otherwise incorrect
        if (closeBracket > -1)
               str_cp.replace(closeBracket, 1, "");

        
        std::vector<std::string> stringVals = SplitLine(str_cp, ",");
        
        for (auto stringVal : stringVals) {
                if (stringVal.length() > 0)
                        arr.push_back(Parse<T>(stringVal));       
        }

        return arr;
}



}
