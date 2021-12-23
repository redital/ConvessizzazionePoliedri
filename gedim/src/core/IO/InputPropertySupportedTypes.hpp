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
// First added:  2020-02-07

#ifndef __INPUTPROPERTYSUPPORTEDTYPES_H
#define __INPUTPROPERTYSUPPORTEDTYPES_H

#include <string>
#include <typeinfo>

#include "StringUtilities.hpp"

using namespace std;

namespace GeDiM
{
    class InputPropertySupportedTypes;

    class InputPropertySupportedTypes
    {
        public:
            enum SupportedTypes
            {
                Unknown = 0,
                Int = 1,
                Char = 2,
                String = 3,
                Double = 4,
                VectorInt = 5,
                VectorDouble = 6,
                Bool = 7
            };

            /// Get Supported Type from the type
            template<class K>
            static SupportedTypes GetSupportedType()
            {
                const char* propertyType = typeid(K).name();

                if (propertyType == typeid(int).name())
                    return Int;

                if (propertyType == typeid(char).name())
                    return Char;

                if (propertyType == typeid(double).name())
                    return Double;

                if (propertyType == typeid(string).name())
                    return String;

                if (propertyType == typeid(vector<int>).name())
                    return VectorInt;

                if (propertyType == typeid(vector<double>).name())
                    return VectorDouble;

                if (propertyType == typeid(bool).name())
                    return Bool;

                return  Unknown;
            }

            template<class K>
            static string TypeToString() { return TypeToString(GetSupportedType<K>()); }

            /// Convert the SupportedType to string
            static string TypeToString(const SupportedTypes& type)
            {
                switch (type)
                {
                    case Int:
                        return "int";
                    case Char:
                        return "char";
                    case String:
                        return "string";
                    case Double:
                        return "double";
                    case VectorInt:
                        return "vector<int>";
                    case VectorDouble:
                        return "vector<double>";
                    case Bool:
                        return "bool";
                    default:
                        return "unknown";
                }
            }

            /// Convert a string to SupportedType
            static SupportedTypes StringToType(const string& stringType)
            {
                string stringTypeToLow = StringUtilities::ToLower(stringType);

                if (stringTypeToLow == "int")
                    return Int;
                if (stringTypeToLow == "char")
                    return Char;
                if (stringTypeToLow == "string")
                    return String;
                if (stringTypeToLow == "double")
                    return Double;
                if (stringTypeToLow == "vector<int>")
                    return VectorInt;
                if (stringTypeToLow == "vector<double>")
                    return VectorDouble;
                if (stringTypeToLow == "bool")
                    return Bool;

                return Unknown;
            }

            template<class K>
            static bool IsSupported() { return GetSupportedType<K>() != InputPropertySupportedTypes::Unknown; }
    };
}

#endif // __INPUTPROPERTYSUPPORTEDTYPES_H
