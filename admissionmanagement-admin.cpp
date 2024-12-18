#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// AdmissionManagement Class
class AdmissionManagement {
private:
    vector<string> meritList; // To store the merit list of students

    // Function to display the merit list
    void displayMeritList() const {
        if (meritList.empty()) {
            cout << "\nMerit list is empty!\n";
        }
        else {
            cout << "\n---- Merit List ----\n";
            for (size_t i = 0; i < meritList.size(); ++i) {
                cout << i + 1 << ". " << meritList[i] << "\n";
            }
        }
        cout << "----------------------\n";
    }

public:
    // Function to add a student to the merit list
    void addMeritList() {
        string studentName;
        cout << "Enter student name to add to the merit list: ";
        cin.ignore(); // Clears input buffer
        getline(cin, studentName);
        meritList.push_back(studentName);
        cout << "Student \"" << studentName << "\" has been added to the merit list.\n";
    }

    // Function to edit a student's name in the merit list
    void editMeritList() {
        if (meritList.empty()) {
            cout << "\nMerit list is empty! Nothing to edit.\n";
            return;
        }

        displayMeritList();
        int index;
        cout << "Enter the number of the student you want to edit: ";
        cin >> index;

        if (index < 1 || index > meritList.size()) {
            cout << "Invalid choice! Try again.\n";
            return;
        }

        string newName;
        cout << "Enter the new name for student " << index << ": ";
        cin.ignore();
        getline(cin, newName);
        meritList[index - 1] = newName;
        cout << "Student's name has been updated successfully!\n";
    }

    // Function to display the merit list
    void displayMenuMeritList() const {
        displayMeritList();
    }

    // Function to delete a student from the merit list
    void deleteMeritList() {
        if (meritList.empty()) {
            cout << "\nMerit list is empty! Nothing to delete.\n";
            return;
        }

        displayMeritList();
        int index;
        cout << "Enter the number of the student to delete: ";
        cin >> index;

        if (index < 1 || index > meritList.size()) {
            cout << "Invalid choice! Try again.\n";
            return;
        }

        cout << "Student \"" << meritList[index - 1] << "\" has been removed from the merit list.\n";
        meritList.erase(meritList.begin() + index - 1);
    }

    // Function to handle the menu
    void admissionMenu() {
        int choice;
        do {
            cout << "\n===== ADMISSION MANAGEMENT MENU =====\n";
            cout << "1. Add Merit List\n";
            cout << "2. Edit Merit List\n";
            cout << "3. Display Merit List\n";
            cout << "4. Delete Merit List\n";
            cout << "5. Back To Admin Panel\n";
            cout << "======================================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                addMeritList();
                break;
            case 2:
                editMeritList();
                break;
            case 3:
                displayMenuMeritList();
                break;
            case 4:
                deleteMeritList();
                break;
            case 5:
                cout << "Returning to Admin Panel...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 5);
    }
};

int main() {
    AdmissionManagement admission;

    // Run the Admission Management menu
    admission.admissionMenu();

    cout << "Exiting Program...\n";
    return 0;
}
