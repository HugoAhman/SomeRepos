#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "raymath.h"

typedef enum
{
    North,
    South,
    East,
    West
} Direction;

typedef enum
{
    Unused,
    Border,
    Wall,
    Floor,
    Corridor,
    Door,
} Tile;

/*
Tile map[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
*/

void CreateRoom(Tile *map, int mapWidth, int mapHeight, int minRoomSize, int maxRoomSize)
{
    // Random room size
    int roomWidth = minRoomSize + rand() % (maxRoomSize - minRoomSize + 1);
    int roomHeight = minRoomSize + rand() % (maxRoomSize - minRoomSize + 1);

    // Random position inside the border
    int roomX = 1 + rand() % (mapWidth - roomWidth - 1);   // Ensures room is within borders so it doesn't go out of the border.
    int roomY = 1 + rand() % (mapHeight - roomHeight - 1); // The same but the Y axle.

    // Place the room
    for (int y = roomY; y < roomY + roomHeight; y++)
    {
        for (int x = roomX; x < roomX + roomWidth; x++)
        {
            if (x == roomX || x == roomX + roomWidth - 1 || y == roomY || y == roomY + roomHeight - 1)
            {
                map[y * mapWidth + x] = Wall;
            }
            else
            {
                map[y * mapWidth + x] = Floor;
            }
        }
    }
}

int nextToRoom(Tile *map, int mapWidth, int mapHeight, int x, int y)
{
}

int main()
{
    srand(time(0));

    InitWindow(800, 640, "Endless Dungeon");

    int tileWidth = 16;
    int tileHeight = 16;
    int mapWidth = GetScreenWidth() / tileWidth;    // Makes the mapwidth as big as the screen, we are dividing with tilewidth because then it creates as many tiles as it can inside the window so we dont get any split in half.
    int mapHeight = GetScreenHeight() / tileHeight; // Does the same but for the height.

    Tile *map = (Tile *)malloc(mapWidth * mapHeight * sizeof(Tile)); // Create the map and use the window size as the map size.

    for (int y = 0; y < mapHeight; y++) // Set a border around the whole map using our tile enum
    {
        for (int x = 0; x < mapWidth; x++)
        {
            if (x == 0 || y == 0 || x == mapWidth - 1 || y == mapHeight - 1) // Here we check if its along the edge make it a border and later on we will draw the border.
            {
                map[y * mapWidth + x] = Border;
            }
            else // If it's not along the edge and inside the border we make it unused.
            {
                map[y * mapWidth + x] = Unused;
            }
        }
    }

    int minRoomSize = 4;  // Minimum room dimension
    int maxRoomSize = 12; // Maximum room dimension
    CreateRoom(map, mapWidth, mapHeight, minRoomSize, maxRoomSize);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        for (int y = 0; y < mapHeight; y++)
        {
            for (int x = 0; x < mapWidth; x++)
            {
                int index = y * mapWidth + x;

                if (map[index] == Border)
                {
                    DrawRectangle(x * tileWidth, y * tileHeight, tileWidth, tileHeight, WHITE);
                }
                if (map[index] == Wall)
                {
                    DrawRectangle(x * tileWidth, y * tileHeight, tileWidth, tileHeight, GRAY);
                }
                if (map[index] == Door)
                {
                    DrawRectangle(x * tileWidth, y * tileHeight, tileWidth, tileHeight, BLUE);
                }
                if (map[index] == Floor)
                {
                    DrawRectangle(x * tileWidth, y * tileHeight, tileWidth, tileHeight, LIGHTGRAY);
                }
            }
        }

        for (int y = 0; y < mapHeight; y++)
        {
            for (int x = 0; x < mapWidth; x++)
            {
                int index = y * mapWidth + x;

                if (map[index] == Unused && nextToRoom(map, mapWidth, mapHeight, x, y) - 1)
                {
                    CreateRoom(map, mapWidth, mapHeight, minRoomSize, maxRoomSize);
                }
            }
        }

        EndDrawing();
    }

    free(map);

    CloseWindow();

    return 0;
}
