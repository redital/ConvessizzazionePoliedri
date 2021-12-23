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
// First added:  2020-02-06

#include "IniExporter.hpp"

namespace GeDiM
{
    // ***************************************************************************
    Output::ExitCodes IniExporter::Export(const string& filePath, const bool& append)
    {
        ofstream file;

        if (append)
            file.open(filePath.c_str(), ofstream::app);
        else
            file.open(filePath.c_str());

        if (file.fail())
        {
            Output::PrintErrorMessage("%s - File '%s' cannot be opened", false, __func__, filePath.c_str());
            return Output::GenericError;
        }

        if (!append && !section.empty())
            file<< "# "<< section<< endl;

        for (auto it = properties.begin(); it != properties.end(); it++)
        {
            const IIniExport& row = **it;

            const string& description = row.IniDescription();
            const string& key = row.IniKey();
            const string& type = row.IniType();
            const string& value = row.IniValue();

            if (key.empty() || value.empty() || type.empty())
                continue;

            file<< "#####################################################"<< endl;

            if (!description.empty())
                file<< "# "<< description<< endl;

            file<< key<< " "<< type<< " "<< value<< endl;
        }

        file.close();

        return Output::Success;
    }
    // ***************************************************************************
}
