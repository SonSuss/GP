import pygame
from enum import Enum

def loadImgs(lst):
    return list(map(lambda x: pygame.image.load(x),lst))


class Zombie(pygame.sprite.Sprite):
    blank = pygame.image.load('Image/Zombie/blank.png')
    animation = loadImgs([
                'Image/Zombie/Zombie_wake_01.png',
                'Image/Zombie/Zombie_wake_02.png',
                'Image/Zombie/Zombie_wake_03.png',
                'Image/Zombie/Zombie_wake_04.png',

                'Image/Zombie/Zombie_full_01.png',
                'Image/Zombie/Zombie_full_02.png',
                'Image/Zombie/Zombie_full_03.png',
                'Image/Zombie/Zombie_full_04.png',

                'Image/Zombie/Zombie_vanish_01.png',
                'Image/Zombie/Zombie_vanish_02.png',
                'Image/Zombie/Zombie_vanish_03.png',
                'Image/Zombie/Zombie_vanish_04.png',

                'Image/Zombie/Zombie_bonk_01.png',
                'Image/Zombie/Zombie_bonk_02.png',
                'Image/Zombie/Zombie_bonk_03.png',
                'Image/Zombie/Zombie_bonk_04.png',
                ])
    animation_cooldown = 200
    frame_animated = 4
    
    class State(Enum):
        WAKE = 0
        FULL = 1
        VANISH = 2
        BONKED = 3
        def __init__(self, value):
            if len(self.__class__):
                # make links
                all = list(self.__class__)
                first, previous = all[0], all[-1]
                previous.next = self
                self.previous = previous
                self.next = first

    def __init__(self,game,x,y):
        pygame.sprite.Sprite.__init__(self)
        self.main_game = game

        self.image = Zombie.blank
        self.rect = pygame.Vector2(x,y)

        self.last_update = pygame.time.get_ticks()
        self.frame = 0
        self.current_state = Zombie.State.WAKE

        self.appear = False
        self.bonked = False

        self.hitbox = pygame.Rect(x + 30, y + 125 , 90, 60)
    
    def start(self):
        self.appear = True
        self.last_update = pygame.time.get_ticks()
        self.frame = 0

    def reset(self):
        self.image = Zombie.blank
        self.appear = False
        self.bonked = False
        self.current_state = Zombie.State.WAKE
        self.frame = 0

    def updateState(self):
        if self.frame == Zombie.frame_animated:
            if self.current_state == Zombie.State.BONKED:
                self.reset()
                return False
            elif self.current_state == Zombie.State.VANISH:
                self.reset()
                self.main_game.miss()
                return False
            else :
                self.current_state = self.current_state.next
        return True

    def update(self):
        if self.appear is False:
            return
        current_time = pygame.time.get_ticks()

        if self.bonked == True and self.current_state is not Zombie.State.BONKED:
            self.current_state = Zombie.State.BONKED
            self.frame = 0

        if current_time - self.last_update > Zombie.animation_cooldown:
            self.last_update = current_time

            if self.updateState():
                self.frame %= Zombie.frame_animated
                index = self.frame + self.current_state.value * Zombie.frame_animated
                self.image = Zombie.animation[index]
                self.frame += 1


    