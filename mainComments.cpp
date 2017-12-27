
#if 0
// Забавные факты о КЛАССАХ:

/////////////////////////////////
/* // FACT_1
class A { };
void main()
{
	A a; // No Errors
}
//*/

/////////////////////////////////
/* // FACT_2_1
class A
{
	int fun() { return 1; }
};
void main()
{
	A a; // No Errors
	a.fun(); // ERROR function is inaccessible - reason fun is PTIVATE by default
}
//*/

/* // FACT_2_2
class A
{
public:
	int fun() { return 1; }
};
void main()
{
	A a; // No Errors
	a.fun(); // Ok! - reason fun is now PUBLIC
}
//*/

/////////////////////////////////
/* // FACT_3_1
class A
{
	A()  {};
	~A() {};
public:
	void fun() {};
};

void main()
{
	A a; // ERROR we can NOT create "a", 
		 // because NOW Constructor is SET as a member
		 // that is by Default PRIVATE
	a.fun();
}
//*/

/* // FACT_3_2
class A
{
public:
	A()  {};
	~A() {};
public:
	void fun() {};
};

void main()
{
	A a; // Ok! - reason Constructor is now SET and PUBLIC
	a.fun();
}
//*/


/*

//*/


#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

void parseFile(const std::string inFile, const std::string outFile)
{
	//readFile
	std::string _fileName;
	std::vector<std::string> _vec;

	std::ifstream file;
	file.open(_fileName);
	std::string word;
	char x;
	word.clear();

	while (!file.eof())
	{
		x = file.get();
		while (x != ' ')
		{
			word += x;
			x = file.get();
		}

		std::cout << word << std::endl;
		word.clear();
	}
}

void printFile(const std::string file)
{
	//for ()
	{

	}
}


typedef void Parser(char, FILE *);
Parser* currentParser;

void InStringParser(char c, FILE *output_file);
void InCharParser(char c, FILE *output_file);
void AfterSlashParser(char c, FILE *output_file);
void InInlineCommentParser(char c, FILE *output_file);
void InMultilineCommentParser(char c, FILE *output_file);

void NormalParser(char c, FILE *output_file)
{
	switch (c)
	{
	case '\"':
		currentParser = InStringParser;
		break;
	case '\'':
		currentParser = InCharParser;
		break;
	case '/':
		currentParser = AfterSlashParser;
		// no need to print
		return;
	}
	fprintf(output_file, "%c", c);
}

bool inStringLastEscape = false;
void InStringParser(char c, FILE *output_file)
{
	fprintf(output_file, "%c", c);
	if (c == '\"' && !inStringLastEscape)
		currentParser = NormalParser; // inStringLastEscape will be false
	inStringLastEscape = (c == '\\') && !inStringLastEscape;
}

bool inCharLastEscape = false;
void InCharParser(char c, FILE *output_file)
{
	fprintf(output_file, "%c", c);
	if (c == '\'' && !inCharLastEscape)
		currentParser = NormalParser; // inCharLastEscape will be false
	inCharLastEscape = (c == '\\') && !inCharLastEscape;
}

void AfterSlashParser(char c, FILE *output_file)
{
	switch (c)
	{
	case '/':
		currentParser = InInlineCommentParser;
		return;
	case '*':
		currentParser = InMultilineCommentParser;
		return;
	default:
		fprintf(output_file, "/%c", c);
	}
}

bool inInlineLastEscape = false;
void InInlineCommentParser(char c, FILE *output_file)
{
	if (c == '\n' && !inInlineLastEscape)
	{
		fprintf(output_file, "\n");
		currentParser = NormalParser;
	}
	inInlineLastEscape = (c == '\\') && !inInlineLastEscape;
}

bool inMultilineLastStar = false;
void InMultilineCommentParser(char c, FILE *output_file)
{
	if (c == '/' && inMultilineLastStar)
	{
		fprintf(output_file, " ");
		currentParser = NormalParser; // inMultilineLastStar will be false
	}
	inMultilineLastStar = (c == '*');
}

void main()
{
	// открыть файлы и всё такое
	FILE * file = 

	currentParser = NormalParser;

	char symbol;
	while ((symbol = fgetc(input_file)) != EOF)
		currentParser(symbol, output_file);

	fclose(input_file);
	fclose(output_file);

	/////////////////////////////////////////////
	const std::string inFile = "example.cpp";
	const std::string outFile = "example_clear.cpp";

	printFile(inFile);

	parseFile(inFile, outFile);

	printFile(outFile);
}
#endif

#include <stdio.h>
#include <assert.h>
#include <string>

std::string removeComments(std::string prgm)
{
	int n = prgm.length();
	std::string res;

	// Flags to indicate that single line and multpile line comments
	// have started or not.
	bool isSingle = false;
	bool isMulti = false;


	// Traverse the given program
	for (int i = 0; i<n; i++)
	{
		// Singleline comment => check for it's end
		if (isSingle == true && prgm[i] == '\n')
			isSingle = false;

		// Multiline comment => check for it's end
		else if (isMulti == true && prgm[i] == '*' && prgm[i + 1] == '/')
			isMulti = false, i++;

		// Character is inside a comment => ignore
		else if (isSingle || isMulti)
		{
			continue;
		}

		// Start of the comment tells us => single / multiline
		else if (prgm[i] == '/' && prgm[i + 1] == '/')
		{
			isSingle = true;
			i++;
		}
		else if (prgm[i] == '/' && prgm[i + 1] == '*')
		{
			isMulti = true;
			i++;
		}
		else // Character is NOT inside a comment => append
		{
			res += prgm[i];
		}
	}

	return res;
}

//
// remove multiline and singleline comments from file
// ignore all kind of comments that we meet inside " here "

enum CHARS_THAT_WE_MET // Meet or Met
{
	  MET_EMPTY = 0		// empty or just the start 
	, MET_SLASH			// '/'
	, MET_STAR			// '*'
	, MET_ANOTHER_STAR	// '*'
	, MET_ANOTHER_SLASH	// '/'
	, MET_QUOTES		// '\"'
	, MET_EXTRA			// extra case
};

int main(void)
{
	int curChar = 0;
	CHARS_THAT_WE_MET metChar = MET_EMPTY;

	FILE *ifp = fopen("example.cpp", "rb");
	FILE *ofp = fopen("example_clear.cpp", "wb");

	while ((curChar = getc(ifp)) != EOF)
	{
		switch (metChar)
		{
		case MET_EMPTY:
			if (curChar == '/')
				metChar = MET_SLASH;
			else if (curChar == '\"')
			{
				metChar = MET_QUOTES;
				putc(curChar, ofp);
			}
			else
				putc(curChar, ofp);
		break;
		case MET_SLASH:
			if (curChar == '*')
				metChar = MET_STAR;
			else if (curChar == '/')
				metChar = MET_ANOTHER_SLASH;
			else 
			{
				putc('/', ofp);
				putc(curChar, ofp);
			}
		break;
		case MET_STAR:
			if (curChar == '*')
				metChar = MET_ANOTHER_STAR;
		break;
		case MET_ANOTHER_STAR:
			if (curChar == '*') 
				;
			else if (curChar == '/')
				metChar = MET_EMPTY;
			else
				metChar = MET_STAR;
		break;
		case MET_ANOTHER_SLASH:
			if (curChar == '\n')
				metChar = MET_EMPTY;
		break;
		case MET_QUOTES:
			if (curChar == '\\')
				metChar = MET_EXTRA;
			else if (curChar == '\"')
				metChar = MET_EMPTY;
			putc(curChar, ofp);
		break;
		case MET_EXTRA:
			putc(curChar, ofp);
			metChar = MET_QUOTES;
		break;
		}
	}

	fclose(ifp);
	fclose(ofp);

	return 0;
}





