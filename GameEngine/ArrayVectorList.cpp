#include <iostream>
#include <vector>
#include <list>

using namespace std;

void PushFront(vector<int>& container, int newValue)
{
	container.push_back(container[container.size() - 1]);
	for (int i = container.size() - 2; i >= 1; i--)
	{
		container[i] = container[i - 1];
	}
	container[0] = newValue;
}

void RunVector()
{
	vector<int> m_vcontainer;
	m_vcontainer.push_back(34);
	m_vcontainer.push_back(2);
	m_vcontainer.push_back(100);

	m_vcontainer[0] = 2000;

	//Push front (INEFFICIENT)
	PushFront(m_vcontainer, 5555);

	for (int i = 0; i < m_vcontainer.size(); i++)
	{
		cout << m_vcontainer[i] << endl;
	}

	cout << "=========================" << endl;

	// Standard and consistent way for all kind of containers (array, vector, list, etc)
	// Traverse the vector container by using iterator
	vector<int>::iterator it = m_vcontainer.begin();

	//while (it != m_vcontainer.back()) //Last element
	while (it != m_vcontainer.end()) //After last element
	{
		int value = *it; // Deference iterator to get the value
		cout << value << endl;

		it++; // To next slot
	}
}

void RunList()
{
	list<int> m_lcontainer;
	m_lcontainer.push_back(34);
	m_lcontainer.push_back(2);
	m_lcontainer.push_back(100);

	m_lcontainer.push_front(200);

	//m_lcontainer[0] = 2000; // Cannot be randomly accessed

	// Not working because list cannot be randomly accessed
	/*
	for (int i = 0; i < m_lcontainer.size(); i++)
	{
	cout << m_lcontainer[i] << endl;
	}
	*/

	cout << "=========================" << endl;

	// Remove value example
	list<int>::iterator it = m_lcontainer.begin();

	while (it != m_lcontainer.end())
	{
		int value = *it;

		if (value <= 50)
		{
			it = m_lcontainer.erase(it); //Erase() returns the next following element after the erased element
		}
		else
		{
			*it = value + 1;
			it++;
		}
	}


	// Traverse the vector container by using iterator
	it = m_lcontainer.begin();

	//while (it != m_vcontainer.back()) //Last element
	while (it != m_lcontainer.end()) //After last element
	{
		int value = *it; // Deference iterator to get the value

		cout << value << endl;

		it++; // To next slot
	}
}

/*
int main(void)
{
//RunVector();
RunList();
system("PAUSE");
return 0;
}
*/