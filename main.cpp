#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

struct GroceryItem {
	std::string name;
	int aisle;
	int slot;
	double weight;	// weight in kg
};

//	Function to create a random order with random quantities
std::vector<std::pair<GroceryItem, int >> createRandomOrder(const std::map<std::string, GroceryItem >& groceryList) {
	std::vector<std::pair<GroceryItem, int >>
		orderedItems;

	std::srand(std::time(0));
	for (const auto& item : groceryList) {
		if (std::rand() % 2 == 1) {
			int quantity = std::rand() % 10 + 1;
			// Random quantity between 1 to 10
			orderedItems.push_back({ item.second,quantity });
		}
	}

	//	Sort the ordered items based on their weight
	std::sort(orderedItems.begin(), orderedItems.end(), [](const auto& a, const auto& b) {
		return a.first.weight > b.first.weight;
		});

	return orderedItems;
}

//	Function to validate aisle and slot number
bool isValidAisleSlot(const GroceryItem& item, int confirmedAisle, int confirmedSlot) {
	return confirmedAisle == item.aisle && confirmedSlot == item.slot;
}

//	Function to get user input for aisle, slot, and quantitiy, and validate the input
bool getUserInput(const GroceryItem& item, int& quantityNeeded) {
	int confirmedAisle, confirmedSlot, confirmedQuantity;

	std::cout << "\nConfirm AISLE # for " << item.name << ":";
	std::string input;
	if (!(std::cin >> confirmedAisle >> input) || input != "ok") {
		std::cout << "Invalid input.\n";
		return false;
	}

	std::cout << "\nConfirm you are at SLOT " << item.slot << ": ";
	if (!(std::cin >> confirmedSlot >> input) || input != "ok") {
		std::cout << "Invalid input.\n";
		return false;
	}

	std::cout << "\nConfirm QUANTITY picked " << quantityNeeded << ": ";
	if (!(std::cin >> confirmedQuantity >> input) || input != "ok") {
		std::cout << "Invalid input.\n";
		return false;
	}

	if (isValidAisleSlot(item, confirmedAisle, confirmedSlot)) {
		quantityNeeded = std::min(confirmedQuantity, quantityNeeded);
		return true;
	}
	else {
		std::cout << "Invalid input.\n";
		return false;
	}
}

int main() {

	//	Store item names inside a vector
	std::vector<std::string> groceryItems = { "Apples", "Bananas", "Bread", "Eggs", "Milk", "Cheese", "Beef", "Chicken", "Pasta", "Rice", "Cereal", "Water", "Juice" };
	const int numAisles = 10; //	Number of given aisles in distribution center
	const int numSlots = 5;	//	Number of given slot locations in each aisle in distribution center

	std::map<std::string, GroceryItem > groceryList;

	//	Generate random assignments and weight for each grocery item
	std::srand(std::time(0));
	for (const auto& item : groceryItems) {
		int aisle = std::rand() % numAisles + 1;
		int slot = std::rand() % numSlots + 1;
		double weight = (std::rand() % 1000) / 100.00;	//	Random weight between 0.00 to 9.99 kg

		groceryList[item] = { item, aisle, slot, weight };

	}

	//	Create a random order
	std::vector<std::pair<GroceryItem, int >> orderedItems = createRandomOrder(groceryList);

	//	Display the ordered list with item details and confirm slot location and quantity
	std::cout << "\nEnter aisle #, slot #, and quantity followed by ok. For example: 3 ok\n";
	std::cout << "\n--- Re ---\n";
	for (const auto& item : orderedItems) {
		const GroceryItem& itemDetails = item.first;
		int quantityNeeded = item.second;

		double weightInPounds = itemDetails.weight * 2.20462;	//	Conversion from kg to lbs

		std::cout << "\n" << itemDetails.name << " - Aisle: " << itemDetails.aisle << ", Slot: " << itemDetails.slot << ", Weight: " << weightInPounds << " lbs, " << "Quantity: " << quantityNeeded << "\n";
		bool validInput = false;
		while (!validInput) {
			validInput = getUserInput(itemDetails, quantityNeeded);
		}
	}

	std::cout << "\nTask Complete.\n";

	return 0;
}