#include <stdio.h>

int paths[50][100][100]; // To store all found paths
int maze[100][100];       // Maze array
int count = 0;            // To count the number of paths found

// Check if moving left is valid
int left(int maze[][100], int map[][100], int r, int c) {
    if (c > 0 && maze[r][c - 1] != 0 && map[r][c - 1] != 1) // Valid if within bounds and not visited or a wall
        return 1;
    return 0;
}

// Check if moving up is valid
int up(int maze[][100], int map[][100], int r, int c) {
    if (r > 0 && maze[r - 1][c] != 0 && map[r - 1][c] != 1) // Valid if within bounds and not visited or a wall
        return 1;
    return 0;
}

// Check if moving right is valid
int right(int maze[][100], int map[][100], int r, int c) {
    if (c < 100 && maze[r][c + 1] != 0 && map[r][c + 1] != 1) // Valid if within bounds and not visited or a wall
        return 1;
    return 0;
}

// Check if moving down is valid
int down(int maze[][100], int map[][100], int r, int c) {
    if (r < 100 && maze[r + 1][c] != 0 && map[r + 1][c] != 1) // Valid if within bounds and not visited or a wall
        return 1;
    return 0;
}

// Recursive function to find paths
int findWay(int maze[][100], int map[][100], int r, int c, int x, int y, int targetX, int targetY) {
    if (x == targetX && y == targetY) {
        // Found a path, store it in paths array
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                paths[count][i][j] = map[i][j];
            }
        }
        count++;
        return 1;
    }

    map[x][y] = 1; // Mark current position as visited

    // Explore all 4 directions
    int foundPath = 0;
    if (left(maze, map, x, y)) {
        foundPath |= findWay(maze, map, r, c, x, y - 1, targetX, targetY); // Move left
    }
    if (right(maze, map, x, y)) {
        foundPath |= findWay(maze, map, r, c, x, y + 1, targetX, targetY); // Move right
    }
    if (up(maze, map, x, y)) {
        foundPath |= findWay(maze, map, r, c, x - 1, y, targetX, targetY); // Move up
    }
    if (down(maze, map, x, y)) {
        foundPath |= findWay(maze, map, r, c, x + 1, y, targetX, targetY); // Move down
    }

    map[x][y] = 0; // Unmark current position before backtracking
    return foundPath;
}

int main(void) {
    int r, c;
    scanf_s("%d %d", &r, &c);

    // Input maze and setup boundaries
    for (int i = 0; i < r + 2; i++) {
        for (int j = 0; j < c + 2; j++) {
            if (i == 0 || i == r + 1 || j == 0 || j == c + 1) // Boundary cells
                maze[i][j] = 0;
            else
                scanf_s("%d", &maze[i][j]); // Read maze values
        }
    }

    int map[100][100] = { 0 }; // Initialize map to track visited cells
    int startX = 1, startY = 1; // Starting position
    int targetX = r, targetY = c; // Target position (bottom-right corner)
    findWay(maze, map, r, c, startX, startY, targetX, targetY);
    if (count==0) {
        printf("没有找到路径\n");
    }
    else {
        // Print all paths found
        for (int i = 0; i < count; i++) {
            printf("%d\n", i + 1);
            for (int j = 1; j <= r; j++) {
                for (int k = 1; k <= c; k++) {
                    printf("%d", paths[i][j][k]);
                    if (k != c) {
                        putchar(' ');
                    }
                }
                putchar('\n');
            }
        }
    }

    return 0;
}
