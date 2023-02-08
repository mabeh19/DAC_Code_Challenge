#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include "parser.hpp"

const char OPENING_DELIMITERS[] = {
        '[',
        '{',
        '<',
        '('
};

const char CLOSING_DELIMITERS[] = {
        ']',
        '}',
        '>',
        ')'
};

ssize_t Parser::FindOpeningDelimiter(std::string const& s)
{
        ssize_t i = 0;
        for (char delim : OPENING_DELIMITERS) {
                if ((i = s.find(delim)) >= 0) {
                        return i;
                }
        }

        return -1;
}

ssize_t Parser::FindClosingDelimiter(std::string const& s)
{
        ssize_t i = 0;
        for (char delim : CLOSING_DELIMITERS) {
                if ((i = s.find(delim)) >= 0) {
                        return i;
                }
        }

        return -1;
}



static bool FrontIsDelimiter(std::string const& s)
{
        char front = s.front();

        for (char c : OPENING_DELIMITERS) {
                if (front == c) {
                        return true;
                }
        }

        return false;
}

static void Coalesce(std::vector<std::string> &tokens)
{
        // Handle multi word names
        while (tokens.size() > 3) {
                std::string toRemove;
                if (FrontIsDelimiter(tokens[2])) {
                        // If the array of deps has to be coalesced...
                        tokens[2].append(tokens[3]);
                        toRemove = tokens[3];
                } else {
                        // If the name has to be coalesced...
                        tokens[1].append(" "); // insert the removed space
                        tokens[1].append(tokens[2]);
                        toRemove = tokens[2];
                }
                tokens.erase(std::find(tokens.begin(), tokens.end(), toRemove));
        }
}

std::vector<std::string> Parser::SplitLine(std::string const& line, std::string del)
{
        std::vector<std::string> tokens;
        int start, end = -1 * del.size();

        do {
                start = end + del.size();
                end = line.find(del, start);
                std::string string = line.substr(start, end - start);
                tokens.push_back(string);
        } while (end != -1);

        if (del == " ") {
                Coalesce(tokens);
        }

        return tokens;
}

