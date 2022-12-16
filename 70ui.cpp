#include <fstream>
#include <iostream>
#include "ItemType.h"
// File ItemType.h must be provided by the user of this class.
//  ItemType.h must contain the following definitions:
//  MAX_ITEMS:     the maximum number of items on the list
//  ItemType:      the definition of the objects on teh list
//  RelationType:  (LESS, GREATER, EQUAL)
//  Member function ComparedTo(ItemType item), which returns
//		LESS, if self "comes before" item
//		GREATER, if self "comes after" item
//		EQUAL, if self and item are the same



class UnsortedType
{
public:
	UnsortedType();
	bool IsFull() const;
	int LengthIs() const;
	void RetrieveItem(ItemType& item, bool& found);
	void InsertItem(ItemType item);
	void DeleteItem(ItemType item);
	void ResetList();
	void GetNextItem(ItemType& item);
private:
	int length;
	ItemType info[MAX_ITEMS];
	int currentPos;
};

int main()
{
	using namespace std;
	ifstream dataFile;  //input
	
	void CreateListFromFile (std::ifstream&, UnsortedType);
	Menu()
	{
	cout << "Please enter a command";
		 << "RETRIEVE = Retrieve an item";
		 << "INSERT = Insert an item";
		 << "DELETE = Delete an item";
		 << "RESET = Reset list";
		 << "QUIT = Quit" << endl;
	cin >> input;
	switch (input)
	{
	case RETRIEVE : RetrieveItem(ItemType&, bool&);
					Menu();
	case INSERT   : InsertItem(ItemType);
					Menu();
	case DELETE   : DeleteItem(ItemType);
					Menu();
	case RESET    : ResetList();
					Menu();
	default       : cout << "Goodbye" << endl;
					break;
	}
	Menu();
	GetNextItem(ItemType);
	PrintList(std::ofstream&, UnsortedType);
	}


void PrintList(std::ofstream& dataFile, UnsortedType list)
// Pre:  list has been initialized.
//       dataFile is open for writing.
// Post: Each componenet in list has been written to dataFile.
//       dataFile is still open.
{
	int length;
	ItemType item;

	list.ResetList();
	length = list.LengthIs();
	for (int counter = 1; counter <= length; counter++)
	{
		list.GetNextItem(item);
		item.Print(dataFile);
	}
}

void CreateListFromFile(std::ifstream& dataFile, UnsortedType& list)
// Pre:  datafile exists and is open.
// Post: list contains items from dataFile.
//       dataFile is in the fail state due to end-of-file.
//       Items read after the list becomes full are discarded.
{
	ItemType item:

	list.MakeEmpty();
	GetData(dataFile, item); //Reads one item from dataFile.
	while (dataFile)
	{
		if (!list.IsFull())
			list.InsertItem(item);
		GetData(dataFile, item);
	}
}

void UnsortedType::RetrieveItem(ItemType& item, bool& found)
// Pre:  Key member(s) of item is initialized.
// Post: If found, ite's key matches an element's key in the
//       list and a copy of that element has been stored in item;
//       otherwise, item is unchanged.
{
	bool moreToSearch;
	int location = 0;
	found = false;

	moreToSearch = (location < length);

	while (moreToSearch && !found)
	{
		switch (item.ComparedTo(info[location]))
		{
		case LESS    :
		case GREATER : location++;
					   moreToSearch = (location < length);
					   break;
		case EQUAL   : found = true;
			           item = info[location];
					   break;
		}
	}
}

void UnsortedType::InsertItem(ItemType item)
// Post: item is in the list.
{
	info[length] = item;
	length++;
}

void UnsortedType::DeleteItem(ItemType item)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
{
	int location = 0;
	while (item.ComparedTo(info[location]) != EQUAL)
		location++;

	info[location] = info[length - 1];
	length--;
}

void UnsortedType::ResetList()
// Post: currentPos has been initialized.
{
	currentPos = -1;
}

void UnsortedType::GetNextItem(ItemType& item)
// Pre:  No transformer has been executed since last call
// Post: item is current item.
//       Current position has been updated.
{
	currentPos++;
	item = info[currentPos];
}

