#include "CircularBuffer.h"

int CircularBuffer::GetSize()
{
	return size;
}

char CircularBuffer::GetValue(int index)
{
	int realIndex = (end + index) % BUFFER_SIZE;

	return array[realIndex];
}

char CircularBuffer::GetFront()
{
	return array[start];
}

char CircularBuffer::GetBack()
{
	return array[end];
}

void CircularBuffer::PushFront(char value)
{
	array[start] = value;
	start = (start + 1) % BUFFER_SIZE;
	++size;

	//Check if Overflow happens
	int overflow = size - BUFFER_SIZE;

	if (overflow > 0)
	{
		//std::cout << "Buffer overflow!" << std::endl;
		size -= overflow;
		end = (end + overflow) % BUFFER_SIZE;
	}
}

void CircularBuffer::PushBack(char value)
{
	end = (end - 1) + (end < 1 ? BUFFER_SIZE : 0);
	array[end] = value;
	++size;

	//Check if Overflow happens
	int overflow = size - BUFFER_SIZE;

	if (overflow > 0)
	{
		//std::cout << "Buffer overflow!" << std::endl;
		size -= overflow;
		start = (start - 1) + (start < 1 ? BUFFER_SIZE : 0);
	}
}

char CircularBuffer::PopFront()
{
	if (size <= 0)
	{
		//std::cout << "Buffer empty, nothing to pop!" << std::endl;
		return NULL;
	}

	char ret = GetFront();

	start = (start - 1) + (start < 1 ? BUFFER_SIZE : 0);
	--size;
	return ret;
}

char CircularBuffer::PopBack()
{
	if (size <= 0)
	{
		//std::cout << "Buffer empty, nothing to pop!" << std::endl;
		return NULL;
	}

	char ret = GetBack();

	end = (end + 1) % BUFFER_SIZE;
	--size;
	return ret;
}

CircularBuffer::CircularBuffer()
{
	end = 0;
	start = 0;
	size = 0;
}
