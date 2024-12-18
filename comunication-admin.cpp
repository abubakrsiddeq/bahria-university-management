#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Survey Class
class Survey {
private:
    int id;
    string title;
    string description;

public:
    Survey(int id, string title, string description)
        : id(id), title(title), description(description) {
    }

    int getID() const { return id; }
    string getTitle() const { return title; }
    string getDescription() const { return description; }

    void displaySurvey() const {
        cout << left << setw(5) << id << setw(20) << title << setw(40) << description << endl;
    }

    void editSurvey(const string& newTitle, const string& newDescription) {
        title = newTitle;
        description = newDescription;
    }
};

// Complaint Class
class Complaint {
private:
    int id;
    string studentName;
    string complaintText;

public:
    Complaint(int id, string studentName, string complaintText)
        : id(id), studentName(studentName), complaintText(complaintText) {
    }

    void displayComplaint() const {
        cout << "Complaint ID: " << id << "\nStudent Name: " << studentName
            << "\nComplaint: " << complaintText << "\n" << string(40, '-') << endl;
    }

    int getID() const { return id; }
};

// Communication System Class
class CommunicationSystem {
private:
    vector<Survey> surveys;
    vector<Complaint> complaints;
    int surveyCounter = 1;
    int complaintCounter = 1;

    // Display Survey List
    void displaySurveys() const {
        if (surveys.empty()) {
            cout << "\nNo surveys available.\n";
            return;
        }

        cout << "\n--- List of Surveys ---\n";
        cout << left << setw(5) << "ID" << setw(20) << "Title" << setw(40) << "Description" << "\n";
        cout << string(65, '-') << endl;

        for (const auto& survey : surveys) {
            survey.displaySurvey();
        }
    }

    // Display Complaints List
    void displayComplaints() const {
        if (complaints.empty()) {
            cout << "\nNo complaints available.\n";
            return;
        }

        cout << "\n--- List of Complaints ---\n";
        for (const auto& complaint : complaints) {
            complaint.displayComplaint();
        }
    }

public:
    // Functionality 1: Add New Survey
    void addNewSurvey() {
        string title, description;
        cin.ignore(); // Clear input buffer
        cout << "\nEnter Survey Title: ";
        getline(cin, title);

        cout << "Enter Survey Description: ";
        getline(cin, description);

        surveys.emplace_back(surveyCounter++, title, description);
        cout << "Survey added successfully!\n";
    }

    // Functionality 2: Edit Survey
    void editSurvey() {
        displaySurveys();
        if (surveys.empty()) return;

        int id;
        cout << "\nEnter Survey ID to edit: ";
        cin >> id;

        for (auto& survey : surveys) {
            if (survey.getID() == id) {
                string newTitle, newDescription;
                cin.ignore();
                cout << "Enter New Title: ";
                getline(cin, newTitle);

                cout << "Enter New Description: ";
                getline(cin, newDescription);

                survey.editSurvey(newTitle, newDescription);
                cout << "Survey updated successfully!\n";
                return;
            }
        }
        cout << "Survey ID not found!\n";
    }

    // Functionality 3: Display Student Surveys
    void displayStudentSurveys() const {
        displaySurveys();
    }

    // Functionality 4: Add Student Complaint
    void addComplaint() {
        string studentName, complaintText;
        cin.ignore();
        cout << "\nEnter Student Name: ";
        getline(cin, studentName);

        cout << "Enter Complaint: ";
        getline(cin, complaintText);

        complaints.emplace_back(complaintCounter++, studentName, complaintText);
        cout << "Complaint recorded successfully!\n";
    }

    // Functionality 5: Display All Complaints
    void displayAllComplaints() const {
        displayComplaints();
    }

    // Communication Menu
    void communicationMenu() {
        int choice;
        do {
            cout << "\n=== COMMUNICATION SYSTEM ===\n";
            cout << "1. Add New Survey\n";
            cout << "2. Edit Survey\n";
            cout << "3. Display Students' Surveys\n";
            cout << "4. Students' Complaints\n";
            cout << "5. Back To Admin Panel\n";
            cout << "=============================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                addNewSurvey();
                break;
            case 2:
                editSurvey();
                break;
            case 3:
                displayStudentSurveys();
                break;
            case 4:
                addComplaint();
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

// Main Function
int main() {
    CommunicationSystem communicationSystem;
    communicationSystem.communicationMenu();
    cout << "Exiting Program....\n";
    return 0;
}
