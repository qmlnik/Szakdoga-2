import math
import random

def main():
    n = input("number of variables?")
    r = input("number of occurences?")

    try:
        n = int(n)
        r = int(r)
    except:
        print("give two integers as inputs")
        return None

    variable_map = {}
    for i in range(1, n + 1):
        variable_map[i]  = r
        variable_map[i * (-1)]  = r
    
    availableList = []
    chosenList = []
    chosen = 0
    resultLength = int(math.floor((r * 2 * n) / 3))
    actualLength = 0
    result = set()
    
    for i in range(resultLength):
        availableList.clear()
        chosenList.clear()

        for key, value in variable_map.items():
            if value > 0:
                availableList.append(key)

        for j in range(3):
            try:
                chosen = random.choice(availableList)
            except:
                break
            chosenList.append(chosen)
            availableList.remove(chosen)
            variable_map[chosen] = variable_map[chosen] - 1;

        result.add(tuple(chosenList))
        actualLength = actualLength + 1

    for i in range(actualLength):
        clause = result.pop()
        for j in range(len(clause)):
            print(f"{clause[j]} ", end="")
        print("0")
          

if __name__ == "__main__":
    main()

