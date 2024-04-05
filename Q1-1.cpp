#include <iostream>
#include <ctime>
#include <cmath>

class Vehicle {
private:
    std::time_t timeOfEntry;
protected:
    int foo;
public:
    Vehicle() : timeOfEntry(std::time(nullptr)), foo(0) {}
    virtual ~Vehicle() {}
    int getFoo() const { return foo; }
    std::time_t getTimeOfEntry() const { return timeOfEntry; }
    virtual int getParkingDuration() const {
        return static_cast<int>(std::time(nullptr) - timeOfEntry);
    }
};

class Car : public Vehicle {
public:
    Car() { foo = 1; }
    int getParkingDuration() const override {
        int duration = Vehicle::getParkingDuration();
        return static_cast<int>(duration * 0.9);
    }
};

class Bus : public Vehicle {
public:
    Bus() { foo = 2; }
    int getParkingDuration() const override {
        int duration = Vehicle::getParkingDuration();
        return static_cast<int>(duration * 0.75);
    }
};

class Motorbike : public Vehicle {
public:
    Motorbike() { foo = 3; }
    int getParkingDuration() const override {
        int duration = Vehicle::getParkingDuration();
        return static_cast<int>(duration * 0.85);
    }
};

int main() {
    int numCars, numBuses, numMotorbikes;

    std::cout << "Enter the number of cars: ";
    std::cin >> numCars;
    std::cout << "Enter the number of buses: ";
    std::cin >> numBuses;
    std::cout << "Enter the number of motorbikes: ";
    std::cin >> numMotorbikes;

    Vehicle *vehicles[numCars + numBuses + numMotorbikes];

    for (int i = 0; i < numCars; i++) {
        vehicles[i] = new Car();
    }
    for (int i = 0; i < numBuses; i++) {
        vehicles[numCars + i] = new Bus();
    }
    for (int i = 0; i < numMotorbikes; i++) {
        vehicles[numCars + numBuses + i] = new Motorbike();
    }

    for (int i = 0; i < numCars + numBuses + numMotorbikes; i++) {
        std::cout << "Vehicle " << i + 1 << " parking duration: " << vehicles[i]->getParkingDuration() << " seconds\n";
        delete vehicles[i];
    }

    return 0;
}
