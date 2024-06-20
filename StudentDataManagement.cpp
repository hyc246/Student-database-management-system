#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string regNo;
    string name;
    string mark1;
    string mark2;
    string proctorID;
};

vector<Student> readDatabase(const string& filename) {
    ifstream infile(filename);
    vector<Student> students;
    string regNo, name, mark1, mark2, proctorID;

    while (infile >> regNo >> name >> mark1 >> mark2 >> proctorID) {
        students.push_back({regNo, name, mark1, mark2, proctorID});
    }
    return students;
}

void writeDatabase(const string& filename, const vector<Student>& students) {
    ofstream outfile(filename);
    for (const auto& student : students) {
        outfile << student.regNo << "\t"
                << student.name << "\t"
                << student.mark1 << "\t"
                << student.mark2 << "\t"
                << student.proctorID << "\n";
    }
}

void addNewStudents(vector<Student>& students) {
    int n;
    cout << "Enter the number of students: \n";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        Student student;
        cout << "Enter your registration number: \n";
        cin >> student.regNo;
        cout << "Enter your name: \n";
        cin >> student.name;
        student.name.resize(15, ' ');
        student.mark1 = "00";
        student.mark2 = "00";
        cout << "Enter your proctor ID: \n";
        cin >> student.proctorID;
        students.push_back(student);
    }
    cout << "Students added successfully.\n";
}

void studentLogin(const vector<Student>& students) {
    string regNo;
    cout << "Enter your registration number: \n";
    cin >> regNo;

    bool found = false;
    for (const auto& student : students) {
        if (student.regNo == regNo) {
            cout << "\nRegistration Number: " << student.regNo << '\n'
                 << "Name: " << student.name << '\n'
                 << "CSE1001 mark: " << student.mark1 << '\n'
                 << "CSE1002 mark: " << student.mark2 << '\n'
                 << "Proctor ID: " << student.proctorID << '\n';
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No such registration number found!\n";
    }
}

void facultyLogin(vector<Student>& students) {
    string subcode;
    cout << "Enter your subject code: \n";
    cin >> subcode;

    if (subcode != "CSE1001" && subcode != "CSE1002") {
        cout << "No such subject code found!\n";
        return;
    }

    int option;
    cout << "\nAvailable operations: \n1. Add data about marks\n2. View data\nEnter option: \n";
    cin >> option;

    if (option == 1) {
        cout << "Warning! You need to add mark details for all students!\n";
        for (auto& student : students) {
            cout << "Enter the mark of student " << student.regNo << " : \n";
            string mark;
            cin >> mark;
            if (subcode == "CSE1001") {
                student.mark1 = mark;
            } else if (subcode == "CSE1002") {
                student.mark2 = mark;
            }
        }
        cout << "Marks added successfully.\n";
    } else if (option == 2) {
        cout << "Registration number - Marks\n";
        for (const auto& student : students) {
            cout << student.regNo << " - "
                 << (subcode == "CSE1001" ? student.mark1 : student.mark2) << '\n';
        }
    } else {
        cout << "Invalid option!\n";
    }
}

void proctorLogin(const vector<Student>& students) {
    string procID;
    cout << "Enter your proctor ID: \n";
    cin >> procID;

    bool found = false;
    for (const auto& student : students) {
        if (student.proctorID == procID) {
            cout << "\nRegistration Number: " << student.regNo << '\n'
                 << "Name: " << student.name << '\n'
                 << "CSE1001 mark: " << student.mark1 << '\n'
                 << "CSE1002 mark: " << student.mark2 << '\n';
            found = true;
        }
    }

    if (!found) {
        cout << "No such proctor ID found!\n";
    }
}

void adminView(const vector<Student>& students) {
    string password;
    cout << "Enter the admin password: \n";
    cin >> password;

    string admin_pass = "admin";

    if (password == admin_pass) {
        cout << "Reg No.\tName\tCSE1001\tCSE1002\tProctor ID\n";
        for (const auto& student : students) {
            cout << student.regNo << '\t'
                 << student.name << '\t'
                 << student.mark1 << '\t'
                 << student.mark2 << '\t'
                 << student.proctorID << '\n';
        }
    } else {
        cout << "Incorrect password!\n";
    }
}

int main() {
    string filename = "Example.txt";
    vector<Student> students = readDatabase(filename);

    int option = 0;
    while (option != 6) {
        cout << "\nAvailable operations: \n1. Add New Students\n2. Student Login\n3. Faculty Login\n4. Proctor Login\n5. Admin View\n6. Exit\nEnter option: \n";
        cin >> option;

        switch (option) {
            case 1:
                addNewStudents(students);
                writeDatabase(filename, students);
                break;
            case 2:
                studentLogin(students);
                break;
            case 3:
                facultyLogin(students);
                writeDatabase(filename, students);
                break;
            case 4:
                proctorLogin(students);
                break;
            case 5:
                adminView(students);
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid option!\n";
                break;
        }
    }

    return 0;
}
