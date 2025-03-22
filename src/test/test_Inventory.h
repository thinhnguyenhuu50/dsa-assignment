#ifndef TEST_INVENTORY_H
#define TEST_INVENTORY_H

#include "app/inventory.h"
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>

class TestInventory {
private:
    static string toString(int value) {
        return to_string(value);
    }

    static string toString(string value) {
        return value;
    }

    static string toString(InventoryAttribute attr) {
        return attr.toString();
    }

public:
    // Test List1D methods
    static void testList1D() {
        cout << "\n=== Testing List1D ===\n";
        
        // Constructor tests
        cout << "Testing List1D constructors..." << endl;
        List1D<int> list1;
        assert(list1.size() == 0);
        
        List1D<int> list2(5);
        assert(list2.size() == 5);
        
        int arr[] = {10, 20, 30, 40, 50};
        List1D<int> list3(arr, 5);
        assert(list3.size() == 5);
        assert(list3.get(0) == 10);
        assert(list3.get(4) == 50);
        
        List1D<int> list4(list3);
        assert(list4.size() == 5);
        assert(list4.get(0) == 10);
        
        // Basic methods
        cout << "Testing List1D methods..." << endl;
        list1.add(100);
        list1.add(200);
        assert(list1.size() == 2);
        assert(list1.get(0) == 100);
        assert(list1.get(1) == 200);
        
        list1.set(0, 300);
        assert(list1.get(0) == 300);
        
        list1.add(1, 150);
        assert(list1.size() == 3);
        assert(list1.get(0) == 300);
        assert(list1.get(1) == 150);
        assert(list1.get(2) == 200);
        
        list1.removeAt(1);
        assert(list1.size() == 2);
        assert(list1.get(0) == 300);
        assert(list1.get(1) == 200);
        
        // toString test
        string expected = "[300, 200]";
        string actual = list1.toString();
        assert(actual == expected);
        
        // Clear and assignment
        list1.clear();
        assert(list1.size() == 0);
        
        list1 = list3;
        assert(list1.size() == 5);
        assert(list1.get(0) == 10);
        assert(list1.get(4) == 50);
        
        cout << "List1D tests passed!" << endl;
    }
    
    // Test List2D methods
    static void testList2D() {
        cout << "\n=== Testing List2D ===\n";
        
        // Constructor tests
        cout << "Testing List2D constructors..." << endl;
        List2D<int> matrix1;
        assert(matrix1.rows() == 0);
        
        List1D<int> rows[3];
        rows[0].add(1);
        rows[0].add(2);
        rows[1].add(3);
        rows[1].add(4);
        rows[2].add(5);
        rows[2].add(6);
        
        List2D<int> matrix2(rows, 3);
        assert(matrix2.rows() == 3);
        
        List2D<int> matrix3(matrix2);
        assert(matrix3.rows() == 3);
        
        // Basic methods
        cout << "Testing List2D methods..." << endl;
        assert(matrix2.get(0, 0) == 1);
        assert(matrix2.get(1, 1) == 4);
        assert(matrix2.get(2, 1) == 6);
        
        List1D<int> row = matrix2.getRow(1);
        assert(row.size() == 2);
        assert(row.get(0) == 3);
        assert(row.get(1) == 4);
        
        List1D<int> newRow;
        newRow.add(7);
        newRow.add(8);
        newRow.add(9);
        matrix2.setRow(1, newRow);
        row = matrix2.getRow(1);
        assert(row.size() == 3);
        assert(row.get(0) == 7);
        assert(row.get(2) == 9);
        
        // Add row
        XArrayList<int>* newRowList = new XArrayList<int>();
        newRowList->add(10);
        newRowList->add(11);
        matrix2.add(newRowList);
        assert(matrix2.rows() == 4);
        assert(matrix2.get(3, 0) == 10);
        
        // Remove row
        matrix2.removeAt(1);
        assert(matrix2.rows() == 3);
        assert(matrix2.get(1, 0) == 5); // This was row 2 before removal
        
        // Assignment operator
        List2D<int> matrix4;
        matrix4 = matrix2;
        assert(matrix4.rows() == 3);
        assert(matrix4.get(0, 0) == 1);
        assert(matrix4.get(1, 0) == 5);
        
        // Clear
        matrix4.clear();
        assert(matrix4.rows() == 0);
        
        cout << "List2D tests passed!" << endl;
    }
    
    // Test InventoryAttribute
    static void testInventoryAttribute() {
        cout << "\n=== Testing InventoryAttribute ===\n";
        
        InventoryAttribute attr1("Price", 19.99);
        InventoryAttribute attr2("Weight", 2.5);
        InventoryAttribute attr3("Price", 19.99);
        
        assert(attr1.name == "Price");
        assert(attr1.value == 19.99);
        
        assert(attr1 == attr3);
        assert(!(attr1 == attr2));
        
        assert(attr1.toString() == "Price: 19.990000");
        
        InventoryAttribute attr4(attr1);
        assert(attr4 == attr1);
        
        cout << "InventoryAttribute tests passed!" << endl;
    }
    
    // Test InventoryManager
    static void testInventoryManager() {
        cout << "\n=== Testing InventoryManager ===\n";
        
        // Constructor tests
        cout << "Testing InventoryManager constructors..." << endl;
        InventoryManager inv1;
        assert(inv1.size() == 0);
        
        // Add products and test basic methods
        cout << "Testing adding products and basic methods..." << endl;
        List1D<InventoryAttribute> laptop_attrs;
        laptop_attrs.add(InventoryAttribute("Price", 999.99));
        laptop_attrs.add(InventoryAttribute("Weight", 2.5));
        inv1.addProduct(laptop_attrs, "Laptop", 10);
        
        List1D<InventoryAttribute> phone_attrs;
        phone_attrs.add(InventoryAttribute("Price", 699.99));
        phone_attrs.add(InventoryAttribute("Weight", 0.2));
        inv1.addProduct(phone_attrs, "Phone", 20);
        
        assert(inv1.size() == 2);
        assert(inv1.getProductName(0) == "Laptop");
        assert(inv1.getProductQuantity(0) == 10);
        
        List1D<InventoryAttribute> attrs = inv1.getProductAttributes(0);
        assert(attrs.size() == 2);
        assert(attrs.get(0).name == "Price");
        assert(attrs.get(0).value == 999.99);
        
        // Update quantity
        cout << "Testing updateQuantity..." << endl;
        inv1.updateQuantity(0, 15);
        assert(inv1.getProductQuantity(0) == 15);
        
        // Remove product
        cout << "Testing removeProduct..." << endl;
        inv1.removeProduct(0);
        assert(inv1.size() == 1);
        assert(inv1.getProductName(0) == "Phone");
        
        // Test query
        cout << "Testing query..." << endl;
        List1D<InventoryAttribute> tablet_attrs;
        tablet_attrs.add(InventoryAttribute("Price", 499.99));
        tablet_attrs.add(InventoryAttribute("Weight", 0.5));
        inv1.addProduct(tablet_attrs, "Tablet", 15);
        
        List1D<InventoryAttribute> desktop_attrs;
        desktop_attrs.add(InventoryAttribute("Price", 1299.99));
        desktop_attrs.add(InventoryAttribute("Weight", 10.0));
        inv1.addProduct(desktop_attrs, "Desktop", 5);
        
        // Query for products with price between 400 and 700 and quantity >= 10
        List1D<string> results = inv1.query("Price", 400.0, 700.0, 10, true);
        assert(results.size() == 2);
        assert(results.get(0) == "Tablet"); // Lower price (ascending)
        assert(results.get(1) == "Phone");
        
        // Test removeDuplicates
        cout << "Testing removeDuplicates..." << endl;
        List1D<InventoryAttribute> dupe_attrs;
        dupe_attrs.add(InventoryAttribute("Price", 699.99));
        dupe_attrs.add(InventoryAttribute("Weight", 0.2));
        inv1.addProduct(dupe_attrs, "Phone", 5);
        
        assert(inv1.size() == 4);
        inv1.removeDuplicates();
        assert(inv1.size() == 3);
        // Check that quantities were combined
        assert(inv1.getProductQuantity(0) == 25); // 20 + 5
        
        // Test merge
        cout << "Testing merge..." << endl;
        InventoryManager inv2;
        List1D<InventoryAttribute> watch_attrs;
        watch_attrs.add(InventoryAttribute("Price", 299.99));
        watch_attrs.add(InventoryAttribute("Weight", 0.1));
        inv2.addProduct(watch_attrs, "Watch", 30);
        
        InventoryManager merged = InventoryManager::merge(inv1, inv2);
        assert(merged.size() == 4); // 3 from inv1 + 1 from inv2
        assert(merged.getProductName(3) == "Watch");
        
        // Test split
        cout << "Testing split..." << endl;
        InventoryManager section1, section2;
        merged.split(section1, section2, 0.75); // 75% in section1
        
        assert(section1.size() == 3);
        assert(section2.size() == 1);
        assert(section1.getProductName(0) == "Phone");
        assert(section2.getProductName(0) == "Watch");
        
        // Test getters and toString
        cout << "Testing getters and toString..." << endl;
        List2D<InventoryAttribute> attrMatrix = inv1.getAttributesMatrix();
        List1D<string> names = inv1.getProductNames();
        List1D<int> quantities = inv1.getQuantities();
        
        assert(attrMatrix.rows() == 3);
        assert(names.size() == 3);
        assert(quantities.size() == 3);
        
        string str = inv1.toString();
        assert(str.length() > 0); // Just make sure it returns something
        
        // Test clear and assignment
        cout << "Testing clear and assignment..." << endl;
        inv2.clear();
        assert(inv2.size() == 0);
        
        inv2 = inv1;
        assert(inv2.size() == 3);
        assert(inv2.getProductName(0) == inv1.getProductName(0));
        
        cout << "InventoryManager tests passed!" << endl;
    }
    // Test time complexity of removeDuplicates
    static void testRemoveDuplicatesComplexity() {
        cout << "\n=== Testing removeDuplicates Time Complexity ===\n";
        
        const int SIZES[] = {100, 200, 400, 800, 1600};
        const int REPEATS = 5;
        
        for (int size : SIZES) {
            InventoryManager inv;
            
            // Generate inventory with many products but only a few unique ones
            for (int i = 0; i < size; i++) {
                List1D<InventoryAttribute> attrs;
                // Only use 10 different prices to ensure duplicates
                double price = 100.0 + (i % 10) * 100;
                attrs.add(InventoryAttribute("Price", price));
                attrs.add(InventoryAttribute("Weight", 1.0));
                
                // Only use 10 different product names to ensure duplicates
                string name = "Product" + to_string(i % 10);
                inv.addProduct(attrs, name, 1);
            }
            
            // Measure time for removeDuplicates
            clock_t start = clock();
            for (int i = 0; i < REPEATS; i++) {
                // Create a copy to test with
                InventoryManager testInv = inv;
                testInv.removeDuplicates();
            }
            clock_t end = clock();
            
            double elapsed = static_cast<double>(end - start) / CLOCKS_PER_SEC / REPEATS;
            cout << "Size " << size << ": " << elapsed << " seconds" << endl;
            
            // If this is quadratic time, the ratio should be approximately 4
            // when we double the size
            if (size > SIZES[0]) {
                cout << "Ratio to previous: " << (elapsed / static_cast<double>(end - start) / CLOCKS_PER_SEC / REPEATS) << endl;
            }
        }
        
        // Check that after removing duplicates we have only 10 unique products
        InventoryManager finalTest;
        for (int i = 0; i < 100; i++) {
            List1D<InventoryAttribute> attrs;
            attrs.add(InventoryAttribute("Price", 100.0 + (i % 10) * 100));
            finalTest.addProduct(attrs, "Product" + to_string(i % 10), 1);
        }
        
        finalTest.removeDuplicates();
        assert(finalTest.size() == 10);
        
        cout << "removeDuplicates complexity test completed." << endl;
    }

    // Test worst-case time complexity with many attributes
    static void testRemoveDuplicatesWorstCase() {
        cout << "\n=== Testing removeDuplicates Worst Case Time Complexity ===\n";
        
        const int SIZES[] = {100, 200, 400, 800};
        const int REPEATS = 3;
        
        for (int size : SIZES) {
            InventoryManager inv;
            
            // Generate inventory with many products with many attributes
            for (int i = 0; i < size; i++) {
                List1D<InventoryAttribute> attrs;
                // Add many attributes to make comparison more expensive
                for (int j = 0; j < i % 50 + 10; j++) {  // Variable number of attributes
                    attrs.add(InventoryAttribute("Attr" + to_string(j), j * 1.5));
                }
                
                // Only use 10 different product names to ensure duplicates
                string name = "Product" + to_string(i % 10);
                inv.addProduct(attrs, name, 1);
            }
            
            // Measure time for removeDuplicates
            clock_t start = clock();
            for (int i = 0; i < REPEATS; i++) {
                // Create a copy to test with
                InventoryManager testInv = inv;
                testInv.removeDuplicates();
            }
            clock_t end = clock();
            
            double elapsed = static_cast<double>(end - start) / CLOCKS_PER_SEC / REPEATS;
            cout << "Size " << size << " with many attributes: " << elapsed << " seconds" << endl;
            
            // For quadratic complexity, when doubling the input size, time should roughly quadruple
            if (size > SIZES[0]) {
                double previousTimeForHalfSize = 0;
                for (int j = 0; j < sizeof(SIZES)/sizeof(SIZES[0]); j++) {
                    if (SIZES[j] == size/2) {
                        // This would be a very rough estimate and should be improved
                        cout << "Ratio compared to half size: " << elapsed / previousTimeForHalfSize 
                             << " (expect ~4 for O(n^2))" << endl;
                        break;
                    }
                    previousTimeForHalfSize = elapsed;
                }
            }
        }
        
        cout << "removeDuplicates worst case complexity test completed." << endl;
    }
    // Run all tests
    static void runAllTests() {
        cout << "\n=== Running All Inventory Tests ===\n";
        testList1D();
        testList2D();
        testInventoryAttribute();
        testInventoryManager();
        cout << "\nAll inventory tests passed successfully!" << endl;
    }
};

#endif /* TEST_INVENTORY_H */