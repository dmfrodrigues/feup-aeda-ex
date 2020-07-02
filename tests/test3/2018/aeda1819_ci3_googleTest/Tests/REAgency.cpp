#include "REAgency.h"

REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
	//do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
	this->properties = properties;
}

void REAgency::addProperty(Property* property) {
	this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
	this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
	return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
	PropertyTypeItem itemNotFound("", "", "", 0);
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
			PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
			pti.setItems(it.retrieve().getItems());
			return pti;
		}
		it.advance();
	}
	return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
	PropertyTypeItem itemNotFound("", "","", 0);
	PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
	PropertyTypeItem ptiX = catalogItems.find(pti);
	if(ptiX == itemNotFound) {
		pti.addItems(property);
		this->catalogItems.insert(pti);
	}
	else {
		this->catalogItems.remove(ptiX);
		ptiX.addItems(property);
		this->catalogItems.insert(ptiX);
	}
	properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
	return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
	vector<ClientRecord> records;
	HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
	HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
	for(unsigned int i = 0; i < crs.size(); i++) {
		listingRecords.insert(crs[i]);
	}

}

priority_queue<Client> REAgency::getClientProfiles() const {
	return clientProfiles;
}
void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
	clientProfiles = profiles;
}

//
// TODO: Part I   - BST
//
void REAgency::generateCatalog() {
    auto properties_ = properties;
    properties.clear();
    for(int i = 0; i < properties_.size(); ++i){
        addTypeItem(properties_[i]);
    }
}

vector<Property*> REAgency::getAvailableProperties(Property* property) const {
	vector<Property*> temp;
	//TODO: B
    PropertyTypeItem pti = catalogItems.find(
            PropertyTypeItem(property->getAddress(),
                                property->getPostalCode(),
                                property->getTypology(),
                                property->getPrice()));
    for(Property *p:pti.getItems()){
        if(p->getReservation() == tuple<Client*, int>()){
            temp.push_back(p);
        }
    }
	return temp;
}

bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage) {
	//TODO: C
    PropertyTypeItem itemNotFound("", "","", 0);
    PropertyTypeItem pti = catalogItems.find(
            PropertyTypeItem(property->getAddress(),
                             property->getPostalCode(),
                             property->getTypology(),
                             property->getPrice()));
    if(pti == itemNotFound) return false;
    Property *p = NULL;
    for(Property *q:pti.getItems()){
        if(q->getReservation() == tuple<Client*, int>()){
            p = q;
            break;
        }
    }
    if(p == NULL) return false;
    p->setReservation(tuple<Client*, int>(client, p->getPrice()*(100-percentage)/100));
    client->addVisiting(p->getAddress(),
                        p->getPostalCode(),
                        p->getTypology(),
                        to_string(p->getPrice()));
    return true;
}

//
// TODO: Part II  - Hash Table
//
void REAgency::addClientRecord(Client* client) {
	//TODO: D
    listingRecords.insert(ClientRecord(client));
}

void REAgency::deleteClients() {
	//TODO: E
	auto it = listingRecords.begin();
	while(it != listingRecords.end()){
	    if(it->getClientPointer()->getVisitedProperties().empty() &&
	       it->getClientPointer()->getVisiting() == tuple<string,string,string,string>()){
	        it = listingRecords.erase(it);
	    }else ++it;
	}
}

//
// TODO: Part III - Priority Queue
//
void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {
	//TODO: F
    for(const Client &c:candidates){
        int num_reservations = 0;
        for(const Property *p:properties)
            if(get<0>(p->getReservation())->getEMail() == c.getEMail())
                ++num_reservations;
        int ratio = num_reservations / (1+c.getVisitedProperties().size());
        if(ratio >= min)
            clientProfiles.push(c);
    }
}

vector<Property*> REAgency::suggestProperties() {
	//TODO: G
	vector<Property*> tempProperties(clientProfiles.size(), NULL);
    auto pq = clientProfiles;
    for(int i = 0; i < clientProfiles.size(); ++i){
        Client c = pq.top(); pq.pop();
        string postal_str = get<1>(c.getVisiting());
        if(postal_str == "") continue;
        int postal = stoi(postal_str);
        Property *cur = NULL;
        for(Property *p:properties){
            if(p->getReservation() != tuple<Client*,int>()) continue;
            PropertyTypeItem pti(p->getAddress(), p->getPostalCode(), p->getTypology(), p->getPrice());
            PropertyTypeItem pti0(get<0>(c.getVisiting()), get<1>(c.getVisiting()), get<2>(c.getVisiting()), stoi(get<3>(c.getVisiting())));
            if(pti == pti0) continue;
            bool cont = false;
            for(const auto &prop:c.getVisitedProperties()){
                pti0 = PropertyTypeItem(get<0>(prop), get<1>(prop), get<2>(prop), stoi(get<3>(prop)));
                if(pti == pti0){
                    cont = true;
                    break;
                }
            }
            if(cont) continue;
            if(cur == NULL){ cur = p; continue; }
            int postal2 = stoi(p->getPostalCode());
            if(abs(postal2-postal) < abs(stoi(cur->getPostalCode())-postal)){
                cout << p->getAddress() << " " << p->getPostalCode() << endl;
                cur = p;
            }
        }
        tempProperties[i] = cur;
    }
	return tempProperties;
}
