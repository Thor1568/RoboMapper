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
        self.deltaX = 0
        self.dist = 0

    def moveRaw(self, dx, dy):
        #move deltaX and deltaY or change in x and y
        self.x += dx*scale
        self.y += dy*scale
        self.deltaX += dx*scale+dy*scale
        self.dist += abs(dx*scale)+abs(dy*scale)

    def move(self, dx, dy, map):
        #moves with check
        check = canMove(dx, dy, map)
        if check:
            moveRaw(dx, dy)

    def canMove(self, dx, dy, map):
        future = (self.x+dx, self.y+dy)
        newTile = map[future[1]][future[0]]
        if newTile == (0 or 2):
            return True


    def _reset(self):
        self.x = 0; self.y = 0;
        self.deltaX = 0
        self.dist = 0


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



class MapObject(pygame.sprite.Sprite):
    def __init__(self, x, y, otype):
        pygame.sprite.Sprite.__init__(self)
        self.rect = self.image.get_rect()
        self.place = (x, y)
        self.rect.x = x
        self.rect.y = y
        self.objType = otype

    def move(self, dx, dy):
        self.rect.x += dx
        self.rect.y += dy
        self.place[0] += dx
        self.place[1] += dy


class VisualMap(pygame.Surface):
    def __init__(self, width, height):
        pygame.Surface.__init__(self, size=(width, height))
        self.pos = (width, height)
        self.RECT = (0, 0, width, height)
        self.INRECT = (edge,edge, width-(edge), height-(edge))
        pygame.draw.rect(self, WHITE, self.RECT)
        pygame.draw.rect(self, BLACK, self.INRECT)
        self.objects = pygame.sprite.Group()

    def genBarriers(self, map):
        pass
        #reads barrier count and then adds them as sprites in objects

    def createRobot(self, scale, map):
        self.worldMap = map
        self.robot = Robot(scale, map)

    def render(self, display):
        "Draws surface on the display"
        display.blit(self, (0, self.pos[1]))

def main():
    import os
    amap = UnlimMap(5, 2, 20)
    amap.addBarrier(0, 0)
    amap.addBarrier(4, 1)
    #pls fix this, it saves elsewhere thanks Python very cool
    #amap.saveMap("testerMap.txt")

    #Example

    #scale in centimeters?
    scale = 50
    bot = Robot(scale)
    botMap = UnlimMap(10, 10, scale)


if __name__ == '__main__':
    main()
