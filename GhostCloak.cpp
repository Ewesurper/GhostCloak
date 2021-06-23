/*
Name: GhostCloak.cpp
Purpose: XOR raw shellcode using C++
Date Built: 12 MAY 2020
Date Last Modified: 8 JUNE 2020
Created By: Ewesurper
*/

//Includes
#include <fstream>
#include <iostream>
#include <vector>

//Main Function
//Program starts here
//argc is the number of arguments being passed into the program from command line
//argv is the array of arguments being passed
int main(int argc, char* argv[])
{
	//Check for correct number of arguments(2)
	if (argc != 2)
	{
		std::cout << "Incorrect number of arguments given." << std::endl;
		std::cout << "Usage: Ghostcloak.exe [binary file]" << std::endl;
		std::cout << "GhostCloak is exiting.";
		exit(EXIT_FAILURE);
	}

	//Create vector frk
	//First Round key
	//This vector stores your first secret key
	//This is the key that will be used to XOR your shellcode
	std::vector<uint8_t> frk = { 'H', 'e', 'l', 'l', 'D', 'i', 'v', 'e', 'r', 'o', 'f', 'L', 'y', 'k', 'o', 's'};

	//Read argument[1] as Binary
	std::ifstream ReadFile(argv[1], std::ios::in | std::ios::binary);

	//Create vector OriginalBytes
	//Store binary contents in vector OriginalBytes
	//Stored values are in Decimal format
	std::vector<uint8_t> OriginalBytes((std::istreambuf_iterator<char>(ReadFile)), std::istreambuf_iterator<char>());

	//Create vector EncodedBytes
	//Vector will be used to store EncodedBytes 
	//Vector will reserve memory space for effiency purposes
	std::vector<uint8_t> EncodedBytes;
	EncodedBytes.reserve(OriginalBytes.size());

	//Encode OriginalBytes with frk bytes
	//Populate vector EncodedBytes with EncodedValues
	for (int i = 0, j = 0; i < OriginalBytes.size(); i++)
	{
		uint8_t EncodedValues = OriginalBytes[i] ^ frk[j];
		//Push EncodedValues back to EncodedBytes
		EncodedBytes.push_back(EncodedValues);
		//Increment j by 1
		j++;
		//Reset key position to 0
		//Allows loop to loop through key vector
		if (j >= frk.size())
		{
			j = 0;
		}
	}

	//Messages - Program information
	std::cout << "Program information listed below." << std::endl;
	std::cout << "OriginalBytes size: " << OriginalBytes.size() << std::endl;
	std::cout << "EncodedBytes size: " << EncodedBytes.size() << std::endl;
	std::cout << "frk size: " << frk.size() << std::endl;

	//Write vector information back to binary
	std::ofstream EncodedFile("encoded.bin", std::ios::out | std::ios::binary);
	for (int i = 0; i < EncodedBytes.size(); ++i)
	{
		EncodedFile << EncodedBytes[i];
	}
	EncodedFile.close();

	//Message - Completed File Output
	std::cout << "Bytes have been encoded." << std::endl;

	//Message - End Notification
	std::cout << "GhostCloak has finished  encoding.";
}
