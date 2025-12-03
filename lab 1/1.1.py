import math


def compare_accuracy(a_numerator, a_denominator, a, b_radicand, b):
    """
    Возвращает более точное значение
    a_numerator - числитель
    a_denominator - знаменатель
    a - приближенное значение a
    b_radicand - подкоренное выражение
    b - приближенное значение b
    """
    return (a, b)[abs(a_numerator/a_denominator - a)/a > abs(math.sqrt(b_radicand)-b)/b]


def main():
    a_numerator, a_denominator = map(int, input("Введите числитель и знаменатель дроби через пробел ").split())
    a = float(input("Введите приблеженное значение дроби "))
    b_radicand = float(input("Введите подкоренное выражение "))
    b = float(input("Введите приблеженное значение корня "))
    print(f"Более точное приблеженное значение: {compare_accuracy(a_numerator, a_denominator, a, b_radicand, b)}")


main()
