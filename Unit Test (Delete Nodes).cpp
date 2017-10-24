// Unit test to test the delete node function //
// Testing occurs in main //

#include<iostream>
#include<list>
#include<string>
#include<cstdlib>
#include<math.h>
#include<iomanip>
using namespace std;

struct node{
    
    int arrivalTime;        // customer information to be stored in each node
    int departureTime;      // each node represents one customer
    int customerNum;
    int waitTime;
    
    struct node *next;
    
};

class Queue{
    
private:
    
    node *rear;            // the last node of the list
    
    node *front;           // the first node of the list
    
public:
    
    Queue();
    
    void enqueue(int aTime, int dTime, int custNum, int wTime); // function to add to the list
    
    void dequeue();                                             // function to delete from the list
    
    void display();                      // function to display the list
    
};
Queue::Queue()           // constructor
{
    rear = NULL;
    
    front = NULL;
}

void Queue::enqueue(int aTime, int dTime, int custNum, int wTime)
{
    node *temp = new node;              // create a new temporary node
    
    temp->arrivalTime = aTime;          // temporary node stores this information
    
    temp->departureTime = dTime;
    
    temp->customerNum = custNum;
    
    temp->waitTime = wTime;
    
    temp->next = NULL;                  // the next node pointed to by temp is NULL
    
    if(front == NULL)                   // if the front node is NULL, then the list is empty so
    {                                   // the data gets stored in the front node
        front = temp;
    }
    else                                // if the list in not empty, the next node that the rear
    {                                   // node points to gets the information
        rear->next = temp;
    }
    
    rear = temp;                        // this node that recieved the info becomes the new rear node
}

void Queue::dequeue()
{
    node *temp = new node;
    
    if(front == NULL)              // if the list is empty, display a message
    {
        cout << "Could not delete node. List is empty" << endl;
    }
    else                           // if the list isnt empty,
    {
        temp = front;              // the new temp pointer is equal to the front node
        
        front = front->next;       // the front node is equal to the next node
        
        delete temp;               // the front node is deleted and the next node becomes front
    }
}

void Queue::display()
{
    // set up table columns
    cout << "Cust. #" << setw(10) << "Arrival" << setw(12) << "Departure" << setw(21)<< "Waited (minutes)" << endl;
    cout << "--------------------------------------------------" << endl;
    
    node *p = new node;
    
    p = front;                  // p pointer is equal to the front node
    
    if(front == NULL)           // if the list is empty, display a message
    {
        cout << "Could not diplay list. List is empty" << endl;
    }
    else                        // otherwise,
    {
        while(p != NULL)        // while the front node is not NULL (haven't reached end of list)
        {
            // output the information stored in each node
            cout << setw(4) << p->customerNum << setw(10) << p->arrivalTime << setw(11) << p->departureTime << setw(16) << p->waitTime << endl;
            
            p = p->next;        // p is equal to the next node
        }
    }

}

int main()
{
    Queue queue;
    
    // Test initially by displaying empty list. Message should display of empty list.
    queue.display();
    
    // Test the delete node function by first adding 3 nodes, then displaying, and then deleting
    // the first node.
    
    queue.enqueue(0, 3, 1, 0);
    queue.enqueue(0, 6, 2, 3);
    queue.enqueue(0, 9, 3, 6);
    queue.display();
    
    // Now that the list is seen to be printed with 3 nodes, we test deleting the front node.
    queue.dequeue();
    queue.display();
    
    return 0;
    
}

// As we can see from the output, the delete node function is working as expected //

