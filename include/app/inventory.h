#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "list/DLinkedList.h"
#include "list/XArrayList.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

// -------------------- List1D --------------------
template <typename T>
class List1D {
private:
    IList<T> *pList;

public:
    List1D();
    List1D(int num_elements);
    List1D(const T *array, int num_elements);
    List1D(const List1D<T> &other);
    virtual ~List1D();

    int size() const;
    T get(int index) const;
    void set(int index, T value);
    void add(const T &value);
    string toString() const;

    // template <typename U>
    // friend ostream &operator<<(ostream &os, const List1D<U> &list);
    friend ostream &operator<<(ostream &os, const List1D<T> &list);
};

// -------------------- List2D --------------------
template <typename T>
class List2D {
private:
    IList<IList<T> *> *pMatrix;

public:
    List2D();
    List2D(List1D<T> *array, int num_rows);
    List2D(const List2D<T> &other);
    virtual ~List2D();

    int rows() const;
    void setRow(int rowIndex, const List1D<T> &row);
    T get(int rowIndex, int colIndex) const;
    List1D<T> getRow(int rowIndex) const;
    string toString() const;

    // template <typename U>
    // friend ostream &operator<<(ostream &os, const List2D<U> &matrix);
    friend ostream &operator<<(ostream &os, const List2D<T> &matrix);
};

struct InventoryAttribute {
    string name;
    double value;
    InventoryAttribute(const string &name = "", double value = 0) : name(name), value(value) {}
    string toString() const { return name + ": " + to_string(value); }
    bool operator==(const InventoryAttribute &other) const {
        return (name == other.name) && (fabs(value - other.value) < 1e-9);
    }
    friend ostream &operator<<(ostream &os, const InventoryAttribute &attr) {
        os << attr.toString();
        return os;
    }
};

// -------------------- InventoryManager --------------------
class InventoryManager {
private:
    List2D<InventoryAttribute> attributesMatrix;
    List1D<string> productNames;
    List1D<int> quantities;

public:
    InventoryManager();
    InventoryManager(const List2D<InventoryAttribute> &matrix,
                     const List1D<string> &names,
                     const List1D<int> &quantities);
    InventoryManager(const InventoryManager &other);

    int size() const;
    List1D<InventoryAttribute> getProductAttributes(int index) const;
    string getProductName(int index) const;
    int getProductQuantity(int index) const;
    void updateQuantity(int index, int newQuantity);
    void addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity);
    void removeProduct(int index);

    List1D<string> query(int attributeName, const double &minValue,
                         const double &maxValue, int minQuantity, bool ascending) const;

    void removeDuplicates();

    static InventoryManager merge(const InventoryManager &inv1,
                                  const InventoryManager &inv2);

    void split(InventoryManager &section1,
               InventoryManager &section2,
               double ratio) const;

    List2D<InventoryAttribute> getAttributesMatrix() const;
    List1D<string> getProductNames() const;
    List1D<int> getQuantities() const;
    string toString() const;
};

// -------------------- List1D Method Definitions --------------------
template <typename T>
List1D<T>::List1D() {
    // TODO
    pList = new XArrayList<T>();
}

template <typename T>
List1D<T>::List1D(int num_elements) {
    // TODO
    pList = new XArrayList<T>();
    for (int i = 0; i < num_elements; i++) {
        pList->add(T());
    }
}

template <typename T>
List1D<T>::List1D(const T *array, int num_elements) {
    // TODO
    pList = new XArrayList<T>();
    for (int i = 0; i < num_elements; i++) {
        pList->add(array[i]);
    }
}

template <typename T>
List1D<T>::List1D(const List1D<T> &other) {
    // TODO
    pList = new XArrayList<T>();
    for (int i = 0; i < other.size(); i++) {
        pList->add(other.get(i));
    }
}

template <typename T>
List1D<T>::~List1D() {
    // TODO
    delete pList;
}

template <typename T>
int List1D<T>::size() const {
    // TODO
    return pList->size();
}

template <typename T>
T List1D<T>::get(int index) const {
    // TODO
    return pList->get(index);
}

template <typename T>
void List1D<T>::set(int index, T value) {
    // TODO
    pList->get(index) = value;
}

template <typename T>
void List1D<T>::add(const T &value) {
    // TODO
    pList->add(value);
}

template <typename T>
string List1D<T>::toString() const {
    // TODO
    if constexpr (std::is_fundamental<T>::value) {
        return pList->toString();
    }
    if constexpr (std::is_class<T>::value) {
        return pList->toString([](T &item) -> string {
            return item.toString();
        });
    }
    return "error at List1D<T>::toString()";
}

template <typename T>
ostream &operator<<(ostream &os, const List1D<T> &list) {
    // TODO
    os << list.toString();
    return os;
}

// -------------------- List2D Method Definitions --------------------
template <typename T>
List2D<T>::List2D() {
    // TODO
    pMatrix = new XArrayList<IList<T> *>();
}

template <typename T>
List2D<T>::List2D(List1D<T> *array, int num_rows) {
    // TODO
    pMatrix = new XArrayList<IList<T> *>();
    for (int i = 0; i < num_rows; i++) {
        XArrayList<T> *row = new XArrayList<T>();
        for (int j = 0; j < array[i].size(); j++) {
            row->add(array[i].get(j));
        }
        pMatrix->add(row);
    }
}

template <typename T>
List2D<T>::List2D(const List2D<T> &other) {
    // TODO
    pMatrix = new XArrayList<IList<T> *>();
    for (int i = 0; i < other.rows(); i++) {
        XArrayList<T> *row = new XArrayList<T>();
        for (int j = 0; j < other.pMatrix->get(i)->size(); j++) {
            row->add(other.pMatrix->get(i)->get(j));
        }
        pMatrix->add(row);
    }
}

template <typename T>
List2D<T>::~List2D() {
    // TODO
    for (int i = 0; i < pMatrix->size(); i++) {
        delete pMatrix->get(i);
    }
    delete pMatrix;
}

template <typename T>
int List2D<T>::rows() const {
    // TODO
    return pMatrix->size();
}

template <typename T>
void List2D<T>::setRow(int rowIndex, const List1D<T> &row) {
    // TODO
    if (rowIndex < 0 || rowIndex >= pMatrix->size()) {
        throw out_of_range("Row index out of range");
    }

    // Delete the existing row to prevent memory leaks
    delete pMatrix->get(rowIndex);

    // Create a new row
    XArrayList<T> *newRow = new XArrayList<T>();
    for (int i = 0; i < row.size(); i++) {
        newRow->add(row.get(i));
    }

    // Set the new row at the specified index
    // (*pMatrix)[rowIndex] = newRow;
    pMatrix->get(rowIndex) = newRow;
}

template <typename T>
T List2D<T>::get(int rowIndex, int colIndex) const {
    // TODO
    if (rowIndex < 0 || rowIndex >= pMatrix->size()) {
        throw out_of_range("Row index out of range");
    }

    IList<T> *row = pMatrix->get(rowIndex);
    if (colIndex < 0 || colIndex >= row->size()) {
        throw out_of_range("Column index out of range");
    }

    return row->get(colIndex);
}

template <typename T>
List1D<T> List2D<T>::getRow(int rowIndex) const {
    // TODO
    if (rowIndex < 0 || rowIndex >= pMatrix->size()) {
        throw out_of_range("Row index out of range");
    }

    List1D<T> result;
    IList<T> *row = pMatrix->get(rowIndex);
    for (int i = 0; i < row->size(); i++) {
        result.add(row->get(i));
    }
    return result;
}

template <typename T>
string List2D<T>::toString() const {
    // TODO
    stringstream ss;
    ss << "[";
    for (int i = 0; i < pMatrix->size(); i++) {
        IList<T> *row = pMatrix->get(i);
        // ss << "[";
        for (int j = 0; j < row->size(); j++) {
            if constexpr (std::is_fundamental<T>::value) {
                ss << row->toString();
            } else if constexpr (std::is_class<T>::value) {
                ss << row->toString([](T &item) -> string {
                    return item.toString();
                });
            }
            if (j < row->size() - 1)
                ss << ", ";
        }
        // ss << "]";
        if (i < pMatrix->size() - 1)
            ss << ", ";
    }
    ss << "]";
    return ss.str();
}

template <typename T>
ostream &operator<<(ostream &os, const List2D<T> &matrix) {
    // TODO
    os << matrix.toString();
    return os;
}

// -------------------- InventoryManager Method Definitions --------------------
InventoryManager::InventoryManager()
    : attributesMatrix(List2D<InventoryAttribute>()), productNames(List1D<string>()), quantities(List1D<int>()) {
    // TODO
}

InventoryManager::InventoryManager(const List2D<InventoryAttribute> &matrix,
                                   const List1D<string> &names,
                                   const List1D<int> &quantities)
    : attributesMatrix(matrix), productNames(names), quantities(quantities) {
    // TODO
}

InventoryManager::InventoryManager(const InventoryManager &other)
    : attributesMatrix(other.attributesMatrix), productNames(other.productNames), quantities(other.quantities) {
    // TODO
}

int InventoryManager::size() const {
    // TODO
    return attributesMatrix.rows();
}

List1D<InventoryAttribute> InventoryManager::getProductAttributes(int index) const {
    // TODO
    if (index < 0 || index >= attributesMatrix.rows()) {
        throw out_of_range("Product index out of range");
    }
    return attributesMatrix.getRow(index);
}

string InventoryManager::getProductName(int index) const {
    // TODO
}

int InventoryManager::getProductQuantity(int index) const {
    // TODO
}

void InventoryManager::updateQuantity(int index, int newQuantity) {
    // TODO
}

void InventoryManager::addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity) {
    // TODO
}

void InventoryManager::removeProduct(int index) {
    // TODO
}

List1D<string> InventoryManager::query(int attributeName, const double &minValue,
                                       const double &maxValue, int minQuantity, bool ascending) const {
    // TODO
}

void InventoryManager::removeDuplicates() {
    // TODO
}

InventoryManager InventoryManager::merge(const InventoryManager &inv1,
                                         const InventoryManager &inv2) {
    // TODO
}

void InventoryManager::split(InventoryManager &section1,
                             InventoryManager &section2,
                             double ratio) const {
    // TODO
}

List2D<InventoryAttribute> InventoryManager::getAttributesMatrix() const {
    // TODO
}

List1D<string> InventoryManager::getProductNames() const {
    // TODO
}

List1D<int> InventoryManager::getQuantities() const {
    // TODO
}

string InventoryManager::toString() const {
    // TODO
}

#endif /* INVENTORY_MANAGER_H */
