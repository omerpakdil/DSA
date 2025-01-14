#include "linked_list.h"
#include <cassert>
#include <string>

// Temel operasyonların testi
void testBasicOperations() {
    LinkedList<int> list;
    
    // Boş liste kontrolü
    assert(list.empty());
    assert(list.getSize() == 0);
    
    // pushBack testi
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    assert(list.getSize() == 3);
    assert(list.front() == 1);
    assert(list.back() == 3);
    
    // pushFront testi
    list.pushFront(0);
    assert(list.getSize() == 4);
    assert(list.front() == 0);
    
    // insert testi
    list.insert(2, 5);  // 0 -> 1 -> 5 -> 2 -> 3
    assert(list.getSize() == 5);
    assert(list.at(2) == 5);
    
    std::cout << "Temel operasyon testleri başarılı!" << std::endl;
}

// Silme operasyonlarının testi
void testRemovalOperations() {
    LinkedList<int> list;
    for (int i = 0; i < 5; i++) {
        list.pushBack(i);  // 0 -> 1 -> 2 -> 3 -> 4
    }
    
    // popFront testi
    list.popFront();  // 1 -> 2 -> 3 -> 4
    assert(list.getSize() == 4);
    assert(list.front() == 1);
    
    // popBack testi
    list.popBack();  // 1 -> 2 -> 3
    assert(list.getSize() == 3);
    assert(list.back() == 3);
    
    // index ile silme testi
    list.remove(1);  // 1 -> 3
    assert(list.getSize() == 2);
    assert(list.at(1) == 3);
    
    // değer ile silme testi
    list.removeValue(1);  // 3
    assert(list.getSize() == 1);
    assert(list.front() == 3);
    
    std::cout << "Silme operasyonları testleri başarılı!" << std::endl;
}

// Arama operasyonlarının testi
void testSearchOperations() {
    LinkedList<int> list;
    for (int i = 0; i < 5; i++) {
        list.pushBack(i);  // 0 -> 1 -> 2 -> 3 -> 4
    }
    
    // contains testi
    assert(list.contains(3) == true);
    assert(list.contains(10) == false);
    
    // find testi
    assert(list.find(3) == 3);
    assert(list.find(10) == list.getSize());
    
    std::cout << "Arama operasyonları testleri başarılı!" << std::endl;
}

// İstatistiksel operasyonların testi
void testStatisticalOperations() {
    LinkedList<int> list;
    for (int i = 1; i <= 5; i++) {
        list.pushBack(i);  // 1 -> 2 -> 3 -> 4 -> 5
    }
    
    assert(list.getMax() == 5);
    assert(list.getMin() == 1);
    assert(list.getSum() == 15);
    assert(list.getAverage() == 3.0);
    
    std::cout << "İstatistiksel operasyon testleri başarılı!" << std::endl;
}

// Manipülasyon operasyonlarının testi
void testManipulationOperations() {
    LinkedList<int> list;
    for (int i = 1; i <= 5; i++) {
        list.pushBack(i);  // 1 -> 2 -> 3 -> 4 -> 5
    }
    
    // reverse testi
    list.reverse();  // 5 -> 4 -> 3 -> 2 -> 1
    assert(list.front() == 5);
    assert(list.back() == 1);
    
    // sort testi
    list.sort();  // 1 -> 2 -> 3 -> 4 -> 5
    assert(list.front() == 1);
    assert(list.back() == 5);
    
    std::cout << "Manipülasyon operasyonları testleri başarılı!" << std::endl;
}

// Birleştirme operasyonlarının testi
void testMergeOperations() {
    LinkedList<int> list1;
    LinkedList<int> list2;
    
    // İki sıralı liste oluştur
    list1.pushBack(1);
    list1.pushBack(3);
    list1.pushBack(5);
    
    list2.pushBack(2);
    list2.pushBack(4);
    list2.pushBack(6);
    
    // concat testi
    LinkedList<int> concatList = list1;
    concatList.concat(list2);  // 1 -> 3 -> 5 -> 2 -> 4 -> 6
    assert(concatList.getSize() == 6);
    
    // merge testi
    LinkedList<int> mergedList = list1.merge(list2);  // 1 -> 2 -> 3 -> 4 -> 5 -> 6
    assert(mergedList.getSize() == 6);
    assert(mergedList.front() == 1);
    assert(mergedList.back() == 6);
    
    std::cout << "Birleştirme operasyonları testleri başarılı!" << std::endl;
}

// Özel operasyonların testi
void testSpecialOperations() {
    LinkedList<int> list;
    for (int i = 1; i <= 5; i++) {
        list.pushBack(i);  // 1 -> 2 -> 3 -> 4 -> 5
    }
    
    // findMiddle testi
    auto middle = list.findMiddle();
    assert(middle->data == 3);
    
    std::cout << "Özel operasyon testleri başarılı!" << std::endl;
}

// String operasyonlarının testi
void testStringOperations() {
    LinkedList<std::string> list;
    
    list.pushBack("Hello");
    list.pushBack("World");
    list.pushBack("!");
    
    assert(list.getSize() == 3);
    assert(list.front() == "Hello");
    assert(list.back() == "!");
    
    list.reverse();  // ! -> World -> Hello
    assert(list.front() == "!");
    assert(list.back() == "Hello");
    
    std::cout << "String operasyonları testleri başarılı!" << std::endl;
}

int main() {
    try {
        testBasicOperations();
        testRemovalOperations();
        testSearchOperations();
        testStatisticalOperations();
        testManipulationOperations();
        testMergeOperations();
        testSpecialOperations();
        testStringOperations();
        
        std::cout << "\nTüm testler başarıyla tamamlandı!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test hatası: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
