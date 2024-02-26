#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>

using namespace std;

class DataHandler {
private:
    map<string, int> itemFrequency;

    void saveDataToFile() {
        ofstream outputFile("frequency.dat");
        if (!outputFile.is_open()) {
            cerr << "Error opening output file." << endl;
            exit(1);
        }

        for (const auto& pair : itemFrequency) {
            outputFile << pair.first << " " << pair.second << endl;
        }

        outputFile.close();
        cout << "Data saved to 'frequency.dat'." << endl;
    }

public:
    void readDataFromFile() {
        ifstream inputFile("food.txt");
        if (!inputFile.is_open()) {
            cerr << "Error opening input file." << endl;
            exit(1);
        }

        string item;
        while (inputFile >> item) {
            itemFrequency[item]++;
        }

        inputFile.close();

        if (itemFrequency.empty()) {
            cout << "No data read from the file." << endl;
        }
    }

    void findFrequency(const string& searchItem) {
        if (itemFrequency.find(searchItem) != itemFrequency.end()) {
            cout << "Frequency of " << searchItem << ": " << itemFrequency[searchItem] << endl;
        }
        else {
            cout << "Item not found in the list." << endl;
        }
    }

    void printItemList() {
        cout << "LIST OF ITEMS WITH FREQUENCIES:" << endl;
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    void printHistogram() {
        cout << "HISTOGRAM OF ITEM FREQUENCIES:" << endl;
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }

    void saveDataToFileAndExit() {
        saveDataToFile();
        cout << "Exiting the program." << endl;
    }
};

void displayMenu() {
    cout << "\nMENU OPTIONS:" << endl;
    cout << "1. Find the frequency of a specific word." << endl;
    cout << "2. Print the list of items with their frequencies." << endl;
    cout << "3. Print a histogram of item frequencies." << endl;
    cout << "4. Save data to 'frequency.dat' and exit." << endl;
    cout << "Enter your choice (1-4): ";
}

int getValidIntegerInput() {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail() || input < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 4: ";
        }
        else {
            break;
        }
    }
    return input;
}

int main() {
    DataHandler dataHandler;
    dataHandler.readDataFromFile();

    int choice;
    bool shouldExit = false;

    do {
        displayMenu();
        choice = getValidIntegerInput();

        switch (choice) {
        case 1: {
            string searchItem;
            cout << "Enter the item to look for: ";
            cin >> searchItem;
            dataHandler.findFrequency(searchItem);
            break;
        }

        case 2: {
            dataHandler.printItemList();
            break;
        }

        case 3: {
            dataHandler.printHistogram();
            break;
        }

        case 4: {
            dataHandler.saveDataToFileAndExit();
            shouldExit = true;
            break;
        }

        default:
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
        }

    } while (!shouldExit);

    cin.get();
    return 0;
}
