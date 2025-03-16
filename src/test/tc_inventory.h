#include <iostream>
#include "app/inventory.h" 

using namespace std;

void tc_inventory1001() {
    int arr[] = {1, 2, 3, 4, 5};
    List1D<int> list1D(arr, 5);
    
    cout << list1D.toString() << endl;
}

void tc_inventory1002() {
    int row0[] = {1, 2, 3};
    int row1[] = {4, 5, 6};
    int row2[] = {7, 8, 9};
    
    List1D<int> arr2D[] = { List1D<int>(row0, 3), List1D<int>(row1, 3), List1D<int>(row2, 3) };
    
    List2D<int> matrix(arr2D, 3);
    
    cout << matrix.toString() << endl;
}

void tc_inventory1003() {
    InventoryAttribute attrA1("weight", 10);
    InventoryAttribute attrA2("height", 156);
    InventoryAttribute arrA[] = { attrA1, attrA2 };
    int numAttrA = sizeof(arrA) / sizeof(arrA[0]);
    List1D<InventoryAttribute> listAttrA(arrA, numAttrA);

    InventoryAttribute attrB1("weight", 20);
    InventoryAttribute attrB2("depth", 24);
    InventoryAttribute attrB3("height", 100);
    InventoryAttribute arrB[] = { attrB1, attrB2, attrB3 };
    int numAttrB = sizeof(arrB) / sizeof(arrB[0]);
    List1D<InventoryAttribute> listAttrB(arrB, numAttrB);

    InventoryAttribute attrC1("color", 2);
    InventoryAttribute arrC[] = { attrC1 };
    int numAttrC = sizeof(arrC) / sizeof(arrC[0]);
    List1D<InventoryAttribute> listAttrC(arrC, numAttrC);

    List1D<InventoryAttribute> attributesArray[3] = { listAttrA, listAttrB, listAttrC };
    List2D<InventoryAttribute> attributesMatrix(attributesArray, 3);
    
    string namesArray[] = { "Product A", "Product B", "Product C" };
    List1D<string> productNames(namesArray, 3);
    
    int quantitiesArray[] = { 50, 30, 20 };
    List1D<int> quantities(quantitiesArray, 3);

    InventoryManager inventory(attributesMatrix, productNames, quantities);
    
    cout << inventory.toString() << endl;
}

void tc_inventory1004(){
    InventoryAttribute attrA1("weight", 10);
    InventoryAttribute attrA2("height", 156);
    InventoryAttribute arrA[] = { attrA1, attrA2 };
    int numAttrA = sizeof(arrA) / sizeof(arrA[0]);
    List1D<InventoryAttribute> listAttrA(arrA, numAttrA);

    InventoryAttribute attrB1("weight", 20);
    InventoryAttribute attrB2("depth", 24);
    InventoryAttribute attrB3("height", 100);
    InventoryAttribute arrB[] = { attrB1, attrB2, attrB3 };
    int numAttrB = sizeof(arrB) / sizeof(arrB[0]);
    List1D<InventoryAttribute> listAttrB(arrB, numAttrB);

    InventoryAttribute attrC1("color", 2);
    InventoryAttribute arrC[] = { attrC1 };
    int numAttrC = sizeof(arrC) / sizeof(arrC[0]);
    List1D<InventoryAttribute> listAttrC(arrC, numAttrC);

    List1D<InventoryAttribute> attributesArray[3] = { listAttrA, listAttrB, listAttrC };
    List2D<InventoryAttribute> attributesMatrix(attributesArray, 3);

    string namesArray[] = { "Product A", "Product B", "Product C" };
    List1D<string> productNames(namesArray, 3);
    
    int quantitiesArray[] = { 50, 30, 20 };
    List1D<int> quantities(quantitiesArray, 3);

    InventoryManager inventory(attributesMatrix, productNames, quantities);
    
    InventoryAttribute attrD1("weight", 15);
    InventoryAttribute attrD2("height", 140);
    InventoryAttribute arrD[] = { attrD1, attrD2 };
    int numAttrD = sizeof(arrD) / sizeof(arrD[0]);
    List1D<InventoryAttribute> listAttrD(arrD, numAttrD);
    inventory.addProduct(listAttrD, "Product D", 40);
    cout << "\nAfter adding Product D:" << endl;
    cout << inventory.toString() << endl;

    InventoryManager inventory2 = InventoryManager::merge(inventory, inventory);
    cout << "\nAfter merging with itself:" << endl;
    cout << inventory2.toString() << endl;

    InventoryManager section1, section2;
    inventory2.split(section1, section2, 0.5);
    cout << "\nAfter splitting:" << endl;
    cout << "Section 1:" << endl;
    cout << section1.toString() << endl;
    cout << "Section 2:" << endl;
    cout << section2.toString() << endl;
}

void tc_inventory1005(){
    InventoryAttribute attrA1("weight", 10);
    InventoryAttribute attrA2("height", 156);
    InventoryAttribute arrA[] = { attrA1, attrA2 };
    int numAttrA = sizeof(arrA) / sizeof(arrA[0]);
    List1D<InventoryAttribute> listAttrA(arrA, numAttrA);

    InventoryAttribute attrB1("weight", 20);
    InventoryAttribute attrB2("depth", 24);
    InventoryAttribute attrB3("height", 100);
    InventoryAttribute arrB[] = { attrB1, attrB2, attrB3 };
    int numAttrB = sizeof(arrB) / sizeof(arrB[0]);
    List1D<InventoryAttribute> listAttrB(arrB, numAttrB);

    InventoryAttribute attrC1("color", 2);
    InventoryAttribute arrC[] = { attrC1 };
    int numAttrC = sizeof(arrC) / sizeof(arrC[0]);
    List1D<InventoryAttribute> listAttrC(arrC, numAttrC);

    List1D<InventoryAttribute> attributesArray[3] = { listAttrA, listAttrB, listAttrC };
    List2D<InventoryAttribute> attributesMatrix(attributesArray, 3);

    string namesArray[] = { "Product A", "Product B", "Product C" };
    List1D<string> productNames(namesArray, 3);
    
    int quantitiesArray[] = { 50, 30, 20 };
    List1D<int> quantities(quantitiesArray, 3);

    InventoryManager inventory(attributesMatrix, productNames, quantities);

    List1D<string> queryResult = inventory.query(1, 10, 20, 30, true);
    cout << "\nQuery result (weight between 10 and 20, quantity >= 30):" << endl;
    cout << queryResult << endl;
}

void tc_inventory1006(){
    InventoryAttribute attrA1("weight", 10);
    InventoryAttribute attrA2("height", 156);
    InventoryAttribute arrA[] = { attrA1, attrA2 };
    int numAttrA = sizeof(arrA) / sizeof(arrA[0]);
    List1D<InventoryAttribute> listAttrA(arrA, numAttrA);

    InventoryAttribute attrB1("weight", 20);
    InventoryAttribute attrB2("depth", 24);
    InventoryAttribute attrB3("height", 100);
    InventoryAttribute arrB[] = { attrB1, attrB2, attrB3 };
    int numAttrB = sizeof(arrB) / sizeof(arrB[0]);
    List1D<InventoryAttribute> listAttrB(arrB, numAttrB);

    InventoryAttribute attrC1("color", 2);
    InventoryAttribute arrC[] = { attrC1 };
    int numAttrC = sizeof(arrC) / sizeof(arrC[0]);
    List1D<InventoryAttribute> listAttrC(arrC, numAttrC);

    List1D<InventoryAttribute> attributesArray[3] = { listAttrA, listAttrB, listAttrC };
    List2D<InventoryAttribute> attributesMatrix(attributesArray, 3);

    string namesArray[] = { "Product A", "Product B", "Product C" };
    List1D<string> productNames(namesArray, 3);
    
    int quantitiesArray[] = { 50, 30, 20 };
    List1D<int> quantities(quantitiesArray, 3);

    InventoryManager inventory(attributesMatrix, productNames, quantities);

    inventory.addProduct(listAttrA, "Product A", 20);
    cout << "\nAfter adding duplicate of Product A:" << endl;
    cout << inventory.toString() << endl;
    inventory.removeDuplicates();
    cout << "\nAfter removing duplicates:" << endl;
    cout << inventory.toString() << endl;
}
// Custom testcases

void tc_inventory1007() {
    // Create 10 products with random attributes
    string productNames[] = {
        "Laptop", "Smartphone", "Tablet", "Monitor", "Keyboard",
        "Mouse", "Headphones", "Speaker", "Camera", "Printer"
    };
    
    int quantities[] = {100, 150, 75, 50, 200, 120, 80, 90, 60, 40};
    // Create inventory attributes
    InventoryAttribute attrLaptop1("weight", 2500);
    InventoryAttribute attrLaptop2("price", 1200);
    InventoryAttribute attrLaptop3("memory", 16);
    InventoryAttribute arrLaptop[] = { attrLaptop1, attrLaptop2, attrLaptop3 };
    int numAttrLaptop = sizeof(arrLaptop) / sizeof(arrLaptop[0]);
    List1D<InventoryAttribute> listAttrLaptop(arrLaptop, numAttrLaptop);

    InventoryAttribute attrSmartphone1("weight", 200);
    InventoryAttribute attrSmartphone2("price", 800);
    InventoryAttribute attrSmartphone3("memory", 8);
    InventoryAttribute arrSmartphone[] = { attrSmartphone1, attrSmartphone2, attrSmartphone3 };
    int numAttrSmartphone = sizeof(arrSmartphone) / sizeof(arrSmartphone[0]);
    List1D<InventoryAttribute> listAttrSmartphone(arrSmartphone, numAttrSmartphone);

    InventoryAttribute attrTablet1("weight", 450);
    InventoryAttribute attrTablet2("price", 600);
    InventoryAttribute attrTablet3("memory", 4);
    InventoryAttribute arrTablet[] = { attrTablet1, attrTablet2, attrTablet3 };
    int numAttrTablet = sizeof(arrTablet) / sizeof(arrTablet[0]);
    List1D<InventoryAttribute> listAttrTablet(arrTablet, numAttrTablet);

    InventoryAttribute attrMonitor1("weight", 5000);
    InventoryAttribute attrMonitor2("price", 300);
    InventoryAttribute attrMonitor3("size", 27);
    InventoryAttribute arrMonitor[] = { attrMonitor1, attrMonitor2, attrMonitor3 };
    int numAttrMonitor = sizeof(arrMonitor) / sizeof(arrMonitor[0]);
    List1D<InventoryAttribute> listAttrMonitor(arrMonitor, numAttrMonitor);

    InventoryAttribute attrKeyboard1("weight", 850);
    InventoryAttribute attrKeyboard2("price", 100);
    InventoryAttribute attrKeyboard3("keys", 104);
    InventoryAttribute arrKeyboard[] = { attrKeyboard1, attrKeyboard2, attrKeyboard3 };
    int numAttrKeyboard = sizeof(arrKeyboard) / sizeof(arrKeyboard[0]);
    List1D<InventoryAttribute> listAttrKeyboard(arrKeyboard, numAttrKeyboard);

    InventoryAttribute attrMouse1("weight", 120);
    InventoryAttribute attrMouse2("price", 50);
    InventoryAttribute attrMouse3("buttons", 3);
    InventoryAttribute arrMouse[] = { attrMouse1, attrMouse2, attrMouse3 };
    int numAttrMouse = sizeof(arrMouse) / sizeof(arrMouse[0]);
    List1D<InventoryAttribute> listAttrMouse(arrMouse, numAttrMouse);

    InventoryAttribute attrHeadphones1("weight", 300);
    InventoryAttribute attrHeadphones2("price", 150);
    InventoryAttribute attrHeadphones3("wireless", 1);
    InventoryAttribute arrHeadphones[] = { attrHeadphones1, attrHeadphones2, attrHeadphones3 };
    int numAttrHeadphones = sizeof(arrHeadphones) / sizeof(arrHeadphones[0]);
    List1D<InventoryAttribute> listAttrHeadphones(arrHeadphones, numAttrHeadphones);

    InventoryAttribute attrSpeaker1("weight", 1500);
    InventoryAttribute attrSpeaker2("price", 200);
    InventoryAttribute attrSpeaker3("power", 60);
    InventoryAttribute arrSpeaker[] = { attrSpeaker1, attrSpeaker2, attrSpeaker3 };
    int numAttrSpeaker = sizeof(arrSpeaker) / sizeof(arrSpeaker[0]);
    List1D<InventoryAttribute> listAttrSpeaker(arrSpeaker, numAttrSpeaker);

    InventoryAttribute attrCamera1("weight", 750);
    InventoryAttribute attrCamera2("price", 700);
    InventoryAttribute attrCamera3("megapixel", 24);
    InventoryAttribute arrCamera[] = { attrCamera1, attrCamera2, attrCamera3 };
    int numAttrCamera = sizeof(arrCamera) / sizeof(arrCamera[0]);
    List1D<InventoryAttribute> listAttrCamera(arrCamera, numAttrCamera);

    InventoryAttribute attrPrinter1("weight", 8000);
    InventoryAttribute attrPrinter2("price", 250);
    InventoryAttribute attrPrinter3("color", 1);
    InventoryAttribute arrPrinter[] = { attrPrinter1, attrPrinter2, attrPrinter3 };
    int numAttrPrinter = sizeof(arrPrinter) / sizeof(arrPrinter[0]);
    List1D<InventoryAttribute> listAttrPrinter(arrPrinter, numAttrPrinter);

    List1D<InventoryAttribute> attributesArray[10] = { 
        listAttrLaptop, listAttrSmartphone, listAttrTablet, listAttrMonitor, listAttrKeyboard,
        listAttrMouse, listAttrHeadphones, listAttrSpeaker, listAttrCamera, listAttrPrinter 
    };
    
    // Create attribute matrix, product names list, and quantities list
    List2D<InventoryAttribute> attributesMatrix(attributesArray, 10);
    List1D<string> productNamesList(productNames, 10);
    List1D<int> quantitiesList(quantities, 10);
    
    // Create inventory manager
    InventoryManager inventory(attributesMatrix, productNamesList, quantitiesList);
    
    // Display inventory
    cout << "Inventory with 10 products:" << endl;
    cout << inventory.toString() << endl;
    // Test 1: Remove a product by index
    cout << "\nTest 1: Remove product by index (Tablet at index 2)" << endl;
    inventory.removeProduct(2);
    cout << "After removing Tablet:" << endl;
    cout << inventory.toString() << endl;

    // Test 2: Split inventory into two sections
    cout << "\nTest 2: Split inventory into two sections (ratio 0.6)" << endl;
    InventoryManager section1;
    InventoryManager section2;
    inventory.split(section1, section2, 0.6);

    cout << "Section 1 (60% of inventory):" << endl;
    cout << section1.toString() << endl;

    cout << "Section 2 (40% of inventory):" << endl;
    cout << section2.toString() << endl;

    // Verify that both sections combined should have the same total quantity
    // int totalSection1 = 0;
    // int totalSection2 = 0;
    // for (int i = 0; i < section1.getQuantities().getSize(); i++) {
    //     totalSection1 += section1.getQuantities()[i];
    // }
    // for (int i = 0; i < section2.getQuantities().getSize(); i++) {
    //     totalSection2 += section2.getQuantities()[i];
    // }
    // cout << "Total quantities - Section 1: " << totalSection1 
    //      << ", Section 2: " << totalSection2 
    //      << ", Combined: " << (totalSection1 + totalSection2) << endl;

}