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

#ifndef __INPUT_H
#define __INPUT_H

#include <string>
#include <map>

#include "Output.hpp"
#include "InputProperty.hpp"
#include "StringUtilities.hpp"

using namespace std;
using namespace MainApplication;

namespace GeDiM
{
    class Input;

    class Input
    {        
        protected:
            static unsigned int numberProperties;
            static map<string, InputPropertySupportedTypes::SupportedTypes> propertyTypes;
            static map<string, void*> properties;

            /// Remove Single Property by Id and Type
            static Output::ExitCodes RemoveProperty(const string& id, const InputPropertySupportedTypes::SupportedTypes& type);

            /// Get Property Type by Id
            static InputPropertySupportedTypes::SupportedTypes& GetPropertyType(const string& id) { return propertyTypes[id]; }

            /// Get Property by Id
            template<class T>
            static InputProperty<T>& GetProperty(const string& id) { return *static_cast<InputProperty<T>*>(properties[id]); }
        public:
            static const unsigned int& NumberProperties() { return numberProperties;  }

            /// Read the configuration from csv file
            static Output::ExitCodes InitializeFromCsv(const string& inputFile, const bool& hasHeader = true, const char& separator = ';');

            /// Read the configuration from ini file
            static Output::ExitCodes InitializeFromIni(const string& inputFile);

            /// Read the configuration from command arguments
            /// @note format shall contain keyword id + char + type + char + value (example: id:type=value)
            static Output::ExitCodes Initialize(const int& argc, char** argv, const string& format="id:type=value");

            /// Export the configuration to csv file
            static Output::ExitCodes ExportToCsv(const string& filePath, const bool& append = false, const char& separator = ';');

            /// Export the configuration to ini file
            static Output::ExitCodes ExportToIni(const string& filePath, const bool& append = false, const string& section = "");

            /// Reset the Input class
            static Output::ExitCodes Reset();

            /// Remove Single Property
            static Output::ExitCodes RemoveProperty(const string &id);

            /// Check if Property exists
            static bool ExistsProperty(const string &id) { return !(propertyTypes.find(id) == propertyTypes.end()); }

            template<class T>
            static bool CheckPropertyType(const string &id) { return GetPropertyType(id) == InputPropertySupportedTypes::GetSupportedType<T>(); }

            /// Convert Property by string Type and string value
            static Output::ExitCodes ConvertPropertyFromString(const string& id, const string& type, const string& value, const string& description = "");

            /// Add or Overwrite Property
            template<class T>
            static Output::ExitCodes AddProperty(const string& id, const T value = T(), const string& description = "")
            {
                if (!InputPropertySupportedTypes::IsSupported<T>())
                {
                    Output::PrintErrorMessage("Property '%s': type not supported", false, id.c_str());
                    return Output::GenericError;
                }

                RemoveProperty(id);


                properties.insert(pair<string, void*>(id, new InputProperty<T>()));
                propertyTypes.insert(pair<string, InputPropertySupportedTypes::SupportedTypes>(id, InputPropertySupportedTypes::GetSupportedType<T>()));
                numberProperties++;

                InputProperty<T>& property = GetProperty<T>(id);

                property.SetId(id);
                property.SetValue(value);
                property.SetDescription(description);

                return Output::Success;
            }

            /// Add or Overwrite Property converting const char* to string
            static Output::ExitCodes AddProperty(const string& id, const char* value = "", const string& description = "");

            /// Set Property Value
            template<class T>
            static Output::ExitCodes SetPropertyValue(const string& id, const T value)
            {
                if (!ExistsProperty(id))
                    return Output::GenericError;

                if (!CheckPropertyType<T>(id))
                {
                    string propertyType = InputPropertySupportedTypes::TypeToString(GetPropertyType(id));
                    string valueType = InputPropertySupportedTypes::TypeToString<T>();
                    Output::PrintWarningMessage("Property '%s' has type %s and not %s", false, id.c_str(), propertyType.c_str(), valueType.c_str());
                    return  Output::GenericError;
                }

                InputProperty<T>& property = GetProperty<T>(id);
                property.SetValue(value);

                return Output::Success;
            }

            /// Set Property Value converting const char* to string
            static Output::ExitCodes SetPropertyValue(const string& id, const char* value);

            /// Get Property Value
            template<class T>
            static Output::ExitCodes GetPropertyValue(const string& id, T& value)
            {
                if (!ExistsProperty(id))
                    return Output::GenericError;

                if (!CheckPropertyType<T>(id))
                {
                    string propertyType = InputPropertySupportedTypes::TypeToString(GetPropertyType(id));
                    string valueType = InputPropertySupportedTypes::TypeToString<T>();
                    Output::PrintWarningMessage("Property '%s' has type %s and not %s", false, id.c_str(), propertyType.c_str(), valueType.c_str());
                    return  Output::GenericError;
                }

                const InputProperty<T>& property = GetProperty<T>(id);
                value = property.Value();

                return Output::Success;
            }
    };
}

#endif // __INPUT_H
