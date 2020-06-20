#include <iostream>
#include <string>
#include <fstream>
using namespace std;
template <class T>
class Queue
{
	template<class T>
	struct Node
	{
		T data;
		Node<T> *next;

		Node(const T& d)
		{
			data = d;
			next = NULL;
		}
	};

	Node<T> *front, *rear;
	int count;

public:
	Queue()
	{
		front = rear = NULL;
		count = 0;
	}

	bool isEmpty()
	{
		return !count;
	}

	void enqueue(const T& d)
	{
		if (count == 0)
		{
			front = rear = new Node<T>(d);
		}
		else
		{
			rear->next = new Node<T>(d);
			rear = rear->next;
		}
		count++;
	}

	T dequeue()
	{
		if (!isEmpty())
		{
			T temp = front->data;
			Node<T> *temp1 = front->next;
			delete front;
			front = NULL;
			front = temp1;
			count--;
			return temp;
		}
	}

	void printQ()
	{
		Node<T> *current = front;
		while (current != NULL)
		{
			cout << current->data << " ";
			current = current->next;
		}
	}
	int getCount()
	{
		return count;
	}
};

template <class T>
class vector
{
	int count;	//COUNT OF ELEMENTS CURRENTLY IN
	int capacity;
	T	*arr;

public:

	class Error
	{
		//EXCEPTION CLASS
	};

	vector()	//DEFAULT CONSTRUCTOR
	{
		capacity = count = 0;
		arr = NULL;
	}

	vector(int max_capacity)	//ARGUMENTED CONSTRUCTOR
	{
		capacity = max_capacity;
		arr = new T[capacity];
		count = 0;
	}

	vector(const vector<T>& vec)	//COPY CONSTRUCTOR
	{
		capacity = vec.getCapacity();//CONST-FUNCTION
		count = vec.getCount();	  //CONST-FUNCTION

		arr = new T[capacity];

		for (int i = 0; i < count; i++)	//COPIES ONLY DATA AND NOT GARBAGE
		{
			arr[i] = vec.at(i);	  //CONST-FUNCTION
		}
	}

	void push_back(T& element)
	{	//BACK IS INDICATED BY 'count'	

		if (count == 0)
		{
			arr = new T[1];
			arr[0] = element;
			count++;
			capacity++;
			return;
		}

		if (count < capacity)
		{
			arr[count] = element;
			count++;
		}
		//else arr is full and needs to be resized
		else
		{
			T *temp = new T[2 * capacity];	//A NEW ARRAY OF DOUBLE CAPACITY

			for (int i = 0; i < capacity; i++)
				temp[i] = arr[i];	 //MOVING TO THE NEW ARRAY

			temp[count] = element;
			capacity = 2 * capacity; //CAPACITY IS DOUBLED AT OVERFLOW

			delete[] arr;
			arr = temp;

			count++;
		}
	}

	void pop_back()	//REMOVES THE LAST ELEMENT OF THE VECTOR
	{
		if (count <= capacity / 2)
		{
			T *temp = new T[capacity / 2];
			for (int i = 0; i < count - 1; i++)
				temp[i] = arr[i];
			delete arr;
			arr = temp;
			capacity = capacity / 2;
		}
		count--;
	}

	void reallocate(int max_capacity)
	{	//ERASES ALLOCATED VECTOR, CREATES A NEW ONE OF SPECIFIED CAPACITY

		delete[] arr;
		capacity = max_capacity;
		arr = new T[capacity];
		count = 0;
	}

	T at(int index) const	//RETURNS THE VALUE AT 'index'
	{
		if (count != 0 && index < capacity && index >= 0)
			return arr[index];
		else throw Error();
	}

	const vector<T>& operator = (const vector<T>& vec)
	{
		reallocate(vec.getCapacity());

		for (int i = 0; i < vec.count; i++) //copies only data, not garbage
		{
			arr[i] = vec.at(i);
			count++;
		}

		return *this;
	}

	T& operator[] (int index) const	//RETURNS DATA AT THE iTH INDEX OF THE VECTOR
	{
		if (count != 0 && index >= 0 && index < count)
			return arr[index];
		else throw Error();
	}

	void printVector()	//FOR INTEGARS OR DATA WITH << OPERATOR OVERLOADED
	{
		for (int i = 0; i < count; i++)
			cout << arr[i] << " ";
		cout << endl;
	}

	bool isPresent(const T& data, int i) //checks if data is present before i
	{
		for (int k = 0; k < i; k++)
			if (arr[k] == data)
				return true;
		return false;
	}

	int getCount() const
	{
		return count;
	}

	int getCapacity() const
	{
		return capacity;
	}

	~vector()
	{
		delete arr;
	}
};

class Student
{
	string fname, sname;
	string rno;
	float cgpa;
	int batch;
	int wcount;
public:
	Student()
	{
		fname = sname = rno = "";
		cgpa = batch = wcount = 0;
	}
	Student(const string& roll)
	{
		rno = roll;
		fname = sname = "";
		cgpa = batch = wcount = 0;
	}
	Student(const Student& obj)
	{
		rno = obj.rno;
		fname = obj.fname;
		sname = obj.sname;
		cgpa = obj.cgpa;
		batch = obj.batch;
		wcount = obj.wcount;
	}
	Student(const string& first, const string& sir, const string& roll, float gpa, int b, int wc)
	{
		fname = first;
		sname = sir;
		rno = roll;
		cgpa = gpa;
		batch = b;
		wcount = wc;
	}

	friend ostream& operator << (ostream& out, Student& obj);
	friend bool operator < (const Student& obj1, const Student& obj2);
	friend bool operator > (const Student& obj1, const Student& obj2);
	friend bool operator == (const Student& obj1, const Student& obj2);
	void readFromFile(ifstream& inputFile)
	{
		string f; float a; int b; char ch;
		string s;

		getline(inputFile, f, ',');
		fname = f;
		inputFile.get(ch);

		getline(inputFile, f, ',');
		sname = f;
		inputFile.get(ch);

		getline(inputFile, f, ',');
		rno = f;
		inputFile.get(ch);

		inputFile >> a;
		cgpa = a;
		inputFile.get(ch);

		inputFile >> b;
		batch = b;
		inputFile.get(ch);

		inputFile >> b;
		wcount = b;
		inputFile.get(ch);
	}
	void writeInFile(ofstream& out)
	{
		out << rno << ", " << fname << ", " << sname << ", " << cgpa << ", " << batch << ", " << wcount << "\n";
	}
	void printGPA()
	{
		cout << cgpa << ", " << fname << ", " << sname << ", " << batch << ", " << wcount;
	}
	void getData()
	{
		cout << "Enter Roll Number: ";
		getline(cin, rno);
		cout << "Enter First Name: ";
		getline(cin, fname);
		cout << "Enter Sir Name: ";
		getline(cin, sname);
		cout << "CGPA: ";
		cin >> cgpa;
		cout << "Batch: ";
		cin >> batch;
		cout << "Warning count: ";
		cin >> wcount;

	}
};

bool operator == (const Student& obj1, const Student& obj2)
{
	if (obj1.rno == obj2.rno)
		return true;
	else return false;
}

bool operator > (const Student& obj1, const Student& obj2)
{
	if (obj1.rno > obj2.rno)
		return true;
	else return false;
}

bool operator < (const Student& obj1, const Student& obj2)
{
	if (obj1.rno < obj2.rno)
		return true;
	else return false;
}

ostream& operator << (ostream& out, Student& obj)
{
	out << obj.rno << ", " << obj.fname << ", " << obj.sname << ", " << obj.cgpa << ", " << obj.batch << ", " << obj.wcount;
	return out;
}

template <class T>
class tree23
{
	template <class T>
	struct Node
	{
		T keys[2];
		Node<T>* ch[3];
		int count; //count of keys

		Node()
		{
			count = 0;
			ch[0] = ch[1] = ch[2] = NULL;
		}

		Node(const T& data)
		{
			keys[0] = data;
			count = 1;
			ch[0] = ch[1] = ch[2] = NULL;
		}

		int nodeType()
		{
			if (ch[0] == NULL && ch[1] == NULL && ch[2] == NULL)
				return 1;
			if (count == 1)
				return 2;
			if (count == 2)
				return 3;
			return 0;
		}

		bool isPresent(const T& data) //checks if data is present in the node or not
		{
			if (data == keys[0])
				return true;
			else if (count == 2 && data == keys[1])
				return true;
			else return false;
		}

		void addKey(const T& data)
		{
			if (count == 0)
				keys[0] = data;
			else
			{
				if (data < keys[0])
				{
					keys[1] = keys[0];
					keys[0] = data;
				}
				else keys[1] = data;
			}
			count++;
		}

		void removeKey(const T& data)
		{
			if (data == keys[0])
				keys[0] = keys[1];
			count--;
		}
	};

	Node<T> *root;

	bool rotationPossible(Node<T> *current, const T& data) //rotation "about" current
	{
		if (current->count == 1)
		{
			if (data < current->keys[0])
			{
				if (current->ch[2] != NULL && current->ch[2]->count == 1) //NULL should be checked in case insertion is at leaf
					return true;
				else return false;
			}
			else if (data > current->keys[0])
			{
				if (current->ch[0] != NULL && current->ch[0]->count == 1) //NULL should be checked in case insertion is at leaf
					return true;
				else return false;
			}
		}
		else
		{
			if (data < current->keys[0])
			{
				if (current->ch[1] != NULL && current->ch[1]->count == 1) //NULL should be checked in case insertion is at leaf
					return true;
				else return false;
			}
			else if (data > current->keys[0] && data < current->keys[1])
			{
				if (current->ch[0] != NULL && current->ch[0]->count == 1)
					return true;
				else if (current->ch[2] != NULL && current->ch[2]->count == 1)
					return true;
				else return false;
			}
			else if (data > current->keys[1])
			{
				if (current->ch[1] != NULL && current->ch[1]->count == 1)
					return true;
				else return false;
			}
		}//end of else
	}//end of function

	void rotateRight(Node<T> *current, const T& data, Node<T> *Left, Node<T> *Right)
	{
		T temp = current->keys[0];
		if (data < Left->keys[1])
		{
			current->keys[0] = Left->keys[1];
			if (data < Left->keys[0])
			{
				Left->keys[1] = Left->keys[0];
				Left->keys[0] = data;
			}
			else Left->keys[1] = data;
		}
		else
			current->keys[0] = data;
		Right->addKey(temp);
	}

	void rotateLeft(Node<T> *current, const T& data, Node<T> *Left, Node<T>* Right)
	{
		T temp = current->keys[0];
		if (data > Right->keys[0])
		{
			current->keys[0] = Right->keys[0];
			if (data > Right->keys[1])
			{
				Right->keys[0] = Right->keys[1];
				Right->keys[1] = data;
			}
			else Right->keys[0] = data;
		}
		else
			current->keys[0] = data;
		Left->addKey(temp);
	}

	void rotate(Node<T> *current, const T& data)
	{
		if (current->count == 1)
		{
			if (data < current->keys[0])
				rotateRight(current, data, current->ch[0], current->ch[2]);
			else if (data > current->keys[0])
				rotateLeft(current, data, current->ch[0], current->ch[2]);
		}
		else //count ==  2
		{
			if (data < current->keys[0]) //rotateRight
			{
				current->ch[1]->addKey(current->keys[0]);
				current->removeKey(current->keys[0]);
				if (data < current->ch[0]->keys[1])
				{
					current->addKey(current->ch[0]->keys[1]);
					current->ch[0]->removeKey(current->ch[0]->keys[1]);
					current->ch[0]->addKey(data);
				}
				else current->addKey(data);

			}
			else if (data > current->keys[0] && data < current->keys[1])
			{
				if (current->ch[0]->count == 1) //if left has space
				{
					current->ch[0]->addKey(current->keys[0]);
					current->removeKey(current->keys[0]);
					if (data > current->ch[1]->keys[0])
					{
						current->addKey(current->ch[1]->keys[0]);
						current->ch[1]->removeKey(current->ch[1]->keys[0]);
						current->ch[1]->addKey(data);
					}
					else current->addKey(data);
				}
				else //else right has space
				{
					current->ch[2]->addKey(current->keys[1]);
					current->removeKey(current->keys[1]);
					if (data < current->ch[1]->keys[1])
					{
						current->addKey(current->ch[1]->keys[1]);
						current->ch[1]->removeKey(current->ch[1]->keys[1]);
						current->ch[1]->addKey(data);
					}
					else current->addKey(data);
				}
			}
			else if (data > current->keys[1]) //rotateLeft	
			{
				current->ch[1]->addKey(current->keys[1]);
				current->removeKey(current->keys[1]);
				if (data > current->ch[2]->keys[0])
				{
					current->addKey(current->ch[2]->keys[0]);
					current->ch[2]->removeKey(current->ch[2]->keys[0]);
					current->ch[2]->addKey(data);
				}
				else current->addKey(data);
			}
		}
	}//end of function

	void split(Node<T> *current, const T& data, Node<T> *&ptr)
	{
		Node<T> *temp = NULL;

		if (data < current->keys[0])
		{
			temp = new Node<T>(current->keys[0]);
			temp->ch[2] = new Node<T>(current->keys[1]);
			if (ptr == NULL)
				temp->ch[0] = new Node<T>(data);
			else
			{
				temp->ch[0] = ptr;
				temp->ch[2]->ch[0] = current->ch[1];
				temp->ch[2]->ch[2] = current->ch[2];
			}
		}
		else if (data > current->keys[0] && data < current->keys[1])
		{
			temp = new Node<T>(data);
			temp->ch[0] = new Node<T>(current->keys[0]);
			temp->ch[2] = new Node<T>(current->keys[1]);
			if (ptr != NULL)
			{
				temp->ch[0]->ch[0] = current->ch[0];
				temp->ch[0]->ch[2] = ptr->ch[0];
				temp->ch[2]->ch[0] = ptr->ch[2];
				temp->ch[2]->ch[2] = current->ch[2];
			}
		}
		else if (data > current->keys[1])
		{
			temp = new Node<T>(current->keys[1]);
			temp->ch[0] = new Node<T>(current->keys[0]);
			if (ptr == NULL)
				temp->ch[2] = new Node<T>(data);
			else
			{
				temp->ch[0]->ch[0] = current->ch[0];
				temp->ch[0]->ch[2] = current->ch[1];
				temp->ch[2] = ptr;
			}
		}

		ptr = temp;
		if (current == root)
			root = ptr;
		delete current;
		return;
	}

	void insert(const T& data, Node<T> *current, Node<T> *&ptr, Node<T> *pre) //recursive
	{
		if (current->nodeType() != 1) //if not leaf
		{
			if (!current->isPresent(data))
			{
				if (data < current->keys[0])
					insert(data, current->ch[0], ptr, current);
				else if (current->count == 2 && data < current->keys[1])
					insert(data, current->ch[1], ptr, current);
				else
					insert(data, current->ch[2], ptr, current);
			}
		}
		else if (!current->isPresent(data))
		{	//at leaf
			if (current->count == 1)
				current->addKey(data);
			else
			{
				if (pre != NULL && rotationPossible(pre, data))
					rotate(pre, data);
				else
					split(current, data, ptr); //modifies ptr
			}
			return;
		}
		if (ptr != NULL) //if a key is being promoted to an internal node
		{
			if (current->count == 1)
			{
				if (ptr->keys[0] > current->keys[0])
				{
					current->keys[1] = ptr->keys[0];
					current->ch[2] = ptr->ch[2];
					current->ch[1] = ptr->ch[0];
					current->count++;
				}
				else if (ptr->keys[0] < current->keys[0])
				{
					current->addKey(ptr->keys[0]);
					current->ch[0] = ptr->ch[0];
					current->ch[1] = ptr->ch[2];
				}
				delete ptr;
				ptr = NULL;
			}
			else
			{	//promote again
				split(current, ptr->keys[0], ptr);
				return;
			}
		}
	}//end of function

	Node<T>* search(const T& key, Node<T> *&parent)
	{
		Node<T> *current = root;
		while (current != NULL)
		{
			if (key == current->keys[0])
				return current;
			else if (current->count == 2 && key == current->keys[1])
				return current;
			else if (key < current->keys[0])
			{
				parent = current;
				current = current->ch[0];
			}
			else if (current->count == 2 && key < current->keys[1])
			{
				parent = current;
				current = current->ch[1];
			}
			else
			{
				parent = current;
				current = current->ch[2];
			}
		}
		return NULL;

	}

	Node<T>* getPredecessor(Node<T> *node, const T& key)
	{
		Node<T> * temp = NULL;
		if (node->count == 1)
		{
			temp = node->ch[0];
			while (temp->ch[2] != NULL)
				temp = temp->ch[2];
		}
		else
		{
			if (key == node->keys[0])
			{
				temp = node->ch[0];
				while (temp->ch[2] != NULL)
					temp = temp->ch[2];
			}
			else
			{
				temp = node->ch[1];
				while (temp->ch[2] != NULL)
					temp = temp->ch[2];
			}
		}
		return temp;
	}

	void merge(Node<T> *parent, Node<T> *keyPosition) //parent->count == 1
	{
		parent->ch[0]->addKey(parent->keys[0]);

		if (keyPosition == parent->ch[0])
		{
			parent->ch[0]->addKey(parent->ch[2]->keys[0]);
			parent->ch[2]->removeKey(parent->ch[2]->keys[0]);
			parent->ch[0]->ch[1] = parent->ch[2]->ch[0];
			parent->ch[0]->ch[2] = parent->ch[2]->ch[2];
		}
		else if (keyPosition == parent->ch[2])
		{
			parent->ch[0]->ch[1] = parent->ch[0]->ch[2];
			parent->ch[0]->ch[2] = parent->ch[2]->ch[0];
		}
		parent->removeKey(parent->keys[0]);
		parent->ch[2] = NULL;
	}

	int rotationDirection(Node<T> *parent, const T& key)
	{
		if (parent->count == 1)
		{
			if (key < parent->keys[0] && parent->ch[2]->count == 2)
				return 1;
			else if (key > parent->keys[0] && parent->ch[0]->count == 2)
				return 2;
			else return 0;
		}
		else
		{
			if (key < parent->keys[0] && parent->ch[1]->count == 2)
				return 3;
			else if (parent->ch[1]->count != 2)
				return 8;
			else if (key < parent->keys[1])
			{
				if (parent->ch[0]->count == 2)
					return 4;
				else if (parent->ch[2]->count == 2)
					return 5;
				else return 7;
			}
			else if (key > parent->keys[1] && parent->ch[1]->count == 2)
				return 6;
			else return 9;
		}
	}

	bool Rotate(Node<T> *parent, const T& key) //ROTATION REQUIRED IN DELETE
	{
		//ADJUSTS NODES WHEN THERE IS NO UNDERFLOW

		int d = rotationDirection(parent, key);

		if (d == 0)
			return false;

		if (d == 1)
		{
			parent->ch[0]->addKey(parent->keys[0]);
			parent->removeKey(parent->keys[0]);
			parent->addKey(parent->ch[2]->keys[0]);
			parent->ch[2]->removeKey(parent->ch[2]->keys[0]);
			parent->ch[0]->ch[2] = parent->ch[2]->ch[0];
			parent->ch[2]->ch[0] = parent->ch[2]->ch[1];
			parent->ch[2]->ch[1] = NULL;
			return true;
		}
		if (d == 2)
		{
			parent->ch[2]->addKey(parent->keys[0]);
			parent->removeKey(parent->keys[0]);
			parent->addKey(parent->ch[0]->keys[1]);
			parent->ch[0]->removeKey(parent->ch[0]->keys[1]);
			parent->ch[2]->ch[2] = parent->ch[2]->ch[0];
			parent->ch[2]->ch[0] = parent->ch[0]->ch[2];
			parent->ch[0]->ch[2] = parent->ch[0]->ch[1];
			parent->ch[0]->ch[1] = NULL;
			return true;
		}

		if (d == 3)
		{
			parent->ch[0]->addKey(parent->keys[0]);
			parent->removeKey(parent->keys[0]);
			parent->addKey(parent->ch[1]->keys[0]);
			parent->ch[1]->removeKey(parent->ch[1]->keys[0]);
			parent->ch[0]->ch[2] = parent->ch[1]->ch[0];
			parent->ch[1]->ch[0] = parent->ch[1]->ch[1];
			parent->ch[1]->ch[1] = NULL;
			return true;

		}
		if (d == 4)
		{
			parent->ch[1]->addKey(parent->keys[0]);
			parent->removeKey(parent->keys[0]);
			parent->addKey(parent->ch[0]->keys[1]);
			parent->ch[0]->removeKey(parent->ch[0]->keys[1]);

			parent->ch[1]->ch[2] = parent->ch[1]->ch[0];
			parent->ch[1]->ch[0] = parent->ch[0]->ch[2];
			parent->ch[0]->ch[2] = parent->ch[0]->ch[1];
			parent->ch[0]->ch[1] = NULL;
			return true;
		}
		if (d == 5)
		{
			parent->ch[1]->addKey(parent->keys[1]);
			parent->removeKey(parent->keys[1]);
			parent->addKey(parent->ch[2]->keys[0]);
			parent->ch[2]->removeKey(parent->ch[2]->keys[0]);
			parent->ch[1]->ch[2] = parent->ch[2]->ch[0];
			parent->ch[2]->ch[0] = parent->ch[2]->ch[1];
			parent->ch[2]->ch[1] = NULL;
			return true;
		}

		if (d == 6)
		{
			parent->ch[2]->addKey(parent->keys[1]);
			parent->removeKey(parent->keys[1]);
			parent->addKey(parent->ch[1]->keys[1]);
			parent->ch[1]->removeKey(parent->ch[1]->keys[1]);

			parent->ch[2]->ch[2] = parent->ch[2]->ch[0];
			parent->ch[2]->ch[0] = parent->ch[1]->ch[2];
			parent->ch[1]->ch[2] = parent->ch[1]->ch[1];
			parent->ch[1]->ch[1] = NULL;
			return true;
		}

		if (d == 7)
		{
			parent->ch[0]->addKey(parent->keys[0]);
			parent->removeKey(parent->keys[0]);
			parent->ch[0]->ch[1] = parent->ch[0]->ch[2];
			parent->ch[0]->ch[2] = parent->ch[1]->ch[0];
			parent->ch[1] = NULL;
			return true;
		}
		if (d == 8)
		{
			parent->ch[0]->addKey(parent->keys[0]);
			parent->removeKey(parent->keys[0]);
			parent->ch[0]->addKey(parent->ch[1]->keys[0]);
			parent->ch[1]->removeKey(parent->ch[1]->keys[0]);
			parent->ch[0]->ch[1] = parent->ch[1]->ch[0];
			parent->ch[0]->ch[2] = parent->ch[1]->ch[2];
			return true;
		}
		if (d == 9)
		{
			parent->ch[0]->addKey(parent->keys[0]);
			parent->removeKey(parent->keys[0]);
			parent->addKey(parent->ch[1]->keys[0]);
			parent->ch[1]->removeKey(parent->ch[1]->keys[0]);
			parent->ch[2]->addKey(parent->keys[1]);
			parent->removeKey(parent->keys[1]);

			parent->ch[0]->ch[1] = parent->ch[0]->ch[2];
			parent->ch[0]->ch[2] = parent->ch[1]->ch[0];
			parent->ch[2]->ch[2] = parent->ch[2]->ch[0];
			parent->ch[2]->ch[0] = parent->ch[1]->ch[2];
			return true;
		}

	}

	void recDelete(const T& key, Node<T> *current, Node<T> *parent, int &hole)
	{
		if (current != NULL)
		{
			if (key == current->keys[0] || current->count == 2 && key == current->keys[1])
			{
				if (current->nodeType() != 1)
				{
					//SWAP WITH PREDECESSOR
					Node<T> *pred = getPredecessor(current, key);
					swap(current, pred, key);
					recDelete(key, pred, current, hole);
				}
				else
				{
					current->removeKey(key);
					if (current->count == 1)
						return;
					else
					{
						if (parent == NULL)
						{
							root = NULL;
							return;
						}
						if (Rotate(parent, key) == 0)
						{
							merge(parent, current);
							hole = 1; //hole is promoted up the tree
						}
						else hole = 0;
						return;
					}
				}
			}
			else if (key < current->keys[0])
				recDelete(key, current->ch[0], current, hole);
			else if (current->count == 2 && key < current->keys[1])
				recDelete(key, current->ch[1], current, hole);
			else recDelete(key, current->ch[2], current, hole);

			if (hole)
			{
				if (current == root)
				{
					root = current->ch[0];
					return;
				}

				if (Rotate(parent, key) == 0)
				{
					merge(parent, current);
					hole = 1;
				}
				else hole = 0;
				return;
			}

		}
	}//end of function

	void getNodes_inOrder(vector<Node<T>*>& vec, Node<T> *current)
	{
		if (current != NULL)
		{
			getNodes_inOrder(vec, current->ch[0]);
			vec.push_back(current);
			if (current->count == 2)
			{
				getNodes_inOrder(vec, current->ch[1]);
				vec.push_back(current);
			}
			getNodes_inOrder(vec, current->ch[2]);
		}
	}

public:
	tree23()
	{
		root = NULL;
	}

	template <class T>
	class iterator
	{
		int index;
		vector<Node<T>*> nodes;
	public:

		iterator() {}

		iterator(const iterator<T>& obj)
		{
			nodes = obj.nodes;
			index = 0;
		}

		bool operator != (iterator<T>& obj)
		{
			if (index == nodes.getCount())
				return false;
			else return true;
		}

		iterator<T>& operator ++ ()	//PRE-INCREMENT
		{
			++index;
			return *this;
		}

		iterator<T>& operator ++(int) //POST-INCREMENT
		{
			index++;
			return *this;
		}

		T operator *() //RETURNS DATA IN NODES
		{
			if (index > 0 && nodes.isPresent(nodes[index], index))
			{
				return nodes[index]->keys[1];
			}
			else return nodes[index]->keys[0];
		}

		int getIndex()
		{
			return index;
		}

		vector<Node<T>*>& getVector()
		{
			return nodes;
		}
	};

	void insert(const T& data)
	{
		if (root == NULL)
		{
			root = new Node<T>(data);
		}
		else
		{
			Node<T> *p = NULL;
			insert(data, root, p, p);
		}
	}

	void search(const T& key)
	{
		Node<T> *temp = NULL;
		Node<T> *p = search(key, temp);
		if (p)
			cout << "Record Found." << endl;
		else cout << "Not found." << endl;
	}

	int getHeight() const
	{
		Node<T> *current = root;
		int h = 0;
		while (current != NULL)
		{
			h++;
			current = current->ch[0]; //left, left, left...
		}
		return h;
	}

	void printInOrder() const
	{
		print(root);
		cout << endl;
	}

	void Delete(const T& key)
	{
		Node<T> *parent = NULL; int hole = 0;
		recDelete(key, root, parent, hole);
	}

	iterator<T> begin()
	{
		iterator<T> i;
		getNodes_inOrder(i.getVector(), root);
		return i;
	}

	Node<T>* getRoot()
	{
		return root;
	}

	iterator<T> end() //RETURNS AN EMPTY ITERATOR
	{
		iterator<T> temp;
		return temp;
	}

	void writeInFile(const string& filename) //STORES IN ORDER OF ROLL NUMBER
	{
		vector<Node<T>*> vec;
		ofstream out(filename);

		getNodes_inOrder(vec, root);
		for (int i = 0; i < vec.getCount(); i++)
		{
			vec[i]->keys[0].writeInFile(out);
			if (vec[i]->count == 2)
			{
				vec[i]->keys[1].writeInFile(out);
				i++;
			}
		}


	}

private:

	///////////SUPPLEMENTARY FUNCTIONS///////////

	void print(Node<T> *current) const
	{
		if (current == NULL)
			return;
		else
		{
			print(current->ch[0]);
			cout << current->keys[0] << endl;
			if (current->count == 2)
			{
				print(current->ch[1]);
				cout << current->keys[1] << endl;
			}
			print(current->ch[2]);
		}
	}

	void swap(Node<T> *current, Node<T> *pred, const T& key)
	{
		T predKey;
		if (pred->count == 2)
			predKey = pred->keys[1];
		else predKey = pred->keys[0];
		pred->removeKey(predKey);
		pred->addKey(key);
		current->removeKey(key);
		current->addKey(predKey);
	}
};
template <class T>
void printInOrder(tree23<T>& t);
template <class T>
void readFromFile(tree23<T> &t, const string& filename);
bool isValid(string& ch);

int main()
{
	tree23<Student> t2;
	string c = "", s;


	cout << "\t\t Main Menu\n\n" << endl;
	while (c != "e")
	{
		if (!isValid(c))
		{
			cout << "Read Data from File\t\t\t<p>\n";
			cout << "Print in Order of Roll Number\t\t<1>\n";
			cout << "Print By GPA\t\t\t\t<2>\n";
			cout << "Store in File\t\t\t\t<3>\n";
			cout << "Add\t\t\t\t\t<4>\n";
			cout << "Remove\t\t\t\t\t<5>\n";
			cout << "Exit\t\t\t\t\t<e>\n";
			getline(cin, c);
		}
		if (c != "e" && isValid(c))
		{
			system("CLS");
			if (c == "p")
			{
				cout << "Enter file name: ";
				getline(cin, s);
				readFromFile(t2, s);
			}
			else if (c == "1")
			{
				printInOrder(t2);
			}
			else if (c == "2")
			{
				
			}
			else if (c == "3")
			{
				cout << "Enter file name: ";
				getline(cin, s);
				t2.writeInFile(s);
			}
			else if (c == "4")
			{
				Student S;
				S.getData();
				t2.insert(S);
			}
			else if (c == "5")
			{
				cout << "Enter roll number: ";
				getline(cin, s);
				Student S(s);
				t2.Delete(S);
			}
			

			cout << "Press b to go Back or e to Exit\n"; getline(cin, c);
			while (c != "b" && c != "e")
			{
				cout << "Invalid Command!" << endl;
				getline(cin, c);
			}
			if (c == "b")
				system("CLS");
		}
		else
		{
			while (c != "e" && !isValid(c))
			{
				cout << "Invalid Command." << endl;
				getline(cin, c);
			}
		}

	}//end of while
	
	
	return 0;
}
template <class T>
void readFromFile(tree23<T> &t, const string& filename)
{
	ifstream inputFile(filename);
	if (inputFile.is_open())
	{
		while (!inputFile.eof())
		{
			Student s;
			s.readFromFile(inputFile);
			t.insert(s);
		}
	}
}

template <class T>
void printInOrder(tree23<T>& t)
{
	for (tree23<T>::iterator<T> i = t.begin(); i != t.end(); i++)
	{
		cout << *i << endl;
	}
	cout << endl;
}

bool isValid(string& ch) //checks if command is valid or not
{
	if (ch == "p")
		return true;
	if (ch == "1")
		return true;
	if (ch == "2")
		return true;
	if (ch == "3")
		return true;
	if (ch == "4")
		return true;
	if (ch == "5")
		return true;
	if (ch == "6")
		return true;
	if (ch == "7")
		return true;
	if (ch == "8")
		return true;
	if (ch == "9")
		return true;
	return false;
}