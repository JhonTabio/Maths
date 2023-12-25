#include <stdio.h>

#include "../Headers/cartesianPlane.h"

int main()
{
	int width, height, focus_x, focus_y, spacing, showLines;

	printf("Enter the size of the graph (width, height): ");
	scanf("%d %d", &width, &height);

	printf("Enter the focus points of the viewing grapg (x, y): ");
	scanf("%d %d", &focus_x, &focus_y);

	printf("Space between each interval: ");
	scanf("%d", &spacing);

	Plane *plane = createCartesianPlane(width, height, focus_x, focus_y, spacing);

	printf("Display lines (0: FALSE / 1: TRUE): ");
	scanf("%d", &showLines);

	char option;
	//scanf("%c", &option); // Clear buffer

	while(1)
	{
		printCartesianPlane(plane, showLines);

		for(int i = 0; i < width; i++)
			printf("+++");
		printf("\n");

		printf("\t\tSelect an option below:\n");
		printf("\t[R] - Resize\t[F] - Focus\t[S] - Spacing\t[T] - Toggle Lines\t[C] - Clear Plane\t[X] - Exit");
		printf("\n");

		scanf(" %c", &option);

		switch(option)
		{
			case 'x':
			case 'X':
				destroyCartesianPlane(plane);
				return 0;
			case 'r':
			case 'R':
				printf("Resize plane to (width, height): ");
				scanf("%d %d", &width, &height);
				int res = resizeCartesianPlane(plane, width, height);

				if(!res)
				{
				  printf("There was an error resizing\n");
					destroyCartesianPlane(plane);
					return 1;
				}

				clearCartesianPlane(plane);
				// Add the objs back
				break;
			case 'f':
			case 'F':
				printf("Shift focus (x, y): ");
				scanf("%d %d", &plane->focus_x, &plane->focus_y);
				break;
			case 's':
			case 'S':
				printf("Spacing intervals: ");
				scanf("%d", &plane->spacing);
				break;
			case 't':
			case 'T':
        showLines = !showLines;
				//printf("Toggle lines: ");
				//scanf("%d", &showLines);
				break;
			case 'c':
			case 'C':
				clearCartesianPlane(plane);
				break;
		}
	}
	
	return 0;
}
