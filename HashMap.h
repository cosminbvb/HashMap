#pragma once

#include "KeyHash.h"
#include <iostream>
#include <utility>
#include <list>
#include <vector>

using namespace std;

template<class K, class V, class F=KeyHash<K>>
class HashMap {

	vector<list<pair<K, vector<V>>>> table;
	size_t size;
	KeyHash<K> function = KeyHash<K>(size);
	unsigned distinctKeys;

public:

	HashMap(const size_t& size = 1013) : size(size) {
		distinctKeys = 0;
		table.resize(size);
	}

	HashMap(const HashMap& map) {
		this->size = map.size;
		this->table = map.table;
		this->distinctKeys = map.distinctKeys;
	}

	HashMap operator=(const HashMap&);
	void insert(const K& key, const V&);
	V operator[](const K&);
	vector<V> getValues(const K& key);
	unsigned getDistinctKeys() { return distinctKeys; }
	friend ostream& operator<<(ostream& out, const HashMap& map) {

		out << "{ ";
		for (auto chain : map.table) {
			if (chain.size()) {
				for (auto pair : chain) {
					out << pair.first << ": ";// key:
					unsigned i;
					for (i = 0; i < pair.second.size() - 1; i++) {
						out << pair.second[i] << ", ";
					}
					out << pair.second[i] << "; ";
				}
			}
		}
		out << "}";
		return out;
	}
};

template<class K, class V, class F>
HashMap<K, V, F> HashMap<K, V, F>::operator=(const HashMap& map) {
	if (this == map) {
		return *this;
	}
	this->size = map.size;
	this->table = map.table;
	this->distinctKeys = map.distinctKeys;
	return *this;
}

template<class K, class V, class F>
void HashMap<K, V, F>::insert(const K& key, const V& value) {

	unsigned index = function(key);
	bool found = false;
	list<pair<K, vector<V>>>& currentList = table[index];
	if (currentList.size()) {
		typename list<pair<K, vector<V>>>::iterator it = currentList.begin();
		while (it != currentList.end())
		{
			if (it->first == key) {
				//if we found a node with the same key, we append the value
				found = true;
				it->second.push_back(value);
				break;
			}
			it++;
		}
	}
	if (!found) {
		//if we did not find the given key already
		vector<V> localValues;
		localValues.push_back(value);
		currentList.push_back({ key,localValues });
		distinctKeys++;
	}
}

template<class K, class V, class F>
V HashMap<K, V, F>::operator[](const K& key) {

	unsigned index = function(key);
	list<pair<K, vector<V>>> currentList = table[index];
	typename list<pair<K, vector<V>>>::iterator it = currentList.begin();
	while (it != currentList.end())
	{
		if (it->first == key) {
			return it->second[0];
		}
		it++;
	}
	throw "Key not found";
}

template<class K, class V, class F>
vector<V> HashMap<K, V, F>::getValues(const K& key)
{
	unsigned index = function(key);
	list<pair<K, vector<V>>> currentList = table[index];
	typename list<pair<K, vector<V>>>::iterator it = currentList.begin();
	while (it != currentList.end())
	{
		if (it->first == key) {
			return it->second;
		}
		it++;
	}
	throw "Key not found";
}

