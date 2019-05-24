#ifndef FloydClass_h
#define FloydClass_h

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include "listTemplate.h"

using namespace std;

const int MAX = 100000;

class Floyd {
private:
    map<string, size_t > codes; //Helps to get each city number in matrix
    map<size_t, string> reverseCodes; // Helps to get city by it's number in matrix
    MyList<MyList<string> > wayOut; //Matrix, which stores shortest ways
    map<string, map<string, size_t > > dataMap; //Stores the adjacency list
    MyList<MyList<size_t> > matrix; //Stores the adjacency matrix
    void findingCheapestWay(); //Finding the cheapest ways
public:
    Floyd() {
    }
    Floyd(ifstream &inputText); //Constructor for input
    size_t getShortestPath(string firstCity, string secondCity); //Finding the shortest path from one city to another
};

Floyd::Floyd(ifstream &inputText) {
    setlocale(LC_ALL, "rus");
    char buff[100];
    size_t position = 0;
    while (!inputText.eof()) //Reading file until we reach it's end
    {
        string firstCity = "", secondCity = "";
        string firstPrice = "", secondPrice = "";
        size_t firstPriceInt = MAX, secondPriceInt = MAX;
        size_t counter = 0;
        for (size_t i = 0; i < 100; i++) { //Counting amount of ; in our text
            buff[i] = '\0';
        }
        inputText >> buff;
        for (size_t i = 0; i < 100; i++) { //Counting amount of ; in our text
            if (buff[i] == ';'){
                counter++;
            }
        }
        if (counter != 3) { //If amount of ; is incorrect, throw exception
            throw invalid_argument("Wrong type of input");
        }
        size_t i = 0;
        while (buff[i] != ';') { //Reading the first city
            firstCity += buff[i];
            i++;
        }
        if (codes.find(firstCity) == codes.end()) { //If it's a new city adding it to our codes map
            reverseCodes[position] = firstCity;
            codes[firstCity] = position++;
        }
        i++;
        while (buff[i] != ';') { //Reading the second city
            secondCity += buff[i];
            i++;
        }
        if (codes.find(secondCity) == codes.end()) { //If it's a new city adding it to our codes map
            reverseCodes[position] = secondCity;
            codes[secondCity] = position++;

        }
        i++;
        while (buff[i] != ';') { //Reading the price of first flight
            firstPrice += buff[i];
            i++;
        }
        i++;
        if (firstPrice != "N/A") {
            try {
                firstPriceInt = stoi(firstPrice);
            }
            catch (invalid_argument& e) { //If price is incorrect throw exception
                throw invalid_argument("Wrong type of input");
            }
        }
        while (buff[i] != '\0') { //Reading the price of first flight
            secondPrice += buff[i];
            i++;
        }
        if (secondPrice != "N/A") {
            try {
                secondPriceInt = stoi(secondPrice);
            }
            catch (invalid_argument& e) { //If price is incorrect throw exception
                throw invalid_argument("Wrong type of input");
            }
        }
     //Forming adjacency list
        dataMap[firstCity][secondCity] = firstPriceInt;
        dataMap[secondCity][firstCity] = secondPriceInt;
    }
    for (size_t i = 0; i < codes.size(); i++) { //Creating the basics of matrix
        MyList<size_t > *newRow = new MyList<size_t>;
        for (size_t j = 0; j < codes.size(); j++) {
            newRow->push_back(MAX);
        }
        matrix.push_back(*newRow);
    }
    //Filling the matrix
    for (map<string, size_t >::iterator i = codes.begin(); i != codes.end(); ++i) {
        for (map<string, size_t>::iterator j = dataMap[i->first].begin(); j != dataMap[i->first].end(); ++j) {
            matrix[codes[i->first]][codes[j->first]] = j->second;
        }
    }
    inputText.close();
    findingCheapestWay();
}

void Floyd::findingCheapestWay() {
    //Creating the path matrix
    for (size_t i = 0; i < matrix.get_size(); i++) {
        MyList<string > *newRow = new MyList<string>;
        for (size_t j = 0; j < matrix.get_size(); j++)
        {
            newRow->push_back(reverseCodes[j]);
        }
        wayOut.push_back(*newRow);
    }
    //Going through all of the elements to find the ceapest price
    for (size_t k = 0; k < matrix.get_size(); k++) {
        for (size_t i = 0; i < matrix.get_size(); i++) {
            for (size_t j = 0; j < matrix.get_size(); j++) {
                if (matrix[i][j] > (matrix[i][k] + matrix[k][j])) { //If found cheaper
                    if (i != j) {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];  //Insert new value to matrix
                        wayOut[i][j] = wayOut[i][k]; //Insert new path
                    }
                }
            }
        }
    }
}

size_t Floyd::getShortestPath(string firstCity, string secondCity)
{
    setlocale(LC_ALL, "rus");
    //Checking if the given cities exist
    if (codes.find(firstCity) == codes.end() || codes.find(secondCity) == codes.end() ) {
        throw invalid_argument("There is no such cities");
    }
    //Checking if the path exist
    if (matrix[codes[firstCity]][codes[secondCity]] == MAX || firstCity == secondCity) {
        cout << "There is no such way" << endl;
        return 0;
    }
    else {
        string helpCity = firstCity;
        //Going through path matrix from firstCity to the secondCity
        while (helpCity != secondCity) {
            cout << helpCity << " => ";
            helpCity = wayOut[codes[helpCity]][codes[secondCity]];
        }
        cout << secondCity << endl;
    }
    cout << "Flight costs: " << matrix[codes[firstCity]][codes[secondCity]] << endl;
    return (matrix[codes[firstCity]][codes[secondCity]]);
}


#endif /* FloydClass_h */
