# MBIIPremium
This is a multiplayer bot support mod that I developed for over 3 years in C++
**Here you can watch a demo featuring most of the things described below: https://www.youtube.com/watch?v=-_jMBa06cF4**
**The mod features:**

- Tweaked pathfinding algorithms for a complex dynamic 3D environment
- A custom toolset for generating,  editing, and saving a navigation mesh in-game
- Custom mesh trigger cells:
  - The "jump" cell, "can only go down/up" cell, "elevator, elevator button (of different types)" cells, "danger" cells to avoid etc.
- Real-time navmesh adaptation to dynamic world changes:
  - Bridges retracting and extending, doors becoming locked/unlocked, "mover" objects being destroyed/spawned in
- Calculations of dynamic objects on screen
  - bots predicting the trajectories of incoming grenades and calculating the best possible escape plan if in range
  - bots evading environmental dangers; shooting mines 
- Complex state-based bot behavior e.g.:
  - formation system where multiple bots follow their leader in a certain formation to avoid collisions
  - different modes of behavior: seek and destroy, where the bots explore the map autonomously trying to find enemies, or basic mode where a bot follows the leader trying to protect it 
  - bots behaving differently to certain enemy classes based on their own class and tactical situations
  - target priority system, e.g. prioritizing nearby strong melee players first, followed by players actively shooting within a narrow forward angle etc.
  - anti friendly fire system
  - anti melee system
  - predictive target aiming for the bots 
- Interprocess communication to enable different game instances interact with one another
- A system of dynamic triggers and conditions to control AI behavior contextually
- A launcher
- Many more utility functions
