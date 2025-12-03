def _narrow_accuracy(num):
    if num % 1 == 0:
        return 0
    a = str(num).split(".")[-1]
    return 5*10**(-len(a)-1)


def _wide_accuracy(num):
    if num % 1 == 0:
        return 0
    a = str(num).split(".")[-1]
    return 10**(-len(a))


def absolute_accuracy(num, is_nar=True):
    if is_nar:
        return _narrow_accuracy(num)
    return _wide_accuracy(num)


def relative_accuracy(num, is_nar=True):
    if is_nar:
        return _narrow_accuracy(num)/num
    return _wide_accuracy(num)/num


def main():
    num = float(input("Введите число "))
    is_nar = bool(int(input("В узком смылсе - 1, в широком смысле - 0 ")))
    print(f"Абсолютная погрешность {absolute_accuracy(num, is_nar)}")
    print(f"Относительная погрешность {relative_accuracy(num, is_nar)}")


main()