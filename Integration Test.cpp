// Because this specific solution involves using only 1 Queue class and then 1 struct for the nodes,
// my two modules of this solution are that class and struct (as the class relies on the struct to
// build the linked list and modify it). To show the use of the struct within the 3 class functions,
// the testing will look almost identical to the unit testing for display (because display does many
// of the functions). This test will show the add node function using the struct to create a linked
// list and add to it, the delete node function using the struct to delete a node, and the display
// function to show the list. Each function is connected to the class fucntions through creating a new
// temporary node which a pointer points to and thats thats used to traverse the list to print,
// traverse the list to get to the end to add a node, or assign the front node to that pointer, then
// delete that front node and make the next node the new front. All of this can be seen simply by the
// solution running.

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
    
    void display(int MaxPpl, int maxTime);                      // function to display the list
    
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

void Queue::display(int MaxPpl, int maxTime)
{
    // set up table columns
    cout << "Cust. #" << setw(10) << "Arrival" << setw(12) << "Departure" << setw(21)<< "Waited (minutes)" << endl;
    cout << "--------------------------------------------------" << endl;
    
    double totalWaitTime = 0;      // initialize total wait time variable
    
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
            
            totalWaitTime = totalWaitTime + p->waitTime;  // add the wait times of each nodes
            
            p = p->next;        // p is equal to the next node
        }
    }
    
    cout << endl;
    
    p = front;                  // once again, p is equal to the front node
    if (front == NULL)
    {
        cout << "No customers have left because list is empty" << endl;
    }
    else
    {
        while (p != NULL)           // while the front node isnt NULL (list isn't at the end),
        {
            // if a customers departure time was less than the max time from the simulation,
            if (p->departureTime < maxTime)
            {
                // output the customer number and that they have left the queue
                cout << "Customer " << p->customerNum << " has departed at minute " << p->departureTime << " and has been removed from the queue." << endl;
                cout << endl;
                dequeue();          // delete that customer from the queue
            }
            
            p = p->next;            // p is equal to the next node
        }
    }
    
    cout << endl;
    p = front;                  // p is once again equal to the front node
    
    // set up the column titles for the list
    cout << "This is the remaining queue: " << endl;
    cout << endl;
    cout << "Cust. #" << setw(10) << "Arrival" << setw(12) << "Departure" << setw(21)<< "Waited (minutes)" << endl;
    cout << "--------------------------------------------------" << endl;
    
    if (front == NULL)
    {
        cout << "No remaining queue. Queue is empty" << endl;
    }
    else
    {
        while (p != NULL)           // while the list isnt at the end,
        {
            // output each customers' information from the queue
            cout << setw(4) << p->customerNum << setw(10) << p->arrivalTime << setw(11) << p->departureTime << setw(16) << p->waitTime << endl;
            
            p = p->next;            // p is equal to the next node
        }
    }
    
    double avgWaitTime = totalWaitTime/MaxPpl; // calculate average wait time
    cout << endl;
    cout << "The average wait time using " << MaxPpl << " customers was: " << avgWaitTime << " minutes" << endl;        // output average wait time
}

int main()
{
    Queue queue;
    
    // Test the display function by adding 11 nodes using the parameters 1 teller, 1 minute service
    // time, 11 customers, and 10 customers every 1 minute.
    queue.enqueue(0, 1, 1, 0);
    queue.enqueue(0, 2, 2, 1);
    queue.enqueue(0, 3, 3, 2);
    queue.enqueue(0, 4, 4, 3);
    queue.enqueue(0, 5, 5, 4);
    queue.enqueue(0, 6, 6, 5);
    queue.enqueue(0, 7, 7, 6);
    queue.enqueue(0, 8, 8, 7);
    queue.enqueue(0, 9, 9, 8);
    queue.enqueue(0, 10, 10, 9);
    queue.enqueue(1, 11, 11, 9);
    
    queue.display(11, 10);
}

// After running the simulation, we can clearly see that each time the add node function was called,
// the new nodes were added to the back of the list, as would happen with a queue and this was done
// by creating a new temporary node. The display function calls the delete node function, and the
// delete node function successfully deletes nodes from the front of the list only, and again, this is
// done using a new temporary node. Lastly, the display function also displays the list properly and
// it does so by creating a new temporary node that is poined to by a pointer and traversing the list. 
