"""OK, so we need to make some constraints:
This mapping program is made to function in two ways:
Unlimited mode and Limited mode.
Unlimited is outdoors where there are not obstacles everywhere and the
robot will patrol a clearly defined area.
Limited is indoors where there are obstacles and it will patrol until it
is disabled? Maybe merge them but here are framework classes for how it will work

"""
class Robot():
    """
    'Robot' that acts as a virtual placeholder for the actual thing.
    could be visualized some day or something
    """
    def __init__(self, scale):
        self.x = 0; self.y = 0;


    def move(self, dx, dy):
        #move deltaX and deltaY or change in x and y
        self.x += dx*scale
        self.y += dy*scale

    def _reset(self):
        self.x = 0; self.y = 0;


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
        self._createMap(x_dim, y_dim)


    def addBarrier(self, x, y):
        self.map[y][x] = 1

    def removeBarrier(self, x, y):
        self.map[y][x] = 0

    def _createMap(self, x_dim, y_dim):
        for x in range(y_dim):
            #Creates a row
            self.map.append([])
            for p in range(x_dim):
                self.map[x].append(0)

    def saveMap(self, file):
        f = open(file, "w")
        for y in range(len(self.map)):
            f.writelines(str(self.map[y])+"\n")

class LimMap():
    def __init__(self, scale, max_size):
        self.max = max_size
        self.scale = scale

    def addBarrier(self, x, y):
        self.map[y][x] = 1

    def removeBarrier(self, x, y):
        self.map[y][x] = 0

    def _createMap(self):
        pass
        #? how to go about this?
        #robot needs to FIND dimensions i guess

    def saveMap(self, file):
        f = open(file, "w")
        for y in range(len(self.map)):
            f.writelines(str(self.map[y])+"\n")


def main():
    import os
    amap = UnlimMap(5, 2, 20)
    amap.addBarrier(0, 0)
    amap.addBarrier(4, 1)
    #pls fix this, it saves elsewhere thanks Python very cool
    #amap.saveMap("testerMap.txt")


if __name__ == '__main__':
    main()
