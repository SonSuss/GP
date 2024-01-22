import pygame

class Crowbar:
    def __init__(self, x, y, width, height, color):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.color = color

    def update_position(self, mouse_pos):
        self.x, self.y = mouse_pos[0], mouse_pos[1]

    def draw(self, window):
        pygame.draw.rect(window, self.color, (self.x, self.y, self.width, self.height))

class Target:
    def __init__(self, width, height, color, hit_duration):
        self.width = width
        self.height = height
        self.color = color
        self.x = WIDTH // 2 - width // 2
        self.y = HEIGHT // 2 - height // 2
        self.start_time = 0
        self.hit_duration = hit_duration

    def update_color(self, crowbar):
        elapsed_time = pygame.time.get_ticks() - self.start_time

        # Change color after 2 seconds
        if elapsed_time > 2000:
            # Stay green for 1 second
            if elapsed_time <= 3000:
                self.color = (0, 255, 0)
            else:
                # Check if hit
                if (
                    self.x < crowbar.x < self.x + self.width
                    and self.y < crowbar.y < self.y + self.height
                    and self.color == (0, 255, 0)  # Only check for hits when target is green
                ):
                    # Turn red when hit
                    self.color = (255, 0, 0)
                    self.start_time = pygame.time.get_ticks()  # Record the start time
                else:
                    self.color = (0, 0, 255)

    def draw(self, window, crowbar):
        self.update_color(crowbar)
        pygame.draw.rect(window, self.color, (self.x, self.y, self.width, self.height))

# 1280:720
WIDTH, HEIGHT = 1280, 720
WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("BONK ZOMBIE!!!")

FPS = 60

# Create instances of the Crowbar and Target classes
crowbar = Crowbar(WIDTH // 2 - 40 // 2, HEIGHT // 2 - 60 // 2, 40, 60, (255, 0, 0))
target = Target(300, 400, (0, 0, 255), 500)  # Added hit_duration of 500 milliseconds

# Counter for hits
points = 0

pygame.font.init()  # Initialize the font module
font = pygame.font.Font(None, 36)  # Use a default font with size 36

def draw_game_window():
    WIN.fill((0, 0, 0))  # Fill the window with black background
    target.draw(WIN, crowbar)
    crowbar.draw(WIN)

    # Display points at the top-left corner of the screen
    points_text = font.render(f"Points: {points}", True, (255, 255, 255))
    WIN.blit(points_text, (10, 10))

    pygame.display.update()

def main():
    global points  # Use global variable for points
    clock = pygame.time.Clock()
    run = True
    while run:
        clock.tick(FPS)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            elif event.type == pygame.MOUSEMOTION:
                # Update box position to follow the mouse
                mouse_pos = event.pos
                crowbar.update_position(mouse_pos)
            elif event.type == pygame.MOUSEBUTTONDOWN:
                # Check for hits when the mouse is clicked
                target.update_color(crowbar)  # Check and update color
                if target.color == (255, 0, 0):  # Check if target is red after update
                    points += 1  # Increase points when hit

        draw_game_window()

    pygame.quit()

if __name__ == "__main__":
    main()
