#include <stdio.h>
#include <stdlib.h>

#define MAX_USERS 50
#define MAX_ITEMS 20

typedef struct {
    int userId;
    int items[MAX_ITEMS];   // store item ids like 1,2,3...
    int itemCount;
} User;

int itemCatalog[MAX_ITEMS+1]; // 1-based: itemCatalog[i]=1 if exists
User users[MAX_USERS];
int userCount = 0;
int maxItemId = 5; // default catalog size (items 1..5)

// ----- Helper: check if user bought an item -----
int hasBought(const User *u, int itemId) {
    for (int i = 0; i < u->itemCount; ++i)
        if (u->items[i] == itemId) return 1;
    return 0;
}

// ----- Similarity: co-occurrence count between two items -----
int similarity(int itemA, int itemB) {
    int score = 0;
    for (int i = 0; i < userCount; ++i) {
        if (hasBought(&users[i], itemA) && hasBought(&users[i], itemB))
            score++;
    }
    return score;
}

// ----- Recommendation for a user (top scored items) -----
void recommendForUser(const User *u) {
    printf("\nRecommendations for User %d:\n", u->userId);

    int recItems[MAX_ITEMS];
    int recScore[MAX_ITEMS];
    int recCount = 0;

    // For each item in catalog (1..maxItemId)
    for (int item = 1; item <= maxItemId; ++item) {
        if (!itemCatalog[item]) continue;             // skip non-existing
        if (hasBought(u, item)) continue;            // skip already bought

        int score = 0;
        // score = sum of co-occurrence with user's purchased items
        for (int j = 0; j < u->itemCount; ++j) {
            score += similarity(item, u->items[j]);
        }

        if (score > 0) {
            recItems[recCount] = item;
            recScore[recCount] = score;
            recCount++;
        }
    }

    // If nothing found
    if (recCount == 0) {
        printf("No recommendations found!\n");
        return;
    }

    // Sort descending by score (simple selection sort)
    for (int i = 0; i < recCount - 1; ++i) {
        int best = i;
        for (int j = i + 1; j < recCount; ++j)
            if (recScore[j] > recScore[best]) best = j;
        // swap
        int tS = recScore[i]; recScore[i] = recScore[best]; recScore[best] = tS;
        int tI = recItems[i]; recItems[i] = recItems[best]; recItems[best] = tI;
    }

    // Print top recommendations
    for (int i = 0; i < recCount; ++i)
        printf("Item %d (score %d)\n", recItems[i], recScore[i]);
}

// ----- Add user with interactive item choices -----
void inputUser() {
    if (userCount >= MAX_USERS) {
        printf("User storage full.\n");
        return;
    }

    int id, n, item;
    printf("Enter User ID (integer): ");
    if (scanf("%d", &id) != 1) { while(getchar() != '\n'); printf("Invalid.\n"); return; }

    users[userCount].userId = id;

    printf("How many items did User %d purchase? (0-%d): ", id, MAX_ITEMS);
    if (scanf("%d", &n) != 1 || n < 0 || n > MAX_ITEMS) { while(getchar() != '\n'); printf("Invalid count.\n"); return; }

    users[userCount].itemCount = 0;
    for (int i = 0; i < n; ++i) {
        printf("Item %d id (1-%d): ", i+1, maxItemId);
        if (scanf("%d", &item) != 1) { while(getchar() != '\n'); printf("Invalid item.\n"); return; }
        if (item < 1 || item > maxItemId || !itemCatalog[item]) {
            printf("Item %d is not in catalog. Try again.\n", item);
            --i; // repeat this index
            continue;
        }
        users[userCount].items[users[userCount].itemCount++] = item;
    }
    userCount++;
    printf("User added successfully!\n");
}

// ----- Initialize a small demo dataset (optional) -----
void seed_demo() {
    // Define which items exist (1..maxItemId)
    for (int i = 1; i <= maxItemId; ++i) itemCatalog[i] = 1;

    // Example: User1: 1,2 ; User2: 1,2,3
    users[0].userId = 1; users[0].items[0]=1; users[0].items[1]=2; users[0].itemCount=2;
    users[1].userId = 2; users[1].items[0]=1; users[1].items[1]=2; users[1].items[2]=3; users[1].itemCount=3;
    userCount = 2;
}

// ----- Show catalog -----
void showCatalog() {
    printf("Catalog items available: ");
    for (int i = 1; i <= maxItemId; ++i)
        if (itemCatalog[i]) printf("%d ", i);
    printf("\n");
}

int main() {
    int choice;
    // you can change maxItemId if you want more items
    maxItemId = 5;
    for (int i = 0; i <= MAX_ITEMS; ++i) itemCatalog[i] = 0;
    for (int i = 1; i <= maxItemId; ++i) itemCatalog[i] = 1;

    // preload demo users so you can test fast
    seed_demo();

    while (1) {
        printf("\n==== MENU ====\n");
        printf("1. Show catalog\n");
        printf("2. Add user purchases\n");
        printf("3. Recommend for a user\n");
        printf("4. List users\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) { while(getchar()!='\n'); printf("Invalid.\n"); continue; }

        if (choice == 1) {
            showCatalog();
        } else if (choice == 2) {
            inputUser();
        } else if (choice == 3) {
            int uid;
            printf("Enter User ID to recommend for: ");
            if (scanf("%d", &uid) != 1) { while(getchar()!='\n'); printf("Invalid.\n"); continue; }
            int found = 0;
            for (int i = 0; i < userCount; ++i) {
                if (users[i].userId == uid) {
                    recommendForUser(&users[i]);
                    found = 1;
                    break;
                }
            }
            if (!found) printf("User not found!\n");
        } else if (choice == 4) {
            if (userCount == 0) printf("No users.\n");
            for (int i = 0; i < userCount; ++i) {
                printf("User %d: ", users[i].userId);
                for (int j = 0; j < users[i].itemCount; ++j) printf("%d ", users[i].items[j]);
                printf("\n");
            }
        } else if (choice == 5) {
            printf("Bye!\n"); break;
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
