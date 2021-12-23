// Copyright (C) 2020 Vicini Fabio
//
// This file is part of the dissertation of the author.
//
// This is a free program: you can redistribute it and/or modify
// it under the terms of the author.
//
// This program is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.
//
// Modified by Vicini Fabio 2020
//
// First added:  2020-02-05

#ifndef __STRINGUTILITIES_H
#define __STRINGUTILITIES_H

#include <string>
#include <vector>

#include "Output.hpp"

using namespace MainApplication;
using namespace std;

namespace GeDiM
{
    class StringUtilities;

    class StringUtilities
    {
        private:
        public:
            /// Divide a string by a character in a vector of strings
            /// @example stringToSplit="pippo_pe" character='_' -> result=["pippo", "pe"]
            static vector<string> Split(const string& stringToSplit, const char& character = ' ');

            /// Divide a string by a set of characters in a vector of strings
            /// @example stringToSplit="pippo_pe:pu" characters={'_',':'} -> result=["pippo", "pe", "pu"]
            static vector<string> Split(const string& stringToSplit, const vector<char>& characters = vector<char>(' '));

            /// Find inside a string a separator between two keys
            /// @example stringToSearch="id:value" keyOne="id" keyTwo="value" -> separator=':'
            static Output::ExitCodes FindSeparator(const string& stringToSearch, const string& keyOne, const string& keyTwo, char& separator);

            /// Convert string to lower
            static string ToLower(const string& input);

            /// Convert string to upper
            static string ToUpper(const string& input);

            /// Parse a string to object
            template<class T>
            static Output::ExitCodes Parse(const string& objectString, T& objectConverted)
            {
                istringstream convert;

                convert.str(objectString);
                return (convert >> objectConverted) ? Output::Success : Output::GenericError;
            }

            static Output::ExitCodes Parse(const string& objectString, string& objectConverted) { objectConverted = objectString; return Output::Success; }
            static Output::ExitCodes Parse(const string& objectString, bool& objectConverted);
            /// @note Supported vector separator are {',' ';' ' '}
            static Output::ExitCodes Parse(const string& objectString, vector<int>& objectConverted);
            /// @note Supported vector separator are {',' ';' ' '}
            static Output::ExitCodes Parse(const string& objectString, vector<double>& objectConverted);
    };
}

#endif // __STRINGUTILITIES_H
