#include <iostream>
using namespace std;

template <typename K, typename V>
class KeyValuePair
{
private:
    K key;
    V value;

public:
    // Default constructor
    KeyValuePair() {}

    // Parameterized constructor
    KeyValuePair(K key, V value) : key(key), value(value) {}

    // GETTERS
    K getKey()
    {
        return key;
    }
    V getValue()
    {
        return value;
    }

    // SETTERS
    void setKey(K key)
    {
        this->key = key;
    }
    void setValue(V value)
    {
        this->value = value;
    }
};

template <typename K, typename V>
class Dictionary
{
private:
    int initialSize;
    int entriesCount;
    KeyValuePair<K, V> *entries;

public:
    Dictionary() : initialSize(3) , entriesCount(0)
    {
        this->entries = new KeyValuePair<K, V>[initialSize];
    }


    void Resize()
    {
        int newSize = initialSize * 2;
        KeyValuePair<K, V> *newEntries = new KeyValuePair<K, V>[newSize];
        for (int i = 0; i < entriesCount; ++i)
        {
            newEntries[i] = entries[i];
        }
        delete[] entries;
        entries = newEntries;
        initialSize = newSize;
    }

    void resizeOrNot()
    {
        if (this->entriesCount < this->initialSize)
        {
            cout << "dictionary will not be resized" << endl;
            return;
        }
        cout << "dictionary will be resized" << endl;
        Resize();
    }

    int size() const
    {
        return this->entriesCount;
    }

    V get(K key)
    {
        for (int i = 0; i < this->entriesCount; i++)
        {
            if (this->entries[i].getKey() == key)
            {
                return this->entries[i].getValue();
            }
        }
        throw runtime_error("Key not found");
    }

    void set(K key, V value)
    {
        for (int i = 0; i < this->entriesCount; i++)
        {
            if (this->entries[i].getKey() == key)
            {
                this->entries[i].setValue(value);
                return;
            }
        }
        resizeOrNot();
        this->entries[this->entriesCount] = KeyValuePair<K, V>(key, value);
        this->entriesCount++;
    }

    bool remove(K key)
    {
        for (int i = 0; i < this->entriesCount; i++)
        {
            if (this->entries[i].getKey() == key)
            {
                this->entries[i] = this->entries[this->entriesCount - 1];
                this->entriesCount--;
                return true;
            }
        }
        return false;
    }

    void print() const
    {
        for (int i = 0; i < this->entriesCount; i++)
        {
            cout << "Key: " << this->entries[i].getKey() << " Value: " << this->entries[i].getValue() << endl;
        }
        cout << "--------" << endl;
        cout << "Size: " << this->size() << endl;
    }
};

int main()
{
    Dictionary<string, int> myDictionary;
    myDictionary.set("apple", 5);
    myDictionary.set("banana", 3);
    myDictionary.set("cherry", 8);
    myDictionary.set("mango", 8);
    myDictionary.print();

    return 0;
}
