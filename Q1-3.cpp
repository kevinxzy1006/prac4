#include <iostream>
#include <ctime>

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

class ParkingLot {
private:
    Vehicle **vehicles;
    int maxCapacity;
    int currentCount;
public:
    ParkingLot(int capacity) : maxCapacity(capacity), currentCount(0) {
        vehicles = new Vehicle*[maxCapacity];
    }

    ~ParkingLot() {
        delete[] vehicles;
    }

    int getCurrentCount() const { return currentCount; }

    void parkVehicle(Vehicle *vehicle) {
        if (currentCount < maxCapacity) {
            vehicles[currentCount++] = vehicle;
            std::cout << "Vehicle parked successfully.\n";
        } else {
            std::cout << "The lot is full.\n";
        }
    }

    void unparkVehicle(int id) {
        for (int i = 0; i < currentCount; ++i) {
            if (vehicles[i]->getFoo() == id) {
                delete vehicles[i];
                vehicles[i] = vehicles[--currentCount];
                std::cout << "Vehicle with ID " << id << " removed from the lot.\n";
                return;
            }
        }
        std::cout << "Vehicle not in the lot.\n";
    }

    int countOverstayingVehicles(int maxParkingDuration) const {
        int count = 0;
        for (int i = 0; i < currentCount; ++i) {
            if (vehicles[i]->getParkingDuration() > maxParkingDuration) {
                count++;
            }
        }
        return count;
    }
};

int main() {
    ParkingLot parkingLot(10);

    // Park 5 cars, 3 buses, and 2 motorbikes
    for (int i = 0; i < 5; ++i) {
        parkingLot.parkVehicle(new Car());
    }
    for (int i = 0; i < 3; ++i) {
        parkingLot.parkVehicle(new Bus());
    }
    for (int i = 0; i < 2; ++i) {
        parkingLot.parkVehicle(new Motorbike());
    }

    int overstayingCount = parkingLot.countOverstayingVehicles(15);
    std::cout << "Number of vehicles overstaying in the parking lot: " << overstayingCount << std::endl;

    return 0;
}
