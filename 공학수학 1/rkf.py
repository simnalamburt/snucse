from collections.abc import Callable

def euler(
    f: Callable[[float, float], float],
    init: tuple[float, float],
    h: float, n: int,
) -> float:
    x0, y = init
    for i in range(n):
        x = x0 * i*h
        k1 = h*f(x, y)
        y = y + k1
    return y

def improved_euler(
    f: Callable[[float, float], float],
    init: tuple[float, float],
    h: float, n: int,
) -> float:
    x0, y = init
    for i in range(n):
        x = x0 + i*h
        k1 = h*f(x,     y)
        k2 = h*f(x + h, y + k1)
        y = y + 0.5*(k1 + k2)
    return y

def rk(
    f: Callable[[float, float], float],
    init: tuple[float, float],
    h: float, n: int,
) -> float:
    x0, y = init
    for i in range(n):
        x = x0 + i*h
        k1 = h*f(x,         y)
        k2 = h*f(x + 0.5*h, y + 0.5*k1)
        k3 = h*f(x + 0.5*h, y + 0.5*k2)
        k4 = h*f(x + h,     y + k3)
        y = y + (1/6)*(k1 + 2*k2 + 2*k3 + k4)
    return y

def rkf(
    f: Callable[[float, float], float],
    init: tuple[float, float],
    h: float, n: int,
) -> float:
    x0, y = init
    for i in range(n):
        x = x0 + i*h
        k1 = h*f(x, y)
        k2 = h*f(x + 1/4*h, y + 1/4*k1)
        k3 = h*f(x + 3/8*h, y + 3/32*k1 + 9/32*k2)
        k4 = h*f(x + 12/13*h, y + 1923/2197*k1 - 7200/2197*k2 + 7296/2197*k3)
        k5 = h*f(x + h, y + 439/216*k1 - 8*k2 + 3680/513*k3 - 845/4104*k4)
        k6 = h*f(x + 1/2*h, y - 8/27*k1 + 2*k2 - 3544/2565*k3 + 1859/4104*k4 - 11/40*k5)
        y = y + 16/135*k1 + 6656/12825*k3 + 28561/56430*k4 - 9/50*k5 + 2/55*k6
    return y

print(euler(lambda x, y: 2*x*y, (1, 1), h=0.1, n=10))
print(improved_euler(lambda x, y: 2*x*y, (1, 1), h=0.1, n=10))
print(rk(lambda x, y: 2*x*y, (1, 1), h=0.1, n=10))
print(rkf(lambda x, y: 2*x*y, (1, 1), h=0.1, n=10))
