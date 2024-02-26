#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <fstream>

// Item class represents a single item in the inventory
class Item {
public:
    std::string name;
    int quantity;
    double price;

    Item(std::string n, int q, double p) : name(std::move(n)), quantity(q), price(p) {}
};

// InventoryManager class handles all operations related to inventory management
class InventoryManager {
private:
    std::vector<Item> items;

public:
    void addItem(const Item& item) {
        items.push_back(item);
    }

    void removeItem(const std::string& name) {
        auto it = std::find_if(items.begin(), items.end(), [&](const Item& item) {
            return item.name == name;
            });
        if (it != items.end()) {
            items.erase(it);
        }
        else {
            throw std::invalid_argument("Item not found in inventory.");
        }
    }

    void updateStock(const std::string& name, int quantityChange) {
        auto it = std::find_if(items.begin(), items.end(), [&](const Item& item) {
            return item.name == name;
            });
        if (it != items.end()) {
            it->quantity += quantityChange;
        }
        else {
            throw std::invalid_argument("Item not found in inventory.");
        }
    }

    // Sort inventory by name
    void sortInventoryByName() {
        std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.name < b.name;
            });
    }

    // Sort inventory by quantity
    void sortInventoryByQuantity() {
        std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.quantity < b.quantity;
            });
    }

    // Sort inventory by price
    void sortInventoryByPrice() {
        std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.price < b.price;
            });
    }

    // Display the current inventory
    void displayInventory() const {
        std::cout << "Inventory:\n";
        for (const auto& item : items) {
            std::cout << item.name << " - Quantity: " << item.quantity << " - Price: $" << std::fixed << std::setprecision(2) << item.price << std::endl;
        }
    }
};

class InventoryUI {
private:
    InventoryManager& manager;

public:
    InventoryUI(InventoryManager& m) : manager(m) {}

    // Display menu options
    void displayMenu() {
        std::cout << "Inventory Management System\n";
        std::cout << "1. Add Item\n";
        std::cout << "2. Remove Item\n";
        std::cout << "3. Update Stock\n";
        std::cout << "4. Display Inventory\n";
        std::cout << "5. Sort Inventory by Name\n";
        std::cout << "6. Sort Inventory by Quantity\n";
        std::cout << "7. Sort Inventory by Price\n";
        std::cout << "8. Exit\n";
    }

    // Run the user interface
    void run() {
        int choice;
        std::string name;
        int quantity;
        double price;

        do {
            displayMenu();
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                std::cout << "Enter item name: ";
                std::cin >> name;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;
                std::cout << "Enter price: ";
                std::cin >> price;
                manager.addItem(Item(name, quantity, price));
                break;
            case 2:
                std::cout << "Enter item name to remove: ";
                std::cin >> name;
                try {
                    manager.removeItem(name);
                    std::cout << "Item removed successfully.\n";
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case 3:
                std::cout << "Enter item name to update stock: ";
                std::cin >> name;
                std::cout << "Enter quantity change: ";
                std::cin >> quantity;
                try {
                    manager.updateStock(name, quantity);
                    std::cout << "Stock updated successfully.\n";
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case 4:
                manager.displayInventory();
                break;
            case 5:
                manager.sortInventoryByName();
                std::cout << "Inventory sorted by name.\n";
                break;
            case 6:
                manager.sortInventoryByQuantity();
                std::cout << "Inventory sorted by quantity.\n";
                break;
            case 7:
                manager.sortInventoryByPrice();
                std::cout << "Inventory sorted by price.\n";
                break;
            case 8:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 8);
    }
};

int main() {
    InventoryManager inventoryManager;
    InventoryUI ui(inventoryManager);
    ui.run();
    return 0;
}
