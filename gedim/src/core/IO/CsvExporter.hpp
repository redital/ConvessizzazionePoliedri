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

#ifndef __CSVEXPORTER_H
#define __CSVEXPORTER_H

#include "Output.hpp"
#include "ICsvExport.hpp"

using namespace MainApplication;

namespace GeDiM
{
    class CsvExporter;

    class CsvExporter
    {
        protected:
            char separator;
            list<string> header;
            list<const ICsvExport*> rows;

        public:
            CsvExporter() { separator = ';'; }
            CsvExporter(const char& _separator) { SetSeparator(_separator); }

            void SetSeparator(const char& _separator) { separator = _separator; }

            /// Add field name to header
            void AddFieldName(const string& fieldName) {  header.push_back(fieldName); }
            /// Add row to the Csv file
            void AddRow(const ICsvExport& row) { rows.push_back(&row); }

            /// Export to csv file
            Output::ExitCodes Export(const string& filePath, const bool& append = false);

    };
}

#endif // __CSVEXPORTER_H
