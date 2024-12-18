#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

class Student {
private:
    string username;
    string password;
    string fullName;
    string email;
    string contactNumber;
    string fatherName;
    long long cnic;
    int sscMarks;
    int fscMarks;

public:
    Student(string user, string pass, string name, string mail, string contact, long long cnicNum, string father, int ssc, int fsc)
        : username(user), password(pass), fullName(name), email(mail), contactNumber(contact), cnic(cnicNum), fatherName(father), sscMarks(ssc), fscMarks(fsc) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getFullName() const { return fullName; }
    string getEmail() const { return email; }
    string getContactNumber() const { return contactNumber; }
    long long getCnic() const { return cnic; }
    int getSscMarks() const { return sscMarks; }
    int getFscMarks() const { return fscMarks; }
    int getTotalMarks() const { return sscMarks + fscMarks; }  // Calculates total marks
};

class AdmissionPortal {
private:
    vector<Student> students;
    Student* loggedInStudent = nullptr;

public:
    void registerStudent() {
        string username, password, fullName, email, contactNumber, fatherName;
        long long cnic;
        int sscMarks, fscMarks;

        cout << "\n----------------- Register New Student -----------------\n";
        cout << "Enter username: ";
        cin >> username;
        cin.ignore();

        cout << "Enter password: ";
        getline(cin, password);

        cout << "Enter full name: ";
        getline(cin, fullName);

        cout << "Enter email: ";
        getline(cin, email);

        cout << "Enter contact number: ";
        getline(cin, contactNumber);

        cout << "Enter CNIC number: ";
        cin >> cnic;
        cin.ignore();

        cout << "Enter father's name: ";
        getline(cin, fatherName);

        cout << "Enter SSC marks: ";
        while (!(cin >> sscMarks) || sscMarks < 0 || sscMarks > 1100) {
            cout << "Invalid SSC marks. Please enter a value between 0 and 100: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        cout << "Enter FSC marks: ";
        while (!(cin >> fscMarks) || fscMarks < 0 || fscMarks > 1100) {
            cout << "Invalid FSC marks. Please enter a value between 0 and 100: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        students.push_back(Student(username, password, fullName, email, contactNumber, cnic, fatherName, sscMarks, fscMarks));
        cout << "\nRegistration successful! You can now log in.\n";
    }

    void loginStudent() {
        string username, password;

        cout << "\n----------------- Login -----------------\n";
        cout << "Enter username: ";
        cin >> username;
        cin.ignore();

        cout << "Enter password: ";
        getline(cin, password);

        for (auto& student : students) {
            if (student.getUsername() == username && student.getPassword() == password) {
                loggedInStudent = &student;
                cout << "\nLogin successful! Welcome to Bahria University Admission Portal.\n";
                displayDashboard();
                return;
            }
        }

        cout << "\nInvalid username or password. Please try again.\n";
    }

    void displayDashboard() {
        int choice;
        do {
            cout << "\n\n\t\t\t\t\t\t\t----------------------------------------\n";
            cout << "\t\t\t\t\t\t\t| *** BAHRIA UNIVERSITY *** |\n";
            cout << "\t\t\t\t\t\t\t----------------------------------------\n";
            cout << "\n------------ Welcome, " << loggedInStudent->getFullName() << " ------------\n";
            cout << "1. Take CBT Test\n";
            cout << "2. View Merit List\n";
            cout << "3. Logout\n";
            cout << "----------------------------------------\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                takeCbtTest();
                break;
            case 2:
                viewMeritList();
                break;
            case 3:
                cout << "\nLogging out...\n";
                loggedInStudent = nullptr;
                break;
            default:
                cout << "\nInvalid choice, please try again.\n";
            }
        } while (loggedInStudent != nullptr && choice != 3);
    }

    void takeCbtTest() {
        int score = 0;
        string answer;

        cout << "\nWelcome to the CBT Test!\n";

        // Sample question 1
        cout << "Question 1: What is 2 + 2?\n";
        cout << "A. 3\nB. 4\nC. 5\nD. 6\n";
        cout << "Enter your answer (A/B/C/D): ";
        cin >> answer;
        if (answer == "B" || answer == "b") score++;

        // Sample question 2
        cout << "\nQuestion 2: What is the capital of Pakistan?\n";
        cout << "A. Islamabad\nB. Karachi\nC. Lahore\nD. Peshawar\n";
        cout << "Enter your answer (A/B/C/D): ";
        cin >> answer;
        if (answer == "A" || answer == "a") score++;

        // Show the test result
        cout << "\nTest completed! Your score is: " << score << "/2\n";
    }

    void viewMeritList() {
        cout << "\nDisplaying Merit List:\n";

        // Sort students by their total marks (SSC + FSC)
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.getTotalMarks() > b.getTotalMarks();  // Sort in descending order of total marks
            });

        // Display the students' details in order of merit
        for (const auto& student : students) {
            cout << "Name: " << student.getFullName()
                << ", SSC Marks: " << student.getSscMarks()
                << ", FSC Marks: " << student.getFscMarks()
                << ", Total Marks: " << student.getTotalMarks()
                << "\n";
        }
    }

    void mainMenu() {
        int choice;
        do {
            cout << "\n\n\t\t\t\t\t\t\t----------------------------------------\n";
            cout << "\t\t\t\t\t\t\t|    *** BAHRIA UNIVERSITY ***    |\n";
            cout << "\t\t\t\t\t\t\t----------------------------------------\n";
            cout << "\n--- Bahria University Admission Portal ---\n";
            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "3. Exit\n";
            cout << "----------------------------------------\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                registerStudent();
                break;
            case 2:
                loginStudent();
                break;
            case 3:
                cout << "\nExiting the portal. Thank you for visiting Bahria University.\n";
                break;
            default:
                cout << "\nInvalid choice, please try again.\n";
            }
        } while (choice != 3);
    }
};

int main() {
    AdmissionPortal portal;
    portal.mainMenu();  // Start the portal's main menu
    return 0;
}
