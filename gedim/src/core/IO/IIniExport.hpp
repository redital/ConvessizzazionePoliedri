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

#ifndef __IINIEXPORT_H
#define __IINIEXPORT_H

#include <string>

using namespace std;

namespace GeDiM
{
    class IIniExport;

    class IIniExport
    {
        public:
            virtual ~IIniExport() { };

            /// Get the description
            virtual string IniDescription() const = 0;

            /// Get the key
            virtual string IniKey() const = 0;

            /// Get the type
            virtual string IniType() const = 0;

            /// Get the value
            virtual string IniValue() const = 0;
    };
}

#endif // __IINIEXPORT_H
