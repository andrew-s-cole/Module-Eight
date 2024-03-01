#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

// Class for item tracking
class ItemTracker {
private:
    map<string, int> frequencyMap;

public:
    // Function to read input file and populate frequency map
    void readInputFile(const string& filename) {
        // Read input file and populate frequency map
        ifstream file(filename);
        if (file.is_open()) {
            string item;
            while (file >> item) {
                frequencyMap[item]++;
            }
            file.close();
        } else {
            cout << "Error: Unable to open file: " << filename << endl;
            // Terminate the program if the file cannot be opened
            exit(1);
        }
    }

    // Function to backup item frequencies to a file
    void backupData(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& pair : frequencyMap) {
                outFile << pair.first << " " << pair.second << endl;
            }
            outFile.close();
            cout << "Data successfully backed up to " << filename << endl;
        } else {
            cout << "Error: Unable to create backup file: " << filename << endl;
        }
    }

    // Function to print frequency of specific items
    void printItemFrequency(const string& items) {
        istringstream iss(items);
        string item;
        while (iss >> item) {
            if (frequencyMap.find(item) != frequencyMap.end()) {
                cout << item << " " << frequencyMap[item] << endl;
            } else {
                cout << "Item '" << item << "' not found.\n";
            }
        }
    }

    // Function to print list with frequencies of all items
    void printAllItemsFrequency() {
        for (const auto& pair : frequencyMap) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Function to print histogram of item frequencies
    void printHistogram() {
        for (const auto& pair : frequencyMap) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

int main() {
    ItemTracker tracker;
    tracker.readInputFile("CS210_Project_Three_Input_File.txt");

    int choice;
    do {
        cout << "Menu:\n"
             << "1. Look up item frequency\n"
             << "2. Print list of all item frequencies\n"
             << "3. Print histogram of item frequencies\n"
             << "4. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        // Check if input is valid
        if (cin.fail()) {
            // Clear input buffer and ignore invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                string items;
                cin.ignore(); // Clear input buffer
                cout << "Enter items separated by spaces: ";
                getline(cin, items);

                // Check if input is empty
                if (items.empty()) {
                    cout << "Error: Input cannot be empty.\n";
                    continue;
                }

                tracker.printItemFrequency(items);
                break;
            }
            case 2:
                tracker.printAllItemsFrequency();
                break;
            case 3:
                tracker.printHistogram();
                break;
            case 4:
                tracker.backupData("frequency.dat");
                cout << "Exiting program, have a great day!\n";
                break;
            default:
                cout << "Error: Invalid choice. Please enter a number between 1 and 4.\n";
        }
    } while (choice != 4);

    return 0;
}
