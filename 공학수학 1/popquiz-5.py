from collections.abc import Callable

def rk(
    f: Callable[[float, float], float],
    init: tuple[float, float],
    h: float, n: int,
) -> float:
    x0, y = init
    print(f'(x, y) = ({x0}, {y})')

    for i in range(n):
        x = x0 + i*h
        k1 = h*f(x,         y)
        k2 = h*f(x + 0.5*h, y + 0.5*k1)
        k3 = h*f(x + 0.5*h, y + 0.5*k2)
        k4 = h*f(x + h,     y + k3)
        y = y + (1/6)*(k1 + 2*k2 + 2*k3 + k4)
        print(f'(x, y) = ({x + h}, {y})')

    print()
    return y

print(rk(lambda x, y: 2*x*y, (1, 1), h=0.1, n=10))
