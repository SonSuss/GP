import pygame

WIDTH, HEIGHT = 1280, 720
WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("TINY FOOTBALL")
FPS = 60

class Wall:
    COLOR = (255,0,0)
    def __init__(self, x, y, width, height):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
    
    def draw(self, win):
        pygame.draw.rect(win, self.COLOR, ( self.x, self.y, self.width, self.height))

class Player(Wall):
    COLOR = (255,255,255)
    VEL = 3
    
    
    def movement(self, move): 
        if move == 8 and self.y >= 0:
            self.y -= self.VEL
        if move == 2 and self.y <= HEIGHT - self.height:
            self.y += self.VEL
        if move == 4 and self.x > 0 :
            self.x -= self.VEL
        if move == 6 and self.x < WIDTH -self.width: 
            self.x += self.VEL
        if move == 1:
            if self.y >= HEIGHT - self.height and self.x <= 0:
                pass
            elif self.y >= HEIGHT - self.height:
                self.x -= self.VEL
            elif self.x <= 0:
                self.y += self.VEL
            else: 
                self.x -= self.VEL
                self.y += self.VEL
        if move == 3:
            if self.x >= WIDTH - self.width and self.y >= HEIGHT - self.height:
                pass
            elif self.x >= WIDTH - self.width:
                self.y += self.VEL
            elif self.y >= HEIGHT - self.height:
                self.x += self.VEL
            else:       
                self.y += self.VEL
                self.x += self.VEL
        if move == 9:
            if self.x >= WIDTH - self.width and self.y <=0:
                pass
            elif self.x >= WIDTH - self.width:
                self.y -= self.VEL
            elif self.y <=0:
                self.x += self.VEL
            else: 
                self.y -= self.VEL
                self.x += self.VEL
        if move == 7:
            if self.x <= 0 and self.y <= 0:
                pass
            elif self.x <= 0 :
                self.y -= self.VEL
            elif self.y <= 0 :
                self.x -= self.VEL
            else:    
                self.y -= self.VEL
                self.x -= self.VEL
        if move == 5:
            pass    

            
            
def help_movement(key):
    if key[pygame.K_UP] and key[pygame.K_LEFT]:
        return 7
    if key[pygame.K_UP] and key[pygame.K_RIGHT]:
        return 9
    if key[pygame.K_DOWN] and key[pygame.K_LEFT]:
        return 1
    if key[pygame.K_DOWN] and key[pygame.K_RIGHT]:
        return 3
    if key[pygame.K_UP]:
        return 8
    if key[pygame.K_DOWN]:
        return 2
    if key[pygame.K_LEFT]:
        return 4
    if key[pygame.K_RIGHT]:
        return 6
    return 5
    

def draw(win, walls, player):
    win.fill((0,0,0))
    
    for wall in walls:
        wall.draw(win)
    
    player.draw(win)
    
    pygame.display.update()
    

def main():
    run = True 
    clock = pygame.time.Clock()
    
    wall1 = Wall(WIDTH // 2, 0 , WIDTH // 2 , 20)
    wall2 = Wall(WIDTH // 2, HEIGHT - 20 , WIDTH // 2 , 20)
    wall3 = Wall(WIDTH - 20, HEIGHT // 2 - 400 // 2 , 20 ,400)
    walls = [wall1, wall2, wall3]
    player1 = Player(10 , HEIGHT // 2 - 200 // 2 , 10 , 200)
    
    while run:
        clock.tick(FPS)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
                break
        key = pygame.key.get_pressed()
        player1.movement(help_movement(key))
        
        draw(WIN, walls, player1)
            
            
            
if __name__ == "__main__":
    main()