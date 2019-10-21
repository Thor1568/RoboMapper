#Mapping visualizer using pygame because why not oh yeah yeah

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

    def createRobot(self, robotX, robotY):
        pass

    def render(self, display):
        "Draws surface on the display"
        display.blit(self, (0, self.pos[1]))
