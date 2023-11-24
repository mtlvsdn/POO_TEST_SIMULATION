#include <iostream>
#include <string>

enum class BrandType {PETROM, OMW, ROMPETROL};

class PetrolStation {
private:
	int pumpId = 0;
	std::string location = "Bucharest";
	BrandType brand = BrandType::OMW;
	bool isDiesel = false;
	int* liters = nullptr;
	int noClients = 0;

	//Private Static Attributes
	static const int MIN_ID_LENGTH = 1;
	static const int MIN_LOC_LENGTH = 3;

public:
	//Public Static Attributes
	static float PRICE_PER_LITER;

	//Setters
	void setPumpId(int newPumpId) {
		int copy = newPumpId;
		int contor = 0;
		while (copy != 0) { contor++; copy /= 10; }
		if (contor < MIN_ID_LENGTH) {
			throw std::exception("ID is too short!");
		}
		this->pumpId = newPumpId;
	}
	void setLocation(std::string newLocation) {
		if (newLocation.length() < MIN_LOC_LENGTH) {
			throw std::exception("Location name is too short!");
		}
		this->location = newLocation;
	}
	void setBrand(BrandType newBrand) {
		this->brand = newBrand;
	}
	void setDiesel() {
		this->isDiesel = true;
	}
	void setLiters(int* newLiters, int noClients) {
		if (this->liters != NULL) {
			delete[] this->liters;
		}
		this->liters = new int[noClients + 1];
		for (int i = 0; i < noClients; i++) {
			this->liters[i] = newLiters[i];
		}
	}
	void setNoClients(int newNoClients) {
		if (newNoClients < 0) {
			throw std::exception("Number of clients cannot be a negative number!");
		}
		this->noClients = newNoClients;
	}
	void increaseNoClients() {
		int number = this->noClients;
		number++;
		this->noClients = number;
	}

	//Getters
	int getPumpId() {
		return this->pumpId;
	}
	std::string getLocation() {
		return this->location;
	}
	BrandType getBrand() {
		return this->brand;
	}
	bool getDiesel() {
		return this->isDiesel;
	}
	int* getLiters() {
		int* copy = new int[this->noClients + 1];
		for (int i = 0; i < this->noClients + 1; i++) {
			copy[i] = this->liters[i];
		}
		return copy;
	}
	int getNoClients() {
		return this->noClients;
	}
	int getTotalLiters() {
		int* newArray = new int[this->noClients + 1];
		int sum = 0;
		for (int i = 0; i < this->noClients; i++) {
			newArray[i] = this->liters[i];
			sum = sum + newArray[i];
		}
		return sum;
	}
	float getIncome() {
		int sum = this->getTotalLiters();
		return sum * PRICE_PER_LITER;
	}

	//Other Methods
	void sellGasoline(int amount) {
		if (amount > 1000) {
			throw std::exception("The pump can't deliver more than 1000 liters!");
		}
		//increaseNoClients();
		this->noClients++;
		int* newArray = new int[this->noClients + 1];
		for (int i = 0; i < this->noClients; i++) {
			newArray[i] = this->liters[i];
		}
		newArray[this->noClients - 1] = amount;
		if (this->liters != NULL) {
			delete[] this->liters;
		}
		this->liters = new int[this->noClients + 1];
		for (int i = 0; i < this->noClients; i++) {
			this->liters[i] = newArray[i];
			//std::cout << this->liters[i] << " ";
		}
	}

	//Constructors
	PetrolStation() {
		setPumpId(1);
		setLocation("Bucharest");
	}
	PetrolStation(int newPumpId, std::string newLocation) {
		setPumpId(newPumpId);
		setLocation(newLocation);
	}
	PetrolStation(int newPumpId, std::string newLocation, int* newLiters, int newNoClients, BrandType newBrand) {
		setPumpId(newPumpId);
		setLocation(newLocation);
		setNoClients(newNoClients);
		setLiters(newLiters, newNoClients);
		setBrand(newBrand);
	}
	//Destructor
	~PetrolStation() {
		delete[] this->liters;
	}
};

float PetrolStation::PRICE_PER_LITER = 7.3;

int main() {
	PetrolStation station1(23, "Bucharest");
	std::cout << station1.getLocation();
	station1.setLocation("Ploiesti");
	std::cout << station1.getLocation();
	int liters[]{ 100, 200, 300 };
	PetrolStation station2(24, "Ploiesti", liters, 3, BrandType::PETROM);
	std::cout << "\n" << station2.getTotalLiters();
	PetrolStation station3;
	station3.setPumpId(24);
	std::cout << "\n" << station3.getPumpId();
	station3.setDiesel();
	station2.sellGasoline(500);
	std::cout << "\n" << station2.getNoClients();
	PetrolStation::PRICE_PER_LITER = 6.4;
	std::cout << "\n" << station2.getTotalLiters();
	std::cout << "\nTotal revenue: " << station2.getIncome();
}