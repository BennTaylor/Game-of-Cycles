import pygame
import math
import numpy as np
import os

pygame.init()

# frame rate
clock = pygame.time.Clock()
frame_rate = 30

# window setup
SCREEN_WIDTH, SCREEN_HEIGHT = 800, 600
screen = pygame.display.set_mode((SCREEN_WIDTH,SCREEN_HEIGHT))

# colors constants
BLACK, GRAY, WHITE = (0,0,0), (127,127,127), (255,255,255)
RED, GREEN, BLUE = (255,0,0), (0,255,0), (0,0,255)
YELLOW, CYAN, MAGENTA = (255,255,0), (0,255,255), (255,0,255)

# graph vars setup
nodes = []      # stores coords of node as pair (x,y)
edges = []      # stores edge u->v as pair (u,v)
markings = []     # stores whether edge is marked or not // 0 = not marked, 1 = positive orientation, 2 = negative orientation
cycles = []     # stores list of cycle-cells in graph; 
                # each entry a tuple of (edge, orientation) where edge is index of edge in edges 
                # and orientation is True (positive) or False (negative)

def load_vertices_from_file(board_name):
    """
        Intializes nodes of board in pygame;
        Reads from /board_embeddings/<board_name>_embedding.txt to determine
        placement of nodes in pygame window.
    """
    file_path = "../board_embeddings/" + board_name + "_embedding.txt"
    file = open(file_path, "r")

    lines = file.readlines()

    for line in lines[2:]:
        coords = line.split()
        # storing coords of node
        x, y = int(coords[0]), int(coords[1])
        nodes.append((x,y))
        # adding nodes to display
        pygame.draw.circle(screen, BLACK, (x,y), 10)

    file.close()

def load_encoding_from_file(board_name):
    """
        Initializes edges of board in pygame;
        Reads from /board_encodings/<board_name>_encoding.txt to determine
        which nodes to draw connections between in pygame window.
    """
    file_path = "../board_encodings/" + board_name + "_encoding.txt"
    file = open(file_path, "r")

    lines = file.readlines()

    i = 3
    for line in lines[3:]:
        if line == "CYCLES\n":
            break
        edge = line.split()
        # storing edge u->v
        u, v = int(edge[0]), int(edge[1])
        edges.append((u,v))
        marked.append(False)
        i += 1

        # drawing edge u->v and adding as Rect object
        pygame.draw.line(screen, GRAY, nodes[u], nodes[v])

    # storing cycle cells
    for line in lines[i+1:]:
        cycle = []
        entries = line.split()
        for j in range(len(entries)):
            if entries[j][0] == "+":
                cycle.append((int(entries[j][1:]), True))
            else:
                cycle.append((int(entries[j][1:]), False))
        cycles.append(cycle)
                
    file.close()


def mouse_on_edge(edge_index):
    """
        Checks whether mouse is hovering over edge corresponding to edge_index
    """
    mouse_pos = pygame.mouse.get_pos()
    u = nodes[edges[edge_index][0]]
    v = nodes[edges[edge_index][1]]

    threshold = 8

    def distance_point_to_line(point, line_point1, line_point2):
        x, y = point
        x1, y1 = line_point1
        x2, y2 = line_point2

        numerator = abs((x1 - x) * (y2 - y1) - (x2 - x1) * (y1 - y))
        denominator = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

        return numerator / denominator

    def mouse_in_segment():
        x1 = min(u[0], v[0])
        x2 = max(u[0], v[0])
        x = mouse_pos[0]

        y1 = min(u[1], v[1])
        y2 = max(u[1], v[1])
        y = mouse_pos[1]

        return ( ((x >= x1 and x <= x2) or (abs(x - x1) < threshold)) and 
                 ((y >= y1 and y <= y2) or (abs(y - y1) < threshold)) )

    return ( (distance_point_to_line(mouse_pos, u, v) < threshold) 
            and mouse_in_segment() )

def mark_edge(edge_ind):
    """
        Marks edge corresponding to edge_ind; also looks for direction
    """

    x,y = pygame.mouse.get_pos()
    e1 = nodes[edges[edge_ind][0]]
    e2 = nodes[edges[edge_ind][1]]

    def draw_marking(u,v):
        # draw triangle centered between (ux,uy) and (vx,vy) pointing towards (ux,uy)

        ux, uy = nodes[u]
        vx, vy = nodes[v]

        triangle = [np.array([0,10]),np.array([-7,-7]),np.array([7,-7])]
        
        # angle from +x from u to v
        theta = math.atan2((vy-uy),(vx-ux)) + 0.5*math.pi
        c,s = math.cos(theta), math.sin(theta)
        rot_mat = np.array([[c,-s],
                            [s,c]])
        
        for i in range(3):
            triangle[i] = np.matmul(rot_mat, triangle[i])
            triangle[i] = triangle[i]+np.array([ (ux+vx)/2, (uy+vy)/2 ])

        pygame.draw.polygon(screen, BLUE, triangle)

    if ( ((x-e1[0])**2)+((y-e1[1])**2) < ((x-e2[0])**2)+((y-e2[1])**2) ):   # closer to e1
        markings[edge_ind] = 2
        draw_marking(edges[edge_ind][0],edges[edge_ind][1])
    else:
        markings[edge_ind] = 1
        draw_marking(edges[edge_ind][1],edges[edge_ind][0])

    pygame.draw.line(screen, BLUE, nodes[edges[edge_ind][0]], nodes[edges[edge_ind][1]])

def play_game(board_name):
    screen.fill(WHITE)
    load_vertices_from_file(board_name)
    load_encoding_from_file(board_name)
    pygame.display.update()

    # game loop
    game_active = True
    while run:
        mouse_down = False
        # check for game quit
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_down = True

        # check for mouse collision with edges
        for i in range(len(edges)):
            edge = edges[i]
            if marked[i]:
                continue
            if mouse_on_edge(i):
                if mouse_down:
                    mark_edge(i)
                else:                
                    pygame.draw.line(screen, RED, nodes[edge[0]], nodes[edge[1]])
            else:
                pygame.draw.line(screen, GRAY, nodes[edge[0]], nodes[edge[1]])

        pygame.display.update()
        clock.tick(frame_rate)


# menu setup
boards = []
dir = "../board_encodings/"
for file in dir:
    if file.endswith("_encoding.txt"):
        boards.append(file[:-13])

# outmost game loop; functions as game menu
run = True
while(run):
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
        if event.type == pygame.MOUSEBUTTONDOWN:
            mouse_down = True

    # ... check if click on menu button for board ...
    play_game(board)
    nodes = []
    edges = [] 
    marked = []
    
pygame.quit()