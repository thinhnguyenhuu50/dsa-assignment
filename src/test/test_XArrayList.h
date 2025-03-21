/*
 * File:   test_XArrayList.h
 */

#ifndef TEST_XARRAYLIST_H
#define TEST_XARRAYLIST_H

#include "list/XArrayList.h"
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>

class TestXArrayList {
private:
    // Helper function to convert int to string for testing
    static string intToString(int& value) {
        return to_string(value);
    }

    // Helper function to convert int pointer to string for testing
    static string intPtrToString(int*& value) {
        return to_string(*value);
    }

    // Helper function for pointer equality
    static bool intPtrEqual(int*& a, int*& b) {
        return *a == *b;
    }

    // Helper function for deleting int pointers
    static void deleteIntPtr(int* item) {
        delete item;
    }

    // Helper function for freeing XArrayList of pointers
    static void freeIntPtrList(XArrayList<int*>* list) {
        XArrayList<int*>::free(list);
    }

public:
    static void testConstructor() {
        cout << "Testing constructor..." << endl;
        
        XArrayList<int> list;
        assert(list.empty());
        assert(list.size() == 0);
        
        cout << "Constructor test passed!" << endl;
    }

    static void testAdd() {
        cout << "Testing add method..." << endl;
        
        XArrayList<int> list;
        list.add(10);
        list.add(20);
        list.add(30);
        
        assert(list.size() == 3);
        assert(list.get(0) == 10);
        assert(list.get(1) == 20);
        assert(list.get(2) == 30);
        
        cout << "Add method test passed!" << endl;
    }

    static void testAddAtIndex() {
        cout << "Testing add at index method..." << endl;
        
        XArrayList<int> list;
        list.add(10);
        list.add(20);
        list.add(30);
        
        list.add(1, 15);
        
        assert(list.size() == 4);
        assert(list.get(0) == 10);
        assert(list.get(1) == 15);
        assert(list.get(2) == 20);
        assert(list.get(3) == 30);
        
        // Test edge cases
        list.add(0, 5);
        assert(list.get(0) == 5);
        
        list.add(list.size(), 40);
        assert(list.get(list.size() - 1) == 40);
        
        // Test invalid index
        bool exceptionThrown = false;
        try {
            list.add(-1, 100);
        } catch (const out_of_range&) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);
        
        exceptionThrown = false;
        try {
            list.add(list.size() + 1, 100);
        } catch (const out_of_range&) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);
        
        cout << "Add at index method test passed!" << endl;
    }

    static void testRemoveAt() {
        cout << "Testing removeAt method..." << endl;
        
        XArrayList<int> list;
        list.add(10);
        list.add(20);
        list.add(30);
        
        int removed = list.removeAt(1);
        assert(removed == 20);
        assert(list.size() == 2);
        assert(list.get(0) == 10);
        assert(list.get(1) == 30);
        
        // Test removing from beginning and end
        list.add(40);
        removed = list.removeAt(0);
        assert(removed == 10);
        assert(list.size() == 2);
        
        removed = list.removeAt(list.size() - 1);
        assert(removed == 40);
        assert(list.size() == 1);
        
        // Test invalid index
        bool exceptionThrown = false;
        try {
            list.removeAt(-1);
        } catch (const out_of_range&) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);
        
        exceptionThrown = false;
        try {
            list.removeAt(list.size());
        } catch (const out_of_range&) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);
        
        cout << "RemoveAt method test passed!" << endl;
    }

    static void testRemoveItem() {
        cout << "Testing removeItem method..." << endl;
        
        XArrayList<int> list;
        list.add(10);
        list.add(20);
        list.add(30);
        
        bool removed = list.removeItem(20);
        assert(removed);
        assert(list.size() == 2);
        assert(list.get(0) == 10);
        assert(list.get(1) == 30);
        
        // Test removing non-existent item
        removed = list.removeItem(100);
        assert(!removed);
        assert(list.size() == 2);
        
        cout << "RemoveItem method test passed!" << endl;
    }
    
    static void testRemoveItemWithPointers() {
        cout << "Testing removeItem method with pointers..." << endl;
        
        XArrayList<int*> list(freeIntPtrList, intPtrEqual);
        
        int* p1 = new int(10);
        int* p2 = new int(20);
        int* p3 = new int(30);
        
        list.add(p1);
        list.add(p2);
        list.add(p3);
        
        int* testVal = new int(20);
        bool removed = list.removeItem(testVal, deleteIntPtr);
        assert(removed);
        assert(list.size() == 2);
        
        delete testVal;
        list.clear();
        
        cout << "RemoveItem with pointers test passed!" << endl;
    }

    static void testEmpty() {
        cout << "Testing empty method..." << endl;
        
        XArrayList<int> list;
        assert(list.empty());
        
        list.add(10);
        assert(!list.empty());
        
        list.removeAt(0);
        assert(list.empty());
        
        cout << "Empty method test passed!" << endl;
    }

    static void testSize() {
        cout << "Testing size method..." << endl;
        
        XArrayList<int> list;
        assert(list.size() == 0);
        
        list.add(10);
        list.add(20);
        assert(list.size() == 2);
        
        list.removeAt(0);
        assert(list.size() == 1);
        
        list.clear();
        assert(list.size() == 0);
        
        cout << "Size method test passed!" << endl;
    }

    static void testClear() {
        cout << "Testing clear method..." << endl;
        
        XArrayList<int> list;
        list.add(10);
        list.add(20);
        list.add(30);
        
        list.clear();
        assert(list.empty());
        assert(list.size() == 0);
        
        // Test that we can add after clearing
        list.add(40);
        assert(list.size() == 1);
        assert(list.get(0) == 40);
        
        cout << "Clear method test passed!" << endl;
    }

    static void testGet() {
        cout << "Testing get method..." << endl;
        
        XArrayList<int> list;
        list.add(10);
        list.add(20);
        list.add(30);
        
        assert(list.get(0) == 10);
        assert(list.get(1) == 20);
        assert(list.get(2) == 30);
        
        // Test invalid index
        bool exceptionThrown = false;
        try {
            list.get(-1);
        } catch (const out_of_range&) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);
        
        exceptionThrown = false;
        try {
            list.get(list.size());
        } catch (const out_of_range&) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);
        
        cout << "Get method test passed!" << endl;
    }

    static void testIndexOf() {
        cout << "Testing indexOf method..." << endl;
        
        XArrayList<int> list;
        list.add(10);
        list.add(20);
        list.add(30);
        list.add(20);
        
        assert(list.indexOf(10) == 0);
        assert(list.indexOf(20) == 1);  // Returns first occurrence
        assert(list.indexOf(30) == 2);
        assert(list.indexOf(100) == -1);
        
        cout << "IndexOf method test passed!" << endl;
    }

    static void testContains() {
        cout << "Testing contains method..." << endl;
        
        XArrayList<int> list;
        list.add(10);
        list.add(20);
        list.add(30);
        
        assert(list.contains(10));
        assert(list.contains(20));
        assert(list.contains(30));
        assert(!list.contains(100));
        
        cout << "Contains method test passed!" << endl;
    }

    static void testToString() {
        cout << "Testing toString method..." << endl;
        
        XArrayList<int> list;
        list.add(10);
        list.add(20);
        list.add(30);
        
        string expected = "[10, 20, 30]";
        assert(list.toString(intToString) == expected);
        
        cout << "ToString method test passed!" << endl;
    }

    static void testIterator() {
        cout << "Testing iterator..." << endl;
        
        XArrayList<int> list;
        list.add(10);
        list.add(20);
        list.add(30);
        
        int sum = 0;
        for (auto it = list.begin(); it != list.end(); it++) {
            sum += *it;
        }
        assert(sum == 60);
        
        // Test iterator removal
        auto it = list.begin();
        it++; // Move to second element
        it.remove();
        assert(list.size() == 2);
        assert(list.get(0) == 10);
        assert(list.get(1) == 30);
        
        cout << "Iterator test passed!" << endl;
    }

    static void testCopyConstructor() {
        cout << "Testing copy constructor..." << endl;
        
        XArrayList<int> list;
        list.add(10);
        list.add(20);
        list.add(30);
        
        XArrayList<int> copy(list);
        assert(copy.size() == list.size());
        
        for (int i = 0; i < list.size(); i++) {
            assert(copy.get(i) == list.get(i));
        }
        
        // Modify original list and check that copy is unchanged
        list.add(40);
        assert(copy.size() == 3);
        assert(list.size() == 4);
        
        cout << "Copy constructor test passed!" << endl;
    }

    static void testAssignmentOperator() {
        cout << "Testing assignment operator..." << endl;
        
        XArrayList<int> list1;
        list1.add(10);
        list1.add(20);
        list1.add(30);
        
        XArrayList<int> list2;
        list2.add(100);
        list2.add(200);
        
        list2 = list1;
        assert(list2.size() == list1.size());
        
        for (int i = 0; i < list1.size(); i++) {
            assert(list2.get(i) == list1.get(i));
        }
        
        // Self assignment
        list1 = list1;
        assert(list1.size() == 3);
        assert(list1.get(0) == 10);
        
        cout << "Assignment operator test passed!" << endl;
    }

    static void testCapacity() {
        cout << "Testing capacity handling..." << endl;
        
        XArrayList<int> list;
        // Add more elements than the default capacity
        for (int i = 0; i < 20; i++) {
            list.add(i);
        }
        
        assert(list.size() == 20);
        for (int i = 0; i < 20; i++) {
            assert(list.get(i) == i);
        }
        
        cout << "Capacity handling test passed!" << endl;
    }

    static void runAllTests() {
        testConstructor();
        testAdd();
        testAddAtIndex();
        testRemoveAt();
        testRemoveItem();
        testRemoveItemWithPointers();
        testEmpty();
        testSize();
        testClear();
        testGet();
        testIndexOf();
        testContains();
        testToString();
        testIterator();
        testCopyConstructor();
        testAssignmentOperator();
        testCapacity();
        
        cout << "All tests passed successfully!" << endl;
    }
};

#endif /* TEST_XARRAYLIST_H */