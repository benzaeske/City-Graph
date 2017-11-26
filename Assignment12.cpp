#include "Graph.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void printMenu() {
    cout<<"======Main Menu======"<<endl;
    cout<<"1. Print vertices"<<endl;
    cout<<"2. Find districts"<<endl;
    cout<<"3. Find shortest path"<<endl;
    cout<<"4. Quit"<<endl;
}

int main(int argc, char* argv[]) {
    int choice = 0;
    Graph<string> cities;
    char* filename = argv[1];
    ifstream inFile;
    inFile.open(filename);
    // Read in list of city names and create vertices for each:
    string cityNameLine;
    getline(inFile, cityNameLine);
    istringstream ss(cityNameLine);
    string cityName;
    vector<string> names;
    while(getline(ss, cityName, ',')) {
        if(cityName!="cities") {
            cities.addVertex(cityName);
            names.push_back(cityName);
        }
    }
    // Create paths:
    string pathLine;
    int counter1 = 0;
    while(getline(inFile, pathLine)) {
        string weightS;
        int weightI;
        int counter2 = -1;
        istringstream ss2(pathLine);
        while(getline(ss2, weightS, ',')) {
            if(counter2!=-1) {
                stringstream convert(weightS);
                convert>>weightI;
                if(weightI == 0 || weightI == -1) {
                    counter2++;
                    continue;
                }
                else {
                    cities.addEdge(names[counter1], names[counter2], weightI);
                    counter2++;
                }
            }
            else {
                counter2 = 0;
            }
        }
        counter1++;
    }
    while(choice != 4) {
        printMenu();
        cin>>choice;
        if(choice == 1) {
            cities.displayEdges();
        }
        else if(choice == 2) {
            cities.assignDistricts();
        }
        else if(choice == 3) {
            string c1;
            string c2;
            cout<<"Enter a starting city:"<<endl;
            cin.ignore();
            getline(cin, c1);
            cout<<"Enter an ending city:"<<endl;
            getline(cin, c2);
            cities.shortestPath(c1, c2);
        }
        else if(choice == 4) {
            cout<<"Goodbye!"<<endl;
        }
        else {
            printMenu();
        }
    }
};
