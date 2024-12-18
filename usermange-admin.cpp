#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Base class for User (Common attributes for students and teachers)
class User {
protected:
    string name;
    int id;
    string contact;

public:
    User(string name, int id, string contact)
        : name(name), id(id), contact(contact) {
    }

    virtual void displayDetails() const {
        cout << left << setw(10) << id << setw(20) << name << setw(15) << contact;
    }

    int getID() const { return id; }
    string getName() const { return name; }

    virtual ~User() = default; // Virtual destructor
};

// Derived class for Student
class Student : public User {
private:
    bool isPassOut;

public:
    Student(string name, int id, string contact, bool passOut = false)
        : User(name, id, contact), isPassOut(passOut) {
    }

    void displayDetails() const override {
        User::displayDetails();
        cout << setw(10) << (isPassOut ? "Yes" : "No") << endl;
    }

    void markPassOut() { isPassOut = true; }

    void editDetails(const string& newName, const string& newContact) {
        name = newName;
        contact = newContact;
    }
};

// Derived class for Teacher
class Teacher : public User {
private:
    string subject;

public:
    Teacher(string name, int id, string contact, string subject)
        : User(name, id, contact), subject(subject) {
    }

    void displayDetails() const override {
        User::displayDetails();
        cout << setw(20) << subject << endl;
    }

    void editDetails(const string& newName, const string& newContact, const string& newSubject) {
        name = newName;
        contact = newContact;
        subject = newSubject;
    }
};

// User Management System
class UserManagement {
private:
    vector<Student> students;
    vector<Teacher> teachers;
    int studentIDCounter = 1000;
    int teacherIDCounter = 2000;

    // Display list of students
    void displayStudents() const {
        if (students.empty()) {
            cout << "\nNo students available.\n";
            return;
        }

        cout << "\n--- Student List ---\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Contact" << "Pass-out\n";
        cout << string(55, '-') << endl;

        for (const auto& student : students)
            student.displayDetails();
    }

    // Display list of teachers
    void displayTeachers() const {
        if (teachers.empty()) {
            cout << "\nNo teachers available.\n";
            return;
        }

        cout << "\n--- Teacher List ---\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Contact" << "Subject\n";
        cout << string(65, '-') << endl;

        for (const auto& teacher : teachers)
            teacher.displayDetails();
    }

public:
    // Functionality 1: Add New Student
    void addNewStudent() {
        string name, contact;
        cout << "\nEnter Student Name: ";
        cin.ignore(); // Clear buffer
        getline(cin, name);

        cout << "Enter Contact: ";
        getline(cin, contact);

        students.emplace_back(name, studentIDCounter++, contact);
        cout << "Student added successfully!\n";
    }

    // Functionality 2: Edit Student Details
    void editStudent() {
        displayStudents();
        if (students.empty()) return;

        int id;
        cout << "\nEnter Student ID to edit: ";
        cin >> id;

        cin.ignore(); // Clear buffer
        for (auto& student : students) {
            if (student.getID() == id) {
                string newName, newContact;
                cout << "Enter New Name: ";
                getline(cin, newName);

                cout << "Enter New Contact: ";
                getline(cin, newContact);

                student.editDetails(newName, newContact);
                cout << "Student details updated successfully!\n";
                return;
            }
        }
        cout << "Student ID not found!\n";
    }

    // Functionality 3: Remove Student
    void removeStudent() {
        displayStudents();
        if (students.empty()) return;

        int id;
        cout << "\nEnter Student ID to remove: ";
        cin >> id;

        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->getID() == id) {
                cout << "Student \"" << it->getName() << "\" removed successfully.\n";
                students.erase(it);
                return;
            }
        }
        cout << "Student ID not found!\n";
    }

    // Functionality 4: Add New Teacher
    void addNewTeacher() {
        string name, contact, subject;
        cout << "\nEnter Teacher Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Contact: ";
        getline(cin, contact);

        cout << "Enter Subject: ";
        getline(cin, subject);

        teachers.emplace_back(name, teacherIDCounter++, contact, subject);
        cout << "Teacher added successfully!\n";
    }

    // Main User Management Menu
    void userManagementMenu() {
        int choice;
        do {
            cout << "\n=== USER MANAGEMENT ===\n";
            cout << "1. Add New Student\n";
            cout << "2. Edit Student Details\n";
            cout << "3. Remove Student\n";
            cout << "4. Add New Teacher\n";
            cout << "5. Back To Admin Panel\n";
            cout << "=========================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: addNewStudent(); break;
            case 2: editStudent(); break;
            case 3: removeStudent(); break;
            case 4: addNewTeacher(); break;
            case 5: cout << "Returning to Admin Panel...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
            }
        } while (choice != 5);
    }
};

// Main function
int main() {
    UserManagement um;
    um.userManagementMenu();
    cout << "Exiting Program...\n";
    return 0;
}
