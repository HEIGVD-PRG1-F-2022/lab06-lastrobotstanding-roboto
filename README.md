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
Pseudocode of roboto strategy:
```

```

g++ main.cpp _deps/libdio-src/src/display.cpp -I_deps/libdio-src/include -o main

