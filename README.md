# Provinces-Map
This project is designed to manage a map of provinces, where each province can be connected to others by a direct distance. It implements a series of operations for checking distances between provinces, marking provinces as visited, and performing various pathfinding algorithms. The project uses different data structures, such as stacks and queues, to manage the provinces and navigate the map.

The key features of the system include loading distance data, performing range checks between provinces, and using stacks and queues to manage the traversal of the provinces. The queue implementation supports both regular and priority enqueuing, making it suitable for different traversal strategies.

Key Features
  - Distance Management: Stores and manages the distances between provinces in a matrix, allowing you to check if the distance between any two provinces is within a specified range.
  - Pathfinding: Implements a simple pathfinding algorithm using stacks (LIFO) and queues (FIFO, with priority enqueuing), enabling traversal of provinces in different ways.
  - Visited States: Allows marking provinces as visited and counting how many provinces have been visited, useful for traversal and pathfinding tasks.
  - Data Loading: The system can load the distance matrix from a CSV file, making it flexible for different map configurations.

Classes and Functionality
Map Class
The Map class is the central part of the project, responsible for managing the map of provinces and their distances. The class provides various methods for managing the distance matrix, marking provinces as visited, and loading data from a file.

Key Features
  - Distance Matrix: Stores the distance between provinces in a 2D matrix.
  - Visited Provinces: Tracks which provinces have been visited.
  - Distance Checking: Provides a method to check if the distance between two provinces is within a specified range.

Important Functions
loadDistanceData(const std::string& filename): Loads the distance data from a CSV file into the distance matrix.
isWithinRange(int provinceA, int provinceB, int maxDistance): Checks if the distance between two provinces is within a given range.
markAsVisited(int province): Marks a province as visited.
isVisited(int province): Checks if a province has been visited.
resetVisited(): Resets all provinces to unvisited.
countVisitedProvinces(): Returns the number of visited provinces.
getDistance(int provinceA, int provinceB): Returns the distance between two provinces.

Queue Class
The Queue class implements a circular queue with support for both regular and priority enqueuing. It manages the provinces in a first-in, first-out (FIFO) manner, but priority can be given to provinces in certain cases.

Key Features
  - Circular Queue: Ensures efficient use of memory by using a circular queue structure.
  - Priority Enqueuing: Allows adding provinces to the front of the queue, giving them priority over others.

Important Functions
enqueue(int province): Adds a province to the queue.
dequeue(): Removes and returns the province at the front of the queue.
peek(): Returns the province at the front of the queue without removing it.
isEmpty(): Checks if the queue is empty.
enqueuePriority(int province): Adds a province to the front of the queue, giving it priority.

Stack Class
The Stack class implements a basic stack data structure, which is used to store provinces in a last-in, first-out (LIFO) manner. It supports basic stack operations like push, pop, and peek.

Key Features
Simple Stack: Implements a basic stack for province management.
Overflow and Underflow Prevention: Ensures that you cannot push to a full stack or pop from an empty stack.

Important Functions
push(int province): Adds a province to the top of the stack.
pop(): Removes and returns the top province from the stack.
peek(): Returns the top province without removing it.
isEmpty(): Checks if the stack is empty.
getSize(): Returns the current size of the stack.

