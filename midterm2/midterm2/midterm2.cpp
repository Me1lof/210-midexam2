// Melissa OChoa FLores
// COMSC 210
// Midterm Part 2

#include <iostream>
#include <cstdlib>  
#include <ctime>    
#include <fstream>  
#include <vector>   
#include "DoublyLinkedList.h"


using namespace std;

// Constants for probabilites
const int PROB_SERVE = 40;   
const int PROB_NEW_CUSTOMER = 60; 
const int PROB_LEAVE_END = 20; 
const int PROB_LEAVE_RANDOM = 10; 
const int PROB_VIP = 10;

void loadNames(vector<string>& names);
void simulateCoffeeShop();

int main() {
    srand(static_cast<unsigned int>(time(0))); 
    simulateCoffeeShop(); 
    return 0;
}

void loadNames(vector<string>& names) {
    ifstream inFile("names.txt");
    string name;


    if (!inFile) { // Check if the file opened successfully
        cout << "Error opening names.txt" << endl;
        return; 
    }
   

    while (getline(inFile, name)) {
        names.push_back(name); 
    }

    inFile.close(); // Close the file after reading

    // Check if the names vector is empty
    if (names.empty()) {
        cout << "names.txt is empty." << endl;
    }
}

void simulateCoffeeShop() {
    DoublyLinkedList line; // Create a new doubly linked list to represent the line
    vector<string> names; 
    loadNames(names); 

    // Check is there are names loaded before starting simulation
    if (names.empty()) {
        cout << "No customer names found. Simulation cannot proceed." << endl;
        return; // Exit the simulation if there are no names loaded
    }

    cout << "Store opens:" << endl;

    // Initial customers joining the line
    for (int i = 0; i < 5; i++) {
        int randomIndex = rand() % names.size(); // Pick a random name
        string customerName = names[randomIndex];
        line.push_back(customerName); // Add customer to the line
        cout << "    " << customerName << " joined the line" << endl;
    }

    line.print();


    for (int timeStep = 1; timeStep <= 20; timeStep++) {
        cout << "Time step #" << timeStep << ":" << endl;
        // Check if a customer can be served
        if (rand() % 100 < PROB_SERVE && line.getHead() != nullptr) {
            string servedCustomer = line.getHead()->data; // Get the customer at the front
            cout << "    " << servedCustomer << " is served" << endl;
            line.pop_front();
        }


        // Check for a new customer joining the line
        if (rand() % 100 < PROB_NEW_CUSTOMER) {
            int randomIndex = rand() % names.size();
            string newCustomer = names[randomIndex];
            line.push_back(newCustomer);
            cout << "    " << newCustomer << " joined the line" << endl;
        }


        // Check if the last customer leaves
        if (rand() % 100 < PROB_LEAVE_END && line.getTail() != nullptr) {
            string leavingCustomer = line.getTail()->data;
            cout << "    " << leavingCustomer << " (at the rear) left the line" << endl;
            line.pop_back(); 
        }


        // Check if any random customer leaves
        if (rand() % 100 < PROB_LEAVE_RANDOM && line.getHead() != nullptr) {
            int randomIndex = rand() % line.size(); 
            line.delete_pos(randomIndex); 
        }

        // Check if a VIP joins the front
        if (rand() % 100 < PROB_VIP) {
            int randomIndex = rand() % names.size();
            string vipCustomer = names[randomIndex];
            cout << "    " << vipCustomer << " (VIP) joins the front of the line" << endl;
            line.push_front(vipCustomer); // Add VIP customer to the front
        }

        
        line.print();
    }
}