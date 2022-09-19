#include "Stack.h"

Stack::Stack()
{
	top = NULL;
	return;
}

bool Stack::is_empty()
{
	if (top == NULL)
	{
		return true;
	}
	else return false;
}

Stack::~Stack()
{
	Labirint::Position buffer_pos;
	while (pop(buffer_pos))
	{

	}
	top = NULL;
}

const Labirint::Position Stack::take_top()
{
	return top->pos;
}

void Stack::push(const Labirint::Position push_pos)
{
	Node* node = new Node;
	if (!node)
	{
		Labirint::Position buffer_pos;
		std::cout << "Push (new) error!!!" << std::endl;
		while (pop(buffer_pos))
		{

		}
		return;
	}

	node->next = top;
	node->pos = push_pos;
	top = node;
	return;
}

int Stack::pop(Labirint::Position& buffer)
{
	if (is_empty())
	{
		return 0;
	}

	Node* tmp = top;
	top = tmp->next;
	tmp->next = NULL;
	buffer = tmp->pos;
	delete tmp;
	return 1;
}

void Stack::print_stack()
{
	Node* tmp = top;

	while (tmp)
	{
		std::cout << tmp->pos << std::endl;
		tmp = tmp->next;
	}
	return;
}

