//****************************************************************************************
//
//	INCLUDE FILES
//
//****************************************************************************************
#include	<fstream>
#include	<iostream>
#include	<sstream>
#include	<string>
#include	<vector>

#include	"Roster.h"

using namespace std;

//****************************************************************************************
//
//	CONSTANT DEFINITIONS
//
//****************************************************************************************

//****************************************************************************************
//
//	CLASSES, TYPEDEFS AND STRUCTURES
//
//****************************************************************************************
typedef vector<string>	StringVector;

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
static uint32_t	failureCount;


static	StringVector	expectedFullRoster =
{
	"1000\tI\tJack Jones\t1200 South Central Ave\tSunset Dunes\tCA\t99456",
	"2000\tH\tJohn Smith\t100 West Shady Lane\tHemet\tCA\t99123",
	"2000\tP\tJoan Smith",
	"2000\tC\tSally Smith",
	"2000\tC\tBillie Smith",
	"2000\tC\tBobbie Smith",
	"300\tH\tFred Brown\t700 North Ocean Drive\tLong Beach\tCA\t94327",
	"300\tP\tMarcia Jones",
	"4000\tH\tPaul Sims\t400 East Grand Blvd\tWalnut\tCA\t92155",
	"4000\tC\tMary Sims",
	"4000\tC\tDoug Sims"
};

static	StringVector	expectedMember2000 =
{
	"2000\tH\tJohn Smith\t100 West Shady Lane\tHemet\tCA\t99123",
	"2000\tP\tJoan Smith",
	"2000\tC\tSally Smith",
	"2000\tC\tBillie Smith",
	"2000\tC\tBobbie Smith"
};

static	StringVector	expectedRemove300Roster =
{
	"1000\tI\tJack Jones\t1200 South Central Ave\tSunset Dunes\tCA\t99456",
	"2000\tH\tJohn Smith\t100 West Shady Lane\tHemet\tCA\t99123",
	"2000\tP\tJoan Smith",
	"2000\tC\tSally Smith",
	"2000\tC\tBillie Smith",
	"2000\tC\tBobbie Smith",
	"4000\tH\tPaul Sims\t400 East Grand Blvd\tWalnut\tCA\t92155",
	"4000\tC\tMary Sims",
	"4000\tC\tDoug Sims"
};

//****************************************************************************************
//
//	FUNCTION PROTOTYPES
//
//****************************************************************************************
void	Test1(Roster& roster);

void	Test2(Roster& roster);

void	Test3(Roster& roster);

void	Test4(Roster& roster);

void	Test5(Roster& roster);

void	Test6(Roster& roster);

void	Test7(Roster& roster);

void	Test8(Roster& roster);

void	Test9(Roster& roster);

void	Test10(Roster& roster);

string	VerifyRosterFile(const string& fileName, const StringVector& expectedText);

bool	VerifyRosterText(const string& actualText, const StringVector& expectedText);

//****************************************************************************************
//
//	MAIN PROGRAM
//
//****************************************************************************************
int main (int argc, char * const argv[])
{
	//************************************************************************************
	//	LOCAL DATA
	Roster	roster;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	failureCount = 0;

	Test1(roster);
	
	Test2(roster);
	
	Test3(roster);
	
	Test4(roster);
	
	Test5(roster);
	
	Test6(roster);
	
	Test7(roster);
	
	Test8(roster);
	
	Test9(roster);
	
	Test10(roster);
	
	cout << endl;
	if (failureCount == 0)
	{
		cout << "All tests passed." << endl;
	}
	else if (failureCount == 1)
	{
		cout << "1 test failed." << endl;
	}
	else
	{
		cout << failureCount << " tests failed." << endl;
	}

	cout << endl << "** Finished **" << endl;

	return(0);
}

//****************************************************************************************
//
//	Test1: ShowAllMemberships, before a roster has been loaded.
//
//	The function should write "empty".
//
//****************************************************************************************
void	Test1(Roster& roster)
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	stream;
	
	string			text;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Test 1: ShowAllMemberships (empty roster)" << endl;
	
	//	Call the function being tested and check its results.
	roster.ShowAllMemberships(stream);
	text = stream.str();
	if (text == "empty")
	{
		cout << "  Pass" << endl;
	}
	else
	{
		cout << "  Fail" << endl;
		++failureCount;
	}
	
	return;
}

//****************************************************************************************
//
//	Test2: ShowOneMembership, before a roster has been loaded.
//
//	The function should return false.
//
//****************************************************************************************
void	Test2(Roster& roster)
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	stream;
	
	bool			success;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Test 2: ShowOneMembership (empty roster)" << endl;
	
	//	Call the function being tested and check its return status.
	success = roster.ShowOneMembership(stream, "1000");
	if (!success)
	{
		cout << "  Pass" << endl;
	}
	else
	{
		cout << "  Fail" << endl;
		++failureCount;
	}
	
	return;
}

//****************************************************************************************
//
//	Test3: RemoveMembership, before a roster has been loaded.
//
//	The function should return false.
//
//****************************************************************************************
void	Test3(Roster& roster)
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	stream;
	
	bool			success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Test 3: RemoveMembership (empty roster)" << endl;
	
	//	Call the function being tested and check its return status.
	success = roster.RemoveMembership("1000");
	if (!success)
	{
		cout << "  Pass" << endl;
	}
	else
	{
		cout << "  Fail" << endl;
		++failureCount;
	}
	
	return;
}

//****************************************************************************************
//
//	Test4: LoadRoster
//
//	The function should succeed and the roster should match the expected elements.
//
//****************************************************************************************
void	Test4(Roster& roster)
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	stream;
	
	bool			success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Test 4: LoadRoster" << endl;
	
	//	Call the function being tested and check its return status.
	success = roster.LoadMemberships("roster_in.txt");
	if (success)
	{
		//	Show the roster and verify it against the expected elements.
		roster.ShowAllMemberships(stream);
		success = VerifyRosterText(stream.str(), expectedFullRoster);
		if (success)
		{
			cout << "  Pass" << endl;
		}
		else
		{
			cout << "  Fail (roster not as expected)" << endl;
			++failureCount;
		}
	}
	else
	{
		cout << "  Fail (couldn't load file." << endl;
		++failureCount;
	}
	
	return;
}

//****************************************************************************************
//
//	Test5: ShowAllMemberships, after a roster has been loaded.
//
//	The text returned should match its expected contents.
//
//****************************************************************************************
void	Test5(Roster& roster)
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	stream;
	
	bool			success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Test 5: ShowAllMemberships (after Load)" << endl;
	
	//	Show the roster and verify it against the expected elements.
	roster.ShowAllMemberships(stream);
	success = VerifyRosterText(stream.str(), expectedFullRoster);
	if (success)
	{
		cout << "  Pass" << endl;
	}
	else
	{
		cout << "  Fail" << endl;
		++failureCount;
	}
	
	return;
}

//****************************************************************************************
//
//	Test6: ShowOneMember, with a known id
//
//	The function should succeed and the text returned should match its expected contents.
//
//****************************************************************************************
void	Test6(Roster& roster)
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	stream;
	
	bool			success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Test 6: ShowOneMembership (after Load, known id)" << endl;
	
	//	Call the function being tested and check its return status.
	success = roster.ShowOneMembership(stream, "2000");
	if (success)
	{
		//	It shuold succedd' the id is known.
		success = VerifyRosterText(stream.str(), expectedMember2000);
		if (success)
		{
			cout << "  Pass" << endl;
		}
		else
		{
			cout << "  Fail (membership not as expected)" << endl;
			++failureCount;
		}
	}
	else
	{
		cout << "  Fail (membership not found)" << endl;
		++failureCount;
	}
	
	return;
}

//****************************************************************************************
//
//	Test7: ShowOneMembership, with an unknow id.
//
//	The function should return false.
//
//****************************************************************************************
void	Test7(Roster& roster)
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	stream;
	
	bool			success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Test 7: ShowOneMembership (after Load, unknown id)" << endl;
	
	//	Call the function being tested and check its return status.
	success = roster.RemoveMembership("9999");
	if (!success)
	{
		cout << "  Pass" << endl;
	}
	else
	{
		cout << "  Fail" << endl;
		++failureCount;
	}
	
	return;
}

//****************************************************************************************
//
//	Test8: RemoveMembership, known id.
//
//	The fucntion should succeed and the modified roster should match its expected contents.
//
//****************************************************************************************
void	Test8(Roster& roster)
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	stream;
	
	bool			success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Test 8: RemoveMembership (after Load, known id)" << endl;
	
	//	Call the function being tested and check its return status.
	success = roster.RemoveMembership("300");
	if (success)
	{
		//	Show the modified roster and verify its actual contents against
		//	the expected contents.
		roster.ShowAllMemberships(stream);
		success = VerifyRosterText(stream.str(), expectedRemove300Roster);
		if (success)
		{
			cout << "  Pass" << endl;
		}
		else
		{
			cout << "  Fail (roster after Remove not as expected)" << endl;
			++failureCount;
		}
	}
	else
	{
		cout << "  Fail (can't remove membership 300" << endl;
		++failureCount;
	}
	
	return;
}

//****************************************************************************************
//
//	Test9: RemoveMembership, unknown id.
//
//	The function shoiuld return false.
//
//****************************************************************************************
void	Test9(Roster& roster)
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	stream;
	
	bool			success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Test 9: RemoveMembership (after Load, unknown id)" << endl;
	
	//	Call the function being tested and check its return status.
	success = roster.RemoveMembership("9999");
	if (!success)
	{
		//	It was unsuccessful as expected.
		cout << "  Pass" << endl;
	}
	else
	{
		//	It should have been unsuccessful.
		cout << "  Fail" << endl;
		++failureCount;
	}
	
	return;
}

//****************************************************************************************
//
//	Test10
//
//	The function should succeed and the output file should match its expected contents.
//
//****************************************************************************************
void	Test10(Roster& roster)
{
	//************************************************************************************
	//	LOCAL DATA
	string			result;

	stringstream	stream;
	
	bool			success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	cout << "Test 10: StoreRoster" << endl;

	//	Call the function being tested and check its return status.
	success = roster.StoreMemberships("roster_out.txt");
	if (success)
	{
		//	No errors during Store. Verify the output file.
		result = VerifyRosterFile("roster_out.txt", expectedRemove300Roster);
		if (result.empty())
		{
			cout << "  Pass" << endl;
		}
		else
		{
			cout << "  " << result << endl;
			++failureCount;
		}
	}
	else
	{
		cout << "  Fail (can't store into file)" << endl;
		++failureCount;
	}

	return;
}

//****************************************************************************************
//
//	VerifyRosterFile
//
//	Compares the stored roster with its expected contents.
//	Returns a text string containing the result.
//	1.	"": no errors
//	2.	"Fail (contents don't match)"
//	3.	"Fail (file shorter than expected)": the end of the file was reached
//		before the end of the expected text.
//	4.	"Fail (file longer than expected)":the end of the expected text was reached
//		before the end of the file.
//	In cases 3 and 4, the shorter of the file and the expected text matched; that is,
//	the shorter of the two is a prefix of the longer. This is still a mismatch but
//	not of the characters in the file.
//
//****************************************************************************************
string	VerifyRosterFile(const string& fileName, const StringVector& expectedTextVector)
{
	//************************************************************************************
	//	LOCAL DATA
	StringVector	actualFieldVector;
	
	string			actualText;
	
	bool			endOfFile;
	
	string			expectedText;
	
	MembershipFile	file;

	uint32_t		lineIndex;

	bool			mismatch;

	string			result;

	bool			success;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	//	Open the file and check for success.
	success = file.Open(fileName);
	if (success)
	{
		//	Set the two "reasons for leaving the compare" loop.
		endOfFile = false;
		mismatch = false;
		
		//	Initialize the expected line index.
		lineIndex = 0;
		while (true)
		{
			//	Get a file line and check for end-of-file.
			//	Set indicator and leave loop.
			success = file.Read(actualFieldVector);
			if (!success)
			{
				endOfFile = true;
				break;
			}
			
			//	Form an actual text contiguous string,
			//	because that's what's in the rows of
			//	the expected text vector.
			uint32_t i = 0;
			actualText.erase();
			while (true)
			{
				actualText += actualFieldVector[i];
				++i;
				if (i < actualFieldVector.size())
				{
					actualText += '\t';
				}
				else
				{
					break;
				}
			}

			//	Compare actual and expected text.
			//	On mismatch, set indicator and leave loop.
			expectedText = expectedTextVector[lineIndex];
			if (actualText != expectedTextVector[lineIndex])
			{
				mismatch = true;
				break;
			}
			
			//	Advance to next expected line and check for "end of expected lines."
			++lineIndex;
			if (lineIndex == expectedTextVector.size())
			{
				//	There are no more expected lines but the end of the file
				//	hasn't been reached. There's one legitimate reason: the
				//	last line of the file ends with a endl. It doesn't have
				//	to but it's not wrong to do so. One more read should see
				//	and end-of-file; see if it does and set the indicator.
				success = file.Read(actualFieldVector);
				if (!success)
				{
					endOfFile = true;
				}
				break;
			}
		}

		//	We've left the loop; check the reason.
		if (mismatch)
		{
			//	Mismatch, return the appropriate indicator
			result = "Fail (contents don't match)";
		}
		else
		{
			//	No mismatch; did we reach both the end of the file and
			//	the end of the expected lines?
			if (endOfFile && (lineIndex == expectedTextVector.size()))
			{
				//	Yes, indicate a successful verification.
				result = "";
			}
			else
			{
				//	No, which end did we reach? Return an appropriate indicator.
				if (endOfFile)
				{
					result = "Fail (file shorter than expected)";
				}
				else
				{
					result = "Fail (file longer than expected)";
				}
			}
		}
	}
	else
	{
		result = "Fail (can't open file)";
	}

	return(result);
}

//****************************************************************************************
//
//	VerifyRosterText
//
//	Compares the actual text returned by a Show... function with the expected text.
//	Returns true if they match, false if they don't.
//
//****************************************************************************************
bool	VerifyRosterText(const string& actualText, const StringVector& expectedTextVector)
{
	//************************************************************************************
	//	LOCAL DATA
	stringstream	stream;
	
	string			expectedText;
	
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	//	Form a stringstream from the expected text lines.
	for (uint32_t i = 0; i < expectedTextVector.size(); ++i)
	{
		stream << expectedTextVector[i] << endl;
	}
	
	//	Get a single expected text string.
	expectedText = stream.str();
	
	//	Compare the strings and return the appropriate status.
	if (actualText == expectedText)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}