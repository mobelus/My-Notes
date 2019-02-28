// AllFilesInDirSearcher.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

#include <experimental/filesystem>
#include <filesystem>

using namespace std;
namespace filesys = std::experimental::filesystem;


// c++ 17
///
 // Get the list of all files in given directory and its sub directories.
 //
 // Arguments
 // 	dirPath : Path of directory to be traversed
 // 	dirSkipList : List of folder names to be skipped
 //		onlyFilesOrDirs : 0 - only files, 1 - only dirs, 2 - files and dirs
 //
 // Returns:
 // 	vector containing paths of all the files in given directory and its sub directories
 //
 ///
std::vector<std::string> getAllFilesInDir(const std::string &dirPath, const int onlyFilesOrDirs, const std::vector<std::string> dirSkipList = { })
{

	// Create a vector of string
	std::vector<std::string> listOfFiles;
	try {
		// Check if given path exists and points to a directory
		if (filesys::exists(dirPath) && filesys::is_directory(dirPath))
		{
			// Create a Recursive Directory Iterator object and points to the starting of directory
			filesys::recursive_directory_iterator iter(dirPath);

			// Create a Recursive Directory Iterator object pointing to end.
			filesys::recursive_directory_iterator end;

			// Iterate till end
			while (iter != end)
			{
				// Check if current entry is a directory and if exists in skip list
				if (filesys::is_directory(iter->path()) &&
					(std::find(dirSkipList.begin(), dirSkipList.end(), iter->path().filename()) != dirSkipList.end()))
				{
					// Skip the iteration of current directory pointed by iterator
#ifdef USING_BOOST
					// Boost Fileystsem  API to skip current directory iteration
					iter.no_push();
#else
					// c++17 Filesystem API to skip current directory iteration
					iter.disable_recursion_pending();
#endif
				}
				else
				{
					std::string pathForObject = iter->path().string();
					//pathForObject.replace(pathForObject.begin(), pathForObject.end(), '\\', '/');

					std::string tmp(pathForObject.size(), '\0');
					std::replace_copy(pathForObject.begin(), pathForObject.end(), tmp.begin(), '\\', '/');
					pathForObject = tmp;

					// Add the name to vector
					switch (onlyFilesOrDirs)
					{
					case 0:
						if (!filesys::is_directory(iter->path()))
							listOfFiles.push_back(pathForObject);
						break;
					case 1:
						if (filesys::is_directory(iter->path()))
							listOfFiles.push_back(pathForObject);
						break;
					case 2:
					default:
						listOfFiles.push_back(pathForObject);
						break;
					}
					
				}

				error_code ec;
				// Increment the iterator to point to next entry in recursive iteration
				iter.increment(ec);
				if (ec) {
					std::cerr << "Error While Accessing : " << iter->path().string() << " :: " << ec.message() << '\n';
				}
			}
		}
	}
	catch (std::system_error & e)
	{
		std::cerr << "Exception :: " << e.what();
	}
	return listOfFiles;
}


/*
#include <string>
#include <functional>
#include <dirent.h>

void listFiles(const std::string &path, std::function<void(const std::string &)> cb) {
	if (auto dir = opendir(path.c_str())) {
		while (auto f = readdir(dir)) {
			if (!f->d_name || f->d_name[0] == '.') continue;
			if (f->d_type == DT_DIR)
				listFiles(path + f->d_name + "/", cb);

			if (f->d_type == DT_REG)
				cb(path + f->d_name);
		}
		closedir(dir);
	}
}
*/

//*/ Generate UUID

#include <vector>
#include <iostream>
#include <sstream>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>
#include <string>

#include  <cctype>

unsigned char random_char()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 255);
	return static_cast<unsigned char>(dis(gen));
}

std::string generate_hex(const unsigned int len)
{

	//         9   14   19   24          36
	// 12345678 9112 3456 7892 123456789312 = 32

	std::stringstream ss;
	for (auto i = 0; i < len; i++)
	{
		if ((i > 35))
		{
			break;
		}

		if ( (i == 8) || (i == 13) || (i == 18) || (i == 23) )
		{
			ss << '-';
		}
		else
		{
			auto rc = random_char();
			std::stringstream hexstream;
			hexstream << std::hex << int(rc);
			//auto hex = hexstream.str();
			//ss << (hex.length() < 2 ? '0' + hex : hex);
			auto hex = hexstream.str()[0];
			ss << hex;
		}
	}
	return ss.str();
}
//*/

/*
#include <windows.h>


//extern "C"
//{
#ifdef WIN32
#include <Rpc.h>
#else
#include <uuid/uuid.h>
#endif
//}

std::string newUUID()
{
#ifdef WIN32
	UUID uuid;
	UuidCreate(&uuid);

	unsigned char * str;
	UuidToStringA(&uuid, &str);

	std::string s((char*)str);

	RpcStringFreeA(&str);
#else
	uuid_t uuid;
	uuid_generate_random(uuid);
	char s[37];
	uuid_unparse(uuid, s);
#endif
	return s;
}
//*/

#include <Rpc.h>



std::string str_toupper(std::string s)
{
	std::transform(s.begin(), s.end(), s.begin(),
		// static_cast<int(*)(int)>(std::toupper)         // неправильно
		// [](int c){ return std::toupper(c); }           // неправильно
		// [](char c){ return std::toupper(c); }          // неправильно
		[](unsigned char c) { return std::toupper(c); } // правильно
	);
	return s;
}



#include <fstream>



void testUUID()
{
/*
	UUID uuid;
	UuidCreate(&uuid);

	unsigned char * str;
	UuidToStringA(&uuid, &str);

	std::string s((char*)str);

	RpcStringFreeA(&str);

	s;
*/

	// 12345678 9112 3456 7892 123456789312 = 32
	// 5573505B_F045_46ED_B1B9_58703E853A33
	std::string uuidtest = "12345678 9112 3456 7892 123456789312";
	uuidtest = str_toupper(uuidtest);
	std::string uuid = generate_hex(36);
	uuid = str_toupper(uuid);

	//std::string uuid = newUUID();
}



void testReadAllFilesFromDir()
{
	/*
		std::string str1("Quick\\brown\\fox");
		std::string str2(str1.size(), '\0');
		std::replace_copy(str1.begin(), str1.end(), str2.begin(), '\\', '/');
		std::cout << str2 << "\n";
	*/
	std::string path = "C:/Users/Павел Обросов/source/repos/AllFilesInDirSearcher/debug";
	std::vector<std::string> dirSkipList = { };
	std::vector<std::string> files = getAllFilesInDir(path, 0);

	std::cout << "End!\n";
}


void eraseSubStr(std::string & mainStr, const std::string & toErase)
{
	// Search for the substring in string
	size_t pos = mainStr.find(toErase);

	if (pos != std::string::npos)
	{
		// If found then erase it from string
		mainStr.erase(pos, toErase.length());
	}
}

void testWriteToFileSpecialFormatedText(std::string pathWithExeAndDeplyedLibsAndFiles, std::string pathLeftPartToDelete, std::string pathLeftToAddToTheStart)
{
	const int GET_ONLY_FILES = 0;

	//std::string pathWithExeAndDeplyedLibsAndFiles = "C:/Users/Павел Обросов/source/repos/AllFilesInDirSearcher/debug";
	std::vector<std::string> dirSkipList = { };
	std::vector<std::string> filespaths = getAllFilesInDir(pathWithExeAndDeplyedLibsAndFiles, GET_ONLY_FILES);

	// We also need the separated file names
	std::vector<std::string> files = filespaths;
	for (int i = 0, ilen = files.size(); i < ilen; i++)
	{
		files[i].erase(files[i].begin(), files[i].begin() + files[i].find_last_of('/') + 1 );
	}

	//std::string pathLeftPartToDelete	= "C:/Users/Павел Обросов/source/repos/AllFilesInDirSearcher";
	//std::string pathLeftToAddToTheStart	= "../DataGuardDemo";
	
	//std::string pathMiddlePartToAddBetween = "";
	//std::string pathRightToAddToTheEnd	= "";
	std::string pathResult = "";

	// Cut from Start what we do NOT need
	// Add to Start the real  debug  folder location (where all deplyment files with EXE file of our App and all depedencies dlls and such are in there too)
	for (int i = 0, ilen = filespaths.size(); i < ilen; i++)
	{
		pathResult = filespaths[i];
		eraseSubStr(pathResult, pathLeftPartToDelete);
		pathResult = pathLeftToAddToTheStart + pathResult;
		filespaths[i] = pathResult;
	}


	// Prepare some vectors
	std::vector<std::string> uuidsVector;
	std::vector<std::string> componentRefVector;
	std::vector<std::string> componentXmlVector;

	// Generate all UUIDs
	for (int i = 0, ilen = filespaths.size(); i < ilen; i++)
	{
		uuidsVector.push_back( generate_hex(36) );
	}

	// Prepare all ComponentRef Block 
	for (int i = 0, ilen = filespaths.size(); i < ilen; i++)
	{
		componentRefVector.push_back( "      <ComponentRef Id=\"comp_" + uuidsVector[i] + "\" />" );
	}

/*
	<ComponentRef Id = "comp_BC8B2401_E15B_4558_BE27_1A56C3CCC5A7" / >
	<ComponentRef Id = "comp_774A5069_37B3_493E_8854_80DBB9090C8A" / >
	<ComponentRef Id = "comp_dir_B91911B3_5190_4EF6_AD06_7A5377BC2F4A" / >
*/

	// Prepare all Component Block 
	for (int i = 0, ilen = filespaths.size(); i < ilen; i++)
	{
		std::string uuidWithUnderLines(uuidsVector[i].size(), '\0');
		std::replace_copy(uuidsVector[i].begin(), uuidsVector[i].end(), uuidWithUnderLines.begin(), '-', '_');

		std::string firstLine  = "      <Component Id=\"comp_\"" + uuidWithUnderLines + "\" Guid = \"" + generate_hex(36) + "\" Permanent = \"no\" SharedDllRefCount = \"no\" Transitive = \"no\" > ";
		std::string secondLine = "        <File Id=\"_" + generate_hex(36) + "\" DiskId = \"1\" Hidden = \"no\" ReadOnly = \"no\" TrueType = \"no\" System = \"no\" Vital = \"yes\" Name = \""+ files[i] + "\" Source=\"" + filespaths[i] + "\" KeyPath=\"yes\" />";
		std::string thirdLine  = "      </Component>";

		componentXmlVector.push_back(firstLine + "\n" + secondLine + "\n" + thirdLine);
	}

/*
      <Component Id="comp_5573505B_F045_46ED_B1B9_58703E853A33" Guid="14362915-5802-4418-B65F-CAF2362CF0D1" Permanent="no" SharedDllRefCount="no" Transitive="no">
        <File Id="_2D6DBF7A_5799_47B1_9BFD_E417F800750A" DiskId="1" Hidden="no" ReadOnly="no" TrueType="no" System="no" Vital="yes" Name="MSVCP120D.dll" Source="../DataGuardDemo/debug/Qt5Cored.dll" KeyPath="yes" />
      </Component>
*/


	// Write result strings to file
	std::ofstream fout1("1-componentsRef.txt");
	std::ofstream fout2("2-components.txt");

	//fout << std::endl;
	for (int i = 0, ilen = componentRefVector.size(); i < ilen; i++)
	{
		fout1 << componentRefVector[i] + "\n";
	}
	//fout1 << std::endl;
	fout1.close();

	/*
	fout << std::endl;
	fout << std::endl;
	fout << std::endl;
	fout << std::endl;
	*/

	for (int i = 0, ilen = componentXmlVector.size(); i < ilen; i++)
	{
		fout2 << componentXmlVector[i] + "\n";
	}
	fout2.close();

}


/*
int main()
{
	std::string pathWithExeAndDeplyedLibsAndFiles;
	std::string pathLeftPartToDelete;
	std::string pathLeftToAddToTheStart;


	testWriteToFileSpecialFormatedText
	(
		pathWithExeAndDeplyedLibsAndFiles
		, pathLeftPartToDelete
		, pathLeftToAddToTheStart
	);

}
*/

class InputParser {
public:
	InputParser(int &argc, char **argv) {
		for (int i = 1; i < argc; ++i)
			this->tokens.push_back(std::string(argv[i]));
	}
	/// @author iain
	const std::string& getCmdOption(const std::string &option) const {
		std::vector<std::string>::const_iterator itr;
		itr = std::find(this->tokens.begin(), this->tokens.end(), option);
		if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
			return *itr;
		}
		static const std::string empty_string("");
		return empty_string;
	}
	/// @author iain
	bool cmdOptionExists(const std::string &option) const {
		return std::find(this->tokens.begin(), this->tokens.end(), option)
			!= this->tokens.end();
	}
private:
	std::vector <std::string> tokens;
};


int main(int argc, char **argv)
{
	InputParser input(argc, argv);
	if (input.cmdOptionExists("-help"))
	{
		// Do stuff
		std::cout << "AllFilesInDirSearcher.exe -app \"C:/Users/Павел Обросов/source/repos/AllFilesInDirSearcher/debug\" -del \"C:/Users/Павел Обросов/source/repos/AllFilesInDirSearcher\" -add \"../DataGuardDemo\"";
		std::cout << std::endl << std::endl;

		system("pause");
	}
	else
	{
		//const std::string &filename = input.getCmdOption("-f");
		//if (!filename.empty())
		//{
		//	// Do interesting things ...
		//}

		const std::string &pathWithExeAndDeplyedLibsAndFiles = input.getCmdOption("-app");
		const std::string &pathLeftPartToDelete = input.getCmdOption("-del");
		const std::string &pathLeftToAddToTheStart = input.getCmdOption("-add");

		testWriteToFileSpecialFormatedText
		(
			pathWithExeAndDeplyedLibsAndFiles
			, pathLeftPartToDelete
			, pathLeftToAddToTheStart
		);
	}

	return 0;
}




