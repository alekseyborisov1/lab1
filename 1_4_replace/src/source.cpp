#include <stdio.h>
#include <fstream>
#include <iostream>
#include <io.h>

using namespace std;

void ReplaceString(ifstream & fin, ofstream & fout, const string & searchString, const string & replaceString)
{
	char readingChar;
	string currentString;

	do 
	{
		fin.get(readingChar);
		currentString += readingChar;

		if ((currentString.length() == searchString.length()) && !fin.eof())             
		{
			if (!currentString.compare(searchString))
			{ 
				fout << replaceString.c_str();
			    currentString = "";
			}
			else
			{
				fout << currentString[0];
				currentString.erase(0,1);
			}
		}
	} while (!fin.eof());

	if (!currentString.empty())
	{
		currentString.erase(currentString.end() - 1);
		fout << currentString.c_str();
	}
}

int main(int argc, char *argv[])
{
	if (argc != 5)
	{	
		cout << "Not enough or too much parameters" << endl;
		exit(1);
	}

	setlocale(LC_ALL, "rus");

	ifstream fin;
	fin.open(argv[1]);
	if (fin.fail()) 
	{
		cout << "File openning error" << endl;
	    exit(1);
	}
	if (!fin.good())
	{
		cout << "File is corrupted" << endl;
		exit(1);
	}

	ofstream fout;
	fout.open(argv[2]); 
	if (fout.fail()) 
	{
		cout << "File openning error" << endl;
	    exit(1);
	}
	
	string searchString = argv[3];

	if (searchString.length() == 0)
	{
		cout << "Search string is empty" << endl;
		exit(1);
	}

	string replaceString = argv[4];

	ReplaceString(fin, fout, searchString, replaceString);

	fin.close();
	fout.close();

	system("pause");

	return 0;

}