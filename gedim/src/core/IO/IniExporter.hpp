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

#ifndef __INIEXPORTER_H
#define __INIEXPORTER_H

#include "Output.hpp"
#include "IIniExport.hpp"

using namespace MainApplication;

namespace GeDiM
{
    class IniExporter;

    class IniExporter
    {
        protected:
            string section;
            list<const IIniExport*> properties;

        public:
            IniExporter() { section = ""; }
            IniExporter(const string& _section) { SetSection(_section); }

            void SetSection(const string& _section) { section = _section; }

            /// Add row to the Csv file
            void AddProperty(const IIniExport& property) { properties.push_back(&property); }

            /// Export to csv file
            Output::ExitCodes Export(const string& filePath, const bool& append = false);

    };
}

#endif // __INIEXPORTER_H
