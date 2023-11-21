#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

class EventLocation {
    int maxSeats;
    int numRows;
    int* seatsPerRow;

      friend ostream& operator<<(ostream& g,  EventLocation loc);
      friend istream& operator >>(istream& f, EventLocation& loc);

public:
    EventLocation() {
       this->maxSeats = 0;
       this->numRows = 0;
       this->seatsPerRow = 0;
    }
    EventLocation(int maxSeats, int numRows, const int* seatsPerRow)
    {
        try {
        this->maxSeats = maxSeats;
        this->numRows = numRows;
        this->seatsPerRow = new int[this->numRows];
        for (int i = 0; i < this->numRows; ++i) {
            this->seatsPerRow[i] = seatsPerRow[i];
        }

        validateSeats();
         }
         catch (const std::exception& e) {
           cout << "Error in Event Location constructor: " << e.what() << endl;
       }

    }
    EventLocation(const EventLocation& c)
    {
        this->maxSeats = c.maxSeats;
        this->numRows = c.numRows;
        this->seatsPerRow = new int[c.numRows];
        for (int i = 0; i < c.numRows; ++i) {
            this->seatsPerRow[i] = c.seatsPerRow[i];


        }

    }
    EventLocation(const int* seatsPerRow)
    {
        this->maxSeats = maxSeats;
        this->seatsPerRow = new int[numRows];
        for (int i = 0; i < numRows; ++i) {
            this->seatsPerRow[i] = seatsPerRow[i];


        }

    }
    ~EventLocation() {
        delete[] seatsPerRow;
    }

    int getMaxSeats() const {
        return maxSeats;
    }

    void setMaxSeats(int maxSeats) {
        if (maxSeats < 0) {
            throw invalid_argument("Max seats must be positive.");
        }
        this->maxSeats = maxSeats;
    }

    int getNumRows() const {
        return numRows;
    }

    void setNumRows(int numRows) {
        if (numRows < 0) {
            throw invalid_argument("Number of rows must be positive.");
        }
        this->numRows = numRows;
    }

    const int* getSeatsPerRow() const {
        int* seatsCopy = new int[numRows];
        for (int i = 0; i < numRows; ++i) {
            seatsCopy[i] = seatsPerRow[i];
        }
        return seatsCopy;
    }

    void setSeatsPerRow(const int* newSeatsPerRow) {
        delete[] seatsPerRow;
        seatsPerRow = new int[numRows];
        for (int i = 0; i < numRows; ++i) {
            this->seatsPerRow[i] = newSeatsPerRow[i];
        }
    }
    void validateSeats() const {
       
            int totalSeats = 0;
            for (int i = 0; i < numRows; ++i) {
                totalSeats += seatsPerRow[i];
            }

            if (totalSeats > maxSeats) {
                throw std::exception("The product of seats per row and number of rows exceeds maxSeats.");
            }
        
       
    }
    //operators
    EventLocation& operator=(const EventLocation& source) {
        if (this != &source) {
        this->maxSeats = source.maxSeats;
        this->numRows = source.numRows;
        if (this->seatsPerRow != NULL) {
            delete[]this->seatsPerRow;
            this->seatsPerRow = new int[this->numRows];
            for (int i = 0; i < this->numRows; i++)
                this->seatsPerRow[i] = source.seatsPerRow[i];
        }
    }
        return *this;
    }
    bool operator!()
    {
        int sum = 0;
        
        for (int i = 0; i < numRows; i++)
            sum += seatsPerRow[i];
          if(maxSeats>=sum)
            return true;
        
        return false;
    }
    friend bool operator<(int o, const EventLocation& loc)
    {
        return o < loc.maxSeats;
    }
    int operator [](int i)
    {
        if (i<0 || i>this->numRows)
            throw exception("Out of range");
        else
            return this->seatsPerRow[i];
    }

    
    EventLocation operator++()
    {
        this->numRows++;
        return *this;
    }

   EventLocation operator++(int i)
    {
        EventLocation copie = *this;
        this->numRows += i;
        return copie;
    }

  
    EventLocation operator+(int valoare)
    {
        EventLocation copie = *this;
        copie.numRows += valoare;
        return copie;
    }



    bool operator ==(const EventLocation& loc)
    {
        EventLocation sem(*this);
        if (sem.maxSeats== loc.maxSeats &&
            sem.numRows == loc.numRows)
        {
            for (int i = 0; i < sem.numRows; i++)
                if (sem.seatsPerRow[i] != loc.seatsPerRow[i])
                    return false;
            return true;
        }
        return false;
    }

    void printInfo() const {
        cout << "Event Location Information:" << endl;
        cout << "Max Seats: " << maxSeats << endl;
        cout << "Num Rows: " << numRows << endl;
        cout << "Seats Per Row: ";
        for (int i = 0; i < numRows; ++i) {
            cout << seatsPerRow[i] << " ";
        }
        cout << endl;
        cout << "-----------------------------" << endl;
    }

};

ostream& operator<<(ostream& g,  EventLocation loc) {
    g << "Event Location Information:" << endl;
    g << "Max Seats: " << loc.maxSeats << endl;
    g << "Num Rows: " << loc.numRows << endl;
    g << "Seats Per Row: ";
    for (int i = 0; i < loc.numRows; ++i) {
        g << loc.seatsPerRow[i] << " ";
    }
    g << endl;
    g << "-----------------------------" << endl;
    return g;
}
istream& operator >>(istream& f, EventLocation& loc)
{
    cout << "The number maxim of seats at the event is ";
    f >> loc.maxSeats;
    cout << endl;
    cout << "The number of rows is: ";
    f >> loc.numRows;
    cout << endl;
   
    cout << "The number of seats per row are: ";
    for (int i = 0; i < loc.numRows; i++)
    {
        f >> loc.seatsPerRow[i];
        cout << endl;
    }
    return f;
}

    class Event {
        char* name;
        string date;
        string time;

        friend ostream& operator<<(ostream& g, Event eve);
        friend istream& operator >>(istream& f, Event& eve);



    public:
        Event() {
            this->name = new char[2];
            strcpy(this->name, " ");
            this->date = "--------";
            this->time = "-----";
        }
        Event(const char* name, const string& date, const string& time) {
            this->name = new char[strlen(name) + 1];
            strcpy_s(this->name, strlen(name) + 1, name);
            this->date = date;
            this->time = time;
        }
        Event(const Event& c) {
            this->name = new char[strlen(c.name) + 1];
            strcpy_s(this->name, strlen(c.name) + 1, c.name);
            this->date = c.date;
            this->time = c.time;
        }
        Event(const char* name) {
            this->name = new char[strlen(name) + 1];
            strcpy_s(this->name, strlen(name) + 1, name);
            this->date = date;
            this->time = time;
        }

        ~Event() {
            delete[] name;
        }

        const char* getName() const {
            return name;
        }

        void setName(const char* name) {


            if (name == nullptr)
                throw exception("Name cannot be empty");

            delete[] this->name;
            this->name = new char[strlen(name) + 1];
            strcpy_s(this->name, strlen(name) + 1, name);
        }

        const string& getDate() const {
            return date;
        }

        void setDate(const string& date) {
            this->date = date;
        }

        const string& getTime() const {
            return time;
        }

        void setTime(const string& time) {
            this->time = time;
        }
        //operators
        Event& operator=(const Event& source) {
            if (this != &source) {
                if (this->name != NULL) {
                    delete[] this->name;
                    this->name = NULL;
                }
            this->name = new char[strlen(source.name) + 1];
            strcpy_s(this->name, strlen(source.name) + 1, source.name);
            this->date = source.date;
            this->time = source.time;
        }
            return*this;
        }
        void printInfo() const {
            cout << "Event Information:" << endl;
            cout << "Name: " << name << endl;
            cout << "Date: " << date << endl;
            cout << "Time: " << time << endl;
            cout << "-----------------------------" << endl;

            
        }
    };
    ostream& operator<<(ostream& g, Event eve) {
        g << "Event Information:" << endl;
        g << "Name: " << eve.name << endl;
        g << "Date: " << eve.date << endl;
        g << "Time: " << eve.time << endl;
        g << "-----------------------------" << endl;
        return g;
    }
   istream& operator >>(istream& f, Event& eve)
    {
        cout << "The name of the event is: ";
        f >> eve.name;
        cout << endl;
        cout << "The date: ";
        f >> eve.date;
        cout << endl;
        cout << "The time: ";
        f >> eve.time;
        cout << endl;
   
        
        return f;
    }

    class Ticket {
        string type;
        int* ticketId;
        static int nextId;

        friend ostream& operator<<(ostream& g, Ticket eve);
        friend istream& operator >>(istream& f, Ticket& tic);


    public:
        Ticket() {
            this->type = "unknown";
            this->ticketId = nullptr;
            this->nextId = 0;
        }
            
        
        Ticket(const string& type, int* ticketId, static int nextId) {
            this->type = type;
            this->ticketId = ticketId;
            this->nextId = nextId;
            generateTicketId();

        }
        Ticket(const Ticket& c) {
            this->type = c.type;
            this->ticketId = c.ticketId;
            this->nextId = c.nextId;
        }
        Ticket(const string& type) {
            this->type = type;
            this->ticketId = ticketId;
            //this->nextId = nextId;
            generateTicketId();

        }

        ~Ticket() {
            delete[] this->ticketId;
        }

        const string& getType() const {
            return this->type;
        }

        void setType(const string& type) {
            if (type.empty()) {
                throw exception("Ticket type cannot be empty.");
            }
            else

                this->type = type;


        }

        int* getTicketId() const {
            return this->ticketId;
        }
        void setTicketId(int* ticketId) {

            if (*ticketId < 0) {
                throw exception("Ticket ID must be a positive integer.");
            }

            this->ticketId = new int [*ticketId];

        }

        static int getNextId() {
            return nextId;
        }
        friend void setNextId(int NextId);
        //operators
        Ticket& operator=(const Ticket& source) {
            if (this != &source){
                this->type = source.type;
            if (this->ticketId != NULL) {
                delete[] this->ticketId;
                }
                this->ticketId = source.ticketId;
              
                this->nextId = source.nextId;
            }
            return *this;
        }

        int* generateTicketId() {
            delete[] this->ticketId;
                ticketId = new int(nextId++);
                return ticketId;
         }
        
       void printInfo() const {
            cout << "Ticket Information:" << endl;
            cout << "Type: " << type << endl;
            cout << "Ticket ID: " << ticketId << endl;
            cout << "Next ID: " << nextId << endl;
            cout << "-----------------------------" << endl;

        }
    };
    /*istream& operator >>(istream& f, Ticket& tic)
    {
        cout << "The type of the seat: ";
        f >> tic.type;
        cout << endl;
       
       tic.generateTicketId();
        return f;
    }
    ostream& operator<<(ostream& g, Ticket tic) {
        g << "Ticket Information:" << endl;
        g << "Type: " << tic.type << endl;
       //g << "Next ID: " << Ticket::nextId << endl;
        g << "Id:" << tic.ticketId;
        g << "-----------------------------" << endl;
        return g;
    }*/

   int Ticket::nextId = 1; 

    int main() {
       
        //const int seatsPerRow[] = { 10, 12, 10 };
        //EventLocation location(100, 3, seatsPerRow);

        Event event("Concert", "19-11-2023", "19:30");
        //cin >> event;
        //cout << event;
        Ticket bilet;
       // cin >> bilet;
       // cout << bilet;
        
        Ticket bilet1("Regular");
        //location.printInfo();
        //event.printInfo();
       bilet.printInfo();
      //  bilet1.printInfo();

        return 0;
    }

