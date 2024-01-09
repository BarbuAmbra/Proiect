#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <string>
#include<fstream>
using namespace std;



class Abstract {
public:
    virtual void readFromFile(istream& file) = 0;

};


class EventLocation: public Abstract {
    int maxSeats;
    int numRows;
    int* seatsPerRow;



    friend ostream& operator<<(ostream& g, EventLocation loc);
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
        catch (const exception& e) {
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



    int* getSeatsPerRow() const {

        int* seatsCopy = new int[numRows];
        for (int i = 0; i < numRows; ++i) {
            seatsCopy[i] = seatsPerRow[i];
        }
        return seatsCopy;
    }



    void setSeatsPerRow(int* newSeatsPerRow, int newRows) {
        if (newSeatsPerRow != nullptr && newRows > 0) {
            delete[] this->seatsPerRow;
            this->numRows = newRows;
            this->seatsPerRow = new int[numRows];
            for (int i = 0; i < numRows; ++i) {
                this->seatsPerRow[i] = newSeatsPerRow[i];
            }
        }
        else {
            this->seatsPerRow = nullptr;
            this->numRows = 0;
        }
    }



    void validateSeats() const {

        int totalSeats = 0;
        for (int i = 0; i < numRows; ++i) {
            totalSeats += seatsPerRow[i];
        }

        if (totalSeats > maxSeats) {
            throw exception("The product of seats per row and number of rows exceeds maxSeats.");
        }


    }




    void readFromFile(istream& file) override {
        
        file >> maxSeats;
        file >> numRows;

        seatsPerRow = new int[numRows];
        for (int i = 0; i < numRows; ++i) {
            file >> seatsPerRow[i];
        }

        validateSeats();

    }


    friend ostream& operator<<(ostream& g, EventLocation loc);
    friend istream& operator >>(istream& f, EventLocation& loc);




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
        if (maxSeats >= sum)
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


    EventLocation operator--()
    {
        this->numRows--;
        return *this;
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
        if (sem.maxSeats == loc.maxSeats &&
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



ostream& operator<<(ostream& g, EventLocation loc) {
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
    loc.seatsPerRow = new int[loc.numRows];
    for (int i = 0; i < loc.numRows; i++)
    {
        f >> loc.seatsPerRow[i];
    }
    loc.validateSeats();
    return f;
}




class Event:public Abstract{

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
    void readFromFile(istream& file) override {
       
        char buffer[100];
        file.getline(buffer, sizeof(buffer));
        name = new char[strlen(buffer) + 1];
        strcpy(name, buffer);

        file >> date;
        file >> time;
    }
    friend ostream& operator<<(ostream& g, Event eve);
    friend istream& operator >>(istream& f, Event& eve);

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


    bool operator>(const Event& eve) const {
        return (strcmp(name, eve.name) > 0);
    }



    bool operator!() const {
        return time.empty();
    }


    Event operator+(const Event& eve) const {
        char* concatenatedName = new char[strlen(name) + strlen(eve.name) + 1];
        strcpy_s(concatenatedName, strlen(name) + 1, name);
        strcat_s(concatenatedName, strlen(name) + strlen(eve.name) + 1, eve.name);

        Event result(concatenatedName, date, time);
        delete[] concatenatedName;

        return result;
    }

    bool operator==(const Event& eve) const {
        return (strcmp(name, eve.name) == 0);
    }

    void printInfo() const {
        cout << "Event Information:" << endl;
        cout << "Name: " << name << endl;
        cout << "Date: " << date << endl;
        cout << "Time: " << time << endl;
        cout << "-----------------------------" << endl;


    }
 
};

/* Ticket searchTicketById(const string& fileName, int targetId) {
    ifstream inputFile(fileName, ios::binary);

    if (!inputFile.is_open()) {
        cerr << "Error opening " << fileName << " for reading" << endl;
        // Return an empty Ticket object or throw an exception as needed
        return Ticket();
    }

    Ticket foundTicket;

    while (inputFile >> foundTicket) {
        if (foundTicket.getTicketId() == targetId) {
            // Ticket with the target ID found
            cout << "Ticket found:" <<endl;
            cout << foundTicket;
            break;
        }
    }

    inputFile.close();

    // If the loop completes without finding the ticket, display a message
    if (foundTicket.getTicketId() != targetId) {
        cout << "Ticket with ID " << targetId << " not found." << endl;
    }

    return foundTicket;
}*/

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
    f.ignore();
    getline(f, eve.date);
    cout << endl;
    cout << "The time: ";
    f >> eve.time;
    cout << endl;


    return f;
}


class Ticket {
    string type;
    int* ticketId;
    double price;
    friend ostream& operator<<(ostream& g, Ticket eve);
    friend istream& operator >>(istream& f, Ticket& tic);


public:
    Ticket() {
        this->type = "unknown";
        this->ticketId = nullptr;
        this->price = 0.0;
        
    }


    Ticket(const string& type,int* ticketId,double price) {
        this->type = type;
        this->ticketId = ticketId;
        this->price = price;
        

    }
    Ticket(const Ticket& c) {
        this->type = c.type;
        this->ticketId = c.ticketId;
        this->price = c.price;
    }
    Ticket(const string& type) {
        this->type = type;
        this->ticketId = ticketId;
        this->price = price;

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
    double getPrice() const {
        return price;
    }

    void setPrice(double price) {
        if (price < 0.0) {
            throw invalid_argument("Price must be non-negative.");
        }
        this->price = price;
    }
    int* getTicketId() const {
        return this->ticketId;
    }
    void setTicketId(int* ticketId) {

        if (*ticketId < 0) {
            throw exception("Ticket ID must be a positive integer.");
        }

        this->ticketId = new int[*ticketId];

    }

    void saveToBinaryFile(const string& fileName) const;
    bool operator!() const {
        return type.empty();
    }
    //operators


    Ticket& operator=(const Ticket& source) {
        if (this != &source) {
            
            this->type = source.type;

            
            if (source.ticketId != nullptr) {
                this->ticketId = new int(*source.ticketId);
            }
            else {
                this->ticketId = nullptr;
            }
            
            this->price = source.price;
        }
        return *this;
    }

    bool operator==(const Ticket& tic) const {
        return type == tic.type && *ticketId == *tic.ticketId;
    }

    bool operator>(const Ticket& tic) const {
        return *ticketId > *tic.ticketId;
    }

    Ticket& operator++() {
        ++(*ticketId);
        return *this;
    }

    Ticket operator++(int) {
        Ticket temp(*this);
        ++(*ticketId);
        return temp;
    }

    int* generateTicketId() {
        int addvalue=1;
        this->ticketId = new int(addvalue);
        return this->ticketId;
    }
    

    void printInfo() const {
        cout << "Ticket Information:" << endl;
        cout << "Type: " << type << endl;
        cout << "Ticket ID: " << ticketId << endl;
        cout << "-----------------------------" << endl;

    }
    friend ostream& operator<<(ostream& g, Ticket eve);
    friend istream& operator >>(istream& f, Ticket& tic);

};
void printBinaryFile(const string& fileName) {
    ifstream fisierbinar(fileName, ios::binary);

    if (fisierbinar.is_open()) {
        while (!fisierbinar.eof()) {


            int typeSize;
            fisierbinar.read(reinterpret_cast<char*>(&typeSize), sizeof(int));

            if (fisierbinar.eof()) {
                break; 
            }

            char* type = new char[typeSize];
            fisierbinar.read(type, typeSize * sizeof(char));

            int* ticketId = new int;
            fisierbinar.read(reinterpret_cast<char*>(ticketId), sizeof(int));

            double price;
            fisierbinar.read(reinterpret_cast<char*>(&price), sizeof(double));

          
            Ticket ticket(type, ticketId, price);
            ticket.printInfo();


            delete[] type;
            delete ticketId;
        }

        fisierbinar.close();
    }
    else {
        cerr << "Error opening " << fileName << " for reading" << endl;
    }
}
istream& operator>>(istream& f, Ticket& tic) {
    char* tm = new char[256];
    cout << "The type of the seat: ";
    f.ignore();
    getline(f, tic.type);

    cout << "Enter the price: ";
    f >> tic.price;

    cout << "the ticket ID: ";
    tic.generateTicketId();

    cout << "The ticket ID: "  << *tic.getTicketId() << endl;
    return f;
}
ostream& operator<<(ostream& g, Ticket tic) {
    g << "Ticket Information:" << endl;
    g << "Type: " << tic.type << endl;
    g << "Price:" << tic.price << endl;
    g << "Id:" << tic.ticketId << endl;
    g << "-----------------------------" << endl;

    return g;
}

/*int* Ticket::generateTicketId() { //it's wrong!!!!!!!!!!!!!!!
    ifstream inputFile("Tickets.bin", ios::binary);

    int maxId = 0;

   
    while (inputFile.read(reinterpret_cast<char*>(&maxId), sizeof(int))) {
       
        inputFile.seekg(sizeof(char) * maxId, ios::cur);
        inputFile.seekg(sizeof(double), ios::cur);
    }

   
    inputFile.close();


    int* ticketId = new int(maxId + 1);

    return ticketId;
}*/

void displayMenu() {
    cout << "1. Display Event Location Info from file" << endl;
    cout << "2. Display Event Info from file" << endl;
    cout << "3. Display Ticket Info from file" << endl;
    cout << "4. New Ticket" << endl;
    cout << "5. Load from Binary File" << endl;
    cout << "6. Exit" << endl;
}
int* generateTicketId() {
    int* ticketId = new int;


    static int counter = 0;
    *ticketId = ++counter;
    return ticketId;
}
Ticket readTicketFromConsole() {
    string type;
    double price;

    cout << "Enter ticket type: ";
    cin.ignore();  
    getline(cin, type);

    cout << "Enter ticket price: ";
    cin >> price;

    int* ticketId = generateTicketId();

    Ticket ticket(type,ticketId, price);
   // ticket.setTicketId(ticketId);
    
    
    return ticket;

}
/* void deserializeTickets(const string& fileName, vector<Ticket>& tickets) {
    ifstream inputFile(fileName, ios::binary);


    if (!inputFile.is_open()) {
        cerr << "Error opening " << fileName << " for reading" << endl;
        return;
    }

    while (true) {

        int typeSize;
        if (!inputFile.read(reinterpret_cast<char*>(&typeSize), sizeof(int)))
            break;

        char* type = new char[typeSize];
        if (!inputFile.read(type, typeSize * sizeof(char))) {
            delete[] type;
            break;
        }


        int* ticketId = new int;
        if (!inputFile.read(reinterpret_cast<char*>(ticketId), sizeof(int))) {
            delete[] type;
            delete ticketId;
            break;
        }


        double price;
        if (!inputFile.read(reinterpret_cast<char*>(&price), sizeof(double))) {
            delete[] type;
            delete ticketId;
            break;
        }


        Ticket ticket(type, ticketId, price);
        tickets.push_back(ticket);

        delete[] type;
    }

    inputFile.close();
}*/


void Ticket::saveToBinaryFile(const string& fileName) const {
    ofstream outputFile(fileName, ios::app | ios::binary);

    if (outputFile.is_open()) {
        int nrCrt = static_cast<int>(type.size() + 1);
        outputFile.write(reinterpret_cast<const char*>(&nrCrt), sizeof(int));
        outputFile.write(type.c_str(), nrCrt * sizeof(char));


        outputFile.write(reinterpret_cast<const char*>(ticketId), sizeof(int));

        outputFile.write(reinterpret_cast<const char*>(&price), sizeof(double));

        outputFile.close();


        cout << "Ticket saved to " << fileName << endl;
    }
    else {
        cerr << "Error opening " << fileName << " for writing" << endl;
    }
}


int main() {
    Ticket ticket;
    ifstream fisierbinar("Tickets.bin", ios::binary);
    try {
        int choice;

        do {
            displayMenu();
            cout << "Enter your choice (1-6): ";
            cin >> choice;

            switch (choice) {
            case 1: {
                ifstream inputEveloc("EventLocation.txt", ios::in);
                cout << "Event Location Information:" << endl;
                if (inputEveloc.is_open()) {
                    int MaxSeats;
                    inputEveloc >> MaxSeats;

                    int numRows;
                    inputEveloc >> numRows;

                    int* seatsPerRow = new int[numRows];
                    for (int i = 0; i < numRows; i++)
                        inputEveloc >> seatsPerRow[i];

                    cout << endl;
                    cout << "-----------------------------" << endl;

                    EventLocation EveLoc(MaxSeats, numRows, seatsPerRow);
                    cout << EveLoc;
                    inputEveloc.close();
                    delete[] seatsPerRow;
                }
                else {

                    cout << endl << "File does not exist" << endl;
                }
            }
                  break;
            case 2: {

                ifstream inputEve("Event.txt", ios::in);

                cout << "Event Information:" << endl;
                if (inputEve.is_open()) {

                    char* name;
                    char buffer2[100];
                    inputEve.getline(buffer2, sizeof(buffer2));
                    name = new char[strlen(buffer2) + 1];
                    strcpy(name, buffer2);

                    string date;
                    char buffer[50];
                    inputEve.getline(buffer, 50);
                    date = string(buffer);
                    string time;

                    char buffer1[50];
                    inputEve.getline(buffer1, 50);
                    time = string(buffer1);

                    cout << endl;
                    cout << "-----------------------------" << endl;

                    Event EveLoc(name, date, time);
                    cout << EveLoc;
                    inputEve.close();
                    delete[] name;
                }
                else {

                    cout << endl << "File does not exist" << endl;
                }
            }
                  break;

            case 3: {

                ifstream inputTick("Ticket.txt", ios::in);

                cout << "Ticket Information:" << endl;
                if (inputTick.is_open()) {

                    string type;
                    char buffer[100];
                    inputTick.getline(buffer, 100);
                    type = string(buffer);

                    int* ticketId = new int;
                    inputTick >> *ticketId;

                    double price;
                    inputTick >> price;
                    cout << endl;
                    cout << "-----------------------------" << endl;

                    Ticket Tick(type, ticketId, price);
                    cout << Tick;
                    inputTick.close();
                    delete ticketId;
                }

                else {
                    cout << endl << "File does not exist" << endl;
                }
            }
                  break;

            case 4: {
                 ticket = readTicketFromConsole();
                  
                 
                  cout << "New Ticket Created:" << endl;
                
                  ticket.saveToBinaryFile("Tickets.bin");
                  ticket.printInfo();
            }
                break;

            case 5:

                printBinaryFile("Tickets.bin");
                break;

            case 6:
                cout << "Exiting the program." << endl;
                break;

            default:

                cout << "Invalid choice. Try again." << endl;
            }
            cin.ignore();
        } while (choice != 6);

    }
    catch (const exception& e) {

        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
