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

#include "CsvExporter.hpp"

namespace GeDiM
{
    // ***************************************************************************
    Output::ExitCodes CsvExporter::Export(const string& filePath, const bool& append)
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

        if (!append)
        {
            int counter = 0;
            for (auto it = header.begin(); it != header.end(); it++)
            {
                if (counter != 0)
                    file<< separator;

                file<< *it;
                counter++;
            }

            file<< endl;
        }

        for (auto it = rows.begin(); it != rows.end(); it++)
        {
            const ICsvExport& row = **it;

            string rowString = row.ToCsv(separator);

            if (rowString.empty())
                continue;

            file<< rowString<< endl;
        }

        file.close();

        return Output::Success;
    }
    // ***************************************************************************
}
