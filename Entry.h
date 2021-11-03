//
// Created by Andrew on 03.11.2021.
//

#ifndef TREE_ENTRY_H
#define TREE_ENTRY_H

template<class K, class V>
class Entry {
private:
    K* key;
    V* value;

public:
    Entry(K *key, V *value) : key(key), value(value) {}

    K *getKey() const {
        return key;
    }

    void setKey(K *key) {
        Entry::key = key;
    }

    V *getValue() const {
        return value;
    }

    void setValue(V *value) {
        Entry::value = value;
    }
};


#endif //TREE_ENTRY_H
