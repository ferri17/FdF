#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

// Function to check if a point is inside the clipping window
int inside(Point p, int WIN_W, int WIN_H) {
    return (p.x >= 0 && p.x < WIN_W && p.y >= 0 && p.y < WIN_H);
}

// Function to find the intersection point of a line with an edge of the clipping window
Point intersect(Point p1, Point p2, int edge, int WIN_W, int WIN_H) {
    Point intersectPoint;

    if (edge == 0) {
        // Top edge (y = 0)
        intersectPoint.y = 0;
        intersectPoint.x = p1.x + (p2.x - p1.x) * (0 - p1.y) / (p2.y - p1.y);
    } else if (edge == 1) {
        // Right edge (x = WIN_W - 1)
        intersectPoint.x = WIN_W - 1;
        intersectPoint.y = p1.y + (p2.y - p1.y) * (WIN_W - 1 - p1.x) / (p2.x - p1.x);
    } else if (edge == 2) {
        // Bottom edge (y = WIN_H - 1)
        intersectPoint.y = WIN_H - 1;
        intersectPoint.x = p1.x + (p2.x - p1.x) * (WIN_H - 1 - p1.y) / (p2.y - p1.y);
    } else if (edge == 3) {
        // Left edge (x = 0)
        intersectPoint.x = 0;
        intersectPoint.y = p1.y + (p2.y - p1.y) * (0 - p1.x) / (p2.x - p1.x);
    }

    return intersectPoint;
}

// Function to clip a line against a rectangular frame
void clipLine(Point p1, Point p2, int WIN_W, int WIN_H) {
    Point clippedPoints[4];
    int clippedCount = 0;

    Point windowEdges[4] = {
        {0, 0},               // Top-left corner
        {WIN_W - 1, 0},       // Top-right corner
        {WIN_W - 1, WIN_H - 1}, // Bottom-right corner
        {0, WIN_H - 1}        // Bottom-left corner
    };

    for (int edge = 0; edge < 4; edge++) {
        Point clipStart = (clippedCount > 0) ? clippedPoints[clippedCount - 1] : p1;
        Point clipEnd = p2;
        Point edgeStart = windowEdges[edge];
        Point edgeEnd = windowEdges[(edge + 1) % 4];

        // Check if the clipEnd point is inside the window
        if (inside(clipEnd, WIN_W, WIN_H)) {
            clippedPoints[clippedCount++] = clipEnd;
        } else {
            // Check if the clipStart point is inside the window
            if (inside(clipStart, WIN_W, WIN_H)) {
                Point intersectPoint = intersect(clipStart, clipEnd, edge, WIN_W, WIN_H);
                clippedPoints[clippedCount++] = intersectPoint;
            }
        }

        // Check if the edgeEnd point is inside the window
        if (!inside(edgeEnd, WIN_W, WIN_H)) {
            // Check if the edgeStart point is inside the window
            if (inside(clipStart, WIN_W, WIN_H)) {
                Point intersectPoint = intersect(clipStart, clipEnd, edge, WIN_W, WIN_H);
                clippedPoints[clippedCount++] = intersectPoint;
            }
        }
    }

    // Draw the clipped line using the points in clippedPoints array
    for (int i = 1; i < clippedCount; i++) {
        printf("Line: (%d, %d) -> (%d, %d)\n", clippedPoints[i - 1].x, clippedPoints[i - 1].y, clippedPoints[i].x, clippedPoints[i].y);
    }
}

int main() {
    int WIN_W = 10;
    int WIN_H = 10;
    Point p1 = {-10, 0};
    Point p2 = {-40, 0};

    clipLine(p1, p2, WIN_W, WIN_H);

    return 0;
}
