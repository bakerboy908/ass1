#ifndef MY_FORWARD_LIST_HPP
#define MY_FORWARD_LIST_HPP

#include <algorithm>

template <typename T>
class Forward_list
{
public:
    class Node
    {
    public:
        // A node will hold data of type T
        T data{};
        // next will point to the next node in the list
        // we initialise next to nullptr
        Node *next = nullptr;

        // Because we have already intialised the variables
        // the default constructor doesn't need to do anything
        Node() {}

        // To make life easier we also provide a constructor
        // that takes the T data to be copied into the data member variable
        // There is an optional second argument which is
        // used to update the next pointer.  This defaults to nullptr
        // if the constructor is called with just one argument.
        Node(T input_data, Node *next_node = nullptr)
        {
            data = input_data;
            next = next_node;
        }

        // Destructor
        ~Node() {}
    };

private:
    // private member variables for Forward_list
    // the trailing underscore is a stylistic choice to
    // distinguish these as private member variables
    unsigned size_ = 0;
    Node *head_ = nullptr;
    void insert(int pos, const Node *nodeToInsert); // insert a value in to the list at this location

public:
    // public member functions of the Forward_list class
    // We have generally used the same names as for the
    // corresponding functions of std::forward_list

    // Default constructor does not need to do anything
    // and is provided for you.
    Forward_list();

    // The destructor is implemented for you
    ~Forward_list();

    // Copy constructor
    //*** For you to implement
    Forward_list(const Forward_list<T> &other);

    // Constructor from initializer list
    //*** For you to implement
    Forward_list(std::initializer_list<T> input);

    // Add an element to the front of the list
    //*** For you to implement
    void push_front(const T &data);

    // Remove the first element of the list
    //*** For you to implement
    void pop_front();

    // Return the data held in the first item of the list
    // This function should not change the list, which is
    // why it is declared const
    //*** For you to implement
    T front() const;

    // Print out all the data in the list in sequence
    //*** For you to implement
    void display() const;

    // Outputs if the list is empty or not
    // Implemented for you
    bool empty() const;

    // outputs the size of the list
    // Implemented for you, but your code should properly
    // update the size_ member variable as needed
    unsigned size() const;

    // methods related to sorting

    // merge two sorted lists, *this and other
    //*** For you to implement
    void merge(Forward_list &other);

    // split *this into its first half, which becomes the new *this,
    // and its second half which is returned
    //*** For you to implement
    Forward_list split();

    // The sort function uses the helper functions
    // merge and split that you write
    // You do not need to modify sort itself
    void sort();

private:
    // sort is implemented via a recursive merge sort
    // You do not need to modify this function
    void merge_sort(Forward_list &);
};

// Default Constructor
// You do not need to change this
template <typename T>
Forward_list<T>::Forward_list()
{
}

// Destructor
// The destructor is implemented for you
template <typename T>
Forward_list<T>::~Forward_list()
{
    while (head_ != nullptr)
    {
        Node *tmp = head_;
        head_ = head_->next;
        delete tmp;
        --size_;
    }
}

// Copy constructor
// ***For you to implement

// The copy constructor takes as argument a const reference to a
// another Forward_list "other"
// The const means that the function should not modify other
// The function should make a "deep copy" of the other list,
// that is create a new node for every node in other and copy
// the data of other into these new nodes.
template <typename T>
Forward_list<T>::Forward_list(const Forward_list &other)
{
    Node *tempNode = other.head_; // Setup a pointer to allow as to traverse the other list
    Node *newNode = new Node;     // setup a new node to be added to our list

    this->head_ = newNode;      // point the currently empty forward list to the first node
    while (tempNode != nullptr) // traverse the other list until it is depleated
    {
        newNode->data = tempNode->data; // copy data to current node
        this->size_++;                  // increase out list size
        if (tempNode->next != nullptr)  // if the other list contiues make a new node and advance our list
        {
            newNode->next = new Node;
            newNode = newNode->next;
        }
        tempNode = tempNode->next; // advance the other list to either add the next data point or break the while loop.
    }
}

// Constructor from initializer list
// ***For you to implement

// This implements the functionality you see with, for example,
// std::forward_list<int> my_list = {1,2,3}
// which creates a new linked list where the first node holds 1, second 2, and
// third 3.
// The {1,2,3} here is of type std::initializer_list<int> and you
// see this is the argument to this constructor (with data of type T
// rather than just int).

// You can access the elements of a std::initializer_list via an iterator
// for example you can cycle through all the elements with
// for(auto it = input.begin(); it!= input.end(); ++it){Do something with *it}
template <typename T>
Forward_list<T>::Forward_list(std::initializer_list<T> input)
{
    // Create a new node and point the head of the forwardlist at it
    // Node *newNode = new Node;
    // this->head_ = newNode;

    // iterator to move backwards through the inituliser list, creating a new node for each data point
    auto it = input.end() - 1;
    while (it >= input.begin()) // loop until we reach the front
    {
        this->push_front(*it); // add the data to out list.

        std::advance(it, -1); // move the iterator one location to the front
    }
}

// Add element to front of list
// ***For you to implement
template <typename T>
void Forward_list<T>::push_front(const T &data)
{
    Node *newNode = new Node; // create a new node
    newNode->data = data;     // copy the new data in
    newNode->next = head_;    // data gets added to the front, so point this nodes next location to the current front of the list
    this->head_ = newNode;    // set the new front of the list to this node
    this->size_++;            // increase the list size by 1
}

// Remove the front element of the list
// If the list is empty don't do anything
// ***For you to implement
template <typename T>
void Forward_list<T>::pop_front()
{
    if (!this->empty()) // make sure the list contains nodes
    {
        Node *tempNode = this->head_; // get a pointer to the first node
        this->head_ = tempNode->next; // advance the front of the list to the next node
        this->size_--;                // decrease the list size
        delete tempNode;              // delete the old first node
    }
}

// Return the data in the front element of the list
// If the list is empty the behaviour is undefined:
// you can return an arbitrary value, but don't segfault
// ***For you to implement
template <typename T>
T Forward_list<T>::front() const
{
    if (head_ != nullptr) // if the list points to data 
    {
        return head_->data; // return the data
    }
    T result;
    return result;               // if no data return a blank data structure.
}

// Print out the list
// ***For you to implement
template <typename T>
void Forward_list<T>::display() const
{
    Node *tempNode = this->head_; // pointer to start of list
    while (tempNode != nullptr)   // loop until pointer points at nothing
    {
        std::cout << tempNode->data << std::endl;   // print out the data line by line
        tempNode = tempNode->next;                  // advance the point to next item
    }
}

// Outputs if the list is empty or not
// Implemented for you
template <typename T>
bool Forward_list<T>::empty() const
{
    return (head_ == nullptr);
}

// Returns the size of the list
// It is implemented for you but you need to correctly
// update the size_ variable in your code as needed

// Note that std::forward_list actually does not have a size function
template <typename T>
unsigned Forward_list<T>::size() const
{
    return size_;
}

// the split function splits *this into its first half, which becomes
// the new *this, and its second half which is returned
// if the the size of *this is n, then after split the size of *this
// should be ceiling(n/2), and the size of the returned list should be
// floor(n/2)

// As an example, if *this is of the form
// head_ -> a -> b -> c -> d -> nullptr
// then after split *this should be
// head_ -> a -> b -> nullptr
// and you should a return a Forward_list other where
// other.head_ = c -> d -> nullptr

// Don't forget to update the size_ variable of this and other
// You do not need to create any new nodes for this function,
// just change pointers.
// ***For you to implement
template <typename T>
Forward_list<T> Forward_list<T>::split()
{
    Forward_list secondList;
    int midPoint = (this->size_ + 1) / 2; // find the distance to the mid node in this list
    Node *midnode = this->head_; // setup point to be able to traverse to the middle

    // traverse the list until the mid point is reached.
    for (auto i = 1; i < midPoint; i++)
    {
        midnode = midnode->next;
    }

    secondList.size_ = this->size_ - midPoint; // set the size of the new list
    this->size_ = midPoint;                     // set the new size of this list

    
    secondList.head_ = midnode->next;           // set the start of the second list the the midpoint +1
  
    midnode->next = nullptr;                      // set the node.next of the orginal list at the mid point to nullptr, so it no longer continues
   
    return secondList;                           // return the new list
}

// Merging two sorted lists
// For this function it is assumed that both *this and the
// input Forward_list other are already sorted
// The function merges the two lists into sorted order, and the merger becomes
// the new *this

// You do not need to create any new nodes in this function,
// just update pointers.
// Set other to be an empty list at the end of the function
//***For you to implement
template <typename T>
void Forward_list<T>::merge(Forward_list &other)
{
    Node *thisNode = this->head_;
    Node *otherNode = other.head_;
    Node *mergedNode = nullptr;



    if (otherNode == nullptr)                       // check the other list contains data, return if it doesnt
    {
        return;
    }

    if (thisNode == nullptr)                        // check this list has data, if it doesnt point this list at the other list and return
    {
        this->size_ = other.size_;
        this->head_ = other.head_;
        other.size_ = 0;
        other.head_ = nullptr;
        return;
    }
    this->head_ = nullptr;                          // set the head to nullptr so it can be set correctly later   
    if (thisNode->data <= otherNode->data)          // decide which list has the smaller value and set the merged node to this value or the other value
    {
        mergedNode = thisNode;
        thisNode = thisNode->next;
    }
    else
    {
        mergedNode = otherNode;
        otherNode = otherNode->next;
        this->size_++;                              // if the value came from the other list we need to increase the size of this list
    }
    if (this->head_ == nullptr)                     // if we this node is the first one to be merged set the head to the merged node
    {
        this->head_ = mergedNode;
    }

    while (thisNode != nullptr && otherNode != nullptr)  // whilst both of the lists contains data loop though and decide which node should be the next node in the list.
    {
        if (thisNode->data <= otherNode->data)
        {
            mergedNode->next = thisNode;
            thisNode = thisNode->next;
        }
        else
        {
            mergedNode->next = otherNode;
            otherNode = otherNode->next;
            this->size_++;                                  // if taking data from the other list we need to increase the size of this list
        }
        mergedNode = mergedNode->next;                      // advance the merged pointer
    }

    if (thisNode != nullptr)                                // depending on which list depletes first the list might have a null pointer at the next node, these statments catch both cases
    {
        mergedNode->next = thisNode;
        mergedNode = mergedNode->next;
        thisNode = thisNode->next;
    }

    if (otherNode != nullptr)
    {
        mergedNode->next = otherNode;
        mergedNode = mergedNode->next;
        otherNode = otherNode->next;
        this->size_++;
    }

    
    other.head_ = nullptr;                              // set the other list to be empty as all the nodes should now be in this list.
    other.size_ = 0;

}

// recursive implementation of merge_sort
// you do not need to change this function
template <typename T>
void Forward_list<T>::merge_sort(Forward_list &my_list)
{
    if (my_list.size() == 0 || my_list.size() == 1)
    {
        return;
    }
    Forward_list<T> second = my_list.split();
    merge_sort(my_list);
    merge_sort(second);
    my_list.merge(second);
}

// sorts the list by calling merge_sort
// once your merge and split functions are working
// sort should automatically work
// you do not need to change this function
template <typename T>
void Forward_list<T>::sort()
{
    merge_sort(*this);
}

#endif