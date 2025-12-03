from decimal import *


def get_round_pattern(absolute_accuracy, is_nar):
    absolute_accuracy = str(absolute_accuracy)

    if "." in absolute_accuracy:
        absolute_accuracy = absolute_accuracy.split(".")[1]
        place = 0
        for i in range(len(absolute_accuracy)):
            num = int(absolute_accuracy[i])
            if num != 0:
                place = i + 1 * (num < 5 and is_nar) - 1 * is_nar
                break
        return Decimal(str(pow(10, -place)))
    return Decimal("10")


def update_round_pattern(round_pattern):
    if len(str(Decimal(round_pattern))) <= 3:
        return Decimal("1")
    return Decimal(str(round_pattern)[:-2] + "1")


def round_num(num: Decimal, absolute_accuracy=None, relative_accuracy=None, is_nar=True):
    if absolute_accuracy is None and relative_accuracy is not None:
        absolute_accuracy = relative_accuracy * num
    round_pattern = get_round_pattern(absolute_accuracy, is_nar)
    while True:
        new_num = num.quantize(round_pattern)
        new_absolute_accuracy = absolute_accuracy + abs(new_num - num)
        if new_absolute_accuracy < round_pattern/(1, 2)[is_nar]:
            break
        round_pattern = update_round_pattern(round_pattern)
    return new_num


def main():
    num1 = Decimal(input("Введите число в формате 0.0\n"))
    relative_accuracy1 = Decimal(input("Введите относительную погрешность в процентах\n"))/100
    print(f"Ответ: {round_num(num1, relative_accuracy=relative_accuracy1, is_nar=True)}")
    num2 = Decimal(input("Введите число в формате 0.0\n"))
    absolute_accuracy2 = Decimal(input("Введите абсолютную погрешность в формате 0.0\n"))
    print(f"Ответ: {round_num(num2, absolute_accuracy=absolute_accuracy2, is_nar=False)}")


main()
