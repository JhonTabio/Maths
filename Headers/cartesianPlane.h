#include <stdlib.h>
#include <stdio.h>

typedef struct Plane
{
	int ORIGIN_X, ORIGIN_Y;
	int width, height, focus_x, focus_y, spacing;
	char **plane;
} Plane;

Plane *createCartesianPlane(int width, int height, int focus_x, int focus_y, int spacing);
void destroyCartesianPlane(Plane *plane);
void printCartesianPlane(Plane *plane, int lineFlag);
int resizeCartesianPlane(Plane *plane, int width, int height);
void clearCartesianPlane(Plane *plane);
char **createPlane(int width, int height);
void destroyPlane(char **plane, int height);
char **resizePlane(char **plane, int oldWidth, int oldHeight, int width, int height);
void clearPlane(char **plane, int width, int height);
void printPlane(char **plane, int width, int height, int lineFlag, int focus_x, int focus_y);

//Plane *createCartesianPlane(int width, int height, int focus_x, int focus_y, int spacing);

Plane *createCartesianPlane(int width, int height, int focus_x, int focus_y, int spacing)
{
	Plane *ret = (Plane *) malloc(sizeof(Plane));

	if(ret == NULL)
		return NULL;

	ret->ORIGIN_X = 0;				// Origin x component of the plane (Usually should be left at 0)
	ret->ORIGIN_Y = 0;				// Origin y component of the plane (Usually should be left at 0)
	ret->width = width;				// Width of the window
	ret->height = height;				// Height of the window
	ret->focus_x = focus_x;				// X component of the focus point
	ret->focus_y = focus_y;				// Y component of the focus point
	ret->spacing = spacing;				// The space between each index
	ret->plane = createPlane(width, height);	// The plane made of arrays

	if(ret->plane == NULL)
		return NULL;

	clearPlane(ret->plane, width, height);

	return ret;	
}

void destroyCartesianPlane(Plane *plane)
{
	destroyPlane(plane->plane, plane->height);
	free(plane);
}

void printCartesianPlane(Plane *plane, int lineFlag)
{
	printPlane(plane->plane, plane->width, plane->height, lineFlag, plane->focus_x, plane->focus_y);
}

int resizeCartesianPlane(Plane *plane, int width, int height)
{
	char **ret = resizePlane(plane->plane, plane->width, plane->height, width, height);

  if(ret == NULL) return 0;

  plane->plane = ret;
	plane->width = width;
	plane->height = height;

	return 1;
}

void clearCartesianPlane(Plane *plane)
{
	clearPlane(plane->plane, plane->width, plane->height);
}

char **createPlane(int width, int height)
{
	// Add 1 to height to account for '0' in the vertical axis
	char **ret = (char **) malloc(height * sizeof(char *) + 1);

	if(ret == NULL)
		return NULL;

	for(int i = 0; i < height; i++)
	{
		// Add 2 to the width to account for '0' in the horizontal axis
		// and account for the null terminator
		ret[i] = (char *) malloc(width * sizeof(char) + 2);

		if(ret[i] == NULL)
			return NULL;
	}

	return ret;
}

void destroyPlane(char **plane, int height)
{
	for(int i = 0; i < height; i++)
		free(plane[i]);
	free(plane);
}

char **resizePlane(char **plane, int oldWidth, int oldHeight, int width, int height)
{
	int i;
	for(i = 0; i < oldHeight; i++)
	{
		char *temp = (char *) realloc(plane[i], width * sizeof(char) + 2);

		if(temp == NULL)
			return NULL;
		
		temp[width + 2] = '\0';
		plane[i] = temp;
	}

	char **temp = (char **) realloc(plane, height * sizeof(char *) + 1);

	if(temp == NULL)
		return NULL;

	plane = temp;

	for(i = oldHeight; i < height; i++)
	{
		plane[i] = (char *) malloc(width * sizeof(char) + 2);

		if(plane[i] == NULL)
			return NULL;

		plane[i][width + 2] = '\0';
	}

	return plane;
}

void clearPlane(char **plane, int width, int height)
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
			plane[i][j] = 'X';
		plane[i][width - 2] = '\0';
	}
}

void printPlane(char **plane, int width, int height, int lineFlag, int focus_x, int focus_y)
{
	int midWidth = (((width - 1) / 2) + 0.5) - focus_x;
	int midHeight = (((height - 1) / 2) + 0.5) - focus_y;

	for(int i = 0; i < height - 1; i++)
	{
		for(int j = 0; j < width - 1; j++)
		{
			if(i == midHeight && lineFlag)
			{
				printf("---");
				continue;
			}
			
			if(j == midWidth && lineFlag)
			{
				printf(" | ");
				continue;
			}

			printf(" %c ", plane[i][j]);
		}

		printf("\n");
	}
}
