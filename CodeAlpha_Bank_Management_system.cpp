#include <iostream>
#include <string>
using namespace std;

//------------------------------------
// Transaction Class
//------------------------------------
class Transaction {
public:
    string type;
    double amount;

    Transaction() {
        type = "None";
        amount = 0.0;
    }

    Transaction(string t, double a) {
        type = t;
        amount = a;
    }

    void show() {
        cout << "Transaction: " << type
             << " | Amount: " << amount << endl;
    }
};

//------------------------------------
// Customer Class
//------------------------------------
class Customer {
public:
    int customerID;
    string name;

    Customer() {
        customerID = 0;
        name = "Unknown";
    }

    Customer(int id, string n) {
        customerID = id;
        name = n;
    }

    void show() {
        cout << "Customer ID: " << customerID << endl;
        cout << "Customer Name: " << name << endl;
    }
};

//------------------------------------
// Account Class
//------------------------------------
class Account {
private:
    int accountNumber;
    double balance;
    Customer customer;
    Transaction transactions[10];
    int transactionCount;

public:
    Account() {
        accountNumber = 0;
        balance = 0.0;
        transactionCount = 0;
    }

    Account(int accNo, Customer c) {
        accountNumber = accNo;
        customer = c;
        balance = 0.0;
        transactionCount = 0;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    double getBalance() {
        return balance;
    }

    // Deposit
    void deposit(double amount) {
        balance += amount;
        transactions[transactionCount++] = Transaction("Deposit", amount);
    }

    // Withdraw
    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transactions[transactionCount++] = Transaction("Withdraw", amount);
        } else {
            cout << "Insufficient Balance!" << endl;
        }
    }

    // Transfer
    void transfer(Account &receiver, double amount) {
        if (amount <= balance) {
            balance -= amount;
            receiver.balance += amount;

            transactions[transactionCount++] =
                Transaction("Transfer Sent", amount);

            receiver.transactions[receiver.transactionCount++] =
                Transaction("Transfer Received", amount);
        } else {
            cout << "Insufficient Balance for Transfer!" << endl;
        }
    }

    // Show Transactions
    void showTransactions() {
        cout << "Transaction History:" << endl;
        for (int i = 0; i < transactionCount; i++) {
            transactions[i].show();
        }
    }

    // Show Account Info
    void showAccountInfo() {
        customer.show();
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
    }
};

//------------------------------------
// Main Function
//------------------------------------
int main() {

    // Create Customers
    Customer c1(101, "Ahmed");
    Customer c2(102, "Khan");

    // Create Accounts
    Account acc1(1001, c1);
    Account acc2(1002, c2);

    // Perform Operations
    acc1.deposit(5000);
    acc1.withdraw(1500);
    acc1.transfer(acc2, 2000);

    // Display Account Information
    cout << "\n--- Account 1 Details ---" << endl;
    acc1.showAccountInfo();
    acc1.showTransactions();

    cout << "\n--- Account 2 Details ---" << endl;
    acc2.showAccountInfo();
    acc2.showTransactions();

    return 0;
}
