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
   
    while (getline(inFile, name)) {
        names.push_back(name); 
    }

    inFile.close(); // Close the file after reading
}

void simulateCoffeeShop() {
    DoublyLinkedList line; // Create a new doubly linked list to represent the line
    vector<string> names; 
    loadNames(names); 

    cout << "Store opens:" << endl;