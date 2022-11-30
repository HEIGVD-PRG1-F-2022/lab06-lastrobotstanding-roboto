# Last robot standing

## Conception
### Class diagram
```mermaid
classDiagram
	direction TB
	RobotState o-- Roboto
	Game o-- RobotState
	class Roboto {
		-vector vector~Case~ board
		-size_t width
		-size_t height
		-unsigned energy
		-unsigned power
		+Roboto(size_t width, size_t height, unsigned energy, unsigned power)
		+string action(vector~string~ updates)
		+static string name()
		-void extractBoard(string update)
		-Damage receiveDamage(string update)
		-string chooseAction()
	}
	class Game {
		+const size_t size
		-vector ~RobotState~ robots
		+Game(unsigned nbRobots)
		+void generateRobots(unsigned nbRobots)
	}
	class RobotState {
		-int x
		-int y
		-unsigned energy
		-unsigned power
		-Roboto robot
		-string lastAction
		+RobotState(int x, int y, unsigned energy, unsigned power, size_t width, size_t height)
		+int getX()
		+int getY()
		+unsigned getEnergy()
		+unsigned getPower()
		string getLastAction()
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


g++ main.cpp _deps/libdio-src/src/display.cpp -I_deps/libdio-src/include -o main

