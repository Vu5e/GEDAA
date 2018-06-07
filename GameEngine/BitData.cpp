#define MAX 4294967295
#define MIN 0
#define TOTAL_BITS 32

#include <iostream>

using namespace std;

class BitData
{
private:
	unsigned int m_data;

	void legacy_Set(int location, bool flag) //Location starts at 0
	{
		int temp = m_data >> location; //Bitshift to location
		if (flag == temp & 1) return; //Skip operation if flag == current value

		temp += (flag ? 1 : -1); //Edit according to flag
		temp = temp << location; //Bitshift back to original

		int mask = ~(MAX << location); //Mask that takes the missing value from m_data

		m_data = temp + (m_data & mask);
	}

	bool expanded_Get(int location)
	{
		int ret = m_data >> location;
		ret = ret & 1;

		return ret;
	}

public:
	BitData()
	{
		Reset();
	}

	void Reset()
	{
		m_data = 0;
	}

	void Set(int location, bool flag) //Location starts at 0
	{
		if (flag == Get(location)) return;

		m_data += (1 << location) * (flag ? 1 : -1);
	}

	bool Get(int location)
	{
		return (m_data >> location) & 1;
	}
};

void ListContent(BitData data)
{
	for (int i = 0; i < TOTAL_BITS; i++)
	{
		cout << i << ". ";
		if (data.Get(i))
		{
			cout << "TRUE" << endl;
		}
		else
		{
			cout << "FALSE" << endl;
		}
	}
}

int main(void)
{
	BitData bitData;

	bitData.Set(0, true);
	bitData.Set(4, true);
	bitData.Set(7, true);
	bitData.Set(8, true);
	bitData.Set(9, false);
	bitData.Set(10, false);

	ListContent(bitData);

	system("PAUSE");

	return 0;
}