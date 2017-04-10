//****************************************************************************************
//
//	INCLUDE FILES
//
//****************************************************************************************
#include	<fstream>
#include	<iostream>

#include	"Roster.h"

using namespace std;

//****************************************************************************************
//
//	CONSTANT DEFINITIONS
//
//****************************************************************************************
//	This enum provides the index values for the field strings in a FieldVector, which is
//	returned by MembershipFile::Read. The index values can be used in statements like
//	this:
//		type = fieldVector[typeIndex];
//	or:
//		address = fieldVector[addressIndex];
enum	FieldIndex
{
	idIndex		 = 0,
	typeIndex	 = 1,
	nameIndex	 = 2,
	addressIndex = 3,
	cityIndex	 = 4,
	stateIndex	 = 5,
	zipIndex	 = 6
};

//	The number of fields in a type P or C line
const static uint32_t	kShortFieldCount = nameIndex + 1;

//	The number of fields in a type I or H line
const static uint32_t	kLongFieldCount = zipIndex + 1;

//****************************************************************************************
//
//	CLASSES, TYPEDEFS AND STRUCTURES
//
//****************************************************************************************

//****************************************************************************************
//
//	PUBLIC DATA
//
//****************************************************************************************

//****************************************************************************************
//
//	PRIVATE DATA
//
//****************************************************************************************

//****************************************************************************************
//
//	FUNCTION PROTOTYPES
//
//****************************************************************************************


//****************************************************************************************
//
//	MembershipFile::Close
//
//****************************************************************************************
void	MembershipFile::Close()
{
	//************************************************************************************
	//	LOCAL DATA
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	file_.close();

	return;
}

//****************************************************************************************
//
//	MembershipFile::GetField
//
//	Extracts a single field delimited by a tab character, from a text string.
//
//****************************************************************************************
string	MembershipFile::GetField()
{
	//************************************************************************************
	//	LOCAL DATA
	string		field;

	StringSize	i;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	//	Scan for the tab.
	for (i = position_; i < line_.size(); ++i)
	{
		if (line_[i] == '\t')
		{
			break;
		}
	}
	
	//	Asssign return to the caller.
	field.assign(line_, position_, i - position_);
	
	//	Adbance the pisition for the next scan, dependning on whether this was the last field.
	if (i < line_.size())
	{
		position_ = i + 1;
	}
	else
	{
		position_ = i;
	}

	return(field);
}

//****************************************************************************************
//
//	MembershipFile::GetLine
//
//	This function reads a series of characters from a file and puts it into a string,
//	stopping when it sees a line break:
//		1. A carriage return (CR)
//		2. A line feed (LF)
//		3. A CR/LF pair
//		4. A LF/CR pair
//	The #3 and #4 pairs are a single line break.
//	The line break (any of the four) is consumed but not added to the output string.
//
//	The return status is true if at least one character, oncluidng a line break, is read;
//	the status is false if an end-of-file is immediately encountered.
//
//****************************************************************************************
bool	MembershipFile::GetLine()
{
	//************************************************************************************
	//	LOCAL DATA
	int		c;
	
	int		p;
	
	bool	success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	line_.erase();
	success = false;
	while (true)
	{
		c = file_.get();
		if (file_.good())
		{
			success = true;
			
			if (c == '\r')
			{
				p = file_.peek();
				if (p == '\n')
				{
					file_.ignore();
				}
				break;
			}
			else if (c == '\n')
			{
				p = file_.peek();
				if (p == '\r')
				{
					file_.ignore();
				}
				break;
			}
			else
			{
				line_ += c;
			}
		}
		else
		{
			break;
		}
	}
	
	//	If we reached the end of file, but at least one character was seen,
	//	including any delimiter, clear the stream's state so the caller won't
	//	ignore the last line of a file.
	if (success)
	{
		file_.clear();
	}
	
	return(success);
}

//****************************************************************************************
//
//	MembershipFile::Open
//
//	Opens a membership file for input.
//
//****************************************************************************************
bool	MembershipFile::Open(const string& name)
{
	//************************************************************************************
	//	LOCAL DATA
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	//	Clear any residual errors, such as end-of-file.
	file_.clear();
	
	file_.open(name, ios::in);
	
	return(file_.good());
}

//****************************************************************************************
//
//	MembershipFile::Read
//
//	Read an input file line and pass back a vector of strings containing its fields.
//	The vector's field strings are in the order they appear in the input file line.
//	There is an enum, FieldIndex, at the front of this .cpp file that shows that order.
//	To access a specific field, use a statement like this one:
//		type = fieldVector[typeIndex];
//
//****************************************************************************************
bool	MembershipFile::Read(StringVector& fieldVector)
{
	//************************************************************************************
	//	LOCAL DATA
	string	field;
	
	bool	success;

	string	type;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	//	Empty the field vector.
	fieldVector.clear();

	//	Get a file line; return false upon end-of-file.
	success = GetLine();
	if (success)
	{
		//	Scan the line for fields and push each one into the field vector.
		position_ = 0;
		while (true)
		{
			if (position_ == line_.size())
			{
				break;
			}
			field = GetField();
			fieldVector.push_back(field);
		}
		
		//	Check for the expected number of fields, which depends on the
		//	membership type.
		type = fieldVector[typeIndex];
		if ((type == "I") || (type == "H"))
		{
			if (fieldVector.size() != kLongFieldCount)
			{
				success = false;
			}
		}
		else
		{
			if (fieldVector.size() != kShortFieldCount)
			{
				success = false;
			}
		}
	}

	return(success);
}

//****************************************************************************************
//
//	Roster::LoadMemberships
//
//	Loads the roster with memberships defined in a file.
//
//	Returns false if it is unsuccessful because:
//	1. The file couldn't be opened.
//	2. A file line was missing some information.
//
//****************************************************************************************
bool	Roster::LoadMemberships(const string& fileName)
{
	//************************************************************************************
	//	LOCAL DATA
	StringVector	fieldVector;
	
	MembershipFile	file;

	string			id;
	
	string			line;
	
	string			name;
	
	string			state;
	
	bool			success;
	
	string			type;
	
	string			zip;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	success = file.Open(fileName);
	if (success)
	{
		while (true)
		{
			success = file.Read(fieldVector);
			if (success)
			{
				//	COMPLETE THE ROSTER LOADING HERE.
			}
			else
			{
				//	COMPLETE THE END-OF-FILE HANDLING HERE.
				success = true;
				break;
			}
		}

		return(success);
	}
	else
	{
		cout << "Can't open file." << endl;

		return(false);
	}
}

//****************************************************************************************
//
//	Roster::RemoveMembership
//
//	Removes one membership, specified by its id, from the roster.
//
//	Returns false if the membership doesn't exist in the roster.
//
//****************************************************************************************
bool	Roster::RemoveMembership(const string& id)
{
	//************************************************************************************
	//	LOCAL DATA

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	//	COMPLETE THE FUNCTION HERE. MAKE SURE IT RETURNS THE CORRECT STATUS EVERYWHERE.

	return(true);
}

//****************************************************************************************
//
//	Roster::ShowAllMemberships
//
//	Displays the entire roster in the same format as the input file used to load the
//	initial roaster. Displays "empty" if there are no memberships in the roster.
//	The display is written to an output stream (ostream), which can be a file, the cout
//	stream, or a stringstream.
//
//****************************************************************************************
void	Roster::ShowAllMemberships(ostream& stream)
{
	//************************************************************************************
	//	LOCAL DATA

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	//	COMPLETE THE FUNCTION HERE.

	return;
}

//****************************************************************************************
//
//	Roster::ShowOneMembership
//
//	Displays a single membership in the same format as the input file used to load the
//	initial roster. The display is written to an output stream (ostream), which can be
//	a file, the cout stream, or a stringstream.
//
//	Returns false if the membership doesn't exist in the roster.
//
//****************************************************************************************
bool	Roster::ShowOneMembership(ostream& stream, const string& id)
{
	//************************************************************************************
	//	LOCAL DATA
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	//	COMPLETE THE FUNCTION HERE. MAKE SURE IT RETURNS THE CORRECT STATUS EVERYWHERE.

	return(true);
}

//****************************************************************************************
//
//	Roster::StoreMemberships
//
//	Stores the current roster in the specified file, in the same format
//	as the input file used to load the initial roster.
//
//	Returns false if the file can't be created.
//
//****************************************************************************************
bool	Roster::StoreMemberships(const string& fileName)
{
	//************************************************************************************
	//	LOCAL DATA
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	//	COMPLETE THE FUNCTION HERE. MAKE SURE IT RETURNS THE CORRECT STATUS EVERYWHERE.

	return(false);
}