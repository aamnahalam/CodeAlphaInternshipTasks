#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to check if username already exists
bool userExists(const string &username) {
    ifstream checkFile(username + ".txt");
    return checkFile.good(); // returns true if file exists
}

// Function to register a new user
void registerUser() {
    string username, password, confirmPassword;

    cout << "\n--- User Registration ---\n";
    cout << "Enter a username: ";
    cin >> username;

    // Check for duplicate username
    if (userExists(username)) {
        cout << "Username already exists! Please try a different one.\n";
        return;
    }

    cout << "Enter a password: ";
    cin >> password;
    cout << "Confirm password: ";
    cin >> confirmPassword;

    if (password != confirmPassword) {
        cout << "Passwords do not match! Registration failed.\n";
        return;
    }

    // Save credentials to a file named username.txt
    ofstream outFile(username + ".txt");
    if (!outFile) {
        cout << "Error creating user file!\n";
        return;
    }
    outFile << password;
    outFile.close();

    cout << "Registration successful! You can now login.\n";
}

// Function to login a user
void loginUser() {
    string username, password;

    cout << "\n--- User Login ---\n";
    cout << "Enter username: ";
    cin >> username;

    // Check if user exists
    if (!userExists(username)) {
        cout << "User not found! Please register first.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Read password from file
    ifstream inFile(username + ".txt");
    string storedPassword;
    inFile >> storedPassword;
    inFile.close();

    // Verify password
    if (password == storedPassword) {
        cout << "Login successful! Welcome, " << username << "!\n";
    } else {
        cout << "Incorrect password! Try again.\n";
    }
}

// Main menu loop
int main() {
    int choice;
    bool running = true;

    cout << "=== Welcome to the Login & Registration System ===\n";

    while (running) {
        cout << "\nMenu:\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting program. Goodbye!\n";
                running = false;
                break;
            default:
                cout << "Invalid choice! Please enter 1, 2, or 3.\n";
        }
    }

    return 0;
}