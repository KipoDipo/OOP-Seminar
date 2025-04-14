# Пренаписване на оператори (Operator Overloading)

Можем да пишем `1 + 1`, `p + 5`, `arr[1]` и т.н. за всички примитивни типове в езика. Но какво ако би било логично за класа, който пишем, също да можем да прилагаме операции, без експлицитно викане на методи (напр. `.add(n)`, `.at(i)`).

```cpp
Complex z1(1, 2);
Complex z2(6, -1);

// solution 1
Complex z3 = z1.add(z2);

// solution 2
Complex z4 = Complex::add(z1, z2);

// best looking syntax
Complex z5 = z1 + z2;
```

## Синтаксис

Езикът ни предоставя инструмент, чрез който да постигнем точно това, и той се нарича *operator overloading*. Синтаксиса му е като на стандартна функция, но идентификатора на тази функция е от вида:  
`<type> operator<op>([params])`

Вече сме се запознали с един такъв, `operator=` при нуждата на такъв, но има и още много, напр. `operator+`

```cpp
class Complex
{
public:
    Complex() : r(0), i(0) {}
    Complex(float r, float i) : r(r), i(i) {}

    Complex operator+(const Complex& other) const
    {
        return Complex(r + other.r, i + other.i);
    }

private:
    float r, i;
};
```

Сега вече езикът ни позволява да се възползваме от този метод, все едно е самия оператор:

```cpp
Complex z5 = z1 + z2;

// equivalent to
Complex z5 = z1.operator+(z2);
```

## Оператори, които (не) могат да се пренапишат

Могат да се пренапишат всички оператори, освен:
- `.` - *Class member selector operator*
- `::` - *Scope resolution operator*
- `?:` - *Ternary operator*
- `sizeof` - *Size of operator*

## Особености
Всички оператори, освен `()`, имат стриктни изисквания към броя параметри, които приемат. Напр. индексиращия оператор `[]` задължително приема точно 1 параметър, като типът му не е от значение.

```cpp
int operator[](int x, int y) // Not possible

int operator[](float index) // OK, as long as it makes sense in the class
```

При оператор `()`:

```cpp
int operator()(int x, int y) // OK

int operator()(float index) // OK
```

*Note:* Клас, който може да се използва като функция (т.е. има пренаписан `operator()`), се нарича **Функтор**

---
Оператори, които работят само с един операнд, се наричат *унарни*. Например за да поддържаме синтаксиса `-a` трябва да напишем оператор `-` в класа, който не приема никакви параметри.

```cpp
Vector operator-()
{
    return Vector(-x, -y);
}
```

Ако имаше параметър (напр. друг Vector, но не задължително), тогава щеше да е *бинарния* оператор `-`, който вече работи с 2 операнда.

---

Специален случай са постинкрементален и преинкрементален `operator++`. Тъй като в езика всички оператори започват с думата `operator`, няма такова нещо като `++operator`. За да се направи разлика между двете се поставя параметър `int`, който *не* се използва.  
Когато този помощен параметър присъства, говорим за постинкрементална операция.  
Когато го няма - за преинкрементална операция

```cpp
Integer& operator++() // pre-increment: ++var
{
    data++;
    return *this;
}

Integer operator++(int) // post-increment: var++
{
    Integer temp(*this); // save current state
    
    data++;
    
    return temp;
}
```

Аналогично за `operator--`.

## На практика

### Пренаписване на оператори извън класа

Голяма част от операторите могат да се напишат и извън класа. Често това е най-добре да се прилага, когато операторът не променя данни от класа, както и класа има нужните getter-и:

```cpp
class Complex 
{
public:
    Complex(float r, float i) : r(r), i(i) {}

    Complex operator+(const Complex& other)
    {
        return Complex(r + other.r, i + other.i);
    }

    Complex& operator+=(const Complex& other)
    {
        *this = *this + other; // will use operator+(other)
        return *this;
    }

private:
    float r, i;    
};
```

С подходящия метод написан извън класа:

```cpp
class Complex 
{
public:
    Complex(float r, float i) : r(r), i(i) {}

    float getReal() const { return r; }
    float getImaginary() const { return i; }

    Complex& operator+=(const Complex& other)
    {     
        *this = *this + other; // will use operator+(left, right)
        return *this;
    }

private:
    float r, i;    
};

Complex operator+(const Complex& left, const Complex& right)
{
    return Complex(left.getReal() + right.getReal(), left.getImaginary() + right.getImaginary());
}
```

*Note:* нямаме достъп до `this` във външна функция, защото тя не е част от класа и съответно не е обвързана със специфична инстанция.

### Оператор за извеждане << 
Много често е полезно да можем да изкараме обекта на стандартния поток към конзолата или към файл чрез `operator<<`. Една имплементация е чрез помощта на `friend` функция:

```cpp
class Complex 
{
public:
    Complex(float r, float i) : r(r), i(i) {}

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) 
    {
        os << "(" << c.r << ", " << c.i << ")";
        return os;
    }

private:
    float r, i;
};

int main() 
{
    Complex z1(1, 2);
    std::cout << "Complex number: " << z1 << std::endl; // (1, 2)
    return 0;
}
```

*Note:* `friend` функциите не са част от класа ни, а само позволение на функция с такава сигнатура да достъпва `private` член данните. 

*Note 2:* Ако е възможно, е хубаво да се избягва `friend`. Най-често ако класът ни има подходящите getter-и, не се налага да създаваме такова позволение.

```cpp
class Complex 
{
public:
    Complex(float r, float i) : r(r), i(i) {}

    float getReal() const { return r; }
    float getImaginary() const { return i; }

private:
    float r, i;
};

std::ostream& operator<<(std::ostream& os, const Complex& c) 
{
    os << "(" << c.getReal() << ", " << c.getImaginary() << ")";
    return os;
}

int main() 
{
    Complex z1(1, 2);
    std::cout << "Complex number: " << z1 << std::endl; // (1, 2)
    return 0;
}
```