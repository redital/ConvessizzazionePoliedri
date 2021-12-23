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

#include "Input.hpp"
#include "StringUtilities.hpp"
#include "CsvExporter.hpp"

namespace GeDiM
{
    // ***************************************************************************
    map<string, InputPropertySupportedTypes::SupportedTypes> Input::propertyTypes;
    map<string, void*> Input::properties;
    unsigned int Input::numberProperties = 0;
    // ***************************************************************************
    Output::ExitCodes Input::RemoveProperty(const string& id, const InputPropertySupportedTypes::SupportedTypes& type)
    {
        switch (type)
        {
            case InputPropertySupportedTypes::Int:
                delete static_cast<const InputProperty<int>*>(properties[id]);
                break;
            case InputPropertySupportedTypes::Char:
                delete static_cast<const InputProperty<char>*>(properties[id]);
                break;
            case InputPropertySupportedTypes::String:
                delete static_cast<const InputProperty<string>*>(properties[id]);
                break;
            case InputPropertySupportedTypes::Double:
                delete static_cast<const InputProperty<double>*>(properties[id]);
                break;
            case InputPropertySupportedTypes::VectorInt:
                delete static_cast<const InputProperty<vector<int>>*>(properties[id]);
                break;
            case InputPropertySupportedTypes::VectorDouble:
                delete static_cast<const InputProperty<vector<double>>*>(properties[id]);
                break;
            case InputPropertySupportedTypes::Bool:
                delete static_cast<const InputProperty<bool>*>(properties[id]);
                break;
            default:
                Output::PrintWarningMessage("Property '%s' cannot be deleted. Type not recognized", false);
                break;
        }

        properties.erase(id);
        propertyTypes.erase(id);
        numberProperties--;

        return Output::Success;
    }
    // ***************************************************************************
    Output::ExitCodes Input::ConvertPropertyFromString(const string& id, const string& type, const string& value, const string& description)
    {
        auto convertedType = InputPropertySupportedTypes::StringToType(type);

        Output::ExitCodes result;

        switch (convertedType)
        {
            case InputPropertySupportedTypes::Int:
            {
                result = AddProperty(id, int(), description);
                if (result != Output::Success)
                    return result;

                int parsedValue;
                result = StringUtilities::Parse(value, parsedValue);
                if (result != Output::Success)
                    return result;

                result = SetPropertyValue(id, parsedValue);
                if (result != Output::Success)
                    return result;
                break;
            }
            case InputPropertySupportedTypes::Char:
            {
                result = AddProperty(id, char(), description);
                if (result != Output::Success)
                    return result;

                char parsedValue;
                result = StringUtilities::Parse(value, parsedValue);
                if (result != Output::Success)
                    return result;

                result = SetPropertyValue(id, parsedValue);
                if (result != Output::Success)
                    return result;

                break;
            }
            case InputPropertySupportedTypes::String:
            {
                result = AddProperty(id, string(), description);
                if (result != Output::Success)
                    return result;

                string parsedValue;
                result = StringUtilities::Parse(value, parsedValue);
                if (result != Output::Success)
                    return result;

                result = SetPropertyValue(id, parsedValue);
                if (result != Output::Success)
                    return result;

                break;
            }
            case InputPropertySupportedTypes::Double:
            {
                result = AddProperty(id, double(), description);
                if (result != Output::Success)
                    return result;

                double parsedValue;
                result = StringUtilities::Parse(value, parsedValue);
                if (result != Output::Success)
                    return result;

                result = SetPropertyValue(id, parsedValue);
                if (result != Output::Success)
                    return result;

                break;
            }
            case InputPropertySupportedTypes::VectorInt:
            {
                result = AddProperty(id, vector<int>(), description);
                if (result != Output::Success)
                    return result;

                vector<int> parsedValue;
                result = StringUtilities::Parse(value, parsedValue);
                if (result != Output::Success)
                    return result;

                result = SetPropertyValue(id, parsedValue);
                if (result != Output::Success)
                    return result;

                break;
            }
            case InputPropertySupportedTypes::VectorDouble:
            {
                result = AddProperty(id, vector<double>(), description);
                if (result != Output::Success)
                    return result;

                vector<double> parsedValue;
                result = StringUtilities::Parse(value, parsedValue);
                if (result != Output::Success)
                    return result;

                result = SetPropertyValue(id, parsedValue);
                if (result != Output::Success)
                    return result;

                break;
            }
            case InputPropertySupportedTypes::Bool:
            {
                result = AddProperty(id, bool(), description);
                if (result != Output::Success)
                    return result;

                bool parsedValue;
                result = StringUtilities::Parse(value, parsedValue);
                if (result != Output::Success)
                    return result;

                result = SetPropertyValue(id, parsedValue);
                if (result != Output::Success)
                    return result;

                break;
            }
            default:
                Output::PrintErrorMessage("Property '%s': type not supported", false, id.c_str());
                return Output::GenericError;
        }

        return Output::Success;
    }
    // ***************************************************************************
    Output::ExitCodes Input::AddProperty(const string& id, const char* value, const string& description)
    {
        RemoveProperty(id);

        properties.insert(pair<string, void*>(id, new InputProperty<string>()));
        propertyTypes.insert(pair<string, InputPropertySupportedTypes::SupportedTypes>(id, InputPropertySupportedTypes::String));
        numberProperties++;

        InputProperty<string>& property = GetProperty<string>(id);

        property.SetId(id);
        property.SetValue(string(value));
        property.SetDescription(description);

        return Output::Success;
    }
    // ***************************************************************************
    Output::ExitCodes Input::SetPropertyValue(const string& id, const char* value)
    {
        if (!ExistsProperty(id))
            return Output::GenericError;

        InputProperty<string>& property = GetProperty<string>(id);
        property.SetValue(string(value));

        return Output::Success;
    }
    // ***************************************************************************
    Output::ExitCodes Input::InitializeFromCsv(const string& inputFile, const bool& hasHeader, const char& separator)
    {
        if (!Output::FileExists(inputFile))
        {
            Output::PrintErrorMessage("%s - File '%s' not found", false, __func__, inputFile.c_str());
            return Output::GenericError;
        }

        ifstream inFile;
        inFile.open(inputFile.c_str());

        if(!inFile.is_open())
        {
            Output::PrintErrorMessage("%s - Cannot open file '%s'", false, __func__, inputFile.c_str());
            return Output::GenericError;
        }

        int numberLines = 0;
        while (!inFile.eof())
        {
            string line;
            getline(inFile, line);

            // Skip Comment Line
            if(line[0] == '#')
                continue;

            if (numberLines == 0 && hasHeader)
            {
                numberLines++;
                continue;
            }

            vector<string> columns = StringUtilities::Split(line, separator);

            if (columns.size() < 2)
                continue;

            switch (columns.size())
            {
                case 2:
                {
                    const string& id = columns[0];
                    const string& type = "string";
                    const string& value = columns[1];

                    ConvertPropertyFromString(id, type, value);
                    break;
                }
                case 3:
                {
                    const string& id = columns[0];
                    const string& type = columns[1];
                    const string& value = columns[2];

                    ConvertPropertyFromString(id, type, value);
                    break;
                }
                case 4:
                {
                    const string& id = columns[0];
                    const string& type = columns[1];
                    const string& value = columns[2];
                    const string& description = columns[3];

                    ConvertPropertyFromString(id, type, value, description);
                    break;
                }
                default:
                    break;
            }
        }

        inFile.close();

        return Output::Success;
    }
    // ***************************************************************************
    Output::ExitCodes Input::InitializeFromIni(const string& inputFile)
    {
        if (!Output::FileExists(inputFile))
        {
            Output::PrintErrorMessage("%s - File '%s' not found", false, __func__, inputFile.c_str());
            return Output::GenericError;
        }

        ifstream inFile;
        inFile.open(inputFile.c_str());

        if(!inFile.is_open())
        {
            Output::PrintErrorMessage("%s - Cannot open file '%s'", false, __func__, inputFile.c_str());
            return Output::GenericError;
        }

        // Find Property in File
        while (!inFile.eof())
        {
            string line;

            getline(inFile, line);

            // Skip Comment Line
            if(line[0] == '#')
                continue;

            vector<string> columns = StringUtilities::Split(line, ' ');

            if (columns.size() < 2)
                continue;

            switch (columns.size())
            {
                case 2:
                {
                    const string& id = columns[0];
                    const string& type = "string";
                    const string& value = columns[1];

                    ConvertPropertyFromString(id, type, value);
                    break;
                }
                case 3:
                {
                    const string& id = columns[0];
                    const string& type = columns[1];
                    const string& value = columns[2];

                    ConvertPropertyFromString(id, type, value);
                    break;
                }
                default:
                    break;
            }
        }

        inFile.close();

        return Output::Success;
    }
    // ***************************************************************************
    Output::ExitCodes Input::Initialize(const int& argc, char **argv, const string& format)
    {
        char typeSeparator = ':';
        char valueSeparator = '=';

        Output::ExitCodes result;

        result = StringUtilities::FindSeparator(format, "id", "type", typeSeparator);

        if (result != Output::Success)
        {
            Output::PrintErrorMessage("Input Format '%s' wrong. No type separator found", true, format.c_str());
            return result;
        }

        result = StringUtilities::FindSeparator(format, "type", "value", valueSeparator);

        if (result != Output::Success)
        {
            Output::PrintErrorMessage("Input Format '%s' wrong. No value separator found", true, format.c_str());
            return result;
        }

        for (int i = 0; i < argc; i++)
        {
            vector<string> strings = StringUtilities::Split(argv[i], { typeSeparator, valueSeparator });

            switch (strings.size())
            {
                case 2:
                {
                    const string& id = strings[0];
                    const string& type = "string";
                    const string& value = strings[1];

                    ConvertPropertyFromString(id, type, value);
                    break;
                }
                case 3:
                {
                    const string& id = strings[0];
                    const string& type = strings[1];
                    const string& value = strings[2];

                    ConvertPropertyFromString(id, type, value);
                    break;
                }
                default:
                    break;
            }
        }

        return Output::Success;
    }
    // ***************************************************************************
    Output::ExitCodes Input::ExportToCsv(const string& filePath, const bool& append, const char& separator)
    {
        CsvExporter exporter(separator);

        exporter.AddFieldName("name");
        exporter.AddFieldName("type");
        exporter.AddFieldName("value");
        exporter.AddFieldName("description");

        for (auto it = propertyTypes.begin(); it != propertyTypes.end(); it++)
        {
            const string& id = it->first;
            const InputPropertySupportedTypes::SupportedTypes type = it->second;

            switch (type)
            {
                case InputPropertySupportedTypes::Int:
                    exporter.AddRow(GetProperty<int>(id));
                    break;
                case InputPropertySupportedTypes::Char:
                    exporter.AddRow(GetProperty<char>(id));
                    break;
                case InputPropertySupportedTypes::String:
                    exporter.AddRow(GetProperty<string>(id));
                    break;
                case InputPropertySupportedTypes::Double:
                    exporter.AddRow(GetProperty<double>(id));
                    break;
                case InputPropertySupportedTypes::VectorInt:
                    exporter.AddRow(GetProperty<vector<int>>(id));
                    break;
                case InputPropertySupportedTypes::VectorDouble:
                    exporter.AddRow(GetProperty<vector<double>>(id));
                    break;
                case InputPropertySupportedTypes::Bool:
                    exporter.AddRow(GetProperty<bool>(id));
                    break;
                default:
                    Output::PrintWarningMessage("Property '%s' cannot be converted. Type not recognized", false);
                    break;
            }
        }

        return exporter.Export(filePath, append);
    }
    // ***************************************************************************
    Output::ExitCodes Input::ExportToIni(const string& filePath, const bool& append, const string& section)
    {
        IniExporter exporter(section);

        for (auto it = propertyTypes.begin(); it != propertyTypes.end(); it++)
        {
            const string& id = it->first;
            const InputPropertySupportedTypes::SupportedTypes type = it->second;

            switch (type)
            {
                case InputPropertySupportedTypes::Int:
                    exporter.AddProperty(GetProperty<int>(id));
                    break;
                case InputPropertySupportedTypes::Char:
                    exporter.AddProperty(GetProperty<char>(id));
                    break;
                case InputPropertySupportedTypes::String:
                    exporter.AddProperty(GetProperty<string>(id));
                    break;
                case InputPropertySupportedTypes::Double:
                    exporter.AddProperty(GetProperty<double>(id));
                    break;
                case InputPropertySupportedTypes::VectorInt:
                    exporter.AddProperty(GetProperty<vector<int>>(id));
                    break;
                case InputPropertySupportedTypes::VectorDouble:
                    exporter.AddProperty(GetProperty<vector<double>>(id));
                    break;
                case InputPropertySupportedTypes::Bool:
                    exporter.AddProperty(GetProperty<bool>(id));
                    break;
                default:
                    Output::PrintWarningMessage("Property '%s' cannot be converted. Type not recognized", false);
                    break;
            }
        }

        return exporter.Export(filePath, append);
    }
    // ***************************************************************************
    Output::ExitCodes Input::Reset()
    {
        for (auto it = propertyTypes.begin(); it != propertyTypes.end(); it++)
        {
            const string& id = it->first;
            const InputPropertySupportedTypes::SupportedTypes& type = it->second;

            RemoveProperty(id, type);
        }

        numberProperties = 0;

        return Output::Success;
    }
    // ***************************************************************************
    Output::ExitCodes Input::RemoveProperty(const string& id)
    {
        if (!ExistsProperty(id))
            return  Output::GenericError;

        return RemoveProperty(id, GetPropertyType(id));
    }
    // ***************************************************************************
}
