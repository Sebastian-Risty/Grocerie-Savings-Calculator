//
// Name: Sebastian Risty
// Date: 10/5/2020
// Filename: hw3.cpp
// Description: program to get total amount saved when purchasing from hyvee vs amazon
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    //create file streams
    ifstream priceList("priceList.txt");
    ifstream shoppingList("shoppingList.txt");
    ofstream inSavingsList("savings.txt");
    //check for errors when opening streams
    if (priceList.fail()) {
        cerr << "Failed to open priceList.txt" << endl;
        return -1;
    }
    if (shoppingList.fail()) {
        cerr << "Failed to open shoppingList.txt" << endl;
        return -1;
    }
    if (inSavingsList.fail()) {
        cerr << "Failed to open savings.txt" << endl;
        return -1;
    }
    //begin by getting number of items in shopping list
    int numShoppingItems;
    shoppingList >> numShoppingItems;
    //loop through number of items on shopping list
    for (int i = 0; i < numShoppingItems; i++) {
        string shoppingListItemName;
        int shoppingListNumItems;
        shoppingList >> shoppingListItemName >> shoppingListNumItems;
        int numPrices;
        priceList >> numPrices;
        //compare item in shopping list with store list
        for (int j = 0; j < numPrices; j++) {
            string priceListItemName;
            double priceListAmazonCost;
            double priceListHyveeCost;
            priceList >> priceListItemName >> priceListAmazonCost >> priceListHyveeCost;
            if (priceListItemName.compare(shoppingListItemName) == 0) {
                double priceDifference;
                string cheaperStore;
                //compare prices, find price diff and what store was cheaper
                if (priceListAmazonCost > priceListHyveeCost) {
                    priceDifference = priceListAmazonCost - priceListHyveeCost;
                    cheaperStore = "HyVee";
                }
                else {
                    priceDifference = priceListHyveeCost - priceListAmazonCost;
                    cheaperStore = "Amazon";
                }
                //calculate savings with amount purchased and then output to savings file
                priceDifference = priceDifference * shoppingListNumItems;
                inSavingsList << shoppingListItemName << " " << priceDifference << " " << cheaperStore << endl;
            }
        }
        //go back to beginning of store list and look for next item in shopping list
        priceList.seekg(0, ios::beg);
    }
    //close streams once finished
    priceList.close();
    shoppingList.close();
    inSavingsList.close();
    //create stream for the savings file we made to compare data and also check for errors opening etc
    ifstream outSavingsList("savings.txt");

    if (outSavingsList.fail()) {
        cerr << "Failed to open savings.txt" << endl;
        return -1;
    }

    string savingsListItemName;
    double savingsListSavings;
    string savingsListCheaperStore;
    double amazonSavings = 0;
    double hyveeSavings = 0;

    //we could have for looped using shoppingListNumItems var because it will be the same amount in this file, but this also works
    while (!outSavingsList.eof()) {
        outSavingsList >> savingsListItemName >> savingsListSavings >> savingsListCheaperStore;
        //add up amount saved and for which store saved the money
        if (savingsListCheaperStore.compare("Amazon") == 0) {
            amazonSavings += savingsListSavings;
        }
        else {
            hyveeSavings += savingsListSavings;
        }
    }
    //print out which store saved the most and how much
    if (amazonSavings > hyveeSavings) {
        cout << "The store with the greatest savings was Amazon with savings totaling $" << amazonSavings << endl;
    }
    else {
        cout << "The store with the greatest savings was HyVee with savings totaling $" << hyveeSavings << endl;
    }
    //close the savings list stream
    outSavingsList.close();
    return 0;
}
