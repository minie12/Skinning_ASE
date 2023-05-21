#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

class ASELexer
{
	enum TokenType : uint8_t
	{
		TYPE_IDENTIFIER = 0,
		VALUE_IDENTIFIER,
		LBRACKET,
		RBRACKET,
		DOUBLE,
		INTEGER,
		STRING,
		MAX
	};

public:
	ASELexer() { }

	~ASELexer()
	{}

	void ParseLine(const string& InTextLine)
	{
		if (InTextLine.empty())
		{
			return;
		}

		unsigned int LineLength = InTextLine.length();
		unsigned int CharIndex = 0;

		while (CharIndex < LineLength)
		{
			char C = InTextLine[CharIndex++];
			TokenType TableKey = TokenType::MAX;
			string TableValue = "";

			if (C == '*')
			{
				TableKey = TokenType::TYPE_IDENTIFIER;
				unsigned int PreviousIndex = CharIndex;
				while (IsEndOfToken(C) && CharIndex < LineLength)
				{
					C = InTextLine[CharIndex++];
				}

				unsigned int CopyLength = CharIndex - PreviousIndex - 1;
				if (CharIndex >= LineLength)
				{
					CopyLength += 1;
				}
				TableValue = InTextLine.substr(PreviousIndex, CopyLength);
			}
			else if (C == '{')
			{
				TableKey = TokenType::LBRACKET;
			}
			else if (C == '}')
			{
				TableKey = TokenType::RBRACKET;
			}
			else if (C == '\"')
			{
				TableKey = TokenType::STRING;
				unsigned int PreviousIndex = CharIndex;
				do
				{
					C = InTextLine[CharIndex++];
				} while (C != '\"' && CharIndex < LineLength);

				unsigned int CopyLength = CharIndex - PreviousIndex - 1;
				TableValue = InTextLine.substr(PreviousIndex, CopyLength);
			}
			else if (C == '-' || isdigit(C))
			{
				bool bIsDouble = false;

				unsigned int PreviousIndex = CharIndex - 1;
				while (IsEndOfToken(C) && CharIndex < LineLength)
				{
					C = InTextLine[CharIndex++];
					if (C == '.')
					{
						bIsDouble = true;
					}
				}

				unsigned int CopyLength = CharIndex - PreviousIndex - 1;
				if (CharIndex >= LineLength)
				{
					CopyLength += 1;
				}
				TableValue = InTextLine.substr(PreviousIndex, CopyLength);

				if (bIsDouble)
				{
					TableKey = TokenType::DOUBLE;
				}
				else
				{
					TableKey = TokenType::INTEGER;
				}
			}
			else
			{
				continue;
			}

			if (false == TableValue.empty() && TableValue.back() == ':')
			{
				TableKey = TokenType::VALUE_IDENTIFIER;
				TableValue.pop_back();
			}
			LexerTable.push_back(make_pair(TableKey, TableValue));
		}
	}

	bool CreateLexerTable(const string& InFilePath)
	{
		if (InFilePath.empty())
		{
			return false;
		}

		ifstream ReadStream(InFilePath.c_str());

		if (false == ReadStream.good())
		{
			cout << "ERROR: File could not be found." << endl;
			return false;
		}	

		LexerTable.clear();

		string TextLine;
		while (getline(ReadStream, TextLine))
		{
			cout << TextLine << endl;

			ParseLine(TextLine);
		}

		ReadStream.close();
		return true;
	}

private:
		inline bool IsEndOfToken(const char C) const
		{
			return (C != ' ') && (C != '\t');
		}
private:
	vector<pair<TokenType, string>> LexerTable;
};

class ASEReader
{
public:
	ASEReader()	{ }

	void ReadASE(const string& InFilePath)
	{
		FilePath = InFilePath;

		ASELexer ASE;
		ASE.CreateLexerTable(InFilePath);

		return;
	}

private:
	string FilePath;
};

int main()
{
	string FilePath = "./input/murturl.ase";

	ASEReader DataReader;
	DataReader.ReadASE(FilePath);

	return 0;
}