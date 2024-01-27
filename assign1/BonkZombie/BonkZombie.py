import random
import pygame
from zombie import *
from background import BackGround

class BonkZombie:
    class State(Enum):
        MENU = 0
        RUN = 1

    def __init__(self):
        self.pygame = pygame

    def init(self):
        # main game
        self.pygame.init()
        self.state = self.State.MENU

        self.width = 1280
        self.height = 720
        self.screen = pygame.display.set_mode((self.width, self.height))
        pygame.display.set_caption('Bonk Zombie')
        self.clock = pygame.time.Clock()
        self.font = pygame.font.Font('freesansbold.ttf', 32)

        self.last_update = pygame.time.get_ticks()
        self.cooldown = 1000
        self.running = True

        self.background = BackGround(self.screen)
        self.zombies = pygame.sprite.Group()

        for grave in self.background.graves:
            self.zombies.add(Zombie(self,grave.x,grave.y))

        self.point = 0
        self.point_per_hit = 100
        self.hit_count = 0
        self.heart_point = 5

        self.point_pos = pygame.Rect(10,10,self.width,50)
        self.heart_image = pygame.image.load('Image/Heart.png')

        # menu
        self.start_button = pygame.Rect(self.width/2 - 60, self.height/2 - 40, 120, 80)
        self.start_font = self.font.render('Start!', True, 'Black')
        self.start_font_center = self.start_font.get_rect(center=(self.width/2, self.height/2))

        self.last_point = 0

        #sound
        self.bonk_sound = pygame.mixer.Sound('Sound/bonk.mp3')
        self.zombie_sound = pygame.mixer.Sound('Sound/zombie_sound.mp3')

    def update(self):
        current_time = pygame.time.get_ticks()
        if current_time - self.last_update > self.cooldown:
            self.last_update = current_time
            lst = self.zombies.sprites()
            not_appear_zoms = list(filter(lambda x: x.appear == False,lst))
            if not_appear_zoms:
                random.choice(not_appear_zoms).start()
                pygame.mixer.Sound.play(self.zombie_sound,0,1000,500)
        
        self.zombies.update()

    def draw(self):
        # fill the self.screen with a color to wipe away anything from last frame
        self.screen.fill("black")
        # RENDER GAME
        self.background.draw()
        self.zombies.draw(self.screen)

        text = self.font.render(str(self.point),True, 'white')
        self.screen.blit(text, self.point_pos)
        self.draw_heart()

    def draw_heart(self):
        for i in range(0,self.heart_point):
            self.screen.blit(self.heart_image, (self.width - 36 - 26*i, 10))

    def menu(self):
        point_font = self.font.render('Point: ' + str(self.last_point), True, 'white')
        point_rect = point_font.get_rect(center=(self.width/2, self.height/2 - 100))

        self.screen.fill("black")
        pygame.draw.rect(self.screen, 'gray', self.start_button)
        self.screen.blit(self.start_font,self.start_font_center)
        self.screen.blit(point_font,point_rect)

    def miss(self):
        self.heart_point -= 1
        if self.heart_point <= 0:
            self.reset()
            self.state = self.State.MENU

    def hit(self):
        pygame.mixer.Sound.play(self.bonk_sound)

        self.hit_count += 1
        self.point += self.point_per_hit

        if self.hit_count % 10 == 9 and self.cooldown > 200:
            self.point_per_hit += 20
            self.cooldown -= 50

    def reset(self):
        self.last_point = self.point
        self.point = 0
        self.point_per_hit = 100
        self.hit_count = 0
        self.heart_point = 5
        self.cooldown = 1000

        for zom in self.zombies.sprites():
            zom.reset()

    def run(self):
        self.init()
        pygame.mixer.music.load('Sound/Sakura-Girl-Daisy-chosic.com_.mp3')
        pygame.mixer.music.play(-1)
        pygame.mixer.music.set_volume(0.2)
        while self.running:
            if self.state == self.State.RUN:
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        self.running = False

                    if event.type == pygame.MOUSEBUTTONUP:
                        lst = self.zombies.sprites()
                        for zombie in list(filter(lambda x: x.appear == True and x.bonked == False ,lst)):
                            if zombie.hitbox.collidepoint(event.pos):
                                zombie.bonked = True
                                self.hit()
                                break

                self.update()
                self.draw()

            elif self.state == self.State.MENU:
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        self.running = False
                    if event.type == pygame.MOUSEBUTTONUP:
                        if self.start_button.collidepoint(event.pos):
                            self.state = self.State.RUN
                    

                self.menu()

            # flip() the display to put your work on self.screen
            pygame.display.flip()

            self.clock.tick(60)  # limits FPS to 60

        pygame.quit()
