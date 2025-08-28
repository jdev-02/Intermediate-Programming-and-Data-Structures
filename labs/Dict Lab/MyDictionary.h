//File - MyDictionary.h
// 
// Jonathan Goohs
//Intermediate Programming and Data Structures Lab 3 - MyDictionary Class
//This lab will build a dictionary class from scratch using an array as a hash table (table size 17) with linked lists for collision mitigation

#ifndef MYDICT_H
#define MYDICT_H

#include <iostream>
#include "List.h"
using namespace std;
#define TABLE_SIZE 17
#define INIT_D_LEN 0

//MyDictionary class interface
template<class T>
class MyDictionary
{
	//Hash table-based dictionary implementation with linked lists (List<T>) to handle collisions at each bucket
protected:
	List<T>* hash_table; //array that holds the dictionary in a hash table. Each array element will be a List of pairs that hash to that array index
	int total; //total number of pairs in the dictionary at any time
private:
	int hash(int key); //custom hash function
public:
	MyDictionary(); //default constructor for an empty dictionary
	~MyDictionary(); //destructor to delete pairs and free memory
	void insert(int key, T value); //inserts new pair into dictionary
	T get(int key); //returns value associated with key or 0 if key not found in dictionary
	T remove(int key); //removes pair associated with key from dictionary and returns value, or 0 if key not found
	List<int> keys(); //return a List of all keys in the dictionary
	List<T> values(); //return a List of all values in the dictionary	
	int length(); //returns how many pairs are in the dictionary
};
//begin implementation of MyDictionary
template<class T>
MyDictionary<T>::MyDictionary() : total(INIT_D_LEN) {
	hash_table = new List<T>[TABLE_SIZE];
	//each element of hash table should initially hold empty list (default constructor handles this)
}
template<class T>
MyDictionary<T>::~MyDictionary() {
	delete[] hash_table;
}
template<class T>
int MyDictionary<T>::hash(int key) {
	if (key < 0) {
		//key is negative and we should handle that to provide positive keys for indexing properly
		key = -key;
	}
	//mod table size to prevent larger than 17 key size input
	return key % TABLE_SIZE;
}
template<class T>
void MyDictionary<T>::insert(int key, T value) {
	int hashedk = hash(key);
	hash_table[hashedk].insert(key, value); //use the list method on the hash_table list object
	total++;
}
template<class T>
T MyDictionary<T>::get(int key) {
	return hash_table[hash(key)].getByKey(key);
}
template<class T>
T MyDictionary<T>::remove(int key) {
	int binIndex = hash(key);
	int originalCount = hash_table[binIndex].total;
	T result = hash_table[binIndex].removebyKey(key);
	if (hash_table[binIndex].total < originalCount) {  // Item was actually removed
		total--;
	}
	return result;
}
template<class T>
List<int> MyDictionary<T>::keys() {
	List<int> allKeys;
	for (int i = 0; i < TABLE_SIZE; i++) {
		List<int> binKeys = hash_table[i].keys();  // Get keys from this bin
		allKeys.appendFrom(binKeys);               // Append them to allKeys using list method appendFrom
	}
	return allKeys;
}
template<class T>
List<T> MyDictionary<T>::values() {
	List<T> allVals;
	for (int i = 0; i < TABLE_SIZE; i++) {
		List<T> binVals = hash_table[i].values();  // Get values from this bin
		allVals.appendFrom(binVals);               // Append them to allVals
	}
	return allVals;
}
template<class T>
int MyDictionary<T>::length() {
	return total;
}
#endif
//end MyDictionary