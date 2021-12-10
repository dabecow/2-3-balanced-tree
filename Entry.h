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

    Entry(){
        key = nullptr;
        value = nullptr;
    };

    Entry(K *key, V *value) : key(key), value(value) {}

    K *getKey() const {
        if (key == nullptr)
            return nullptr;

        return key;
    }

    K getKeyValue() {
        return *key;
    }

//    K getKey() {
//        return *key;
//    }

    void setKey(K *k) {
        Entry::key = k;
    }

    V *getValue() const {
        return value;
    }

    void setValue(V *v) {
        Entry::value = v;
    }
};


#endif //TREE_ENTRY_H
