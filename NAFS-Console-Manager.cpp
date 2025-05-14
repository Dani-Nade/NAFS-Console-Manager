#include <iostream>
#include <string>
#include<fstream>
#include<Windows.h>
#include <limits>
#include <conio.h>

using namespace std;

class User {
public:
    User() = default; // Add a default constructor

    //User() = default; // Keep the default constructor
    User(const string& user, const string& pass) : username(user), password(pass) {} // Add a constructor that takes two const string & arguments
    User(const string& n, const string& pass, const string user ,const string& Cn , const string &accountDet ) : name(n), username(user), password(pass), CNIC(Cn), accountDetails(accountDet) {} // Add a constructor that takes two const string & arguments

    User(User& A) {

        this->name = A.getName();
        this->CNIC = A.getCNIC();
        this->accountDetails = A.getAccountDetails();
        this->password = A.getPassword();

    }


    // Getter and setter methods for member variables
    string getName() const { return name; }
    void setName(const string& newName) { name = newName; }

    string getCNIC() const { return CNIC; }
    void setCNIC(const string& newCNIC) { CNIC = newCNIC; }

    string getUsername() const { return username; }
    void setUsername(const string& newUsername) { username = newUsername; }

    string getPassword() const { return password; }
    void setPassword(const string& newPassword) { password = newPassword; }

    string getAccountDetails() const { return accountDetails; }
    void setAccountDetails(const string& newAccountDetails) { accountDetails = newAccountDetails; }


protected:
    string name;
    string CNIC;
    string username;
    string password;
    string accountDetails;
};

class Admin : public User {
public:
    Admin() = default; // Add a default constructor

    Admin(const string& user, const string& pass) : User(user, pass) {}

    void updateFlightSchedule();
    void addNewRoutes();
    void restrictPassengerNumbers();
    void updateAirlineInquiry();
};

class Passenger : public User {
public:
    friend void bookFlight();
    Passenger() = default; // Add a default constructor
    Passenger(string name,  string username, string password, string CNIC, string accountDetails, string passportnum, bool hasvisa) : User( name, username ,password, CNIC , accountDetails ), passportNumber( passportnum ) , hasVisa(hasvisa) {}

    // Getter and setter methods for member variables
    string getPassportNumber() const { return passportNumber; }
    void setPassportNumber(const string& newPassportNumber) {
        passportNumber = newPassportNumber;
    }

    bool getHasVisa() const { return hasVisa; }
    void setHasVisa(bool newHasVisa) { hasVisa = newHasVisa; }

    void updateDetails();
    void viewMostVisitedCountry();

private:
    string passportNumber;
    bool hasVisa;
};



class Flight {
public:
    Flight() = default; // Add a default constructor

    // Getter and setter methods for member variables
    string getOrigin() const { return origin; }
    void setOrigin(const string& newOrigin) { origin = newOrigin; }

    string getDestination() const { return destination; }
    void setDestination(const string& newDestination) { destination = newDestination; }

    string getDepartureTime() const { return departureTime; }
    void setDepartureTime(const string& newDepartureTime) { departureTime = newDepartureTime; }

    string getArrivalTime() const { return arrivalTime; }
    void setArrivalTime(const string& newArrivalTime) { arrivalTime = newArrivalTime; }

    int getAvailableSeats() const { return availableSeats; }
    void setAvailableSeats(int newAvailableSeats) { availableSeats = newAvailableSeats; }

    bool getIsLocal() const { return isLocal; }
    void setIsLocal(bool newIsLocal) { isLocal = newIsLocal; }

    void displayFlightInfo() {
        cout << "Origin: " << origin << endl;
        cout << "Destination: " << destination << endl;
        cout << "Departure Time: " << departureTime << endl;
        cout << "Arrival Time: " << arrivalTime << endl;
        cout << "Available Seats: " << availableSeats << endl;
    }

private:
    string origin;
    string destination;
    string departureTime;
    string arrivalTime;
    int availableSeats;
    bool isLocal;
};

const int MAX_USERS = 100;
const int MAX_FLIGHTS = 100;

Admin admins[MAX_USERS];
Passenger passengers[MAX_USERS];
Flight flights[MAX_FLIGHTS];
int adminCount = 1;
int passengerCount = 0;
int flightCount = 0;
string airlineInquiry[2];

void displayMenu() {
    cout << "\nNAFS Menu:\n";
    cout << "1. Register\n";
    cout << "2. Admin Login\n";
    cout << "3. Passenger Login\n";
    cout << "4. Inquiry \n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

bool validatePassword(const string& password) {
    if (password.length() < 8) {
        return false;
    }

    bool hasSpecialChar = false;
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;

    for (const char& c : password) {
        if (isdigit(c)) {
            hasDigit = true;
        }
        else if (isupper(c)) {
            hasUpper = true;
        }
        else if (islower(c)) {
            hasLower = true;
        }
        else {
            hasSpecialChar = true;
        }
    }

    return hasSpecialChar && hasUpper && hasLower && hasDigit;
}

bool CNICExists(const string& cnic) {
    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].getCNIC() == cnic) {
            return true;
        }
    }
    return false;
}

bool VerifyFinancialDetail(const string& accountDetails) {
    return accountDetails.length() >= 10;
}

// Function to input a password with asterisks (*) instead of the actual characters
string inputPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != 13) {  // Wait for the Enter key (13) to be pressed
        if (ch == 8) {  // If backspace is pressed (8)
            if (!password.empty()) {
                cout << "\b \b";  // Erase the last asterisk
                password.pop_back();
            }
        }
        else {
            cout << '*';
            password.push_back(ch);
        }
    }
    cout << endl;
    return password;
}

void registerUser() {
    fstream info;
    info.open("Users.txt" , ios::app);
    Passenger newPassenger;
    cout << "Enter your name: ";
    cin.ignore();
    string temp;
    getline(cin, temp);
    newPassenger.setName(temp);
    info << temp << endl;

    cout << "Enter your CNIC: ";
    cin >> temp;
    while (temp.length() != 13 || CNICExists(temp)) {
        if (temp.length() != 13) {
            cout << "Invalid CNIC length. Please enter a 13-digit CNIC: ";
        }
        else {
            cout << "CNIC already exists. Please enter a different CNIC: ";
        }
        cin >> temp;
    }
    info << temp << endl;
    newPassenger.setCNIC(temp);

    cout << "Enter your username: ";
    cin >> temp;
    info << temp << endl;
    newPassenger.setUsername(temp);

    cout << "Enter your password: ";
    string password;
    password = inputPassword();
    while (!validatePassword(password)) {
        cout << "Password must be 8 characters long and use a minimum of one special character, uppercase, lowercase, and numeric digit. Please enter a valid password: ";
        password = inputPassword();
    }
    info << password << endl;
    newPassenger.setPassword(password);
    cout << "Do you have a visa? (1 for yes, 0 for no): ";
    int visa;
    cin >> visa;
    info << 1<<endl;
    newPassenger.setHasVisa(visa == 1);
    cout << "Enter your account details: ";
    cin.ignore();
    getline(cin, temp);
    while (!VerifyFinancialDetail(temp)) {
        cout << "Invalid account details. Please enter a valid account details: ";
        getline(cin, temp);
    }
    info << temp << endl;
    newPassenger.setAccountDetails(temp);

    passengers[passengerCount] = newPassenger;
    passengerCount++;
    info.close();
}

void viewFlightSchedules() {
    cout << "\nFlight Schedules:\n";
    for (int i = 0; i < flightCount; i++) {
        cout << "Flight " << i + 1 << ":\n";
        flights[i].displayFlightInfo();
        cout << endl;
    }
}

void bookFlight() {
    viewFlightSchedules();
    cout << "Select a flight number to book: ";
    int flightNumber;
    cin >> flightNumber;
    flightNumber--;

    if (flightNumber >= 0 && flightNumber < flightCount) {
        if (flights[flightNumber].getAvailableSeats() > 0) {
            int var = flights[flightNumber].getAvailableSeats();
            var--;
            flights[flightNumber].setAvailableSeats(var);
            cout << "Flight booked successfully.\n";
        }
        else {
            cout << "No available seats on this flight.\n";
        }
    }
    else {
        cout << "Invalid flight number.\n";
    }
}

void adminMenu() {
    cout << "\nAdmin Functions:\n";
    cout << "1. Add New Route\n";
    cout << "2. Update Flight Schedule\n";
    cout << "3. Restrict Passenger Numbers\n";
    cout << "4. Update Airline Inquiry\n";
    cout << "5. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

void addNewRoute() {
    Flight newFlight;
    cout << "Enter origin: ";
    string temp;
    cin.ignore();
    getline(cin, temp);
    newFlight.setOrigin(temp);
    cout << "Enter destination: ";
    getline(cin, temp);
    newFlight.setDestination(temp);
    cout << "Enter departure time: ";
    cin >> temp;
    newFlight.setDepartureTime(temp);
    cout << "Enter arrival time: ";
    cin >> temp;
    newFlight.setArrivalTime(temp);
    cout << "Enter available seats: ";
    cin >> temp;
    newFlight.setAvailableSeats(stoi(temp));
    cout << "Is this a local flight? (1 for yes, 0 for no): ";
    int local;
    cin >> local;
    newFlight.setIsLocal(local == 1);
    flights[flightCount] = newFlight;
    flightCount++;
}

void updateFlightSchedule() {
    viewFlightSchedules();
    cout << "Select a flight number to update: ";
    int flightNumber;
    cin >> flightNumber;
    flightNumber--;
    if (flightNumber >= 0 && flightNumber < flightCount) {
        string data;
        cout << "Enter new departure time: ";
        cin >> data;
        flights[flightNumber].setDepartureTime(data);
        cout << "Enter new arrival time: ";
        cin >> data;
        flights[flightNumber].setArrivalTime(data);
        cout << "Flight schedule updated successfully.\n";
    }
    else {
        cout << "Invalid flight number.\n";
    }
}

void restrictPassengerNumbers() {
    viewFlightSchedules();
    cout << "Select a flight number to update available seats: ";
    int flightNumber;
    cin >> flightNumber;
    flightNumber--;
    if (flightNumber >= 0 && flightNumber < flightCount) {
        cout << "Enter new available seats: ";
        int seats;
        cin >> seats;
        flights[flightNumber].setAvailableSeats(seats);
        cout << "Available seats updated successfully.\n";
    }
    else {
        cout << "Invalid flight number.\n";
    }
}

void Passenger::updateDetails() {
    system("cls");
    cout << "Enter your new name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter your new CNIC: ";
    cin >> CNIC;
    cout << "Enter your new username: ";
    cin >> username;
    cout << "Enter your new password: ";
    cin >> password;
    cout << "Enter your new passport number: ";
    cin >> passportNumber;
    cout << "Do you have a visa? (1 for yes, 0 for no): ";
    int visa;
    cin >> visa;
    hasVisa = visa == 1;
}

void Passenger::viewMostVisitedCountry() {
    // Implement logic to calculate the most visited country
    string mostVisitedCountry = "Sample Country";
    cout << "The most visited country is " << mostVisitedCountry
        << " with an estimated traveling cost on NAFS.\n";
}

void passengerMenu() {
    system("cls");

    cout << "Welcome Passenger " << passengers[0].getName();


    cout << "\nPassenger Functions:\n";
    cout << "1. Update Details\n";
    cout << "2. View Most Visited Country\n";
    cout << "3. Book Flight\n";
    cout << "4. View Flight Schedules\n";
    cout << "5. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

bool adminLogin() {

    string username, password;
    cout << "Admin Username: ";
    cin >> username;
    cout << "Admin Password: ";
    password = inputPassword();

    for (int i = 0; i < adminCount; i++) {
        if (admins[i].getUsername() == username && admins[i].getPassword() == password) {
            return true;
        }
    }

    return false;
}

bool passengerLogin() {
    fstream info;
    string transfer;
    string username, password;
    cout << "Passenger Username: ";
    cin >> username;
    cout << "Passenger Password: ";
    password = inputPassword();

    info.open("Users.txt");
    while (getline(info, transfer)) {
        if (username == transfer) {
            getline(info, transfer);
            if (password == transfer) {

                return true;

            }


        }


    }

    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].getUsername() == username &&
            passengers[i].getPassword() == password) {
            return true;
        }
    }
    info.close();

    return false;
}

void updateAirlineInquiry() {
    fstream A;
    string Contact, Email;
    cout << "Enter new airline inquiry details: \nContact:";
    cin.ignore();
    getline(cin, Contact);
    cout << "\n Email: ";
    getline(cin, Email);

    A.open("Inquiry.txt", ios::app);
    A << Email << endl << Contact << endl;
    A.close();

    airlineInquiry[0] = Contact;
    airlineInquiry[1] = Email;
    
    cout << "Airline inquiry updated.\n";
}

int main() {
    int choice;
    fstream A;
    string s;
    int count=0;

    // Sample admin
    admins[0] = Admin("admin1", "Admin@123");

    do {
        a:
        displayMenu();
        cin >> choice;
        switch(choice) {
        case 1:
            registerUser();
            break;
            //case 2:
              //viewFlightSchedules();
              //break;
           // case 3:
              //bookFlight();
              //break;
        case 2:
            if (adminLogin()) {
                int adminChoice;
                do {
                    adminMenu();
                    cin >> adminChoice;

                    switch (adminChoice) {
                    case 1:
                        addNewRoute();
                        break;
                    case 2:
                        updateFlightSchedule();
                        break;
                    case 3:
                        restrictPassengerNumbers();
                        break;
                    case 4:
                        updateAirlineInquiry();
                        break;
                    case 5:
                        cout << "Logging out from admin panel.\n";
                        break;
                    default:
                        cout << "Invalid choice, please try again.\n";
                        break;
                    }
                } while (adminChoice != 5);
            }
            else {
                cout << "Invalid admin credentials.\n";
            }
            break;
        case 3:
            if (passengerLogin()) {
                int passengerChoice;
                do {
                    passengerMenu();
                    cin >> passengerChoice;

                    switch (passengerChoice) {
                    case 1:
                        // Replace '0' with the index of the logged-in passenger
                        passengers[0].updateDetails();
                        break;
                    case 2:
                        // Replace '0' with the index of the logged-in passenger
                        passengers[0].viewMostVisitedCountry();
                        break;
                    case 3:
                        bookFlight();
                        break;
                    case 4:
                        viewFlightSchedules();
                        break;
                    case 5:

                        cout << "Logging out from passenger panel.\n";
                        Sleep(3);
                        goto a;
                        break;
                    default:
                        cout << "Invalid choice, please try again.\n";
                        goto a;
                        break;
                    }
                } while (passengerChoice != 3);
            }
            else {
                cout << "Invalid passenger credentials.\n";
            }
            break;
        case 4:
            A.open("Inquiry.txt");
            while (getline(A, s)) {

                airlineInquiry[count] = s;
                count++;
            }
            cout << "Contact: " << airlineInquiry[0] << endl << "Email: " << airlineInquiry[1] << endl;
            A.close();

            break;

        case 5:
            cout << "Thank you for using NAFS!\n";
            break;
        default:
            cout << "Invalid choice, please try again.\n";
            break;
        }
    } while (choice != 5);

    return 0;
}
