# Шаблони

Шаблоните ни позволяват да пишем обобщен код, който може да работи с различни типове, стига да удовлетворяват условията на кода.
Ще разгледаме два вида шаблони:

- Шаблони на функции (Function Templates)
- Шаблони на класове (Class Templates)

## Синтаксис

Една функция или клас се преобразува в шаблон(template), тогава когато се добави следния синтаксис пред нея:
```cpp
template <typename [име на шаблонния параметър]>
```
Тоест ако искаме да напишем шаблон на функция, която има шаблонен параметър T, ние ще напишем:
```cpp
template <typename T>
```

Възможно е да опишем колкото си искаме шаблонни параметри:
```cpp
template <typename T, typename U, typename Z>
```

# Function Templates

Позволява ни да дефинираме функция, която може да работи с произволни типове:
```cpp
template <typename T>
T maxValue(T a, T b) {
    return (a > b) ? a : b;
}
```

Тук `T` представлява произволен тип (int, double, потребителски тип). Единственото ограничение е, че този тип трябва да може да поддръжа оператора `>`.

```cpp
int main()
{
    std::cout << maxValue<int>(10, 20); // 20
}
```

Kогато работим с шаблонни параметри, ние нямаме идея какъв тип може да се подаде на тази функция. Хубаво е да подаваме параметрите по константна референиця(`const&`), освен ако реално не целим копие или промяна на някой от параметърите на функцията

# Class Templates

Аналогично на функциите, шаблоните ни позволяват да създаваме класове с произволни типове:
```cpp
template <typename T, typename U>
class Pair
{
private:
    T first;
    U second;
public:
    Pair(const T& first, const U& second) 
        : first(first), second(second)
    {
    }

    const T& getFirst() const { return first; }
    const U& getSecond() const { return second; }

    void setFirst(const T& first) { this->first = first; }
    void setSecond(const U& second) { this->second = second; }
};
```
