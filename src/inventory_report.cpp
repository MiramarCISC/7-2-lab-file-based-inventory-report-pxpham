#include "inventory_report.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

bool isValidQuantity(int quantity) {
    return quantity >= 0;
}

bool isValidPrice(double price) {
   return price >=0.0;
}

double calculateItemValue(const InventoryItem& item) {
    if (!isValidQuantity(item.quantity) || !isValidPrice(item.price)) {
    return 0.0;
    }
    return item.quantity * item.price;
}
int readInventoryFile(string filename, InventoryItem items[], int maxItems) {
        ifstream inFile(filename);
        if (!inFile ){
          return 0;
}
    int count = 0;
    InventoryItem tempItem;

while (count < maxItems && inFile >> tempItem.sku >> tempItem.name >> tempItem.quantity >> tempItem.price){
    if (isValidQuantity(tempItem.quantity) && isValidPrice(tempItem.price)) {
        items[count] = tempItem;
        count++;
    }
}
    inFile.close();
    return count;
}

double calculateTotalInventoryValue(const InventoryItem items[], int count) {
    
    if (items == nullptr || count <= 0) {
    return 0.0;
}

double totalValue = 0.0;
for (int i = 0; i < count; i++){
    totalValue += calculateItemValue(items[i]);
    }
    return totalValue;
}

bool writeInventoryReport(string filename, const InventoryItem items[], int count) {
     ofstream outFile(filename);
    if (!outFile){
        return false;
    }
    outFile << fixed << setprecision(2);
    outFile << "INVENTORY REPORT\n";
    outFile << "----------------------------------\n";

    for (int i = 0; i < count; i++){
        double itemValue = calculateItemValue(items[i]);
        outFile << "SKU: " << items[i].sku
                << " | Name: " << items[i].name
                << " | Qty: " << items[i].quantity
                << " | Price: $" << items[i].price
                << " | Value: $" << itemValue << "\n";
    }
    double totalValue = calculateTotalInventoryValue(items, count);
    outFile << "---------------------------------\n";
    outFile << "Total inventory value: $" << totalValue << "\n";

    outFile.close();
    return true;
}


int findItemBySku(const InventoryItem items[], int count, string sku) {
    if (items == nullptr || count <= 0){
    return -1;
}
    for (int i = 0; i < count; i++) {
        if (items[i].sku == sku) {
            return i;
            }
        }
        return -1;
    }

int findHighestValueItemIndex(const InventoryItem items[], int count) {
    if (items == nullptr || count <= 0){
    return -1;
}
    int highestIndex = -1;
    double highestValue = -1.0;

    for (int i = 0; i < count; i++){
        if (isValidQuantity(items[i].quantity) && isValidPrice(items[i].price)) {
            double currentValue = calculateItemValue(items[i]);
        if (highestIndex == -1 || currentValue > highestValue) {
            highestValue = currentValue;
            highestIndex = i;
          }
     } 
}
    return highestIndex;
}
