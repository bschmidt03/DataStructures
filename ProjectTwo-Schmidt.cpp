#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Course structure to hold course number, title, and prerequisites
struct Course {
    string number;
    string title;
    vector<string> prerequisites;
};

// Node structure for binary search tree
struct Node {
    Course course;
    Node* left;
    Node* right;
    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class CourseBST {
private:
    Node* root;

    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->course.number << ", " << node->course.title << endl;
        inOrder(node->right);
    }

    void printCourse(Node* node, string courseNumber) {
        if (node == nullptr) return;
        if (courseNumber == node->course.number) {
            cout << node->course.number << ", " << node->course.title << endl;
            if (node->course.prerequisites.empty()) {
                cout << "Prerequisites: None" << endl;
            }
            else {
                cout << "Prerequisites: ";
                for (size_t i = 0; i < node->course.prerequisites.size(); ++i) {
                    cout << node->course.prerequisites[i];
                    if (i != node->course.prerequisites.size() - 1) cout << ", ";
                }
                cout << endl;
            }
        }
        else if (courseNumber < node->course.number) {
            printCourse(node->left, courseNumber);
        }
        else {
            printCourse(node->right, courseNumber);
        }
    }

    void insert(Node*& node, Course course) {
        if (node == nullptr) {
            node = new Node(course);
        }
        else if (course.number < node->course.number) {
            insert(node->left, course);
        }
        else {
            insert(node->right, course);
        }
    }

public:
    CourseBST() : root(nullptr) {}

    void insert(Course course) {
        insert(root, course);
    }

    void printAllCourses() {
        cout << "Here is a sample schedule:" << endl;
        inOrder(root);
    }

    void printCourseInfo(string courseNumber) {
        printCourse(root, courseNumber);
    }
};

// Split string by delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Load course data from file into BST
void loadDataFromFile(CourseBST& bst) {
    ifstream file("CS_300_ABCU_Advising_Program_Input.csv");

    string line;

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        if (tokens.size() < 2) continue;

        Course course;
        course.number = tokens[0];
        course.title = tokens[1];
        for (size_t i = 2; i < tokens.size(); ++i) {
            course.prerequisites.push_back(tokens[i]);
        }

        bst.insert(course);
    }

    file.close();
}

int main() {
    CourseBST bst;
    int choice = 0;
    bool loaded = false;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            loadDataFromFile(bst);
            loaded = true;
            break;
        case 2:
            if (loaded) {
                bst.printAllCourses();
            }
            else {
                cout << "Please load data first." << endl;
            }
            break;
        case 3:
            if (loaded) {
                cout << "What course do you want to know about? ";
                string courseNum;
                cin >> courseNum;
                transform(courseNum.begin(), courseNum.end(), courseNum.begin(), ::toupper);
                bst.printCourseInfo(courseNum);
            }
            else {
                cout << "Please load data first." << endl;
            }
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }

    return 0;
}
