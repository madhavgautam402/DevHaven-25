import pygame
import random
import sys

pygame.init()

WIDTH, HEIGHT = 600, 400
BLOCK_SIZE = 20
FPS = 10

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREEN = (0, 255, 0)
RED = (255, 0, 0)

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Snake Game")

clock = pygame.time.Clock()
snake = [[WIDTH // 2, HEIGHT // 2]]
direction = [0, -BLOCK_SIZE] 
food = [random.randint(0, WIDTH // BLOCK_SIZE - 1) * BLOCK_SIZE,
        random.randint(0, HEIGHT // BLOCK_SIZE - 1) * BLOCK_SIZE]
score = 0

font = pygame.font.SysFont("comicsansms", 20)

def show_score():
    score_text = font.render(f"Score: {score}", True, WHITE)
    screen.blit(score_text, [10, 10])

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP and direction != [0, BLOCK_SIZE]:
                direction = [0, -BLOCK_SIZE]
            elif event.key == pygame.K_DOWN and direction != [0, -BLOCK_SIZE]:
                direction = [0, BLOCK_SIZE]
            elif event.key == pygame.K_LEFT and direction != [BLOCK_SIZE, 0]:
                direction = [-BLOCK_SIZE, 0]
            elif event.key == pygame.K_RIGHT and direction != [-BLOCK_SIZE, 0]:
                direction = [BLOCK_SIZE, 0]

    head = [snake[0][0] + direction[0], snake[0][1] + direction[1]]
    snake.insert(0, head)

    if head[0] < 0 or head[0] >= WIDTH or head[1] < 0 or head[1] >= HEIGHT or head in snake[1:]:
        pygame.quit()
        sys.exit()

    if head == food:
        score += 1
        food = [random.randint(0, WIDTH // BLOCK_SIZE - 1) * BLOCK_SIZE,
                random.randint(0, HEIGHT // BLOCK_SIZE - 1) * BLOCK_SIZE]
    else:
        snake.pop()

    screen.fill(BLACK)  
    for segment in snake:
        pygame.draw.rect(screen, GREEN, (segment[0], segment[1], BLOCK_SIZE, BLOCK_SIZE))  
    pygame.draw.rect(screen, RED, (food[0], food[1], BLOCK_SIZE, BLOCK_SIZE)) 
    show_score() 

    pygame.display.flip()  

    clock.tick(FPS)
