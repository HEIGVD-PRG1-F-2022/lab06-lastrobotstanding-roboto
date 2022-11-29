# Last robot standing

## Conception
### Class diagram
```mermaid
classDiagram
	direction LR
	class Robot {
		-vector vector~Case~ board
		-size_t width
		-size_t height
		-unsigned energy
		-unsigned power
		+MonRobot(size_t width, size_t height, unsigned energy, unsigned power)
		+string action(vector~string~ updates)
		+static string name()
		-void extractBoard(string update)
		-Damage receiveDamage(string update)
	}
	class Game {
		+const size_t size
		-vector ~RobotState~ robots
		+Game(unsigned nbRobots)
		+void generateRobots()
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

```cpp
struct RobotState {
	int x;
	int y;
	unsigned energy;
	unsigned power;
	Robot robot;
}
```
