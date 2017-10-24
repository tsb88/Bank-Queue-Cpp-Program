// System test to test entire solution using a set of parameters for a scenario for which the result
// is already known and can be compared to using the solution's results.
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
    
    cout << endl;
    p = front;                  // p is once again equal to the front node
    
    // set up the column titles for the list
    cout << "This is the remaining queue: " << endl;
    cout << endl;
    cout << "Cust. #" << setw(10) << "Arrival" << setw(12) << "Departure" << setw(21)<< "Waited (minutes)" << endl;
    cout << "--------------------------------------------------" << endl;
    
    while (p != NULL)           // while the list isnt at the end,
    {
        // output each customers' information from the queue
        cout << setw(4) << p->customerNum << setw(10) << p->arrivalTime << setw(11) << p->departureTime << setw(16) << p->waitTime << endl;
        
        p = p->next;            // p is equal to the next node
    }
    
    double avgWaitTime = totalWaitTime/MaxPpl; // calculate average wait time
    cout << endl;
    cout << "The average wait time using " << MaxPpl << " customers was: " << avgWaitTime << " minutes" << endl;        // output average wait time
}


int main()
{
    Queue queue;                // Queue class
    int timeCount = 0;          // overall time as well as arrival time
    int customerNumber = 1;     // customer number initialized
    int serviceTime;            // amount of time a teller takes to assist a customer
    int tellerNum;              // the number of tellers there are
    int maxPpl;                 // maximum number of people to run the simulation for
    int rateTime;               // Y, where Y is: customers come in every Y minutes
    int ratePeople;             // X, where X is: X customers come in every Y minutes
    int departure;              // time at which customer finished at teller and exited bank
    int waitingTime = 0;        // wait time variable initialized
    
    // For the test, we will use the scenario that there is 1 teller, the teller takes 1 minute to
    // help a customer, the simulation runs for 100 customers, and that 10 customers come into the
    // queue every 1 minute.
    // It is known that since 10 customers come in every 1 minute and the simulation runs for 100 customers, the amount of minutes that will pass in the simulation will be 10. We also know that given the scenario, each customer will leave 1 minute afer the previous customer so it is very easy to see which customers will leave within the duration of the simulation (time wise). The function should display that customers 1 through 9 should have left the queue by the time the simulation ends. In addition, because we know which customers should leave the queue, we know what the remaining queue will look like after those customers have left. Lastly, because of the easy departure times, it is very easy to add the wait times of each customer into excel and calculate the average wait time manually to test against the solution. We know that the average wait time should be 45 minutes.
    tellerNum  = 1;
    serviceTime = 1;
    maxPpl = 100;
    ratePeople = 10;
    rateTime = 1;
    
    departure = timeCount + serviceTime;   // initial departure value
    
    for (int i = 0; i < maxPpl; i++)     // loop to run for maximum number of customers in simulation
    {
        queue.enqueue(timeCount, departure, customerNumber, waitingTime); // add customer to queue
        customerNumber++;                   // increment customer number (next customer)
        
        if (customerNumber <= tellerNum)  // if the customer number is less than the number of tellers,
        {
            departure = timeCount + serviceTime;    // departure time equation does not change
        }
        
        if (customerNumber > tellerNum)             // if the customer number is greater
            // than the number of tellers,
        {
            if ((customerNumber-1) % tellerNum == 0) // if the previous customer number is divisible
            {                                        // by the number of tellers,
                departure = departure + serviceTime; // new departure time
            }
            else                                     // otherwise,
            {
                departure = departure;               // departure remains the same
            }
        }
        
        waitingTime = (departure - serviceTime) - timeCount; // waiting time equation
        
        if ((customerNumber-1) % ratePeople == 0)  // if the previous customer is divisible by
            // the amount of people that come in every Y minutes
        {
            timeCount = timeCount + rateTime;      // time count incremented
            waitingTime = (departure - serviceTime) - timeCount;
        }
    }
    
    queue.display(maxPpl, timeCount);           // display list
    
    return 0;
    
}

// After running the solution with the pre-determined scenario, we see that the solution matches all of
// our predictions accurately so we can confirm that it works //

// The acceptance test is identical to the system test so it will be included here as well:
/*As discussed in the summary of the problem at hand and what a solution should look like, we know that the things required of the solution are being able to account for any number of tellers, any amount of service time for the tellers, any number of maximum customers for the simulation, and any rate at which customers arrive. After running through the simulation for the given scenario of setting all parameters equal at 1 minute for service time, 100 maximum customers, and 10 customers arriving every 1 minute while changing the number of tellers going from 1 through 10, we can see that the average wait time is affected in a way similar to a decreasing exponential relation. The solution correctly provides the original queue for the whole simulation, each customer in the queue has their information (such as time of arrival, time of departure, and time waited in queue) displayed next to them, it displays which customers have left the queue and deletes them after displaying this information, and lastly displays the remaining queue and the average wait time. The solution does everything required of it from the analyzing portion of solving this problem and thinking of ways to implement a solution. So for acceptance testing, the solution passes as it meets all of the desired needs.*/





