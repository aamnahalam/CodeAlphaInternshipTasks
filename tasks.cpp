#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

const int MAX_BORROW = 2;
const double FINE_PER_DAY = 10;
const double DAMAGE_FEE = 50;

string getCurrentDate() {
    time_t now = time(0);
    string dt = ctime(&now);
    return dt;
}

// ================= RESOURCE CLASS =================
class Resource {
public:
    int id;
    string title;
    string author;
    string category;
    bool available;
    bool reserved;

    Resource(int i, string t, string a, string c) {
        id = i;
        title = t;
        author = a;
        category = c;
        available = true;
        reserved = false;
    }

    void display() {
        cout << "ID: " << id << "\nTitle: " << title
             << "\nAuthor: " << author
             << "\nCategory: " << category
             << "\nAvailable: " << (available ? "Yes" : "No")
             << "\n----------------------\n";
    }
};

// ================= BORROW HISTORY =================
class BorrowHistory {
public:
    int resourceID;
    string issueDate;
    string dueDate;
    bool returned;

    BorrowHistory(int id) {
        resourceID = id;
        issueDate = getCurrentDate();
        dueDate = "After 7 days";  // Simplified
        returned = false;
    }
};

// ================= USER CLASS =================
class User {
public:
    string username, password;
    string firstName, lastName, address;
    double balance;
    int membershipLevel;  // 1 = Normal, 2 = Gold
    int donationCount;

    vector<BorrowHistory> history;
    int currentBorrows;

    User(string u, string p, string f, string l, string addr) {
        username = u;
        password = p;
        firstName = f;
        lastName = l;
        address = addr;
        balance = 500;
        membershipLevel = 1;
        donationCount = 0;
        currentBorrows = 0;
    }

    void borrowResource(Resource &r) {
        if (currentBorrows >= MAX_BORROW) {
            cout << "Borrow limit reached!\n";
            return;
        }
        if (!r.available) {
            cout << "Resource not available.\n";
            return;
        }

        history.push_back(BorrowHistory(r.id));
        r.available = false;
        currentBorrows++;
        cout << "Resource borrowed successfully!\n";
    }

    void returnResource(Resource &r, bool damaged = false, bool late = false) {
        r.available = true;
        currentBorrows--;

        if (late) {
            balance -= FINE_PER_DAY;
            cout << "Late fine deducted!\n";
        }

        if (damaged) {
            balance -= DAMAGE_FEE;
            cout << "Damage fee deducted!\n";
        }

        cout << "Returned successfully!\n";
    }

    void donateBooks(int qty) {
        donationCount += qty;
        if (donationCount >= 5) {
            membershipLevel = 2;
            cout << "Upgraded to GOLD membership!\n";
        }
    }

    void viewHistory() {
        for (auto &h : history) {
            cout << "Resource ID: " << h.resourceID
                 << "\nIssue Date: " << h.issueDate
                 << "\nDue Date: " << h.dueDate
                 << "\n------------------\n";
        }
    }
};

// ================= ADMIN CLASS =================
class Admin {
public:
    string username = "admin";
    string password = "admin123";

    void reportUsers(vector<User> &users) {
        for (auto &u : users) {
            cout << "Username: " << u.username
                 << "\nBalance: " << u.balance
                 << "\nCurrent Borrows: " << u.currentBorrows
                 << "\n---------------------\n";
        }
    }

    void reportResources(vector<Resource> &resources) {
        for (auto &r : resources) {
            if (!r.available)
                r.display();
        }
    }
};

// ================= MAIN SYSTEM =================
int main() {
    vector<Resource> resources;
    vector<User> users;
    Admin admin;

    resources.push_back(Resource(1, "C++ Basics", "Bjarne", "Education"));
    resources.push_back(Resource(2, "AI Future", "John Smith", "Technology"));
    resources.push_back(Resource(3, "Poetry Book", "Ali Raza", "Literature"));

    int choice;

    while (true) {
        cout << "\n1. Register\n2. Login\n3. Admin Login\n4. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            string u, p, f, l, a;
            cout << "Username: "; cin >> u;
            cout << "Password: "; cin >> p;
            cout << "First Name: "; cin >> f;
            cout << "Last Name: "; cin >> l;
            cout << "Address: "; cin >> a;

            users.push_back(User(u, p, f, l, a));
            cout << "Account created!\n";
        }

        else if (choice == 2) {
            string u, p;
            cout << "Username: "; cin >> u;
            cout << "Password: "; cin >> p;

            bool found = false;
            for (auto &user : users) {
                if (user.username == u && user.password == p) {
                    found = true;
                    int op;

                    while (true) {
                        cout << "\n1. View Available Resources\n2. Borrow\n3. Return\n4. View History\n5. Donate Books\n6. Logout\nChoice: ";
                        cin >> op;

                        if (op == 1) {
                            for (auto &r : resources)
                                if (r.available)
                                    r.display();
                        }
                        else if (op == 2) {
                            int id;
                            cout << "Enter Resource ID: ";
                            cin >> id;
                            for (auto &r : resources)
                                if (r.id == id)
                                    user.borrowResource(r);
                        }
                        else if (op == 3) {
                            int id;
                            cout << "Enter Resource ID: ";
                            cin >> id;
                            bool damaged, late;
                            cout << "Damaged? (1/0): ";
                            cin >> damaged;
                            cout << "Late? (1/0): ";
                            cin >> late;
                            for (auto &r : resources)
                                if (r.id == id)
                                    user.returnResource(r, damaged, late);
                        }
                        else if (op == 4)
                            user.viewHistory();
                        else if (op == 5) {
                            int qty;
                            cout << "How many books donated? ";
                            cin >> qty;
                            user.donateBooks(qty);
                        }
                        else break;
                    }
                }
            }
            if  (!found)
                cout << "Invalid login.\n";
        }

        else if (choice == 3) {
            string u, p;
            cout << "Admin Username: "; cin >> u;
            cout << "Password: "; cin >> p;

            if (u == admin.username && p == admin.password) {
                int op;
                while (true) {
                    cout << "\n1. Report Users\n2. Report Issued Resources\n3. Add Resource\n4. Logout\nChoice: ";
                    cin >> op;

                    if (op == 1)
                        admin.reportUsers(users);
                    else if (op == 2)
                        admin.reportResources(resources);
                    else if (op == 3) {
                        int id;
                        string t, a, c;
                        cout << "ID: "; cin >> id;
                        cout << "Title: "; cin >> t;
                        cout << "Author: "; cin >> a;
                        cout << "Category: "; cin >> c;
                        resources.push_back(Resource(id, t, a, c));
                        cout << "Resource added!\n";
                    }
                    else break;
                }
            }
            else
                cout << "Invalid admin login.\n";
        }

        else break;
    }

    return 0;
} 