#pragma once
#include "Labirint.h"


class Stack
{
private:

	typedef struct Node
	{
		Labirint::Position pos;
		Node* next;
	}Node;

	Node* top;

public:
	//Stack();
	//~Stack();
	//void push(const Cell& cell);
	//int pop(Cell& buffer);
	//Cell& take_top();
	//bool is_empty(); 
	//void print_stack();

	Stack();
	~Stack();
	void push(const Labirint::Position pos);
	int pop(Labirint::Position& buf_pos);
	const Labirint::Position take_top(); //Не вижу смысла возвращать ссылку. Мало ли поменяет кто-то.
	bool is_empty();
	void print_stack();
	
};