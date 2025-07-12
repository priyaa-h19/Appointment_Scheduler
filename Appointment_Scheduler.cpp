#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Appointment {
    char name[50];
    char date[11];   // Format: DD/MM/YYYY
    char time[6];    // Format: HH:MM
    char reason[100];
};

// Function to display menu
void showMenu() {
    cout << "\n===== Appointment Scheduler =====\n";
    cout << "1. Add Appointment\n";
    cout << "2. View All Appointments\n";
    cout << "3. Search Appointment by Date\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

// Function to add a new appointment
void addAppointment() {
    Appointment appt;
    ofstream outFile("appointments.txt", ios::app | ios::binary);

    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    cin.ignore(); // Clear input buffer

    cout << "\nEnter Name: ";
    cin.getline(appt.name, 50);
    cout << "Enter Date (DD/MM/YYYY): ";
    cin.getline(appt.date, 11);
    cout << "Enter Time (HH:MM): ";
    cin.getline(appt.time, 6);
    cout << "Enter Reason: ";
    cin.getline(appt.reason, 100);

    outFile.write(reinterpret_cast<char*>(&appt), sizeof(Appointment));
    outFile.close();

    cout << "\n✅ Appointment added successfully!\n";
}

// Function to view all appointments
void viewAppointments() {
    Appointment appt;
    ifstream inFile("appointments.txt", ios::in | ios::binary);

    if (!inFile) {
        cout << "No appointments found or file missing!" << endl;
        return;
    }

    cout << "\n--- All Appointments ---\n";

    while (inFile.read(reinterpret_cast<char*>(&appt), sizeof(Appointment))) {
        cout << "\nName   : " << appt.name;
        cout << "\nDate   : " << appt.date;
        cout << "\nTime   : " << appt.time;
        cout << "\nReason : " << appt.reason;
        cout << "\n---------------------------";
    }

    inFile.close();
}

// Function to search appointments by date
void searchByDate() {
    Appointment appt;
    char searchDate[11];
    bool found = false;

    ifstream inFile("appointments.txt", ios::in | ios::binary);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    cin.ignore(); // Clear input buffer
    cout << "Enter date to search (DD/MM/YYYY): ";
    cin.getline(searchDate, 11);

    cout << "\n--- Appointments on " << searchDate << " ---\n";

    while (inFile.read(reinterpret_cast<char*>(&appt), sizeof(Appointment))) {
        if (strcmp(appt.date, searchDate) == 0) {
            cout << "\nName   : " << appt.name;
            cout << "\nTime   : " << appt.time;
            cout << "\nReason : " << appt.reason;
            cout << "\n---------------------------";
            found = true;
        }
    }

    if (!found)
        cout << "No appointments found on this date.\n";

    inFile.close();
}

// Main function
int main() {
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addAppointment(); break;
            case 2: viewAppointments(); break;
            case 3: searchByDate(); break;
            case 4: cout << "\n👋 Exiting the program. Goodbye!\n"; break;
            default: cout << "\n❌ Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
