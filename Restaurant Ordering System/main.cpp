//LINDOKUHLE NKOS 45275602
#include <iostream>
#include <iomanip>// Used to calculate
#include <string>//Used for string
#include <fstream>// used to read and write on files
#include <limits>// To use numeric_limits<streamsize>::max()

using namespace std;

// Struct for menu
struct MenuItem
{
    string name;
    double price;
};

// Function to display the menu
void displayMenu(MenuItem* menu, int numOfItems)
{
    cout << "\n********MENU*********\n";
    for (int k = 0; k < numOfItems; k++)
    {
        cout << k + 1 << ". " << (*(menu + k)).name  << " R" << fixed << setprecision(2) << (*(menu + k)).price << endl;
    }
    cout << "************************\n";
}

// Function to take customer details
void CustomerDetails(string& customerName)
{
    //Greeting Message
    cout << "Hello. Welcome to @Trendy Tastes I'm going to take your order " << endl;
    cout << "Enter your name and surname: ";
    getline(cin, customerName);
}

// Function to take order
void TakeOrder(MenuItem* menu, int numOfItems, int* order, int& count, double& totalCost) {
    int choice;
    char anotherOrder;
    do {
        displayMenu(menu, numOfItems);
        cout << "Choose an item from (1 to " << numOfItems << "): ";
        cin >> choice;

        if (choice > 0 && choice <= numOfItems)
        {
            *(order + count) = choice - 1;
            totalCost += (*(menu + choice - 1)).price;
            cout << "Added " << (*(menu + choice - 1)).name << " to your order.\n";
            count++;
        }
        else
        {
            cout << "Invalid choice. Please select a valid menu item.\n";
        }
        cout << "Would you like to order another item? (y/n): ";
        cin >> anotherOrder;
        while (cin.fail() || (anotherOrder != 'y' && anotherOrder != 'Y' && anotherOrder != 'n' && anotherOrder != 'N'))
        {
            cin.clear();//// clear input buffer to restore cin to a usable state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');//it avoids potential issues with type mismatches and ensures that you are working within the correct limits for stream operations
            cout << "Invalid choice. Please enter 'y' or 'n': ";
            cin >> anotherOrder;
        }


    }
     while (anotherOrder == 'y' || anotherOrder == 'Y');

    //The user has to choose a payment method
    int paymentMethod;
    cout << "\nTotal Cost: R" << totalCost << endl;
    cout << "Select a payment method:\n";
    cout << "1. Cash\n";
    cout << "2. Card\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> paymentMethod;

    if (paymentMethod == 1)
    {
        cout << "You have chosen to pay with cash.\n";
    }
    else if (paymentMethod == 2)
    {
        cout << "You have chosen to pay with card.\n";
    }
    else
    {
        cout << "Invalid payment method selected. Please choose between 1 (Cash) or 2 (Card).\n";
    }
}

// Function to remove item from the order
void removeItem(MenuItem* menu, int* order, int& count, double& totalCost) {
    if (count == 0)
    {
        cout << "Your order is empty, no items to remove.\n";
        return;
    }

    int removeChoice;
    cout << "These are your current order items:\n";
    for (int i = 0; i < count; i++)
    {
        cout << i + 1 << ". " << (*(menu + *(order + i))).name << " R" << (*(menu + *(order + i))).price << endl;
    }

    cout << "Enter the number of the item you want to remove: ";
    cin >> removeChoice;

    if (removeChoice > 0 && removeChoice <= count)
    {
        // Decrease the total cost by the price of the item being removed
        totalCost -= (*(menu + *(order + removeChoice - 1))).price;
        cout << "Removed " << (*(menu + *(order + removeChoice - 1))).name << " from your order.\n";

        // Shift the remaining elements in the order array
        for (int i = removeChoice - 1; i < count - 1; i++)
        {
            *(order + i) = *(order + i + 1); // Shift elements to the left
        }

        // Reduce the count of items
        count--;
    }
    else
    {
        cout << "Invalid choice. No item removed.\n";
    }
}

// Function to display receipt
void displayReceipt(const string& customerName, MenuItem* menu, int* order, int count, double totalCost) {
    cout << "\n*********@TRENDY TASTES RESTAURANT************\n";
    cout << "Customer: " << customerName << endl;
    cout << "Order Details:\n";
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". " << (*(menu + *(order + i))).name << " R" << fixed << setprecision(2) << (*(menu + *(order + i))).price << endl;
    }
    cout << "************************************************\n";
    cout << "Total: R" << totalCost << endl;
    cout << "================================================\n";
    cout << "Thank you for your purchase @ TRENDY TASTES, " << customerName << "!\n";
}

// Function to read the menu from a file
void readMenu(MenuItem* menu, int& numOfItems)
{
    //step 2: An ifstream object for reading from a file amd opening a file
    ifstream inputFile("Trendy_Tastes.txt");

    //step 3: Check if the file failed to open
    if (inputFile.fail())
    {
        cout << "Error: Could not open file for reading" << endl;
    }

    numOfItems = 0;
    // step 4: Read from the file using a loop until the end of the file
    while (!inputFile.eof() && numOfItems < 5)
    {
        getline(inputFile, (*(menu+numOfItems)).name);
        inputFile >> (*(menu+numOfItems)).price;
        inputFile.ignore();
        numOfItems++;
    }
    //step 5: Close the file
    inputFile.close();
}

// Function to write receipt to a file
void ReceiptToFile(const string& customerName, MenuItem* menu, int* order, int count, double totalCost) {
    ofstream outputFile("Trendy_Tastes.txt"); //Open the text file for writing

    if (!outputFile.is_open())
    {
        cout << "Error: Could not write to file " << endl;
    }
    //step 4: Writing the data to the text file
    outputFile << "\n===== TRENDY TASTES RESTAURANT =====\n";
    outputFile << "Customer: " << customerName << endl;
    outputFile << "Order Details:\n";
    for (int i = 0; i < count; i++)
    {
        outputFile << i + 1 << ". " << (*(menu + *(order + i))).name << " R" << fixed << setprecision(2) << (*(menu + *(order + i))).price << endl;
    }
    outputFile << "--------------------\n";
    outputFile << "Total: R" << totalCost << endl;
    outputFile << "====================\n";
    outputFile << "Thank you for your purchase @ TRENDY TASTES, " << customerName << "!\n";
    //step 5: Close the file
    outputFile.close();
}

int main() {
    const int menuSize = 5;
    MenuItem* menu = new MenuItem[menuSize];
    menu[0] = { "Cold drink", 27.99 };
    menu[1] = { "Pizza", 120.99 };
    menu[2] = { "Fries", 30.99 };
    menu[3] = { "Wings", 45.99 };
    menu[4] = { "Waffles", 60.00 };

    string customerName;
    int order[10];
    int count = 0;
    double totalCost = 0.0;

    // Customer details
    CustomerDetails(customerName);

    // Take order
    TakeOrder(menu, menuSize, order, count, totalCost);

    // Option to remove an item
    char removeOption;
    cout << "Would you like to remove an item? (y/n): ";
    cin >> removeOption;
    if (removeOption == 'y' || removeOption == 'Y')
    {
        removeItem(menu, order, count, totalCost);

    }

    // Display receipt
    displayReceipt(customerName, menu, order, count, totalCost);

    // Save receipt to file
    ReceiptToFile(customerName, menu, order, count, totalCost);

    // Free the dynamically allocated memory
    delete[] menu;

    return 0;
}
