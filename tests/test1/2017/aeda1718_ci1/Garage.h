/*
 * Garage.h
 *
 *  Created on: 24/10/2017
 *      Author: hlc
 */

#ifndef SRC_GARAGE_H_
#define SRC_GARAGE_H_

#include <vector>
#include <string>

#include <utility>

template <class Vehicle>
class Garage {
	std::vector<Vehicle *> vehicles;
	const unsigned int capacity;
public:
	Garage(int size);
	~Garage();
	std::vector<Vehicle *> getVehicles() const;
	void setVehicles(std::vector<Vehicle *> vehicles);
	int getCapacity() const;
	bool addVehicle(Vehicle *vehicle);
	Vehicle* removeVehicle(std::string brand, std::string model);
	float avgPrice(std::string brand) const;
	void sortVehicles();
};

class NoSuchVehicleException {
public:
	NoSuchVehicleException() { }
};

class NoSuchBrandException {
private:
	std::string brand;
public:
	NoSuchBrandException(std::string brnd):brand(brnd){}
	const std::string& getBrand() const{
		return brand;
	}
};

template <class Vehicle>
Garage<Vehicle>::Garage(int size) : capacity(size) {
}

template <class Vehicle>
Garage<Vehicle>::~Garage() {
	typename std::vector<Vehicle *>::const_iterator it;
	for (it=vehicles.begin(); it!=vehicles.end(); it++) {
		delete *it;
	}
}

template<class Vehicle>
std::vector<Vehicle *> Garage<Vehicle>::getVehicles() const {
	return vehicles;
}

template<class Vehicle>
void Garage<Vehicle>::setVehicles(std::vector<Vehicle*> vehicles) {
	this->vehicles = vehicles;
}

template<class Vehicle>
int Garage<Vehicle>::getCapacity() const {
	return capacity;
}

template<class Vehicle>
bool Garage<Vehicle>::addVehicle(Vehicle *vehicle){
	if(vehicles.size() >= capacity) return false;
	for(size_t i = 0; i < vehicles.size(); ++i){
		if(*vehicles[i] == *vehicle) return false;
	}
	vehicles.push_back(vehicle);
	return true;
}

template<class Vehicle>
Vehicle* Garage<Vehicle>::removeVehicle(std::string brand, std::string model){
	for(size_t i = 0; i < vehicles.size(); ++i){
		if(vehicles[i]->getBrand() == brand && vehicles[i]->getModel() == model){
			Vehicle *p = vehicles[i];
			vehicles.erase(vehicles.begin()+i);
			return p;
		}
	}
	throw NoSuchVehicleException();
}

template<class Vehicle>
float Garage<Vehicle>::avgPrice(std::string brand) const{
	size_t count = 0;
	float sum = 0.0;
	for(const Vehicle *p:vehicles){
		if(p->getBrand() == brand){
			++count;
			sum += p->getPrice();
		}
	}
	if(count == 0) throw NoSuchBrandException(brand);
	return sum/count;
}

template<class Vehicle>
bool comp(const Vehicle &v1, const Vehicle &v2){
	if(v1.getBrand() != v2.getBrand()) return (v1.getBrand() < v2.getBrand());
	return                                    (v1.getPrice() > v2.getPrice());
}

template<class Vehicle>
void Garage<Vehicle>::sortVehicles(){
	for(size_t r = 0; r < vehicles.size(); ++r)
		for(size_t i = 0; i < vehicles.size()-1; ++i)
			if(!comp(*vehicles[i], *vehicles[i+1]))
				std::swap(vehicles[i], vehicles[i+1]);
}

#endif /* SRC_GARAGE_H_ */
