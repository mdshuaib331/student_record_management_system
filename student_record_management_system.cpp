#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Define color codes for styling
#define RESET "\033[0m"
#define FG_RED "\033[31m"
#define FG_GREEN "\033[32m"
#define WHITE "\033[97m"
#define BG_LIGHT_CYAN "\033[48;5;153m"
#define BG_LIGHT_GRAY "\033[48;5;234m"

// Class for a student node
class StudentNode {
public:
    int id;
    string name;
    string department;
    double gpa;
    StudentNode* next;

    StudentNode(int id, const string& name, const string& department, double gpa)
        : id(id), name(name), department(department), gpa(gpa), next(nullptr) {}
};

// Function to display the menu
void displayMenu() {
    cout << BG_LIGHT_CYAN << WHITE << "\n===============================" << RESET << endl;
    cout << BG_LIGHT_CYAN << WHITE << " Student Record Management System " << RESET << endl;
    cout << BG_LIGHT_CYAN << WHITE << "===============================" << RESET << endl;
    cout << BG_LIGHT_GRAY << WHITE << " 1. Add Student" << RESET << endl;
    cout << BG_LIGHT_GRAY << WHITE << " 2. View All Students" << RESET << endl;
    cout << BG_LIGHT_GRAY << WHITE << " 3. Search Student" << RESET << endl;
    cout << BG_LIGHT_GRAY << WHITE << " 4. Update Student" << RESET << endl;
    cout << BG_LIGHT_GRAY << WHITE << " 5. Delete Student" << RESET << endl;
    cout << BG_LIGHT_GRAY << WHITE << " 6. Sort Students by ID" << RESET << endl;
    cout << BG_LIGHT_GRAY << WHITE << " 7. Exit" << RESET << endl;
    cout << FG_GREEN << "\nEnter your choice: " << RESET;
}

// Function to handle user login
bool login() {
    string username, password;
    const string correctUsername = "admin";
    const string correctPassword = "password";

    cout << FG_GREEN << "Enter username: " << RESET;
    cin >> username;
    cout << FG_GREEN << "Enter password: " << RESET;
    cin >> password;

    return (username == correctUsername && password == correctPassword);
}

// Function to add a new student
void addStudent(StudentNode*& head) {
    int id;
    string name, department;
    double gpa;

    cout << "\nEnter student ID: ";
    cin >> id;
    cin.ignore(); // To ignore any remaining newline character
    cout << "Enter student name: ";
    getline(cin, name);
    cout << "Enter department: ";
    getline(cin, department);
    cout << "Enter GPA: ";
    cin >> gpa;

    StudentNode* newNode = new StudentNode(id, name, department, gpa);
    newNode->next = head;
    head = newNode;

    cout << FG_GREEN << "\nStudent added successfully!" << RESET << endl << endl;
}

// Function to view all students
void viewAllStudents(StudentNode* head) {
    StudentNode* current = head;
    cout << "\nID\tName\t\t\tDepartment\t\tGPA\n";
    cout << "==========================================================================\n";
    while (current) {
        cout << current->id << "\t" << current->name << "\t\t\t" << current->department << "\t\t\t" << current->gpa << endl;
        current = current->next;
    }
    cout << endl;
}

// Function to search for a student by ID
void searchStudent(StudentNode* head) {
    int id;
    cout << "\nEnter student ID to search: ";
    cin >> id;

    StudentNode* current = head;
    while (current) {
        if (current->id == id) {
            cout << "\nStudent found!" << endl;
            cout << "ID: " << current->id << endl;
            cout << "Name: " << current->name << endl;
            cout << "Department: " << current->department << endl;
            cout << "GPA: " << current->gpa << endl;
            return;
        }
        current = current->next;
    }
    cout << FG_RED << "Student with ID " << id << " not found." << RESET << endl << endl;
}

// Function to update a student's information
void updateStudent(StudentNode*& head) {
    int id;
    cout << "\nEnter student ID to update: ";
    cin >> id;

    StudentNode* current = head;
    while (current) {
        if (current->id == id) {
            string name, department;
            double gpa;

            cout << "\nEnter new name: ";
            cin.ignore(); // To ignore any remaining newline character
            getline(cin, name);
            cout << "Enter new department: ";
            getline(cin, department);
            cout << "Enter new GPA: ";
            cin >> gpa;

            current->name = name;
            current->department = department;
            current->gpa = gpa;

            cout << FG_GREEN << "\nStudent information updated successfully!" << RESET << endl << endl;
            return;
        }
        current = current->next;
    }
    cout << FG_RED << "Student with ID " << id << " not found." << RESET << endl << endl;
}

// Function to delete a student by ID
void deleteStudent(StudentNode*& head) {
    int id;
    cout << "\nEnter student ID to delete: ";
    cin >> id;

    StudentNode* current = head;
    StudentNode* previous = nullptr;

    while (current) {
        if (current->id == id) {
            if (previous) {
                previous->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
            cout << FG_GREEN << "\nStudent deleted successfully!" << RESET << endl << endl;
            return;
        }
        previous = current;
        current = current->next;
    }
    cout << FG_RED << "Student with ID " << id << " not found." << RESET << endl << endl;
}

// Function to sort the student list by ID in ascending order
void sortStudentsByID(StudentNode*& head) {
    if (!head || !head->next) return;

    bool swapped;
    do {
        swapped = false;
        StudentNode* current = head;
        StudentNode* previous = nullptr;
        StudentNode* nextNode = head->next;

        while (nextNode) {
            if (current->id > nextNode->id) {
                swapped = true;
                current->next = nextNode->next;
                nextNode->next = current;

                if (previous) {
                    previous->next = nextNode;
                } else {
                    head = nextNode;
                }

                previous = nextNode;
                nextNode = current->next;
            } else {
                previous = current;
                current = nextNode;
                nextNode = nextNode->next;
            }
        }
    } while (swapped);

    cout << FG_GREEN << "\nStudents sorted by ID successfully!" << RESET << endl << endl;
}

// Function to save students to a file
void saveStudents(StudentNode* head) {
    ofstream file("students.txt");
    StudentNode* current = head;
    while (current) {
        file << current->id << "," << current->name << "," << current->department << "," << current->gpa << endl;
        current = current->next;
    }
    file.close();
    cout << FG_GREEN << "\nStudents saved to file successfully!" << RESET << endl << endl;
}

// Function to load students from a file
void loadStudents(StudentNode*& head) {
    ifstream file("students.txt");
    int id;
    string name, department;
    double gpa;
    char delimiter;

    while (file >> id >> delimiter) {
        getline(file, name, ',');
        getline(file, department, ',');
        file >> gpa;
        file.ignore(); // To ignore the newline character

        StudentNode* newNode = new StudentNode(id, name, department, gpa);
        newNode->next = head;
        head = newNode;
    }
    file.close();
}

// Main function
int main() {
    StudentNode* head = nullptr;

    if (login()) {
        loadStudents(head);

        int choice;
        do {
            displayMenu();  // Call the new menu display function

            cin >> choice;

            switch (choice) {
                case 1:
                    addStudent(head);
                    break;
                case 2:
                    viewAllStudents(head);
                    break;
                case 3:
                    searchStudent(head);
                    break;
                case 4:
                    updateStudent(head);
                    break;
                case 5:
                    deleteStudent(head);
                    break;
                case 6:
                    sortStudentsByID(head);
                    break;
                case 7:
                    saveStudents(head);
                    break;
                default:
                    cout << FG_RED << "Invalid choice. Please try again." << RESET << endl << endl;
                    break;
            }
        } while (choice != 7);
    } else {
        cout << FG_RED << "Login failed. Exiting program." << RESET << endl;
    }

    // Clean up
    StudentNode* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
