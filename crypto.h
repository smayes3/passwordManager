/*********************************************
*
* @file crypto.h
*
* @brief Crypto class and function declarations.
*
*********************************************/

#pragma once

#include "main.h"
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>

using namespace std;


class Crypto 
{
public:
	Crypto() {}; //constructor
	~Crypto() {}; //destructor
	string generateHash(string);

};


/*********************************************
*
* @brief Function that creates a hash for a given string.
*
* @detail Using OpenSSL SHA256 for hashing.
*
* @param unhashedString: string, the string input that needs to be hashed.
*
* @return hashedString: string, the value of unhashedString after hash applied.
*
*********************************************/
string Crypto::generateHash(string unhashedString)
{
	unsigned char buffer[SHA256_DIGEST_LENGTH];
	string hashedString;

	SHA256((const unsigned char*)unhashedString.c_str(), unhashedString.size(), buffer);

	stringstream ss; //placeholder for string as it gets hashed
	ss << hex; 
	
	//hash the input string
	for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		ss << setw(2) << setfill('0') << int(buffer[i]);
	}

	hashedString = ss.str();
	ss << dec;

	return hashedString;

}//generateHash function