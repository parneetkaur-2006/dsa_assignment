// PARNEET KAUR(2401360010) - LAB ASSIGNMENT
 #include <iostream>
#include <vector>
#include <string>
using namespace std;


struct Item {
    int id;
    string name;
    int quantity;
    double price;
};

class InventorySystem {
private:
    vector<Item> items;
    int nextID = 1; 

public:
    
    void insertItem(string name, int quantity, double price) {
        Item newItem = {nextID++, name, quantity, price};
        items.push_back(newItem);
        cout << "Inserted: " << name << " (ID: " << newItem.id << ")\n";
    }

    
    void deleteItem(int id) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->id == id) {
                cout << "Deleted: " << it->name << " (ID: " << id << ")\n";
                items.erase(it);
                return;
            }
        }
        cout << "Item with ID " << id << " not found.\n";
    }

    
    void searchItem(string name) {
        bool found = false;
        for (auto &item : items) {
            if (item.name == name) {
                cout << "Found: " << item.name << " | ID: " << item.id 
                     << " | Quantity: " << item.quantity 
                     << " | Price: $" << item.price << endl;
                found = true;
            }
        }
        if (!found) cout << "Item " << name << " not found.\n";
    }

    
    void updateQuantity(int id, int newQuantity) {
        for (auto &item : items) {
            if (item.id == id) {
                item.quantity = newQuantity;
                cout << "Updated Quantity: " << item.name 
                     << " -> " << newQuantity << endl;
                return;
            }
        }
        cout << "Item with ID " << id << " not found.\n";
    }

    
    void displayInventory() {
        cout << "\nCurrent Inventory:\n";
        cout << "ID\tName\t\tQuantity\tPrice\n";
        
        for (auto &item : items) {
            cout << item.id << "\t" 
                 << item.name << "\t\t" 
                 << item.quantity << "\t\t" 
                 << item.price << endl;
        }
    }

    
    void analyzeComplexity() {
        cout << "\nTime Complexity:\n";
        cout << "Insert: O(1)\n";
        cout << "Delete: O(N) (linear search by ID)\n";
        cout << "Search: O(N) (linear search by name)\n";
        cout << "Update: O(N) (linear search by ID)\n";
        cout << "Display: O(N)\n";
        cout << "\nSpace Complexity:\n";
        cout << "Storage: O(N) for N items\n";
    }
};


int main() {
    InventorySystem inventory;

    
    inventory.insertItem("Milk", 50, 1.5);
    inventory.insertItem("Bread", 30, 2.0);
    inventory.insertItem("Eggs", 100, 0.2);

    inventory.displayInventory();

    cout << "\nSearch for Bread:\n";
    inventory.searchItem("Bread");

    cout << "\nUpdate Quantity of Milk:\n";
    inventory.updateQuantity(1, 60);

    cout << "\nDelete Eggs from Inventory:\n";
    inventory.deleteItem(3);

    inventory.displayInventory();

    inventory.analyzeComplexity();

    return 0;
}
