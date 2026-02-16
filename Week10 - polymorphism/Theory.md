## Виртуални методи

Ключовата дума `virtual` ни позволява да дефинираме функция в базов клас, която може да бъде **презаписана** в производни класове. При извикване чрез **указател или референция** към базов клас, C++ ще определи _по време на изпълнение_ коя реализация да се извика.

```cpp
class Animal
{
public:
    virtual void Speak()
    {
        std::cout << "...\n";
    }
};

class Dog : public Animal
{
public:
    void Speak() override
    {
        std::cout << "Woof!\n";
    }
};

class Cat : public Animal
{
public:
    void Speak() override
    {
        std::cout << "Meow!\n";
    }
};
```

```cpp
Animal* a1 = new Dog();
Animal* a2 = new Cat();

a1->Speak(); // Woof!
a2->Speak(); // Meow!
```

> Важно: Ако не използваме `virtual`, ще се извика винаги функцията от типа на указателя, а не реалния тип на обекта.

## override и final

- `override` се използва за **проверка от компилатора**, че наистина презаписваме виртуална функция. Ако направим грешка в името/сигнатурата – компилаторът ще ни уведоми.
- `final` указва, че дадена виртуална функция **не може да бъде override-ната** в наследници.

```cpp
class Animal
{
public:
    virtual void Speak() const
    {
        std::cout << "Some animal sound\n";
    }
};

class Dog : public Animal
{
public:
    void Speak() const override final
    {
        std::cout << "Woof!\n";
    }
};

class Bulldog : public Dog
{
    void Speak() const override // Error: Speak is final in Dog
    {
        //...
    }
};
```

## Виртуални деструктори

Когато очакваме, че класовете наследници ще имат деструктори (напр. имат динамична памет), **винаги** правим деструктора на базовия клас виртуален. Това гарантира, че при изтриване през указател към базов клас, ще се извика коректно деструктора на производния клас.

> Rule of thumb: `virtual` идва с цена (виртуална таблица). Когато имаме **виртуални методи**, на практика не губим нищо като добавим и виртуален деструктор, защото цената вече е платена т.е. имаме ли виртуални методи, слагаме и виртуален деструктор

```cpp
class Animal
{
public:
    virtual ~Animal()
    {
        std::cout << "Animal destroyed\n";
    }
};

class Dog : public Animal
{
public:
    ~Dog()
    {
        std::cout << "Dog destroyed\n";
    }
};
```

```cpp
Animal* pet = new Dog();
delete pet;
```

```
Dog destroyed
Animal destroyed
```

> Важно: Ако деструкторът не е `virtual`, ще се извика само този от типа на указателя, което може да доведе до изтичане на ресурс.

## Абстрактни класове и чисто виртуални методи

Ако искаме да направим **само интерфейс**, без имплементация, можем да дефинираме **чисто виртуални методи**, като използваме `= 0`.

```cpp
class Shape
{
public:
    virtual int Area() const = 0; // чисто виртуална функция
};
```

Клас, който съдържа поне една чисто виртуална функция, се нарича **абстрактен клас**. Не можем да създаваме обекти от него. Ако искаме клас наследник да може да има обекти, то следва и да имплементираме чисто виртуалната функция.

```cpp
class Rectangle : public Shape
{
private:
    int width, height;

public:
    Rectangle(int w, int h) : width(w), height(h) {}
    int Area() const override
    {
        return width * height;
    }
};
```

```cpp
Shape* s = new Rectangle(3, 4);
std::cout << s->Area(); // 12
```

## Полиморфизъм чрез масиви от указатели (хетерогенен контейнер)

Полиморфизмът проблясва, когато искаме да обработим множество различни обекти чрез един и същ интерфейс.

```cpp
Animal** animals = new Animal*[2];
animals[0] = new Dog();
animals[1] = new Cat();

for (int i = 0; i < 2; i++)
{
    animals[i]->Speak();
}
```

```
Woof!
Meow!
```