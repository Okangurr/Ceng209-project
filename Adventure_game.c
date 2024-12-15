#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INVENTORY 5
#define MAX_DESCRIPTION 256
#define MAX_ROOMS 10

typedef struct Item {
    char name[MAX_DESCRIPTION];
    int damage;
    struct Item* next;
} Item;

typedef struct Creature {
    char name[MAX_DESCRIPTION];
    int health;
    int strength;
} Creature;

typedef struct Room {
    char description[MAX_DESCRIPTION];
    struct Room *up;
    struct Room *down;
    struct Room *left;
    struct Room *right;
    Item* items;
    Creature* creature;
    int trap;
    int is_exit;
    int has_key;
} Room;

typedef struct {
    char name[MAX_DESCRIPTION];
    int health;
    int strength;
    Room* current_room;
    int has_exit_key;
    Item* inventory;
    int inventory_size;
} Player;

Room* rooms[MAX_ROOMS];
Player player;


void initialize_game(Player* player, Room* rooms[]) {
    // Oda 0 - Starting Room
    player->health = 100;   // Oyuncunun başlangıç canı
    player->strength = 10;  // Oyuncunun başlangıç gücü
    //player->inventory = NULL;
  //  player->inventory_size = 0;
    player->has_exit_key = 0;

    rooms[0] = malloc(sizeof(Room));
    strcpy(rooms[0]->description, "A dark, damp dungeon room with mossy walls.");
    rooms[0]->items = NULL;
    rooms[0]->creature = NULL;
    rooms[0]->trap = 0;
    rooms[0]->is_exit = 0;
    rooms[0]->has_key = 0;

    // Add a Dagger item to Room 0
    Item* dagger = malloc(sizeof(Item));
    strcpy(dagger->name, "Dagger");
    dagger->damage = 5; // Dagger has 5 damage
    dagger->next = NULL;
    rooms[0]->items = dagger;

    // Oda 1 - Room with items and creature
    rooms[1] = malloc(sizeof(Room));
    strcpy(rooms[1]->description, "A bright room with a golden chest in the corner.");
    rooms[1]->items = NULL;
    rooms[1]->creature = malloc(sizeof(Creature));
    strcpy(rooms[1]->creature->name, "Goblin");
    rooms[1]->creature->health = 25;
    rooms[1]->creature->strength = 10;
    rooms[1]->trap = 0;
    rooms[1]->is_exit = 0;
    rooms[1]->has_key = 0;

    // Add items to Room 1
    Item* sword = malloc(sizeof(Item));
    strcpy(sword->name, "Sword");
    sword->damage = 10; // Sword has 10 damage
    sword->next = NULL;
    rooms[1]->items = sword;

    // Oda 2 - Room with shield, creature, and key
    rooms[2] = malloc(sizeof(Room));
    strcpy(rooms[2]->description, "A cold room with icy walls and a slippery floor.");
    rooms[2]->items = NULL;
    rooms[2]->creature = malloc(sizeof(Creature));
    strcpy(rooms[2]->creature->name, "Ice Wraith");
    rooms[2]->creature->health = 30;
    rooms[2]->creature->strength = 8;
    rooms[2]->trap = 0;
    rooms[2]->is_exit = 0;
    rooms[2]->has_key = 1; // Key for the exit room is here

    // Add an Axe item to Room 2
    Item* axe = malloc(sizeof(Item));
    strcpy(axe->name, "Axe");
    axe->damage = 20; // Axe has 20 damage
    axe->next = NULL;
    rooms[2]->items = axe;

    // Add Exit Key item to Room 2
    Item* exit_key = malloc(sizeof(Item));
    strcpy(exit_key->name, "Key");
    exit_key->next = rooms[2]->items; // Key added before the Axe item
    rooms[2]->items = exit_key;

    // Oda 3 - Room with a trap
    rooms[3] = malloc(sizeof(Room));
    strcpy(rooms[3]->description, "A room with spikes on the floor, beware of traps!");
    rooms[3]->items = NULL;
    rooms[3]->creature = NULL;
    rooms[3]->trap = 1; // Trap present in this room
    rooms[3]->is_exit = 0;
    rooms[3]->has_key = 0;

    // Oda 4 - Boss room
    rooms[4] = malloc(sizeof(Room));
    strcpy(rooms[4]->description, "A massive chamber with a mighty dragon guarding the exit.");
    rooms[4]->items = NULL;
    rooms[4]->creature = malloc(sizeof(Creature));
    strcpy(rooms[4]->creature->name, "Dragon");
    rooms[4]->creature->health = 50;
    rooms[4]->creature->strength = 15;
    rooms[4]->trap = 0;
    rooms[4]->is_exit = 0;
    rooms[4]->has_key = 0;

    // Oda 5 - Exit Room
    rooms[5] = malloc(sizeof(Room));
    strcpy(rooms[5]->description, "The exit room, but the door is locked.");
    rooms[5]->items = NULL;
    rooms[5]->creature = NULL;
    rooms[5]->trap = 0;
    rooms[5]->is_exit = 1; // This is the exit room
    rooms[5]->has_key = 0;

        // Player starts in Room 0
    player->current_room = rooms[0];
   // player->has_exit_key = 0; // No key at the start

    // Room connections
    // Oda 0 - Baþlangýç Odasý
    rooms[0]->up = rooms[1];
    rooms[0]->down = NULL;
    rooms[0]->left = NULL;
    rooms[0]->right = rooms[2];

    // Oda 1 - Oda 0 ile baðlantý
    rooms[1]->up = NULL;
    rooms[1]->down = rooms[0];
    rooms[1]->left = NULL;
    rooms[1]->right = NULL;

    // Oda 2 - Oda 0 ile baðlantý
    rooms[2]->up = rooms[3];
    rooms[2]->down = NULL;
    rooms[2]->left = rooms[0];
    rooms[2]->right = NULL;

    // Oda 3 - Oda 2 ile baðlantý
    rooms[3]->up = rooms[4];
    rooms[3]->down = rooms[2];
    rooms[3]->left = NULL;
    rooms[3]->right = NULL;

    // Oda 4 - Oda 3 ile baðlantý
    rooms[4]->up = rooms[5];
    rooms[4]->down = rooms[3];
    rooms[4]->left = NULL;
    rooms[4]->right = NULL;

    // Oda 5 - Çýkýþ Odasý
    rooms[5]->up = NULL;
    rooms[5]->down = rooms[4];
    rooms[5]->left = NULL;
    rooms[5]->right = NULL;
}



void show_health(Player* player) {
    printf("Your current health: %d\n", player->health);
}

void cleanup_game(Room* rooms[]) {
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (rooms[i]) {
            free(rooms[i]->creature);
            Item* item = rooms[i]->items;
            while (item) {
                Item* temp = item;
                item = item->next;
                free(temp);
            }
            free(rooms[i]);
        }
    }
}

void save_game(const char* filepath) {
    FILE* file = fopen(filepath, "w");
    if (!file) {
        printf("Failed to save the game. Could not open file: %s\n", filepath);
        return;
    }

    // Save player information
    fprintf(file, "Player\n");
    fprintf(file, "Name: %s\n", player.name);
    fprintf(file, "Health: %d\n", player.health);
    fprintf(file, "Strength: %d\n", player.strength);
    fprintf(file, "HasExitKey: %d\n", player.has_exit_key);
    fprintf(file, "InventorySize: %d\n", player.inventory_size);

    // Save player inventory
    fprintf(file, "Inventory\n");
    Item* item = player.inventory;
    while (item) {
        fprintf(file, "Item: %s\n", item->name);
        item = item->next;
    }

    // Save room information
    fprintf(file, "Rooms\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (rooms[i]) {
            fprintf(file, "Room %d\n", i);
            Item* room_item = rooms[i]->items;
            while (room_item) {
                fprintf(file, "RoomItem: %s\n", room_item->name);
                room_item = room_item->next;
            }
        }
    }

    // Save current room index
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (rooms[i] == player.current_room) {
            fprintf(file, "CurrentRoom: %d\n", i);
            break;
        }
    }

    fclose(file);
    printf("Game saved successfully to %s\n", filepath);
}

void load_game(const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        printf("Failed to load the game. Could not open file: %s\n", filepath);
        return;
    }

    char line[MAX_DESCRIPTION];

    // Load player information
    fgets(line, sizeof(line), file); // Skip "Player" line
    fscanf(file, "Name: %[^\n]\n", player.name);
    fscanf(file, "Health: %d\n", &player.health);
    fscanf(file, "Strength: %d\n", &player.strength);
    fscanf(file, "HasExitKey: %d\n", &player.has_exit_key);
    fscanf(file, "InventorySize: %d\n", &player.inventory_size);

    // Load player inventory
    player.inventory = NULL;
    fgets(line, sizeof(line), file); // Skip "Inventory" line
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Item: ", 6) != 0) break; // Stop when items end

        Item* new_item = malloc(sizeof(Item));
        sscanf(line, "Item: %[^\n]\n", new_item->name);
        new_item->next = player.inventory;
        player.inventory = new_item;
    }

    // Load room information
    fgets(line, sizeof(line), file); // Skip "Rooms" line
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (rooms[i]) {
            rooms[i]->items = NULL; // Clear existing items
            while (fgets(line, sizeof(line), file)) {
                if (strncmp(line, "RoomItem: ", 10) != 0) break; // Stop when items end for the room

                Item* room_item = malloc(sizeof(Item));
                sscanf(line, "RoomItem: %[^\n]\n", room_item->name);
                room_item->next = rooms[i]->items;
                rooms[i]->items = room_item;
            }
        }
    }

    // Load current room index
    int current_room_index;
    sscanf(line, "CurrentRoom: %d\n", &current_room_index);
    player.current_room = rooms[current_room_index];

    fclose(file);
    printf("Game loaded successfully from %s\n", filepath);
}




void look(Player* player) {
    Room* room = player->current_room;
    printf("%s\n", room->description);

    Item* item = room->items;
    if (item) {
        printf("Items in the room: ");
        while (item) {
            printf("%s ", item->name);
            item = item->next;
        }
        printf("\n");
    } else {
        printf("No items in the room.\n");
    }

    Creature* creature = room->creature;
    if (creature && creature->health > 0) {
        printf("A %s is here.\n", creature->name);
    }

    if (room->trap) {
        printf("Beware! There's a trap here.\n");
    }

    if (room->is_exit) {
        if (player->has_exit_key) {
            printf(" Key available! You can open the exit door and escape!\n");
            printf("Congratulations! You have successfully escaped the dungeon.");
            exit(0);
        } else {
            printf("The exit door is locked. You need a key to open it.\n");
        }
    }
}

void move(Player* player, const char* direction) {
    Room* next_room = NULL;

    if (strcmp(direction, "up") == 0) {
        next_room = player->current_room->up;
    } else if (strcmp(direction, "down") == 0) {
        next_room = player->current_room->down;
    } else if (strcmp(direction, "left") == 0) {
        next_room = player->current_room->left;
    } else if (strcmp(direction, "right") == 0) {
        next_room = player->current_room->right;
    }

    if (next_room) {

       Creature* creature = player->current_room->creature;
        if (creature && creature->health > 0) {
            printf("A %s blocks your way! You must defeat it before leaving the room.\n", creature->name);
            return; // Oyuncu savaşı kazanmadığı için hareket edemez
        }
        if (next_room->is_exit && !player->has_exit_key) {
            printf("The exit door is locked. You need a key to proceed.\n");
            return;
        }

        if (next_room->trap) {
            printf("You triggered a trap!\n");
            player->health -= 10;
            if (player->health <= 0) {
                printf("You have been defeated by the trap...\n");
                exit(0);
            }
        }

        player->current_room = next_room;
        printf("You moved %s.\n", direction);

    } else {
        printf("You can't move %s.\n", direction);
    }
}

void inventory(Player* player) {
    printf("Inventory:\n");
    if (!player->inventory) {
        printf("Your inventory is empty.\n");
        return;
    }
    Item* item = player->inventory;
    while (item) {
        printf("- %s\n", item->name);
        item = item->next;
    }
}

void pickup(Player* player, const char* item_name) {
    if (player->inventory_size >= MAX_INVENTORY) {
        printf("Your inventory is full!\n");
        return;
    }

    Item* item = player->current_room->items;
    Item* prev = NULL;

    while (item) {
        if (strcmp(item->name, item_name) == 0) {
            if (prev) {
                prev->next = item->next;
            } else {
                player->current_room->items = item->next;
            }

            item->next = player->inventory;
            player->inventory = item;
            player->inventory_size++;

            printf("You picked up the %s.\n", item_name);

            if (strcmp(item_name, "Key") == 0) {
                player->has_exit_key = 1;
            }
            return;
        }
        prev = item;
        item = item->next;
    }
    printf("No such item in the room.\n");
}

void attack(Player* player) {
    Creature* creature = player->current_room->creature;

    if (!creature || creature->health <= 0) {
        printf("There is nothing to attack here.\n");
        return;
    }

    // Envanter boşsa oyuncu yumruk kullanacak
    if (!player->inventory) {
        printf("You don't have any weapons to attack with! Using your fists instead.\n");
    }

    // Envanterden saldırı itemini seç
    printf("Select a weapon from your inventory (or press 0 to use your fists):\n");
    Item* current = player->inventory;
    int index = 1;
    while (current) {
        printf("%d. %s (Damage: %d)\n", index, current->name, current->damage);
        current = current->next;
        index++;
    }
    printf("0. Fists (Damage: 1)\n");

    printf("Enter the weapon number: ");
    int choice;
    scanf("%d", &choice);
    getchar(); // For newline

    int weapon_damage = 1; // Varsayılan yumruk hasarı
    const char* weapon_name = "Fists";

    if (choice > 0) {
        current = player->inventory;
        index = 1;
        while (current && index < choice) {
            current = current->next;
            index++;
        }

        if (current) {
            weapon_damage = current->damage;
            weapon_name = current->name;
        } else {
            printf("Invalid choice. Using your fists instead.\n");
        }
    } else {
        printf("You decided to use your fists.\n");
    }

    printf("You attack the %s with your %s (Damage: %d)!\n", creature->name, weapon_name, weapon_damage);

    // Savaş döngüsü
    while (player->health > 0 && creature->health > 0) {
        // Oyuncu saldırır
        creature->health -= weapon_damage;
        if (creature->health < 0) creature->health = 0; // Canavarın canını sıfırlama
        printf("You deal %d damage to the %s. %s's health: %d\n", weapon_damage, creature->name, creature->name, creature->health);

        if (creature->health == 0) {
            printf("You defeated the %s!\n", creature->name);
            return;
        }

        // Canavar saldırır
        printf("The %s attacks you!\n", creature->name);
        player->health -= creature->strength;
        if (player->health < 0) player->health = 0; // Oyuncunun canını sıfırlama
        printf("The %s deals %d damage to you. Your health: %d\n", creature->name, creature->strength, player->health);

        if (player->health == 0) {
            printf("You have been defeated by the %s...\n", creature->name);
            exit(0);
        }
    }
}



void execute_command(Player* player, Room* rooms[], const char* command) {
    if (strncmp(command, "move", 4) == 0) {
        char direction[MAX_DESCRIPTION];
        sscanf(command, "move %s", direction);
        move(player, direction);
    } else if (strcmp(command, "look") == 0) {
        look(player);
    } else if (strcmp(command, "inventory") == 0) {
        inventory(player);
    } else if (strncmp(command, "pickup", 6) == 0) {
        char item_name[MAX_DESCRIPTION];
        sscanf(command, "pickup %s", item_name);
        pickup(player, item_name);
    } else if (strcmp(command, "attack") == 0) {
        attack(player);
    } else if (strncmp(command, "save", 4) == 0) {
        char filepath[MAX_DESCRIPTION];
        sscanf(command, "save %s", filepath);
        save_game(filepath);
    } else if (strncmp(command, "load", 4) == 0) {
        char filepath[MAX_DESCRIPTION];
        sscanf(command, "load %s", filepath);
        load_game(filepath);
    } else if (strcmp(command, "health") == 0) {
    show_health(player);
}

     else {
        printf("Unknown command. Try again.\n");
    }
}

void trigger_trap(Player* player) {
    printf("You triggered a trap!\n");
    player->health -= 10;
    if (player->health <= 0) {
        printf("You have been defeated by the trap...\n");
        exit(0);
    }}
int main() {
    player.inventory = NULL;
    player.inventory_size = 0;
    initialize_game(&player, rooms);
    printf("Game initialized successfully!\n");

    printf("\nWelcome to the Dungeon Adventure Game!\n");
    printf("Available commands:\n");
    printf("  move <direction>  : Move to a different room (up, down, left, right).\n");
    printf("  look              : Look around the current room.\n");
    printf("  inventory         : Show your inventory.\n");
    printf("  pickup <item>     : Pick up an item in the room.\n");
    printf("  attack            : Attack the creature in the room using a weapon from your inventory.\n");
    printf("  health            : Show your health.\n");
    printf("  save <filepath>   : Save your current game state to a file.\n");
    printf("  load <filepath>   : Load a saved game from a file.\n");
    printf("  exit              : Quit the game.\n");

    char command[MAX_DESCRIPTION];
    while (1) {
        printf("> ");
        fgets(command, MAX_DESCRIPTION, stdin);
        command[strcspn(command, "\n")] = '\0'; // Remove newline
        if (strcmp(command, "exit") == 0) {
            printf("Exiting game... Goodbye!\n");
            break;
        }
        execute_command(&player, rooms, command);
    }

    cleanup_game(rooms);
    return 0;
}
