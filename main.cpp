#include <iostream>
#include <string>
using namespace std;

struct Student {
    string id;
    string first_name;
    string last_name;
    string course;
    float gpa;
};

const int MAX_STUDENTS = 1000;
Student students[MAX_STUDENTS];
int studentCount = 0;

void clearScreen() {
    system("cls");
}

bool isDuplicate(string id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            return true;
        }
    }
    return false;
}

bool isValid(float gpa) {
    return (gpa >= 0.0 && gpa <= 4.0);
}

void addStudent() {
    clearScreen();

    Student add;

    cin.clear();
    cin.ignore(1000, '\n');

    cout << "Enter Student ID: ";
    while (!(cin >> add.id)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    if (isDuplicate(add.id)) {
        cout << "\nID already exists. Please enter a new ID.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    cin.ignore(1000, '\n');

    cout << "Enter First Name: ";
    getline(cin, add.first_name);

    cout << "Enter Last Name: ";
    getline(cin, add.last_name);

    cout << "Enter Course: ";
    getline(cin, add.course);

    while (true) {
        cout << "Enter GPA (0.0-4.0): ";
        if (cin >> add.gpa) {
            if (isValid(add.gpa)) {
                break;
            }
            cout << "Invalid GPA! Must be between 0.0 and 4.0\n";
        } else {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    students[studentCount++] = add;
    cout << "\nStudent added successfully!\n";
    cin.clear();
    cin.ignore(1000, '\n');
}

void editStudent() {
    clearScreen();

    if (studentCount == 0) {
        cout << "No students available to edit.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    string id;
    cout << "Enter Student ID to edit: ";
    cin >> id;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            cout << "\nEditing student: " << students[i].first_name << " " << students[i].last_name << endl;

            cout << "Enter new First Name (current: " << students[i].first_name << "): ";
            cin >> students[i].first_name;

            cout << "Enter new Last Name (current: " << students[i].last_name << "): ";
            cin >> students[i].last_name;

            cout << "Enter new Course (current: " << students[i].course << "): ";
            cin >> students[i].course;


        while (true) {
            cout << "Enter new GPA (current: " << students[i].gpa << "): ";
            if (cin >> students[i].gpa) {
                    if (isValid(students[i].gpa)) {
                        break;
                    }
                    cout << "GPA must be between 0.0 and 4.0\n";
                }
            else {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
            }

            cout << "\nStudent updated successfully!\n";
            return;
        }
    }
    cout << "\nStudent not found!\n";
}

void deleteStudent() {
    clearScreen();

    if (studentCount == 0) {
        cout << "No students available to delete.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    string id;
    cout << "Enter Student ID to delete: ";
    cin >> id;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            cout << "\nAre you sure you want to delete " << students[i].first_name
                 << " " << students[i].last_name << "? (y/n): ";
            char confirm;
            cin >> confirm;

            if (confirm == 'y') {
                for (int j = i; j < studentCount - 1; j++) {
                    students[j] = students[j + 1];
                }
                studentCount--;
                cout << "Student deleted successfully!\n";
                cin.clear();
                cin.ignore(1000, '\n');
                return;
            }
            else if (confirm == 'n'){
                cout << "Deletion cancelled.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                return;
            }
            else {
                cout << "Invalid choice. Please select from the choices only.";
                cin.clear();
                cin.ignore(1000, '\n');
                return;
            }

        }
    }
    cout << "\nStudent not found!\n";
    cin.clear();
    cin.ignore(1000, '\n');
    return;
}
void sortbyName(Student arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].last_name > arr[j + 1].last_name) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sortbyGPA(Student arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].gpa < arr[j + 1].gpa) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void viewStudents() {
    clearScreen();

    if (studentCount == 0) {
        cout << "No students available.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    Student tempStudents[MAX_STUDENTS];
    for (int i = 0; i < studentCount; i++) {
        tempStudents[i] = students[i];
    }

    cout << "Sort Options:\n";
    cout << "[1] Alphabetically \n";
    cout << "[2] By GPA \n";
    cout << "Enter your choice: ";

    int option;
    cin >> option;

    switch (option) {
        case 1:
            sortbyName(tempStudents, studentCount);
            break;
        case 2:
            sortbyGPA(tempStudents, studentCount);
            break;
        default:
            cout << "Invalid option.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return;
    }

    cout << "\nSTUDENT RECORDS (" << studentCount << " total)\n";
    cout << "========================================\n";
    for (int i = 0; i < studentCount; i++) {
        cout << "ID: " << tempStudents[i].id << "\n";
        cout << "Name: " << tempStudents[i].first_name << " " << tempStudents[i].last_name << "\n";
        cout << "Course: " << tempStudents[i].course << "\n";
        cout << "GPA: " << tempStudents[i].gpa << "\n";
        if (i < studentCount - 1) cout << "----------------------------------------\n";
    }
    cin.clear();
    cin.ignore(1000, '\n');
}

void displayMenu() {
    clearScreen();

    cout << "[1] Add Student\n";
    cout << "[2] Edit Student\n";
    cout << "[3] Delete Student\n";
    cout << "[4] View All Students\n";
    cout << "[5] Exit\n\n";
    cout << "Enter your choice (1-5): ";
}

int main() {
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                editStudent();
                break;
            case 3:
                deleteStudent();
                break;
            case 4:
                viewStudents();
                break;
            case 5:
                cout << "\nExiting program.\n";
                return 0;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

        cin.clear();
        cin.ignore(1000, '\n');

    } while (true);

    return 0;
}
