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
// First added:  2020-02-04

#ifndef __INPUTPROPERTY_H
#define __INPUTPROPERTY_H

#include <vector>
#include <string>

#include "ICsvExport.hpp"
#include "IniExporter.hpp"
#include "StringUtilities.hpp"
#include "InputPropertySupportedTypes.hpp"

using namespace std;

namespace GeDiM
{
    template <class T>
    class InputProperty;

    template <class T>
    class InputProperty : public ICsvExport, public IIniExport
    {
        protected:
            string id; ///< Id
            string description; ///< Description
            T value; ///< Actual Value

        public:
            InputProperty() { id = ""; description= ""; value = T(); }
            InputProperty(const string& _id, const T& _value) { id = _id; description= ""; value = _value; }
            InputProperty(const string& _id, const T& _value, const string& _description) { id = _id; description= _description; value = _value; }

            const string& Id() const { return id; }
            const string& Description() const { return description; }
            const T& Value() const { return value; }

            void SetId(const string& _id) { id = _id; }
            void SetValue(const T& _value) { value = _value; }
            void SetDescription(const string& _description) { description = _description; }

            virtual string ToCsv(const char &separator = ';') const override
            {
                if (!InputPropertySupportedTypes::IsSupported<T>())
                    return "";

                ostringstream propertyString;

                propertyString<< id<< separator;
                propertyString<< InputPropertySupportedTypes::TypeToString<T>()<< separator;
                propertyString<< value<< separator;
                propertyString<< description<< flush;

                return propertyString.str();
            }

            virtual string IniKey() const override { return id; }
            virtual string IniType() const override { return InputPropertySupportedTypes::TypeToString<T>(); }
            virtual string IniValue() const override { ostringstream propertyString; propertyString<< value<< flush;  return propertyString.str(); }
            virtual string IniDescription() const override { return description; }
    };
}

#endif // __INPUTPROPERTY_H
