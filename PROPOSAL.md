# Proposal: Snake

## Synopsis
### Elements
Our game will have 5 elements: 
###
-A moving snake_ that consists of connected rectangles, 
###
-Grids to compose a ground that snake_ can move on. Additional features can be added to the edges of the ground. 
###
-Two types of apples that snake_ can eat: one is the normal apple, another one is the apple that will disappear after certain times. They count for different scores.
###
-A scoreboard and a text sprite indicating whether the skill is available. 
###
-Additional screens (as opposed to the gameplaying screen itself) for starting, pausing, and leveling up. 
###Goal
The player's goal is to eat as many apple as he/she can and earn as much score as he/she can to pass the level.  
### Game play
There will be three levels in total. Within each level, the snake_ will start with length 2 and grows as it eats apples. 
Once the player has earned enough scores, a door would open on the lower right corner, allowing the player to advance to the next level and restart with length 2. 

The total score will include both the scores received from eating apples and the length of snake_'s body * 5. 

Apples will appear randomly on the board. 
Normal apple counts as 1 point; timed apples count as 10 points initially and depreciates with time.
Timed apples will appear as the 5th, 10th, etc. apple; they will disappear after certain amount of time. 

After reaching a certain body length, the snake_'s body color will change. 
Our current thought is from white -> yellow -> green -> blue -> red -> purple. 

The player can "eat" the snake_'s tail to cut down the length of the snake_, but if they accidentally collide with other body parts, the game will be over. 
If the snake_ collide with edges of the ground, the game will be over as well. 
Depends on the level, there will be 1/3/6 obstacles randomly located on the board, and game will also be over if the snake_ hits them. 

There will be 4 "wormholes" opened in the middle of the four edges. 
If the snake_ gets into any of the 4 holes, its head will reappear at the opposite side with its direction unchanged. 

Every once a while (call it a "cycle", maybe a minute), the player will gain a skill that slows down the speed of snake_ by half for the next few updates. 
A text will show up at the lower left corner when the skill is available. 
The player has 20 seconds to press space to use this skill, otherwise they have to wait another cycle for the skill to show up again. 
## Functional requirements
1. The ground will be initialized with the dimension specified. The frequency of "updates" is predetermined since the built-in on_frame can be too quick. 
2. The snake_ will start from the left middle of the ground. 
3. The snake_ will move in a constant speed in every level. Speed can change across levels. 
4. An apple will be placed randomly on one grid in the beginning and after the snake_ eats the previous apple. 
5. The snake_ will be controlled by the keyboard with "left", "right", "up", and "down" keys.
6. If the snake_ eats an apple, the snake_ will grow its body length. 
7. Every time the snake_ reaches a certain length, its color would change according to the aforementioned sequence.
8. If the snake_ collides with its body's last rectangle, the last rectangle will disappear and its body length will minus 1.
9. If the snake_ collides with its other body parts, edges of the ground, or an obstacle, the snake_ will die and the game will be over.
10. The scoreboard will update each points the player earns and shows the targeted score at each level. 
11. There will be 4 holes on the middle of the top, bottom, left, and right edge, as explained in "Gameplay" section. 
12. There will be 3 levels of difficulty, each with a different speed and a different number of obstacles. 
13. A "door" would at the lower right corner when the player reaches the target score of the level. Then, the snake_ needs to get in there to truly pass the level. 
14. A skill to slow down gamespeed will be avaiable to the player once every "cycle", and it will be gone if left unused for a while. 
15. The game needs to be started by pressing any key on the keyboard. The player can also press "q" to pause during the game. To resume, the player can again press any button. 
16. A screen will pop up to indicate "level up!" when the player finishes a level. The player can choose to continue playing another level or replaying this level by pressing different buttons.

## Open questions

- Is it feasible to use an update frequency that we define ourselves?
- What dimensions of ground and snake_'s moving velocities make the game work best?
- How to randomly generate apples on one grid? How can it be tested?
- How to randomly generate obstacles on grid(s)? How can them be tested?
- How to test whether timed apples appear every 5 times and disappear after a certain amount of time?
- Whether the definition of tail is appropriate?
- How to define how much time it needs for the player to be able to call the skill?


