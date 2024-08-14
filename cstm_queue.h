#include <iostream>

using namespace std;

template <typename T>
struct Nod
{
	T data;
	Nod *next;
	Nod(T value)
	{
		data = value;
		next = nullptr;
	}
};

template <typename T>
class Queue
{
  private:
	Nod <T>*front;
	Nod <T>*rear;

  public:
	Queue()
	{
		front = nullptr;
		rear = nullptr;
	}
	
	void display()
	{
		Nod<T> *temp = front;
		while(temp != nullptr)
		{
			cout << temp->data;
			temp = temp->next;
		}
	}

	bool isEmpty()
	{
		return front == nullptr;
	}

	void enqueue(T &value)
	{
		Nod<T> *newNod = new Nod<T>(value);
		if (isEmpty())
		{
			front = rear = newNod;
		}
		else
		{
			rear->next = newNod;
			rear = newNod;
		}
	}

	bool dequeue()
	{
		if (isEmpty())
		{
			std::cout << "Queue is empty. Cannot dequeue." << std::endl;
			return false;
		}

		Nod<T> *temp = front;
		front = front->next;
		delete temp;

		if (front == nullptr)
		{
			rear = nullptr;
		}
		return true;
	}

	T frontValue()
	{
		if (isEmpty())
		{
			std::cout << "Queue is empty. No front element." << std::endl;
			// Return an Empty object of type T
			return T();
		}

		return front->data;
	}
};