#include <iostream>
#include <limits>
#include "CircularBuffer.h"

using namespace std;

CircularBuffer cb;

void DisplayMessage()
{
	for (int i = 0; i < cb.GetSize(); i++)
	{
		cout << cb.GetValue(i) << " ";
	}
	cout << endl;

	cout << "=========================" << endl;
	cout << "Choose : "					<< endl;
	cout << "[1] Push Back"				<< endl;
	cout << "[2] Push Front"			<< endl;
	cout << "[3] Pop Back "				<< endl;
	cout << "[4] Pop Front"				<< endl;
	cout << "=========================" << endl;
}

void ResetInput()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
/*
int main(void)
{
	while (true)
	{
		char choice = NULL;
		char input = NULL;
		char selected = NULL;
		int index = NULL;

		DisplayMessage();

		while (!(cin >> choice))
		{
			ResetInput();
			cout << "Please input correct value: ";
		}
		ResetInput();

		switch (choice)
		{
		case '1':
			cout << "Type a character: ";
			while (!(cin >> input))
			{
				ResetInput();
				cout << "Input only accepts character: ";
			}
			cb.PushBack(input);
			break;
		case '2':
			cout << "Type a character: ";
			while (!(cin >> input))
			{
				ResetInput();
				cout << "Input only accepts character: ";
			}
			cb.PushFront(input);
			break;
		case '3':
			cout << "Pop Back." << endl;
			cb.PopBack();
			break;
		case '4':
			cout << "Pop Front." << endl;
			cb.PopFront();
			break;
		default:
			cout << "Invalid choice." << endl;
			break;
		}

		ResetInput();
		system("PAUSE");
		system("CLS");
	}

	system("PAUSE");
	return 0;
}
*/