#pragma once
#define BUFFER_SIZE 10

#include <iostream>

class CircularBuffer
{
private:
	int end;
	int start;
	char array[BUFFER_SIZE];
	int size;
public:
	int GetSize();
	char GetValue(int index);
	char GetFront();
	char GetBack();
	void PushFront(char value);
	void PushBack(char value);
	char PopFront();
	char PopBack();

	CircularBuffer();
};