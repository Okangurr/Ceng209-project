# Dungeon Adventure Game

Welcome to the **Dungeon Adventure Game**! This game is a text-based dungeon crawler where you navigate through rooms, fight creatures, collect items, and aim to escape the dungeon.

## Game Overview
You start in a dungeon filled with dangerous traps, fierce creatures, and useful items. Your goal is to find the exit and escape the dungeon. To do this, you must:

- Explore rooms
- Collect items
- Fight creatures
- Avoid traps
- Find the key to unlock the exit

## How to Play

### Controls
You control the game by typing commands into the terminal. Here are the available commands:

- **`move <direction>`**: Move to a different room. Directions can be:
  - `up`
  - `down`
  - `left`
  - `right`
- **`look`**: Look around the current room to see items, creatures, and traps.
- **`pickup <item>`**: Pick up an item in the room and add it to your inventory.
- **`inventory`**: Show the list of items in your inventory.
- **`attack`**: Attack the creature in the room using a weapon from your inventory.
- **`health`**: Show your current health.
- **`save <filepath>`**: Save your current game state to a file.
- **`load <filepath>`**: Load a previously saved game state from a file.
- **`exit`**: Quit the game.

### Objective
Your objective is to:

1. Find the **key** hidden in one of the rooms.
2. Navigate to the exit room.
3. Use the key to unlock the exit door and escape.

## Room Details
Each room in the dungeon may contain:

- **Items**: Weapons or keys you can pick up and use.
- **Creatures**: Hostile enemies you must defeat to proceed.
- **Traps**: Dangerous obstacles that reduce your health.
- **Exit**: The final room where you can escape the dungeon.

## Gameplay Example
```plaintext
Welcome to the Dungeon Adventure Game!
Available commands:
  move <direction>  : Move to a different room (up, down, left, right).
  look              : Look around the current room.
  inventory         : Show your inventory.
  pickup <item>     : Pick up an item in the room.
  attack            : Attack the creature in the room using a weapon from your inventory.
  health            : Show your health.
  save <filepath>   : Save your current game state to a file.
  load <filepath>   : Load a saved game from a file.
  exit              : Quit the game.

> look
A dark, damp dungeon room with mossy walls.
Items in the room: Dagger
> pickup Dagger
You picked up the Dagger.
> move up
You moved up.
A bright room with a golden chest in the corner.
A Goblin is here.
> attack
You attack the Goblin with your Dagger (Damage: 5)!
...
```

## Code Structure

### Main Components
- **Player**: The main character controlled by the user.
- **Room**: Represents a room in the dungeon. Contains items, creatures, traps, and connections to other rooms.
- **Item**: Represents an item in the game (e.g., weapons, key).
- **Creature**: Represents a hostile enemy in the game.

### Code Files
- `dungeon_game.c`: The main game logic and functions.

### Key Functions
1. **`initialize_game()`**:
   - Sets up the game world, including rooms, items, and creatures.
2. **`execute_command()`**:
   - Processes player commands.
3. **`move()`**:
   - Handles movement between rooms.
4. **`look()`**:
   - Displays details about the current room.
5. **`pickup()`**:
   - Allows the player to collect items.
6. **`attack()`**:
   - Handles combat with creatures.
7. **`save_game()`**:
   - Saves the current game state to a file.
8. **`load_game()`**:
   - Loads a previously saved game state.

## Development Notes

### Adding New Features
- To add new rooms, modify the `initialize_game()` function.
- To create new commands, extend the `execute_command()` function.
- To add new items or creatures, modify their respective structures and initialization logic.

### Memory Management
- The game uses `malloc` to dynamically allocate memory for rooms, items, and creatures. Ensure all allocated memory is freed using `cleanup_game()` to prevent memory leaks.

## Troubleshooting

### Common Issues
1. **Command not recognized**:
   - Ensure you typed the command correctly.
2. **Game crashes**:
   - Check if you have sufficient memory allocated for new rooms or items.
3. **Saved game won't load**:
   - Ensure the save file path is correct and the file exists.

## Future Improvements
- Add more rooms and items.
- Implement a leveling system for the player.
- Introduce more complex traps and puzzles.
- Add a graphical interface for better user experience.

Enjoy the adventure and good luck escaping the dungeon!
