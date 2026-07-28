#include "inventory_report.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

bool isValidQuantity(int quantity) {
    // TODO: Return true when quantity is 0 or greater.
    return quantity >= 0;
}

bool isValidPrice(double price) {
    // TODO: Return true when price is 0 or greater.
    return price >= 0;
}

double calculateItemValue(const InventoryItem& item) {
    // TODO: Return quantity multiplied by price.
    // If quantity or price is invalid, return 0.0.
    if (!isValidQuantity(item.quantity) || !isValidPrice(item.price)) return 0.0;
    return item.quantity * item.price;
}

int readInventoryFile(string filename, InventoryItem items[], int maxItems) {
    // TODO:
    // Open the input file.
    // Read records in this format: sku name quantity price
    // Store valid records in the items array.
    // Stop when the file ends or maxItems is reached.
    // Return the number of records stored.
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Error opening file."; return 0;
    }
    int recordCount = 0;
    string sku;
    string name;
    int quantity;
    double price;
    while(recordCount < maxItems && inputFile >> sku >> name >> quantity >> price){
        if (isValidPrice(price) && isValidQuantity(quantity)){
            items[recordCount] = InventoryItem{sku, name, quantity, price};
            recordCount++;
        }
    }
    inputFile.close();
    return recordCount;
}

bool writeInventoryReport(string filename, const InventoryItem items[], int count) {
    // TODO:
    // Open the output file.
    // Write each item and its total value.
    // Write the total inventory value.
    // Return true if the report was written successfully.
    ofstream outputFile(filename);
    if (!outputFile) {
        cout << "Error opening file."; return false;
    }
    double totalValue = 0;
    for (int i = 0; i < count; i++){
        double value = calculateItemValue(items[i]);
        outputFile << items[i].sku << " " << items[i].name << " " << value << endl;
        totalValue += value;
    }
    outputFile << "Total inventory value: " << totalValue << endl;
    outputFile.close();
    return true;
}

double calculateTotalInventoryValue(const InventoryItem items[], int count) {
    // TODO:
    // Return the sum of all item values.
    // Return 0.0 for null arrays or invalid counts.
    if (items == NULL || count <=0) return 0.0;
    double total = 0;
    for (int i = 0; i < count; i++){
        total += calculateItemValue(items[i]);
    }
    return total;
}

int findItemBySku(const InventoryItem items[], int count, string sku) {
    // TODO:
    // Search for a matching SKU.
    // Return the index if found.
    // Return -1 if not found.
    for (int i = 0; i < count; i++){
        if (items[i].sku == sku) return i;
    }
    return -1;
}

int findHighestValueItemIndex(const InventoryItem items[], int count) {
    // TODO:
    // Return the index of the item with the highest item value.
    // Return -1 for null arrays or invalid counts.
    if (items == NULL || count <= 0) return -1;
    int highest = 0; //takes the index, not the item itself
    for (int i = 1; i < count; i++){
        if (calculateItemValue(items[i]) > calculateItemValue(items[highest])) highest = i;
    }
    return highest;
}
