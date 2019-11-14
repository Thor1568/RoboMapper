"""OK, so we need to make some constraints:
This mapping program is made to function in two ways:
Unlimited mode and Limited mode.
Unlimited is outdoors where there are not obstacles everywhere and the
robot will patrol a clearly defined area.
Limited is indoors where there are obstacles and it will patrol until it
is disabled? Maybe merge them but here are framework classes for how it
will work

"""

import pygame
WHITE = (255,255,255)
BLACK = (0,0,0)
RED = (255,0,0)
GREEN = (0,255,0)
BLUE = (0,0,255)
GRAY = (60, 60, 60)

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


class LimMap():
    """
    Creates a limited map where the dimensions are clearly
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


class UnlimMap():
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
    def __init__(self, size, x, y, otype):
        """Class for any object that is shown on the map so robot, wall,
        or otherwise"""
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.Surface(size)
        if otype == 0:
            self.image.fill(RED)
            pygame.draw.rect(self.image, BLACK, (5, 5, size[0]-5*2, size[1]-5*2))
        else:
            self.image.fill((255,255,255))
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
    def __init__(self, width, height, scale, map):
        pygame.Surface.__init__(self, size=(width, height))

        #how to do size?
        #vizmap is constant size: 800-50 x 600-50 (25 on each size for cool stuff).
        #maps are abritrary size.

        self.fill((0, 255, 0))
        self.scale= scale
        self.worldMap = map
        edge = scale/2
        self.edge = edge
        #reverse these deej
        self.RECT = (0, 0, width, height)
        self.INRECT = (edge,edge, width-(edge*2), height-(edge*2))
        pygame.draw.rect(self, WHITE, self.RECT)
        pygame.draw.rect(self, GRAY, self.INRECT)
        self.objects = pygame.sprite.Group()

    def genBarriers(self):
        rawmap = self.worldMap.map
        for y in range(len(rawmap)):
            for x in range(len(rawmap[y])):
                if rawmap[y][x] == 1:
                    #create add
                    oof = MapObject((self.scale, self.scale), x*self.scale+self.edge, y*self.scale+self.edge, 0)
                    self.objects.add(oof)
                else:
                    pass
        #Draw lines at map bounds. rawmap[-1][-1] is max. Or rawmap.length since all maps are square
        #reads barrier count and then adds them as sprites in objects

    def createRobot(self, x, y):
        self.robot = MapObject((self.scale-self.edge*2, self.scale-self.edge*2), x*self.scale+self.edge, y*self.scale+self.edge, "r")
        self.objects.add(self.robot)

    def render(self, display):
        "Draws surface on the display"
        self.objects.draw(self)
        display.blit(self, (0, 0))

def main():
    import os
    #amap = UnlimMap(5, 2, 20)
    #amap.addBarrier(0, 0)
    #amap.addBarrier(4, 1)
    #pls fix this, it saves elsewhere thanks Python very cool
    #amap.saveMap("testerMap.txt")

    #Example

    #scale in centimeters? relate to map size in some way?
    scale = 50
    bot = Robot(scale)
    botMap = LimMap(10, 10, scale)
    botMap.addBarrier(1, 1)
    botMap.addBarrier(1, 0)
    botMap.addBarrier(2, 0)
    botMap.addBarrier(5, 5)
    botMap.addBarrier(7, 8)
    botMap.addBarrier(8, 8)
    botMap.addBarrier(9, 9)
    botMap.addBarrier(7, 9)
    botMap.addBarrier(1, 5)
    botMap.saveMap("botmap.txt")


    #pygame crap for vis
    wid = 800
    height = 600
    gDisp = pygame.display.set_mode((wid,height), pygame.FULLSCREEN, 16)
    pygame.display.set_caption('mapper test')
    gclock = pygame.time.Clock()


    temp = VisualMap(wid, height, scale, botMap)
    temp.genBarriers()
    temp.createRobot(0,0)

    run = True
    while (run):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    run = False

        #Reset robot position and tiles seen by robot
        botMap.updateRobot(bot)
        #Update the visual map
        temp.update()
        #blah blah
        gDisp.fill(BLACK)
        temp.render(gDisp)
        pygame.display.flip()
        gclock.tick(60)


    pygame.quit()
    exit()


if __name__ == '__main__':
    main()
