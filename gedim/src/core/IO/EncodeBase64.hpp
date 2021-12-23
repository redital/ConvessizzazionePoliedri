// Copyright (C) 2014 Vicini Fabio
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
// Modified by Vicini Fabio 2014
//
// First added:  2018-03-16

#ifndef BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A
#define BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A

#include <string>
#include <iostream>

using namespace std;

namespace MainApplication
{
	class EncodeBase64;

	class EncodeBase64
	{
		private:
			static const string base64_chars;

		public:
			static const bool IsBase64(unsigned char c) { return (isalnum(c) || (c == '+') || (c == '/')); }
			static string Encode(const string& stringToEncode);
			static string Decode(const string& stringToDecode);
	};
}
#endif /* BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A */
