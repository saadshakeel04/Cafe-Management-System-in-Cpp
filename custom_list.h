#include <iostream>

using namespace std;

template <typename T>
struct Node
{
	T data;
	Node<T> *next;
};

template <typename T>
class SingleLL
{
	Node<T> *head, *tail;

  public:
	SingleLL()
	{
		head = tail = nullptr;
	}
	bool is_empty()
	{
		return (head == nullptr);
	}
	int length() //Returns Number of Nodes
	{
		int count = 0;
		Node<T> *temp = head;
		while (temp != nullptr)
		{
			temp = temp->next;
			count++;
		}
		return count;
	}
	int size()
	{
		return length();
	}
	void display()
	{
		Node<T> *temp = head;
		for (int i = 0; i < length(); i++)
		{
			cout << temp->data << endl;
			temp = temp->next;
		}
	}
	void push_back(T d) //inserts at end
	{
		Node<T> *temp = new Node<T>;
		temp->data = d;
		temp->next = nullptr;
		if (is_empty())
		{
			head = tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}
	void insert_at_start(T d)
	{
		Node<T> *temp = new Node<T>;
		temp->data = d;
		temp->next = nullptr;
		if (is_empty())
		{
			head = tail = temp;
		}
		else
		{
			temp->next = head;
			head = temp;
		}
		cout << " added successfully";
	}
	void insert_at_position(T d, int pos)
	{
		Node<T> *temp = new Node<T>;
		temp->data = d;
		temp->next = nullptr;
		if (pos < 1 || pos > length() + 1)
		{
			cout << "Invalid Position";
		}
		else if (pos == 1)
		{
			insert_at_start(d);
		}
		else if (pos == length() + 1)
		{
			push_back(d);
		}
		else
		{
			Node<T> *cur, *prev;
			cur = head;
			for (int i = 1; i < pos; i++)
			{
				prev = cur;
				cur = cur->next;
			}
			prev->next = temp;
			temp->next = cur;
			cout << " added successfully";
		}
	}
	void delete_at_start()
	{
		if (is_empty())
		{
			cout << "List Empty";
		}
		else
		{
			Node<T> *temp = head;
			head = head->next;
			cout << temp->data << " deleted";
			delete temp;
		}
	}
	void delete_at_end()
	{
		if (is_empty())
		{
			cout << "List Empty";
		}
		else
		{
			Node<T> *curr, *prev;
			curr = head;
			for (int i = 1; i < length(); i++)
			{
				prev = curr;
				curr = curr->next;
			}
			tail = prev;
			tail->next = nullptr;
			cout << curr->data << " is to be deleted";
			delete curr;
		}
	}
	void delete_at_position(int pos)
	{
		if (is_empty())
		{
			cout << "List Empty";
		}
		else if (pos < 1 || pos > length())
		{
			cout << "Invalid Position";
		}
		else if (pos == 1)
		{
			delete_at_start();
		}
		else if (pos == length())
		{
			delete_at_end();
		}
		else
		{
			Node<T> *cur, *prev, *next;
			cur = head;
			for (int i = 1; i < pos; i++)
			{
				prev = cur;
				cur = cur->next;
				next = cur->next;
			}
			prev->next = next;
			cout << cur->data << " deleted";
			delete cur;
		}
	}

	T at(int index)
	{
		if (index < 0 || index >= length())
		{
			return T();
		}
		Node<T> *temp = head;
		for (int i = 0; i < index; ++i)
		{
			temp = temp->next;
		}
		return temp->data;
	}
};