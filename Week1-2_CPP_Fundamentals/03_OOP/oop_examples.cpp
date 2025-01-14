#include <iostream>
#include <string>
#include <memory>

// Temel class örneği
class Student {
private:
    int id;
    std::string name;
    double gpa;

public:
    // Constructor
    Student(int id, std::string name, double gpa) 
        : id(id), name(name), gpa(gpa) {}
    
    // Copy constructor
    Student(const Student& other) 
        : id(other.id), name(other.name), gpa(other.gpa) {
        std::cout << "Copy constructor çağrıldı" << std::endl;
    }
    
    // Move constructor
    Student(Student&& other) noexcept 
        : id(other.id), name(std::move(other.name)), gpa(other.gpa) {
        std::cout << "Move constructor çağrıldı" << std::endl;
    }
    
    // Getter methods
    int getId() const { return id; }
    std::string getName() const { return name; }
    double getGpa() const { return gpa; }
    
    // Öğrenci bilgilerini göster
    void display() const {
        std::cout << "ID: " << id << ", İsim: " << name << ", Not: " << gpa << std::endl;
    }
};

// Abstract class örneği
class Shape {
public:
    virtual double calculateArea() = 0;
    virtual double calculatePerimeter() = 0;
    virtual ~Shape() = default;
};

// Derived class örneği
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}
    
    double calculateArea() override {
        return 3.14159 * radius * radius;
    }
    
    double calculatePerimeter() override {
        return 2 * 3.14159 * radius;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double calculateArea() override {
        return width * height;
    }
    
    double calculatePerimeter() override {
        return 2 * (width + height);
    }
};

// Polymorphism örneği
class Animal {
public:
    virtual void makeSound() = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void makeSound() override {
        std::cout << "Köpek havlıyor: Hav hav!" << std::endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        std::cout << "Kedi miyavlıyor: Miyav!" << std::endl;
    }
};

// Multiple inheritance örneği
class Printer {
public:
    virtual void print() {
        std::cout << "Döküman yazdırılıyor..." << std::endl;
    }
};

class Scanner {
public:
    virtual void scan() {
        std::cout << "Döküman taranıyor..." << std::endl;
    }
};

class AllInOne : public Printer, public Scanner {
public:
    void print() override {
        std::cout << "All-in-One yazıcıdan yazdırılıyor..." << std::endl;
    }
    
    void scan() override {
        std::cout << "All-in-One tarayıcıdan taranıyor..." << std::endl;
    }
};

// Template class örneği
template<typename T>
class Container {
private:
    T* data;
    size_t size;

public:
    Container(size_t s) : size(s) {
        data = new T[size];
    }
    
    ~Container() {
        delete[] data;
    }
    
    void setElement(size_t index, T value) {
        if (index < size) {
            data[index] = value;
        }
    }
    
    T getElement(size_t index) const {
        if (index < size) {
            return data[index];
        }
        throw std::out_of_range("Index sınırların dışında");
    }
};

// Smart pointer kullanım örneği
class Resource {
public:
    Resource() {
        std::cout << "Resource oluşturuldu" << std::endl;
    }
    
    ~Resource() {
        std::cout << "Resource yok edildi" << std::endl;
    }
    
    void use() {
        std::cout << "Resource kullanılıyor" << std::endl;
    }
};

int main() {
    std::cout << "=== OOP Examples ===" << std::endl;
    
    // Basic class usage
    Student student(1, "John Doe", 3.8);
    student.display();
    
    // Inheritance and polymorphism
    Circle circle(5.0);
    Rectangle rectangle(4.0, 6.0);
    std::cout << "Daire alanı: " << circle.calculateArea() << std::endl;
    std::cout << "Dikdörtgen alanı: " << rectangle.calculateArea() << std::endl;
    
    // Polymorphic behavior
    Dog dog;
    Cat cat;
    Animal* animals[] = {&dog, &cat};
    for (Animal* animal : animals) {
        animal->makeSound();
    }
    
    // Multiple inheritance
    AllInOne device;
    device.print();
    device.scan();
    
    // Template class
    Container<int> numbers(5);
    for (size_t i = 0; i < 5; ++i) {
        numbers.setElement(i, i * 10);
        std::cout << "Number: " << numbers.getElement(i) << std::endl;
    }
    
    // Smart pointer
    std::unique_ptr<Resource> resource = std::make_unique<Resource>();
    resource->use();
    
    return 0;
} 