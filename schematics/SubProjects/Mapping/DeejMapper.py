"""OK, so we need to make some constraints:
This mapping program is made to function in two ways:
Unlimited mode and Limited mode.
Unlimited is outdoors where there are not obstacles everywhere and the
robot will patrol a clearly defined area.
Limited is indoors where there are obstacles and it will patrol until it
is disabled? Maybe merge them but here are framework classes for how it
will work

"""


""" Mapper testing:
Create random map with robot in random position. Pathfinding? I pick an unexplored point and move towards the point."""

import pygame
from random import randint
WHITE = (255,255,255)
BLACK = (0,0,0)
RED = (255,0,0)
GREEN = (0,255,0)
BLUE = (0,0,255)
GRAY = (60, 60, 60)
LTGRAY = (120,120,120)

class Robot():
    """
    'Robot' that acts as a virtual placeholder for the actual thing.
    Returns a changed map after reading the map and checking if it can move
    """
    def __init__(self, scale):
        self.x = 0; self.y = 0;
        self.scaleX = 0; self.scaleY = 0;
        self.lastX = 0; self.lastY = 0;
        self.deltaX = 0
        self.dist = 0
        self.scale = scale

    def moveRaw(self, dx, dy):
        #move deltaX and deltaY or change in x and y
        self.lastX = self.x; self.lastY = self.y;
        #change map position x and y
        self.x += dx
        self.y += dy
        #change scaled x and y
        self.scaleX += dx*self.scale
        self.scaleY += dy*self.scale
        #delta x is displacement in taxicab geometry
        self.deltaX += dx*self.scale+dy*self.scale
        #dist is total movement in taxicab geometry
        self.dist += abs(dx*self.scale)+abs(dy*self.scale)

    def move(self, dx, dy, map):
        #moves with check
        check = self.canMove(dx, dy, map)
        print(check)
        if check:
            self.moveRaw(dx, dy)

        #return the edited map with the robot moved on it
        newPos = (self.x, self.y)
        #2 is explored so replace last position with 2
        print("Before", map)
        map[self.lastY][self.lastX] = 2
        #current position set to 3
        map[newPos[1]][newPos[0]] = 3
        #returns changed map.
        print(newPos)
        print("after", map)
        return map

    def canMove(self, dx, dy, map):
        future = (self.x+dx, self.y+dy)
        xSize = len(map[0])
        ySize = len(map)
        if (future[0] < xSize) and (future[0] >= 0):
            if (future[1] < ySize) and (future[1] >= 0):
                newTile = map[future[1]][future[0]]
                if (newTile == 0) or (newTile == 2):
                    return True
                else:
                    return False
            else:
                return False
        else:
            return False


    def _reset(self):
        self.x = 0; self.y = 0;
        self.deltaX = 0
        self.dist = 0


class LimMap():
    """
    Creates a limited map where the dimensions are clearly
    defined and the scale is the area of the "squares" that
    the map is made up of.(subject to change) Ideally scale
    is the size of the robot. Object for the map? May delete for beign unnecessary"""
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

    def updateMap(self, map):
        #fill in map with a spot where the robot is
        self.map = map


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
        elif otype == "e":
            self.image.fill(LTGRAY)
        else:
            self.image.fill(BLUE)

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
        self.width = width
        self.height = height
        #reverse these deej
        self.RECT = (0, 0, self.width, self.height)
        self.INRECT = (self.edge,self.edge, self.width-(self.edge*2), self.height-(self.edge*2))
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
                elif rawmap[y][x] == 2:
                    oof = MapObject((self.scale, self.scale), x*self.scale+self.edge, y*self.scale+self.edge, "e")
                    self.objects.add(oof)
                elif rawmap[y][x] == 3:
                    self.robot = MapObject((self.scale, self.scale), x*self.scale+self.edge, y*self.scale+self.edge, "r")
                    self.objects.add(self.robot)

                else:
                    pass
        #Draw lines at map bounds. rawmap[-1][-1] is max. Or rawmap.length since all maps are square
        #reads barrier count and then adds them as sprites in objects

    def createRobot(self, x, y):
        self.robot = MapObject((self.scale-self.edge*2, self.scale-self.edge*2), x*self.scale+self.edge, y*self.scale+self.edge, "r")
        self.objects.add(self.robot)

    def render(self, display):
        "Draws surface on the display"
        self.fill(BLACK)
        self.RECT = (0, 0, self.width, self.height)
        self.INRECT = (self.edge,self.edge, self.width-(self.edge*2), self.height-(self.edge*2))
        pygame.draw.rect(self, WHITE, self.RECT)
        pygame.draw.rect(self, GRAY, self.INRECT)
        self.objects.draw(self)
        display.blit(self, (0, 0))

    def update(self, newMap):
        #regenerate all objects?
        self.objects = pygame.sprite.Group()
        self.worldMap = newMap
        self.genBarriers()

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
    myRobot = Robot(scale)
    maxWidth = 10
    maxHeight = 10
    barrierAmt = 20
    botMap = LimMap(maxWidth, maxHeight, scale)
    randMap = True
    if randMap:
        for x in range(barrierAmt):
            ytemp = randint(0, maxHeight-1)
            xtemp = randint(0, maxWidth-1)
            botMap.addBarrier(xtemp, ytemp)
    """
    botMap.addBarrier(1, 1)
    botMap.addBarrier(1, 0)
    botMap.addBarrier(2, 0)
    botMap.addBarrier(5, 5)
    botMap.addBarrier(7, 8)
    botMap.addBarrier(8, 8)
    botMap.addBarrier(9, 9)
    botMap.addBarrier(7, 9)
    botMap.addBarrier(1, 5)
    """
    #botMap.saveMap("botmap.txt")


    #pygame crap for vis
    wid = 800
    height = 600
    gDisp = pygame.display.set_mode((wid,height), 0, 16)
    pygame.display.set_caption('mapper test')
    gclock = pygame.time.Clock()


    temp = VisualMap(wid, height, scale, botMap)
    temp.worldMap.map[0][0] = 3
    temp.genBarriers()
    temp.createRobot(0,0)

    run = True
    #key presses for debugging
    wkey = False
    skey = False
    dkey = False
    akey = False
    newmap = []
    while (run):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    run = False
                if event.key == pygame.K_w:
                    wkey = True
                if event.key == pygame.K_s:
                    skey = True
                if event.key == pygame.K_d:
                    dkey = True
                if event.key == pygame.K_a:
                    akey = True



        if wkey:
            newmap = myRobot.move(0, -1, botMap.map)
            #make the robot actually move
            botMap.updateMap(newmap)
        if skey:
            newmap = myRobot.move(0, 1, botMap.map)
            botMap.updateMap(newmap)
        if dkey:
            newmap = myRobot.move(1, 0, botMap.map)
            botMap.updateMap(newmap)
        if akey:
            newmap = myRobot.move(-1, 0, botMap.map)
            botMap.updateMap(newmap)

        wkey = False;skey =False;dkey= False;akey= False



        #Reset robot position and tiles seen by robot
        #Update the visual map?
        temp.update(botMap)
        #blah blah
        gDisp.fill(BLACK)
        temp.render(gDisp)
        pygame.display.flip()
        gclock.tick(30)


    #print(myRobot)
    #print(myRobot.x, myRobot.y)
    pygame.quit()
    #exit()


if __name__ == '__main__':
    main()
