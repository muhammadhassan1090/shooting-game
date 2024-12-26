**PROJECT TITLE:   2D SHOOTING GAME**

**GROUP MEMBERS: **
1. MUHAMMAD HASSAN
2. ASIF ALI ANSAREE
3. DAWOOD AKBAR
4. IQRAR UR REHMAN


**PROJECT DESCRIPTION:**
The project basically involves a game which is a thrilling test of precision, strategy, and quick reflexes, designed to keep players engaged with escalating challenges. With multiple difficulty modes, dynamic gameplay, and immersive audio-visual feedback, it offers a rewarding experience for all skill levels.Each level brings a new layer of excitement, pushing players to sharpen their focus and aim for success. As players master the mechanics, the increasing pace and complexity ensure they remain challenged. It’s a perfect blend of fun, challenge, and replayability that guarantees hours of entertainment.

**FEATURES OF GAME:**
1.Player Control:
The player can move left and right using the arrow keys.
Shooting is triggered by the spacebar, allowing players to fire bullets at descending objects.

2.Dynamic Target and Obstacle System:
Targets (green objects) descend randomly and can be shot to earn points.
Stones (gray obstacles) also descend and reduce the score if hit, adding an element of challenge.

3.Difficulty Levels:
Players can choose between Easy, Medium, and Hard difficulty.
Each level affects object speed, spawn rate, and the target score required to win.

4.Level Progression:
Each level has a time limit and a score target.
Players advance to the next level by achieving the target score before the timer runs out.

5.Game Timer  System:
A countdown timer keeps track of the remaining time.
Once the timer is up , win/loss evaluation is made.

6.Visual and Audio Feedback:
Sound effects play for shooting, hitting targets, and hitting obstacles to enhance immersion.
A background image and visual indicators for score, timer, and targets add to the experience.

7. Retry and Endgame System:
If the player runs out of time or fails to reach the target score, they can retry the level.
Winning or losing displays appropriate messages with options to replay or quit.

8.Randomized Gameplay:
The spawn position and timing of targets and stones are randomized for unpredictable gameplay.

9.Incremental Difficulty:
As levels progress, the speed of descending objects and the complexity of gameplay increase.

10.User-Friendly Interface:
Instructions and difficulty selection menus are presented clearly to guide players.




**ARCHITECHTURE OF THE GAME:**
**Core Modules**
The project is divided into several key modules, each responsible for a specific aspect of the game. These modules work in tandem to create an engaging and functional gameplay experience.

1.Game Initialization Module:
*Initializes the game environment (window, audio, textures).
*Loads resources like sounds and images.
*Prepares variables for game logic.
*Game assets loaded into memory.

2.Input Handling Module:
*Captures player input for movement and shooting.
*Maps keyboard actions to game behaviors.
*Updates to player position and bullet spawning.

3.Game Object Management Module:
*Manages game objects like bullets, targets, and stones.
*Handles spawning, updating, and deactivating objects.
*Object struct to store attributes (position, active state).
*Active and updated objects in the game world.

4.Collision Detection Module:
*Detects collisions between game objects.
*Updates game state based on collision results.
*Updates to object states and score.

5.Scoring System Module:
*Tracks and updates the player's score.
*Adjusts the score based on collisions.
*Increment and decrement logic based on collisions.
*Outputs current score value.

6.Timer and Level Progression Module:
*Tracks the remaining time for each level.
*Determines win/loss conditions based on time and score.
*Timer variable (levelTimer).
*Inputs frame time and player progress.
*Outputs updates to game state (win/loss).

7.UI Rendering Module:
*Displays game-related information (score, timer, end-game messages).
*Renders the player, targets, and bullets on the screen.
*Outputs updated visuals for the player.
*Display initial page for user to choose between different difficulties

8.Audio Module:
*Plays sound effects for actions like shooting, hitting targets, and collisions.

9. Game Loop Module:
*Connects all modules and ensures smooth gameplay.
*Handles game flow, including initialization, updates, and rendering.
*Main while loop.
*Inputs all module outputs.
*Outputs continuous game state updates.

**Modules Interactions**
*Game Initialization Module initializes resources and passes them to the Game Loop Module.
*Input Handling Module updates the Game Object Management Module (e.g., player movement, bullet firing).
*Game Object Management Module communicates with the Collision Detection Module and Scoring System Module to process object interactions.
*Scoring System Module updates the score, which is displayed by the UI Rendering Module.
*Timer and Level Progression Module informs the Game Loop Module about win/loss conditions.
*Audio Module is triggered by various events, such as collisions or player actions.


**HOW TO RUN AND DEPLOY THE PROGRAM:**
In order to run the program, you can either choose VISUAL STUDIO or VISUAL STUDIO CODE.
First you need to include the raylib library in your IDE setting. The setup for raylib library can be downloaded from the google chrome.
After including the raylib library , include the "raylib.h" in program and simply run the program.
