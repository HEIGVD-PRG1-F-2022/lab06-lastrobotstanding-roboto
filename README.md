# Last robot standing

## Conception
### Class diagram
```mermaid
classDiagram
	direction TB
	RobotState --o Roboto
	Game --o RobotState
	class Roboto {
		-vector vector~Case~ board
		-size_t width
		-size_t height
		-unsigned energy
		-unsigned power
		+Roboto()
		+void setConfig(size_t width, size_t height, unsigned energy, unsigned power)
		+string action(vector~string~ updates)
		+static string name()
		-void extractBoard(string update)
		-Damage receiveDamage(string update)
		-string chooseAction()
		+Case readOnBoard(int relativeX, int relativeY)
	}
	class Game {
		+const size_t size
		-vector ~RobotState~ robots
		-unsigned nbRobots
		+Game(unsigned nbRobots)
		+void start()
		+void generateRobots(unsigned nbRobots)
		+void printBoard()
		+vector vector~string~ buildDynamicBoard()
		+string computeBoardAsString()
	}
```

### Enums
```cpp
enum Case { EMPTY, SELF, OTHER, BONUS };
```

### Struct
```cpp
struct Damage {
	int attackerX;
	int attackerY;
	unsigned energyLoss;
}
```

### Algorithms
Pseudocode of Roboto's strategy:

Goals:
- getting a lot of bonus
- getting bonus or escaping is a priority when
- avoid collisions

case: when an attack received

case si attack received proche et forte, le robot en face a plus de power que nous, fuite.
```
iteration = 0
const float nbRobots = size^2 / 10 //estimated number of robots (a bit under the real value)
int minEnergyLevel = 10;
IF energy > minEnergyLevel 
	IF at least robot in the zone
		Attack the closest robot
	ELSE IF bonus in the zone
		IF bonus is touching us
			IF another robot is touching the bonus
				Attack the other robot
			ELSE
				take the bonus

		ELSE IF robot touching
			attack the closest robot
		
		IF no other visible robot is nearer than us

ELSE
	IF BONUS in the zone
		IF no other visible robot is nearer than us
			Go in the bonus direction
		ELSE
			Attack the robot that is the closest from the bonus
	ELSE IF at least robot in the zone
		Move to escapeDirection(board)
	ELSE //no robot nor bonus in the zone
		move X


ENDIF

FUNCTION escapeDirection(board)
	Map touchingRobotsPerCells
	

	FOR EACH touching cell including self cell around the robot
		Calculate number of touching robots
		Store number in a map touchingRobotsPerCells at index cell
		Calculate number of distant robots (magnitude >= 2)
		Store number in a map distantRobotsPerCells at index cell
	
	Sort the touchingRobotsPerCells map by ascending value

	IF there is only 1 touchingRobot for on of the cell
		Move to this cell
	ELSE IF more than 1 touchingRobot for on of the cell
		


minEnergyLevel += iteration % (20 / nbRobots) == 0 ? 1 : 0;



//Si + d'un robot autour -> fuir

//Si un robot autour (diagonale) ->
//  Si peu energy -> fuir autre direction
//  Si bon energy peu power -> ?
//  Si bon energy bon power -> s'aligner pour attaquer

//Si un robot en face (ligne/colonne) ->
//  Si peu energy -> fuir
//  Si bon energy peu power -> ?
//  Si bon energy et bon power -> attaquer

//Si bonus autour ->
//  Si peu energy -> aller vers bonus
//  Si bon energy -> ?

//Radar?
//Damage?
//Wait?


```

g++ main.cpp _deps/libdio-src/src/display.cpp -I_deps/libdio-src/include -o main

