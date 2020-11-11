from pathlib import Path
from typing import Iterator, Tuple

import matplotlib.pyplot as plt


def get_path() -> Iterator[int]:
    return map(int, input("Enter route: ").split(" "))


def get_coords() -> Iterator[Tuple[float, float]]:
    numb = input("Enter file number: ")
    file = f"tour{'0' * (3-len(numb))}{numb}.txt"
    data = Path(__file__).parent.parent.joinpath("data", file).read_text()
    for line in data.splitlines()[2:]:
        x, y = line.split()
        yield float(x), float(y)


def main():
    xs, ys = zip(*get_coords())
    plt.scatter(xs, ys)
    path = list(get_path())
    plt.plot(
        [xs[i] for i in path] + [xs[path[0]]], [ys[i] for i in path] + [ys[path[0]]]
    )
    plt.show()


if __name__ == "__main__":
    main()
