from math import sqrt


class Number:
    """
    Класс предназначен для удобной работы над числами с заданной точностью
    на вход подается число в формате: 0.000 (0.000)
    где в скобках относительная погрешность
    """
    def __init__(self, number_with_accuracy: str):
        number = number_with_accuracy.split("(")
        self.number = float(number[0])
        self.accuracy = float(number[1][:-1])
        self.relative_accuracy = self.accuracy/self.number


def expression_value(num1, num2, num3):
    return sqrt(num1.number * num2.number / num3.number)


def relative_accuracy_value(num1, num2, num3):
    return (num1.relative_accuracy + num2.relative_accuracy + num3.relative_accuracy)/2


def absolute_accuracy_value(num1, num2, num3):
    return expression_value(num1, num2, num3) * relative_accuracy_value(num1, num2, num3)


def main():
    print("Решение для выражения типа √(c*d/b)")
    while True:
        print('Введите значение для переменной "c" в формате 0.000 (0.000)')
        try:
            c = Number(input())
        except Exception:
            print("Неверный формат")
            break
        print('Введите значение для переменной "d" в формате 0.000 (0.000)')
        try:
            d = Number(input())
        except Exception:
            print("Неверный формат")
            break
        print('Введите значение для переменной "b" в формате 0.000 (0.000)')
        try:
            b = Number(input())
        except Exception:
            print("Неверный формат")
            break
        print(f"√({c.number}*{d.number}/{b.number}) = {expression_value(c, d, b)}")
        print(f"Относительная погрешность: {relative_accuracy_value(c, d, b)}")
        print(f"Абсолютная погрешность: {absolute_accuracy_value(c, d, b)}")
        if input("Продолжить? (Да/Нет)\n") == "Нет":
            break


main()
