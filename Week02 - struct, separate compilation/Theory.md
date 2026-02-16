# Структури
Структурие в С++ ни позволяват да опишем обект, като го представим чрез отделните му компоненти.  

Например, един пиксел се състои от 3 канала - Red, Green, Blue; всеки един от тези канали има целочислена стойност. В контекста на структурата, отделнтие компоненти се наричат *полета* или *член данни*. За да опишем един пиксел, пишем следната структура:

```cpp
struct Pixel
{
    int red;
    int green;
    int blue;
};
```

Сега вече имаме "скелета" на един пиксел. За да го използваме, трябва да създадем *инстанция* на тази структура. Това става по същия начин, както с нормалните променливи:

```cpp
Pixel pixel;
```

Сега вече много по-лесно можем да създаваме и управляваме обекти. Можем дори да правим масиви, например ако искаме да направим платно от 1280х720 пиксела, пишем следното:

```cpp
Pixel canvas[1280][720];
```

---

За да зададем някакви стойности на този пиксел, можем да подходим по няколко начина. Първият е след като създадем *обекта*, чрез оператора `.`, да *достъпим* отделните *полета* (red, green, blue).

```cpp
Pixel pixel;

pixel.red = 255;
pixel.green = 0;
pixel.blue = 255;
```

Друг вариант е още докато го създаваме, с помощта на къдрави скоби `{}` да въведем съответните стойности. Въвеждането на стойностите следва реда на деклариране на полетата в структурата.

```cpp
//           r    g    b
Pixel pixel {255, 0, 255};
```

---

Обекти можем да подаваме на функции, както нормални променливи. Например, за да напишем функция, която принтира стойностите на един пиксел:

```cpp
void printPixelInfo(Pixel pixel)
{
    std::cout << "R: " << pixel.red << std::endl;
    std::cout << "G: " << pixel.green << std::endl;
    std::cout << "B: " << pixel.blue << std::endl;
}

int main()
{
    Pixel pixel {255, 0, 255};

    printPixelInfo(pixel);
}
```

Обектите, както нормалните променливи, се подават като **копие**. Това означава, че ако искаме да напишем функция, която увеличава яркостта на пиксела, и подадем обектът по копие, няма да има отразена промяна в оригиналния обект. За това подаваме по референция.

```cpp
void increaseBrightnessWrong(Pixel pixel, int amount)
{
    pixel.red += amount;
    pixel.green += amount;
    pixel.blue += amount;
}

void increaseBrightnessCorrect(Pixel& pixel, int amount)
{
    pixel.red += amount;
    pixel.green += amount;
    pixel.blue += amount;
}

int main()
{
    Pixel pixel {100, 0, 100};

    increaseBrightnessWrong(pixel, 100);
    printPixelInfo(pixel);

    std::cout << "\n\n";

    increaseBrightnessRight(pixel, 100);
    printPixelInfo(pixel);
}

```

```
R: 100
G: 0
B: 100

R: 200
G: 100
B: 200
```

---

Виждаме, че в такъв тип функции, в които искаме да използваме обекта, винаги трябва да го подаваме като  параметър. В такива случаи е по-удобно да напишем функцията вътре в структурата. Такава функция се нарича *метод* или *член функция*. В методите се приема, че работим със специфична инстанция на структурата, следователно нямаме частта `pixel.` а работим директно с полетата.

```cpp
struct Pixel
{
    int red;
    int green;
    int blue;

    void printInfo()
    {
        std::cout << "R: " << red << std::endl;
        std::cout << "G: " << green << std::endl;
        std::cout << "B: " << blue << std::endl;
    }

    void increaseBrightness(int amount)
    {
        red += amount;
        green += amount;
        blue += amount;
    }
};
```

```cpp
int main()
{
    Pixel pixel {100, 0, 50};

    pixel.increaseBrightness(100);
    pixel.printInfo();
}
```

```
R: 200
G: 100
B: 150
```

# Разделна компилация
Използваме `#include <iostream>` от самото начало, но за сега е било на принципа "прави се така защото трябва". `#include` е просто инструкция, която казва "вземи съдържанието на указания файл, и го постави тук".

С други думи можем да си отделим функциите в отделен текстови файл (типично `.h` или `.hpp`) и после да ги include-нем. 

Когато си създаваме собствени файлове, пишем `#include "file.h"`, а не `#include <file.h>`

**functions.h**
```cpp
int fib(int n)
{
    if (n == 1)
        return 1;
    if (n == 0)
        return 0;

    return fib(n - 1) + fib(n - 2);
}

void printFib(int n)
{
    std::cout << fib(n);
}
```

**main.cpp**
```cpp
#include <iostream>
#include "functions.h"

int main()
{
    printFib(8);
}
```

---

**Разделната компилация** е процесът на разделяне на *декларация* и *дефиниция* в отделни файлове. Това става по следния начин:

- Декларациите отиват в `.h`/`.hpp` файл
- Дефинициите отиват в `.cpp` файл

Причините за да правим разделна компилация са няколко:
- В по-голям проект, всичко да е на един файл става трудно за управление  
- При разглеждане на кода е много по-лесно да се влезе в `.h` файла за да се види каква функционалност има, без много да се затрупваме от имплементацията.
- Компилират се само тези `.cpp` файлове, които са променени от последната компилация, т.е. разделната компилация води и до *по-бързо* компилиране

Пример:  

**Vector2D.h**
```cpp
struct Vector2D
{
    double x, y;
};

double dot(Vector2D a, Vector2D b);

double length(Vector2D vec);
```

**Vector2D.cpp**
```cpp
#include "Vector2D.h"
#include <cmath>

double dot(Vector2D a, Vector2D b)
{
    return a.x * b.x + a.y * b.y;
}

double length(Vector2D vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}
```

**main.cpp**

```cpp
#include <iostream>
#include "Vector2D.h"

int main()
{
    Vector2D vec1 {5, 10};
    Vector2D vec2 {2, -12};

    std::cout << dot(vec1, vec2) << '\n';
    std::cout << length(vec1);
}
```