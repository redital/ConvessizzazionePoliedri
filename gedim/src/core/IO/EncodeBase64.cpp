#include "EncodeBase64.hpp"
#include <iostream>

namespace MainApplication
{
	// ***************************************************************************
	const string EncodeBase64::base64_chars ="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
																		 "abcdefghijklmnopqrstuvwxyz"
																		 "0123456789+/";
	// ***************************************************************************
	string EncodeBase64::Encode(const string& stringToEncode)
	{
		string stringEncoded;
		unsigned char const* bytes_to_encode = reinterpret_cast<const unsigned char*>(stringToEncode.c_str());
		unsigned int in_len = stringToEncode.length();
		int i = 0, j = 0;
		unsigned char char_array_3[3], char_array_4[4];

		while (in_len--)
		{
			char_array_3[i++] = *(bytes_to_encode++);
			if (i == 3)
			{
				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;

				for(i = 0; (i <4) ; i++)
					stringEncoded += base64_chars[char_array_4[i]];
				i = 0;
			}
		}

		if (i)
		{
			for (j = i; j < 3; j++)
				char_array_3[j] = '\0';

			char_array_4[0] = ( char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

			for (j = 0; (j < i + 1); j++)
				stringEncoded += base64_chars[char_array_4[j]];

			while ((i++ < 3))
				stringEncoded += '=';
		}

		return stringEncoded;
	}
	// ***************************************************************************
	std::string EncodeBase64::Decode(const string& stringToDecode)
	{
		int in_len = stringToDecode.size();
		int i = 0;
		int j = 0;
		int in_ = 0;
		unsigned char char_array_4[4], char_array_3[3];
		string stringDecoded;

		while (in_len-- && ( stringToDecode[in_] != '=') && IsBase64(stringToDecode[in_]))
		{
			char_array_4[i++] = stringToDecode[in_]; in_++;
			if (i ==4)
			{
				for (i = 0; i <4; i++)
					char_array_4[i] = base64_chars.find(char_array_4[i]);

				char_array_3[0] = ( char_array_4[0] << 2       ) + ((char_array_4[1] & 0x30) >> 4);
				char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
				char_array_3[2] = ((char_array_4[2] & 0x3) << 6) +   char_array_4[3];

				for (i = 0; (i < 3); i++)
					stringDecoded += char_array_3[i];
				i = 0;
			}
		}

		if (i)
		{
			for (j = 0; j < i; j++)
				char_array_4[j] = base64_chars.find(char_array_4[j]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

			for (j = 0; (j < i - 1); j++)
				stringDecoded += char_array_3[j];
		}

		return stringDecoded;
	}
}
