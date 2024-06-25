#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Location Location;
typedef struct Placement Placement;

struct Placement
{
    int id;
    long long int previousFoodLevel;
    long long int takenFood;
};

struct Location
{
    char name[19 + 1];
    int *arr;
    int size, cap;
    long long int foodTaken;
    Placement *placements;
    int numPlacements;
};

Location *createLocationList()
{
    Location *ret;
    ret = (Location *)malloc(sizeof(Location));
    // Intialize the list of locations
    ret->size = 0;
    ret->arr = (int *)malloc(sizeof(int) * ret->size);
}

void addPlacement(struct Location *loc, int id, long long int food)
{
    loc->placements = realloc(loc->placements, (loc->size + 1) * sizeof(struct Placement));
    loc->placements[loc->size].id = id;
    loc->placements[loc->size].previousFoodLevel = food;
    loc->placements[loc->size].takenFood = 0;
    loc->size++;
}

void initializeLocation(struct Location *loc)
{
    loc->numPlacements = 0;
    loc->foodTaken = 0;
    loc->placements = NULL;
}

void freeLocations(struct Location *locations, int numLocations)
{
    for (int i = 0; i < numLocations; ++i)
    {
        free(locations[i].placements);
    }
    free(locations);
}

int main()
{
    Location *myLocation = createLocationList();
    // Name of location
    char Location[19 + 1];

    // Initializing variables
    int numLocations = 0;
    int id;
    long long int food;

    // END of program condition
    char end[] = "END";
    int result = strcmp(Location, end);
    scanf("%s%d%lld", Location, &id, &food);
    while (!(strcmp(Location, "END") == 0) && !(id == -1) && !(food == -1))
    {

        int foundLocation = -1;

        for (int i = 0; i < numLocations; ++i)
        {
            if (strcmp(myLocation[i].name, Location) == 0)
            {
                foundLocation = i;

                // Search for the placement in the location
                int foundPlacement = -1;
                for (int j = 0; j < myLocation[i].size; ++j)
                {
                    if (myLocation[i].placements[j].id == id)
                    {
                        foundPlacement = j;
                        long long int foodTaken = 0;
                        if (food > myLocation[i].placements[j].previousFoodLevel)
                        {
                            foodTaken = 0;
                            printf("%lld\n", foodTaken);
                        }
                        // Calculate and print food taken

                        if (food < myLocation[i].placements[j].previousFoodLevel)
                        {
                            foodTaken += labs(food - myLocation[i].placements[j].previousFoodLevel);
                            printf("%lld\n", foodTaken);
                            
                        }
                        // Update placement information
                        myLocation[i].placements[j].previousFoodLevel = food;

                        if (foodTaken < myLocation[i].placements[j].takenFood || myLocation[i].placements[j].takenFood == 0)
                        {
                            myLocation[i].placements[j].takenFood = foodTaken;
                        }

                        // Update location food taken
                        myLocation[i].foodTaken += foodTaken;
                        break;
                    }
                }

                // If placement is not found, it's a new placement
                if (foundPlacement == -1)
                {
                    printf("New placement.\n");

                    // Add new placement to the location
                    addPlacement(&myLocation[i], id, food);

                    // Update location food taken
                }

                break;
            }
        }

        // If location is not found, it's a new location
        if (foundLocation == -1)
        {
            printf("New placement.\n");

            // Create a new location
            myLocation = realloc(myLocation, (numLocations + 1) * sizeof(struct Location));
            initializeLocation(&myLocation[numLocations]);
            strcpy(myLocation[numLocations].name, Location);

            // Add new placement to the location
            addPlacement(&myLocation[numLocations], id, food);

            // Update location food taken
            numLocations++;
        }
        scanf("%s%d%lld", Location, &id, &food);
    }

    // Print the food taken from each location
    for (int i = 0; i < numLocations; ++i)
    {
        printf("%s %lld\n", myLocation[i].name, myLocation[i].foodTaken);
    }

    // Free allocated memory
    freeLocations(myLocation, numLocations);

    return 0;
}
