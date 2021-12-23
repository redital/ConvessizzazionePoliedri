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

#ifndef __ICSVEXPORT_H
#define __ICSVEXPORT_H

#include <string>

using namespace std;

namespace GeDiM
{
    class ICsvExport;

    class ICsvExport
    {
        public:
            virtual ~ICsvExport() { };

            /// Convert the object to Csv
            /// @return empty string if error
            virtual string ToCsv(const char& separator = ';') const = 0;
    };
}

#endif // __ICSVEXPORT_H
