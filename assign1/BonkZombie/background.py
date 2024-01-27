import random
import pygame

class Grave:
    width = 150
    height = 230
    graveImg = pygame.image.load('Image/Background/Grave01.png')

    def __init__(self,x,y):
        self.haveZombie = False
        self.x = x - Grave.width/2
        self.y = y - Grave.height/2
        self.center = pygame.Vector2(x,y)
        self.color = 'red'
        self.lineWidth = 3

    def draw(self, surface:pygame.Surface):
        rect = pygame.Rect(self.x, self.y, Grave.width, Grave.height)
        # pygame.draw.rect(surface, self.color, rect, self.lineWidth)
        surface.blit(Grave.graveImg ,rect)

        # newRect = pygame.Rect(self.x + 30, self.y + 125 , 90, 60) # hit box
        # pygame.draw.rect(surface,'red',newRect)

class BackGround:
    paddingWidth = 80
    paddingHeight = 100

    def __init__(self, surface:pygame.Surface):
        self.surface = surface
        self.width = surface.get_width()
        self.height = surface.get_height()
        self.numGrave = 10
        self.numRow = 2
        self.graves = []
        self.addGrave()

        self.image = pygame.image.load('Image/Background/Grass.png')

    def addGrave(self):
        numGravePerRow = int(self.numGrave/self.numRow)
        widthGap = (self.width - BackGround.paddingWidth*2 - Grave.width) / (numGravePerRow - 1) if numGravePerRow != 1 else 0
        heightGap = (self.height - BackGround.paddingHeight*2 - Grave.height) / (self.numRow - 1) if self.numRow != 1 else 0

        x = BackGround.paddingWidth + Grave.width / 2
        y = BackGround.paddingHeight + Grave.height / 2

        for i in range(0,self.numRow):
            for j in range(0,numGravePerRow):
                self.graves.append(Grave(x,y))
                x = x + widthGap
            y = y + heightGap
            x = BackGround.paddingWidth + Grave.width / 2

    def draw(self):
        self.surface.blit(self.image,[0,0])
        for grave in self.graves:
            grave.draw(self.surface)