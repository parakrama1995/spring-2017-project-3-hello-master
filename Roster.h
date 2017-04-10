#pragma once

//****************************************************************************************
//
//	INCLUDE FILES
//
//****************************************************************************************
#include	<iostream>
#include	<map>
#include	<vector>

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
typedef string::size_type	StringSize;

typedef vector<string>	StringVector;

class	MembershipFile
{
	public:
		void	Close();
	
		bool	Open(const string& name);
	
		bool	Read(StringVector& fieldVector);
	
	private:
		string	GetField();

		bool	GetLine();

		fstream		file_;
	
		string		line_;

		StringSize	position_;
};

class	Roster
{
	public:
		bool	LoadMemberships(const string& fileName);
		
		bool	RemoveMembership(const string& id);
		
		void	ShowAllMemberships(ostream& stream);
		
		bool	ShowOneMembership(ostream& stream, const string& id);

		bool	StoreMemberships(const string& fileName);

	private:
};

//****************************************************************************************
//
//	FUNCTION PROTOTYPES
//
//****************************************************************************************

