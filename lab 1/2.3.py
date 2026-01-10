from decimal import *
from math import sqrt


def accuracy(*args: str):
    try:
        decimal_place = len(args[0].split(".")[1])
    except IndexError:
        decimal_place = 0
    for arg in args:
        try:
            decimal_place_temp = len(arg.split(".")[1])
        except IndexError:
            decimal_place_temp = 0
        if decimal_place > decimal_place_temp:
            decimal_place = decimal_place_temp
    return decimal_place


def str_to_decimal_and_round(*args: str, round_pattern: Decimal):
    return [Decimal(arg).quantize(round_pattern) for arg in args]


def compute_expression(a_s: str, b_s: str, c_s: str):
    decimal_place = accuracy(a_s, b_s, c_s)
    round_pattern = Decimal("1." + "0" * (decimal_place + 1))
    answer_round_pattern = Decimal("1." + "0" * decimal_place)
    a, b, c = str_to_decimal_and_round(a_s, b_s, c_s, round_pattern=round_pattern)
    p = ((a+b+c)/2).quantize(round_pattern)
    return Decimal(sqrt(p*(p-a)*(p-b)*(p-c))).quantize(answer_round_pattern)


while True:
    print("Вычисление площади по формуле Герона. Рекомендуемый формат чисел 0.0")
    a = input("Введите значения для a\n")
    b = input("Введите значения для b\n")
    c = input("Введите значения для c\n")
    print(f"S = {compute_expression(a, b, c)}")
    print("Чтобы выйти отправьте 0, чтобы продолжить - любой символ")
    if input() == "0":
        break
