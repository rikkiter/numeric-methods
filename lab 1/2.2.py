class Number:
    """
    Класс предназначен для удобной работы над числами с заданной точностью
    на вход подается число в формате: 0.000 (0.000)
    где в скобках относительная погрешность
    """
    def __init__(self, number_with_accuracy: str):
        if not number_with_accuracy.endswith(")"):
            raise Exception
        number = number_with_accuracy.split("(")
        self.number = float(number[0])
        self.accuracy = float(number[1][:-1])
        self.relative_accuracy = self.accuracy/self.number


def expression_value(num1, num2, num3, num4):
    return pow(num1.number - num2.number, 1/3)/num3.number/(num4.number - num1.number)


def relative_accuracy_value(num1, num2, num3, num4):
    number1 = num1.number - num2.number
    accuracy1 = num1.accuracy + num2.accuracy
    number2 = num4.number - num1.number
    accuracy2 = num4.accuracy + num1.accuracy
    return (accuracy1/number1)/3 + accuracy2/number2 + num3.relative_accuracy


def absolute_accuracy_value(num1, num2, num3, num4):
    return expression_value(num1, num2, num3, num4) * relative_accuracy_value(num1, num2, num3, num4)


def main():
    print("Решение для выражения типа ∛(a-b)/(m*(n-a))")
    while True:
        print('Введите значение для переменной "a" в формате 0.000 (0.000)')
        try:
            a = Number(input())
        except Exception:
            print("Неверный формат")
            break
        print('Введите значение для переменной "b" в формате 0.000 (0.000)')
        try:
            b = Number(input())
        except Exception:
            print("Неверный формат")
            break
        print('Введите значение для переменной "m" в формате 0.000 (0.000)')
        try:
            m = Number(input())
        except Exception:
            print("Неверный формат")
            break
        print('Введите значение для переменной "n" в формате 0.000 (0.000)')
        try:
            n = Number(input())
        except Exception:
            print("Неверный формат")
            break
        print(f"Относительная погрешность: {relative_accuracy_value(a, b, m, n)}")
        print(f"Абсолютная погрешность: {absolute_accuracy_value(a, b, m, n)}")
        if input("Продолжить? (Да/Нет)\n") == "Нет":
            break


main()
