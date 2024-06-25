
// Solution to Assignment 1 with more general void pointer array list

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 19

typedef struct ArrayList ArrayList;
typedef struct World World;
typedef struct Location Location;
typedef struct Place Place;
typedef long long int big_int;

struct ArrayList 
{
  int size, cap; // Standard Array List values
  void ** array; // void * so that the array can store any type of pointer
};

struct World 
{
  ArrayList * location_list; // The list of locations
};

struct Location
{
  ArrayList * place_list; // The list of places
  char * name; // The name of the location
  big_int answer; // The total amount taken
};

struct Place
{
  big_int level; // The current food level at the place
  int ID; // The ID of the place
};

// Function to create an ArrayList in the Heap
ArrayList * createList()
{
  // Instanitate and allocate
  ArrayList * list = (ArrayList *) malloc(sizeof(ArrayList));

  // Initialize
  list->size = 0;
  list->cap = 2;
  list->array = (void **) calloc(list->cap, sizeof(void *));

  // Return
  return list;
}

// Function to add an element to the end of the list
void append(ArrayList * list, void * data)
{
  // Check if the list is full
  if (list->size == list->cap)
  {
    // Double the capacity
    list->cap *= 2;
    list->array = (void **) realloc(list->array, list->cap * sizeof(void *));
  }

  // Add the element
  list->array[list->size++] = data;
}

// Function to search for a value in an array list
void * find(ArrayList * list, int comparefunc(void *, void *), void * target)
{
  // Loop through all values in the list
  for (int i = 0; i < list->size; i++)
  {
    // Compare the values using the compare function
    if (comparefunc(list->array[i], target) == 0)
    {
      // Equal to the target so return
      return list->array[i];
    }
  }

  // The value was not found so return a "special" pointer
  return NULL;
}

// Function to free the list
void freeList(ArrayList * list, void freefunc(void *))
{
  // Free the elements
  for (int i = 0; i < list->size; i++)
  {
    freefunc(list->array[i]);
  }
    
  // Free the array
  free(list->array);
}

// Function to create the world
World * createWorld()
{
  // Instantiate and allocate
  World * world = (World *) malloc(sizeof(World));

  // Create the list of locations
  world->location_list = createList();

  // Return the world
  return world;
}

// Function to create a location
Location * createLocation(char * name)
{
  // Instantiate and allocate
  Location * location = (Location *) malloc(sizeof(Location));

  // Initialize the location
  location->name = strdup(name);
  location->place_list = createList();
  location->answer = 0;

  // Return the location
  return location;
}

// Function to create a place
Place * createPlace(int ID)
{
  // Instantiate and allocate
  Place * place = (Place *) malloc(sizeof(Place));

  // Initialize
  place->ID = ID;
  place->level = -1;
  
  // Return the place
  return place;
}

// Function to free a location
void freeLocation(void * location_void)
{
  // Cast the location to a location pointer
  Location * location = (Location *) location_void;
  
  // Every place needs to only be free'd (nothing more)
  freeList(location->place_list, free);

  // Clean up the name from strdup
  free(location->name); 

  // Clean up the location
  free(location);
}

// Function to free the world
void freeWorld(World * world)
{
  // Free the locations
  freeList(world->location_list, freeLocation);
  free(world);
}

// Function to compare 2 locations
int compareLocations(void * location1_void, void * location2_void)
{
  // Cast the locations to location pointers
  Location * location1 = (Location *) location1_void;
  Location * location2 = (Location *) location2_void;

  // Compare the names of the locations
  return strcmp(location1->name, location2->name);
}

// Function to compare 2 places
int comparePlaces(void * place1_void, void * place2_void)
{
  // Cast the places to place pointers
  Place * place1 = (Place *) place1_void;
  Place * place2 = (Place *) place2_void;
  
  // Check if the IDs are equal
  if (place1->ID == place2->ID)
  {
    return 0;
  }

  // Return based on the greater ID
  return (place1->ID > place2->ID) ? 1 : -1;
}

// The main function
int main(void) 
{
  // Create the world
  World * world = createWorld();

  char name[MAX_LENGTH + 1];
  int ID;
  int level;
  
  // Loop until a negative food level is given
  do 
  {
    // Read in the information for the update
    scanf("%s%d%d", name, &ID, &level);
    if (level >= 0)
    {
      // Make a location for searching
      Location tmp;
      tmp.name = name;

      // Find the pointer to the location
      Location * location = find(world->location_list, compareLocations, &tmp);

      // If the location was not found
      if (location == NULL)
      {
        // Create the location
        location = createLocation(name);

        // Insert
        append(world->location_list, location);
      }

      // Find the place in the location
      Place tmp2;
      tmp2.ID = ID;

      // Find the pointer to the place
      Place * place = find(location->place_list, comparePlaces, &tmp2);

      // If the place was not found
      if (place == NULL)
      {
        // Create the place
        place = createPlace(ID); 

        // Insert
        append(location->place_list, place);
      }

      // Check what should be printed
      if (place->level == -1)
      {
        // The place is new so print the answer
        printf("New placement.\n");
      }
      else
      {
        // Determine if the raccoons took anything
        if (place->level > level)
        {
          // The raccoons took something
          printf("%lld\n", place->level - level);

          // Update the total taken for the location
          location->answer += place->level - level;
        }
        else
        {
          // Print nothing has been taken
          printf("0\n");
        }
      }

      // Update the level
      place->level = level;
    }
  } while (level != -1);

  // Print the totals for each location
  for (int i = 0; i < world->location_list->size; i++)
  {
    // Cast the location to a location pointer
    Location * location = (Location *) world->location_list->array[i];
    
    // Print the name and the total
    printf("%s %lld\n", location->name, location->answer);
  }

  // Delete the world
  freeWorld(world);
  
  // Exit the program
  return 0;
}