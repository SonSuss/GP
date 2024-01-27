#2052688

import pygame

WIDTH, HEIGHT = 1280, 720
WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("TINY FOOTBALL")
FPS = 60
WHITE = (255,255,255)
BALL_R = 12

PLAYER_WIDTH = 30
PLAYER_HEIGHT = 150

class Wall:
    COLOR = (76,153,0)
    def __init__(self, x, y, width, height):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.hit_box = (x,y,x+width,y+height)
    
    def draw(self, win):
        pygame.draw.rect(win, self.COLOR, ( self.x, self.y, self.width, self.height))
        

class Player(Wall):
    COLOR = WHITE
    VEL = 3
    
    def movement(self, move): 
        if move == 8 :
            self.y -= self.VEL
        if move == 2 :
            self.y += self.VEL
        if move == 4 :
            self.x -= self.VEL
        if move == 6 : 
            self.x += self.VEL
        if move == 1: 
            self.x -= self.VEL
            self.y += self.VEL
        if move == 3:      
            self.y += self.VEL
            self.x += self.VEL
        if move == 9:
            self.y -= self.VEL
            self.x += self.VEL
        if move == 7:
            self.y -= self.VEL
            self.x -= self.VEL
        
        if self.y < 0:
            self.y = 0
        if self.y > HEIGHT - self.height:
            self.y =  HEIGHT - self.height
        if self.x < 0:
            self.x = 0;
        if self.x > WIDTH - self.width:
            self.x = WIDTH - self.width
            
        self.hit_box = (self.x ,self.y , self.x+self.width ,self.y+self.height)
        
            
class Ball:
    COLOR = (0, 255, 255)
    
    def __init__(self, x, y, radius):
        self.pre_x = x
        self.pre_y = y
        self.x = x
        self.y = y
        self.radius = radius
        self.x_vel = -5
        self.y_vel = 0  

    def draw(self, win):
        pygame.draw.circle(win, self.COLOR, (self.x, self.y), self.radius)

    def move(self):
        self.pre_x = self.x
        self.pre_y = self.y
        self.x += self.x_vel
        self.y += self.y_vel

#self.hit_box = (x,y,x+width,y+height)

    def hit(self, object):
        # Hit top
        if self.y_vel > 0:
            if object.hit_box[0] - self.radius < self.x < object.hit_box[2] + self.radius:
                if self.y + self.radius >= object.hit_box[1] and self.pre_y  < object.hit_box[1] :
                    self.y_vel *= -1
                    self.y = object.hit_box[1] - self.radius
        # Hit bottom
        else:
            if object.hit_box[0] - self.radius < self.x < object.hit_box[2] + self.radius:
                if self.y - self.radius <= object.hit_box[3] and self.pre_y  > object.hit_box[3] :
                    self.y_vel *= -1
                    self.y = object.hit_box[3] + self.radius
        # Hit left
        if self.x_vel > 0:
            if object.hit_box[1] - self.radius < self.y < object.hit_box[3] + self.radius:
                if self.x + self.radius >= object.hit_box[0] and self.pre_x  < object.hit_box[0] :
                    self.x_vel *= -1
                    self.x = object.hit_box[0] - self.radius
        # Hit right
        else:
            if object.hit_box[1] - self.radius < self.y < object.hit_box[3] + self.radius:
                if self.x - self.radius <= object.hit_box[2] and self.pre_x > object.hit_box[2] :
                    self.x_vel *= -1
                    self.x = object.hit_box[2] + self.radius



def catch_pass_through(ball, object):
    if object.x < ball.x < object.x + object.width and object.y < ball.y < object.y + object.height:
        print([ball.x ,ball.y, ball.x_vel, ball.y_vel, object.x, object.y])
        pygame.quit()
    
            
def ball_contract(balls, objects):
    for ball in balls:
        for object in objects:
            ball.hit(object)       

def help_movement_player1(key):
    if key[pygame.K_w] and key[pygame.K_a]:
        return 7
    if key[pygame.K_w] and key[pygame.K_d]:
        return 9
    if key[pygame.K_s] and key[pygame.K_a]:
        return 1
    if key[pygame.K_s] and key[pygame.K_d]:
        return 3
    if key[pygame.K_w]:
        return 8
    if key[pygame.K_s]:
        return 2
    if key[pygame.K_a]:
        return 4
    if key[pygame.K_d]:
        return 6
    return 5            
          
def help_movement_player2(key):
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
    

def draw(win, walls, players,balls):
    win.fill((0,0,0))

    for line in range(22, HEIGHT, HEIGHT // 10):
        if line % 2 == 1:
            continue
        pygame.draw.rect(win, WHITE, (WIDTH // 2 - 5 , line , 10, HEIGHT // 40))
   
    for wall in walls:
        wall.draw(win)
    
    for player in players:
        player.draw(win)
        
    for ball in balls:
        ball.draw(win)
    
    ball.draw(win)

    pygame.display.update()
    


def main():
    run = True 
    clock = pygame.time.Clock()
    
    wall1 = Wall(0, 0 , WIDTH, 20)
    wall2 = Wall(0 , HEIGHT - 20 , WIDTH  ,20)
    wall3 = Wall(0, 0 , 20 , HEIGHT )
    wall4 = Wall(0, HEIGHT - HEIGHT // 3 , 20 , HEIGHT // 3)
    wall5 = Wall(WIDTH - 20, 0 , 20 , HEIGHT )
    wall6 = Wall(WIDTH - 20, HEIGHT - HEIGHT // 3 , 20 , HEIGHT // 3)
    
    walls = [wall1, wall2, wall3, wall4, wall5, wall6]
    
    player1 = Player(10 , HEIGHT // 2 - PLAYER_HEIGHT // 2 , PLAYER_WIDTH , PLAYER_HEIGHT)
    player2 = Player(WIDTH - PLAYER_WIDTH - 10 , HEIGHT // 2 - 100 // 2, PLAYER_WIDTH , PLAYER_HEIGHT)
    
    players = [player1, player2]
    
    ball = Ball(WIDTH // 2 , HEIGHT // 2 , BALL_R)
    
    balls = [ball]
    
    while run:
        clock.tick(FPS)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
                break
        
        key = pygame.key.get_pressed()
        ball.move()
        players[0].movement(help_movement_player1(key))
        players[1].movement(help_movement_player2(key))
        catch_pass_through(ball , players[0])
        
        ball_contract(balls, players + walls)
        
        
        draw(WIN, walls, players, balls)
            
    pygame.quit()
    
            
if __name__ == "__main__":
    main()