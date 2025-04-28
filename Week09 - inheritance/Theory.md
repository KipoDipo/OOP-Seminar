# Наследяване
Наследяването позволява на един клас да придобие характеристиките (методи и член-данни) на друг клас.

Често се използва терминът "базов клас", за класа, който ще бъде наследяван.

```cpp
class Animal
{
public:
    void Walk()
    {
        std::cout << "Walking...";
    }
};

class Dog : public Animal
{
public:
    void Bark()
    {
        std::cout << "Woof!";
    }
};
```

```cpp
Animal animal;
animal.Walk(); // Walking...

Dog dog;
dog.Walk(); // Walking...
dog.Bark(); // Woof!
```

## protected

Освен `public` и `private` модификаторите за видимост на данни, съществува и още един - *`protected`*.  

Припомняме си:  
`public` - Данните са достъпни от и извън класа.  
`private` - Данните са достъпни само за класа.  

Данните, маркирани като `protected`, могат да бъдат достъпвани от класa и *неговите наследници*, но не и от външния свят. 

```cpp
class Shape
{
private:
    int id;

protected:
    int width, height;

public:
    void setDimensions(int width, int height)
    {
        this->width = width;
        this->height = height;
    }
};

class Rectangle : public Shape
{
public:
    int Area() const
    {
        return width * height; // protected fields
    }
};
```

## Видове наследяване

Когато наследяваме клас, можем да го наследим по 3 начина с доста познати ключови думи:
- `public`
- `private`
- `protected`

Feature | Public Inheritance | Protected Inheritance | Private Inheritance
--- | --- | --- | ---
Public members | Stay **public** in derived class | Become **protected** in derived class | Become **private** in derived class
Protected members | Stay **protected** in derived class | Stay **protected** in derived class | Become **private** in derived class
Private members | Not accessible | Not accessible | Not accessible

В 99% от случаите ще използваме *public inheritance*, защото то представлява "is-a" връзка. 

## Конструктор
При наследяване, когато се вика конструктора на класът наследник, задължително преди него трябва да се извика някой конструктор на базовия клас. Ако той не е оказан експлицитно, се подразбира, че се вика **default ctor**-a.

```cpp
class Shape
{
protected:
    int width, height;

public:
    Shape()
    {
        setDimensions(0, 0);
    }
    Shape(int width, int height)
    {
        setDimensions(width, height);
    }

    void setDimensions(int width, int height)
    {
        this->width = width;
        this->height = height;
    }
};

class Rectangle : public Shape
{
public:
    Rectangle()
    {
        // implicitly calls Shape::Shape()
    }
    Rectangle(int width, int height)
        : Shape(width, height) // explicitly call Shape::Shape(int width, int height)
    {
    }

    int Area() const
    {
        return width * height; // protected fields
    }
};
```

*Note:* При имплицитните **конструктори** (default ctor, copy ctor, move ctor), по подразбиране се викат съответните такива от базовия клас. Ако създадем напр. наш copy ctor, трябва да извикаме експлицитно copy ctor-a на базовия клас, защото ако не го направим, имплицитно ще се извика default ctor-a на базовия клас. 

*Note 2:* Деструктора също извиква базовия деструктор преди той самия да се изпълни. Това поведение **не** може да бъде променено.