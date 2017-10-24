// Unit Test to test the function to add new nodes to the list to the back //
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
    
    cout << endl;
    
}

int main()
{
    Queue queue;
    
    // Test function first with empty list. Should display message to inform of empty list.
    queue.display();
    
    // Test function by adding 3 nodes and then displaying the list and accompanying information.
    // 3 customers arrive at once, service time of 3 minutes. Each customer arrived at the same time.
    // The first customer does not wait. There is only one teller.
    queue.enqueue(0, 3, 1, 0);
    queue.enqueue(0, 6, 2, 3);
    queue.enqueue(0, 9, 3, 6);
    
    queue.display(); // display list to check adding node function.
    
    return 0;
}

// After viewing the output, the result is exactly as predicted so the functin does work properly //
