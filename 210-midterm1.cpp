// Brandon Julao
// COMSC-210-5481
// 10-17-2024
// Midterm #1

//Directives, and Namespace.
#include <iostream>
using namespace std;

//Declarations
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

//Implementing DoublyLinkList data structure.
class DoublyLinkedList {

//Private node structure, initialize, point to, and holds value of the node.
private:
	struct Node {
		int data;
		Node* prev;
		Node* next;
		Node(int val, Node* p = nullptr, Node* n = nullptr) {
			data = val;
			prev = p;
			next = n;
		}
	};

	//Pointing to the top and bottom of a node in a list.
	Node* head;
	Node* tail;

	//Sets an empty DoublyLinkedList to head and tail node.
public:
	DoublyLinkedList() { head = nullptr; tail = nullptr; }

	//Inserts a new node after a position in the list.
	//Verify position, create node, find correct position in list, adjust pointers for new node.
	void insert_after(int value, int position) {
		if (position < 0) {
			cout << "Position must be >= 0." << endl;
			return;
		}

		Node* newNode = new Node(value);
		if (!head) {
			head = tail = newNode;
			return;
		}

		Node* temp = head;
		for (int i = 0; i < position && temp; ++i)
			temp = temp->next;

		if (!temp) {
			cout << "Position exceeds list size. Node not inserted.\n";
			delete newNode;
			return;
		}

		newNode->next = temp->next;
		newNode->prev = temp;
		if (temp->next)
			temp->next->prev = newNode;
		else
			tail = newNode;
		temp->next = newNode;
	}

	//Deletes first node that contains a specified value.
	//Verify the list to find node
	//Adjust pointers of nodes to find the node to be removed.
	void delete_val(int value) {
		if (!head) return;
		Node* temp = head;
		while (temp && temp->data != value)
			temp = temp->next;
		if (!temp) return;
		if (temp->prev)
			temp->prev->next = temp->next;
		else
			head = temp->next;
		if (temp->next)
			temp->next->prev = temp->prev;
		else
			tail = temp->prev;
		delete temp;
	}
	//Deletes the node at a specific position
	//Handles edge cases for an empty list or invalid position.
	//Pointers adjust to remove node.
	void delete_pos(int pos) {
		if (!head) {
			cout << "List is empty." << endl;
			return;
		}
		if (pos == 1) {
			pop_front();
			return;
		}
		Node* temp = head;
		for (int i = 1; i < pos; i++) {
			if (!temp) {
				cout << "Position doesn't exist." << endl;
				return;
			}
			else
				temp = temp->next;
		}
		if (!temp) {
			cout << "Position doesn't exist." << endl;
			return;
		}
		if (!temp->next) {
			pop_back();
			return;
		}
		Node* tempPrev = temp->prev;
		tempPrev->next = temp->next;
		temp->next->prev = tempPrev;
		delete temp;
	}

	//Adds a new node with the value "v" at the end of the list.
	//Handles case of empty list.
	//Adjust pointers for new node.
	void push_back(int v) {
		Node* newNode = new Node(v);
		if (!tail)
			head = tail = newNode;
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}
	//Adds a new node with the value of "V" at the beginning of the list.
	//Handles case of empty list.
	//Adjust pointers for new node.
	void push_front(int v) {
		Node* newNode = new Node(v);
		if (!head)
			head = tail = newNode;
		else {
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
	}
	//Removes first node in the list.
	//Empty List.
	//Adjust Pointers.
	//Print to user that the list is empty.
	void pop_front() {
		if (!head) {
			cout << "List is empty." << endl;
			return;
		}
		Node* temp = head;
		if (head->next) {
			head = head->next;
			head->prev = nullptr;
		}
		else
			head = tail = nullptr;
		delete temp;
	}
	//Removes the last node in a list.
	//Empty List.
	//Adjust pointers.
	//Print to the user that the list is empty.
	void pop_back() {
		if (!tail) {
			cout << "List is empty." << endl;
			return;
		}
		Node* temp = tail;
		if (tail->prev) {
			tail = tail->prev;
			tail->next = nullptr;
		}
		else
			head = tail = nullptr;
		delete temp;
	}

	//Destructor cleans up all nodes in the list. 
	//Prevention of Memory links when DoublyLinkedList is destroyed.
	~DoublyLinkedList() {
		while (head) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}

	// Print output!

	void print() {
		Node* current = head;
		if (!current) {
			cout << "List is empty." << endl;
			return;
		}
		while (current) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
	void print_reverse() {
		Node* current = tail;
		if (!current) {
			cout << "List is empty." << endl;
			return;
		}
		while (current) {
			cout << current->data << " ";
			current = current->prev;
		}
		cout << endl;
	}


	//New Method
	//Verify linked list and print every other element starting from the first.
	//Initializes pointer to the top of the list.
	//Initialize count and set to 0.
	//If count equals 0, prints to the user that the list is empty.
	//Advances the current pointer to the next node.
	void every_other_element() {
		Node* current = head;
		int count = 0;
		if (!current) {
			cout << "List is empty." << endl;
			return;
		}
		while(current) {
			if (count % 2 == 0)
				cout << current->data << " ";
			current = current->next;
			count++;
				
		}
		//End Loop, and prints new line.
		cout << endl;
	}
};


int main() {

	//Demonstrating Link Functionality
	//Setup list for showing user from 1-6
	DoublyLinkedList dll;
	dll.push_back(1);
	dll.push_back(2);
	dll.push_back(3);
	dll.push_back(4);
	dll.push_back(5);
	dll.push_back(6);

	//Print to user original list.
	cout << "Original List: ";
	dll.print();

	//Print to user every other list.
	cout << "Every Other Element ";
	dll.every_other_element();

		return 0;
}

