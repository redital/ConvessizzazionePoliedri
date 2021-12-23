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

#include <sstream>
#include <algorithm>
#include <cctype>

#include "StringUtilities.hpp"

namespace GeDiM
{
    // ***************************************************************************
    vector<string> StringUtilities::Split(const string& stringToSplit, const char& character)
    {
        stringstream splitter(stringToSplit);
        string tempString;
        vector<string> strings;

        while (getline(splitter, tempString, character))
            strings.push_back(tempString);

        return strings;
    }
    // ***************************************************************************
    vector<string> StringUtilities::Split(const string& stringToSplit, const vector<char>& characters)
    {
        list<string> stringsTotal;
        stringsTotal.push_back(stringToSplit);

        for (unsigned int c = 0; c < characters.size(); c++)
        {
            const char& character = characters[c];

            list<string> subStrings;

            for (auto it = stringsTotal.begin(); it != stringsTotal.end(); ++it)
            {
                const string& subStringToSplit = *it;
                vector<string> strings = Split(subStringToSplit, character);

                for (unsigned int s = 0; s < strings.size(); s++)
                    subStrings.push_back(strings[s]);
            }

            stringsTotal.clear();
            for (auto it = subStrings.begin(); it != subStrings.end(); ++it)
                stringsTotal.push_back(*it);
        }

        return vector<string>(make_move_iterator(stringsTotal.begin()), make_move_iterator(stringsTotal.end()));
    }
    // ***************************************************************************
    Output::ExitCodes StringUtilities::FindSeparator(const string& stringToSearch, const string& keyOne, const string& keyTwo, char& separator)
    {
        size_t positionKeyOne = stringToSearch.find(keyOne);
        if (positionKeyOne == std::string::npos)
            return Output::GenericError;

        size_t positionKeyTwo = stringToSearch.find(keyTwo);
        if (positionKeyTwo == std::string::npos)
            return Output::GenericError;

        if (positionKeyTwo == positionKeyOne)
            return Output::GenericError;

        if (positionKeyTwo > positionKeyOne)
        {
            size_t separatorPosition = keyOne.length() + positionKeyOne;

            if (positionKeyTwo - separatorPosition != 1)
                return Output::GenericError;

            separator = stringToSearch[separatorPosition];
        }
        else
        {
            size_t separatorPosition = keyTwo.length() + positionKeyTwo;

            if (positionKeyOne - separatorPosition != 1)
                return Output::GenericError;

            separator = stringToSearch[separatorPosition];
        }

        return Output::Success;
    }
    // ***************************************************************************
    string StringUtilities::ToLower(const string& input)
    {
        string output = input;
        transform(output.begin(), output.end(), output.begin(), [](unsigned char c){ return std::tolower(c); });

        return output;
    }
    // ***************************************************************************
    string StringUtilities::ToUpper(const string& input)
    {
        string output = input;
        transform(output.begin(), output.end(), output.begin(), [](unsigned char c){ return std::toupper(c); });

        return output;
    }
    // ***************************************************************************
    Output::ExitCodes StringUtilities::Parse(const string& objectString, bool& objectConverted)
    {
        const string& objStringToLow = ToLower(objectString);

        if (objStringToLow == "false" || objStringToLow == "f" || objStringToLow == "0")
        {
            objectConverted = false;
            return Output::Success;
        }

        if (objStringToLow == "true" || objStringToLow == "t" || objStringToLow == "1")
        {
            objectConverted = true;
            return Output::Success;
        }

        return Output::GenericError;
    }
    // ***************************************************************************
    Output::ExitCodes StringUtilities::Parse(const string& objectString, vector<int>& objectConverted)
    {
        vector<string> numberStrings = Split(objectString, { '[', ',', ';', ']', ' '});

        list<int> numbers;
        for (unsigned int s = 0; s < numberStrings.size(); s++)
        {
            int number;
            auto result = Parse(numberStrings[s], number);

            if (result != Output::Success)
                return Output::GenericError;

            numbers.push_back(number);
        }

        objectConverted.clear();
        objectConverted.reserve(numbers.size());

        for (auto it = numbers.begin(); it != numbers.end(); it++)
            objectConverted.push_back(*it);

        return Output::Success;
    }
    // ***************************************************************************
    Output::ExitCodes StringUtilities::Parse(const string& objectString, vector<double>& objectConverted)
    {
        vector<string> numberStrings = Split(objectString, { '[', ',', ';', ']', ' '});

        list<double> numbers;
        for (unsigned int s = 0; s < numberStrings.size(); s++)
        {
            double number;
            auto result = Parse(numberStrings[s], number);

            if (result != Output::Success)
                return Output::GenericError;

            numbers.push_back(number);
        }

        objectConverted.clear();
        objectConverted.reserve(numbers.size());

        for (auto it = numbers.begin(); it != numbers.end(); it++)
            objectConverted.push_back(*it);

        return Output::Success;
    }
	// ***************************************************************************
}
