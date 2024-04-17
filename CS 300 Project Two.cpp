//Name: Logan Martha
//Data Structure Used: Binary Tree
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;


// Define structure to hold course information
struct Course {
    string courseID;
    string title;
    vector<string> prereqs;
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Default Constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Initialze w/ a course
    Node(Course aCourse) :
        Node() {
            course = aCourse;
        }
};
// BST Tree Class containing methods
class BinarySearchTree {
private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);

public:
    BinarySearchTree();
    Course Search(string courseID);
    void Insert(Course course);
    void InOrder();

};

// Default Constructor
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

// Search Course
Course BinarySearchTree::Search(string CourseID) {
    Node* cur = root;
    while (cur != nullptr) {
        if (cur->course.courseID == CourseID) {
            return cur->course;
        }
        else if (cur->course.courseID > CourseID) {
            cur = cur->left;
        }
        else {
            cur = cur->right;
        }
    }
    Course course;
    return course;
}

// Insert a Course
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        this->addNode(root, course);
    }
}

// Traverse Tree in Order
void BinarySearchTree::InOrder() {
    inOrder(root);
}


// Add Course to BST
void BinarySearchTree::addNode(Node* node, Course course) {
    // IF current node greater than node to be inserted go left branch
    if (node->course.courseID > course.courseID) {
        // IF left branch node null, insert
        if (node->left == nullptr) {
            node->left = new Node(course);
            return;
        }
        // Else recurse down left side
        else {
            this->addNode(node->left, course);
        }
    }
    // Else if current node is less than to be insert, we go right branch
    else {
        // If right branch null, insert
        if (node->right == nullptr) {
            node->right = new Node(course);
            return;
        }
        // Else recurse down right side
        else {
            this->addNode(node->right, course);
        }
    }
}
// OutPut courses in alphanumeric order
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout  << node->course.courseID << ", " << node->course.title << endl;
        inOrder(node->right);
    }
}

// TODO
void loadCourses(string file, BinarySearchTree* bst) {
    ifstream  inputFile(file);

    if (!inputFile) {
        cout << "Failed to open file." << endl;
        return;
    }
    string line;
    while (getline(inputFile, line)) {
        // Parsing string into vector
        istringstream iss(line);
        vector<string> tokens;
        string token;

        while (getline(iss, token, ',')) {
            tokens.push_back(token);
        }
        // Course meets requiremnets
        if (tokens.size() < 2) {
            cout << "Invlaid Data" << endl;
            return;
        }
        // Meets requirments - Add new course
        else if (tokens.size() >= 2) {
            Course course;
            course.courseID = tokens.at(0);
            course.title = tokens.at(1);
            // If course has prereqs, add them to prereqs vector
            if (tokens.size() > 2) {
                for (int i = 2; i < tokens.size(); ++i) {
                    course.prereqs.push_back(tokens.at(i));
                }
            }
            bst->Insert(course);
        }
    }
    cout << "All Data Loaded Successfully!" << endl;
    
}

int main() {
    // Define Tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;
    string courseSearch;

    string file = "Courses.txt";

    int choice = 0;
    while (choice != 4) {
        cout << "Menu:" << endl;
        cout << "1. Load Courses" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Search Course" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;


        switch (choice) {
        case 1:
            loadCourses(file, bst);
            break;
        case 2:
            bst->InOrder();
            break;
        case 3:
            cout << "Enter Course ID to Search: ";
            cin >> courseSearch;
            transform(courseSearch.begin(), courseSearch.end(), courseSearch.begin(), ::toupper);
            course = bst->Search(courseSearch);

            // Print Searched Bid
            if (!course.courseID.empty()) {
                cout << course.courseID << ", " << course.title << endl;
                cout << "Pretrequisites: ";
                for (int i = 0; i < course.prereqs.size(); ++i) {
                    cout << course.prereqs.at(i);
                    if (course.prereqs.at(i) != course.prereqs.back()) {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
            else {
                cout << "Bid " << courseSearch << " Not Found." << endl;
            }
            break;
        }
        // If invalid option, error messaged outputed.
        if (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
            cout << choice << " is not a valid option." << endl;
        }
    }
    cout << "Thank you for using the course planner!" << endl;
    return 0;
}
 

