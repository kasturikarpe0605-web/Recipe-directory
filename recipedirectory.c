#include <stdio.h>
#include <string.h>

#define MAX_RECIPES 100
#define MAX_INGREDIENTS 100

// Recipe structure
typedef struct {
    char name[50];
    int calories;
    int timeRequired; // in minutes
    char ingredients[200];
    char tasteType[10]; // "spicy" or "sweet"
} Recipe;

// Function to input recipes
void inputRecipes(Recipe recipes[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Recipe %d:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]", recipes[i].name);
        printf("Calories: ");
        scanf("%d", &recipes[i].calories);
        printf("Time required (in minutes): ");
        scanf("%d", &recipes[i].timeRequired);
        printf("Ingredients (comma separated): ");
        scanf(" %[^\n]", recipes[i].ingredients);
        printf("Taste type (spicy/sweet): ");
        scanf(" %[^\n]", recipes[i].tasteType);
    }
}

// Bubble Sort by calories
void sortRecipesByCalories(Recipe recipes[], int n) {
    Recipe temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (recipes[j].calories > recipes[j + 1].calories) {
                temp = recipes[j];
                recipes[j] = recipes[j + 1];
                recipes[j + 1] = temp;
            }
        }
    }
}

// Function to display recipes
void displayRecipe(Recipe r) {
    printf("\nName: %s\nCalories: %d\nTime: %d minutes\nIngredients: %s\nTaste: %s\n",
           r.name, r.calories, r.timeRequired, r.ingredients, r.tasteType);
}

void displayAllRecipes(Recipe recipes[], int n) {
    for (int i = 0; i < n; i++) {
        displayRecipe(recipes[i]);
    }
}

// Search by calorie range
void searchByCalories(Recipe recipes[], int n, int min, int max) {
    printf("\nRecipes with calories between %d and %d:\n", min, max);
    for (int i = 0; i < n; i++) {
        if (recipes[i].calories >= min && recipes[i].calories <= max)
            displayRecipe(recipes[i]);
    }
}

// Search by preparation time
void searchByTime(Recipe recipes[], int n, int maxTime) {
    printf("\nRecipes that can be made in %d minutes or less:\n", maxTime);
    for (int i = 0; i < n; i++) {
        if (recipes[i].timeRequired <= maxTime)
            displayRecipe(recipes[i]);
    }
}

// Search by ingredient
void searchByIngredient(Recipe recipes[], int n, char ingredient[]) {
    printf("\nRecipes containing '%s':\n", ingredient);
    for (int i = 0; i < n; i++) {
        if (strstr(recipes[i].ingredients, ingredient))
            displayRecipe(recipes[i]);
    }
}

// Search by taste
void searchByTaste(Recipe recipes[], int n, char taste[]) {
    printf("\n%s recipes:\n", taste);
    for (int i = 0; i < n; i++) {
        if (strcasecmp(recipes[i].tasteType, taste) == 0)
            displayRecipe(recipes[i]);
    }
}

int main() {
    Recipe recipes[MAX_RECIPES];
    int n, choice;

    printf("Enter number of recipes: ");
    scanf("%d", &n);
    inputRecipes(recipes, n);

    // Sort recipes using bubble sort by calories
    sortRecipesByCalories(recipes, n);
    printf("\nRecipes sorted by calories (ascending):\n");
    displayAllRecipes(recipes, n);

    do {
        printf("\n====== Recipe Search Menu ======\n");
        printf("1. Search by Calories\n");
        printf("2. Search by Preparation Time\n");
        printf("3. Search by Ingredient\n");
        printf("4. Search by Taste Type (Spicy/Sweet)\n");
        printf("5. Display All Recipes\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int min, max;
                printf("Enter min and max calories: ");
                scanf("%d %d", &min, &max);
                searchByCalories(recipes, n, min, max);
                break;
            }
            case 2: {
                int maxTime;
                printf("Enter maximum time (in minutes): ");
                scanf("%d", &maxTime);
                searchByTime(recipes, n, maxTime);
                break;
            }
            case 3: {
                char ingredient[50];
                printf("Enter ingredient to search for: ");
                scanf(" %[^\n]", ingredient);
                searchByIngredient(recipes, n, ingredient);
                break;
            }
            case 4: {
                char taste[10];
                printf("Enter taste type (spicy/sweet): ");
                scanf(" %[^\n]", taste);
                searchByTaste(recipes, n, taste);
                break;
            }
            case 5:
                displayAllRecipes(recipes, n);
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
