"""OK, so we need to make some constraints:
This mapping program is made to function in two ways:
Unlimited mode and Limited mode.
Unlimited is outdoors where there are not obstacles everywhere and the
robot will patrol a clearly defined area.
Limited is indoors where there are obstacles and it will patrol until it
is disabled?


"""


class UnlimMap():
    """
    Creates a unlimited map where the dimensions are clearly
    defined and the scale is the area of the "squares" that
    the map is made up of.(subject to change) Ideally scale
    is the size of the robot. """
    def __init__(self, x_dim, y_dim, scale):
        self.size = (x_dim, y_dim)
        self.x_dim = x_dim; self.y_dim = y_dim;
        self.scale = scale
        self.map = []
        self.createMap(x_dim, y_dim)


    def addBarrier(self, x, y):
        self.map[y][x] = 1

    def removeBarrier(self, x, y):
        self.map[y][x] = 0

    def createMap(self, x_dim, y_dim):
        for x in range(y_dim):
            #Creates a row
            self.map.append([])
            for p in range(x_dim):
                self.map[x].append(0)
        print(self.map)

    def saveMap(self, file):
        f = open(file, "w")
        for y in range(len(self.map)):
            for x in range(y):
                f.write(str(self.map[y][x]))
                f.write(" ")
            f.write("\n")

class LimMap():
    def __init__(self, scale, max_size):
        self.max = max_size
        self.scale = scale



def main():
    amap = UnlimMap(5, 2, 20)
    amap.addBarrier(0, 0)
    amap.addBarrier(4, 1)
    print(amap.map)
    print(amap.map[0])
    amap.saveMap("testmap.txt")


if __name__ == '__main__':
    main()
