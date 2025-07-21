# MBIIPremium
This is a multiplayer bot support mod that I developed in C++ for over 3 years 

**Here you can watch a demo featuring most of the things described below: https://www.youtube.com/watch?v=-_jMBa06cF4**
**The mod features:**

- Tweaked pathfinding algorithms for a complex dynamic 3D environment
  
  <img width="200" height="300" alt="image" src="https://github.com/user-attachments/assets/c7fd691d-d295-4eab-9fd2-13aa8ff55651" />
- A custom toolset for generating,  editing, and saving a navigation mesh in-game

  ![mesh_edit](https://github.com/user-attachments/assets/871f7500-43c3-4656-accb-87727e455f1c)
![elevator_edit](https://github.com/user-attachments/assets/9802aafb-320b-499d-bf28-9eeeba425a94)

- Custom mesh trigger cells:
  - The "jump" cell, "can only go down/up" cell, "elevator, elevator button (of different types)" cells, "danger" cells to avoid etc.

    <img width="500" height="250" alt="image" src="https://github.com/user-attachments/assets/b7c24408-d19a-4380-aaa4-e5564eff186c" />
- Real-time navmesh adaptation to dynamic world changes:
  - Bridges retracting and extending, doors becoming locked/unlocked, "mover" objects being destroyed/spawned in
 
    <img width="400" height="300" alt="image" src="https://github.com/user-attachments/assets/512d1f01-4b15-497c-b033-16757ca5fca8" />

- Calculations of dynamic objects on screen
  - bots predicting the trajectories of incoming grenades and calculating the best possible escape plan if in range

<img width="300" height="200" alt="image" src="https://github.com/user-attachments/assets/cb52d931-c3ec-4576-bf65-45a46c74e7f2" />

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

  <img width="400" height="300" alt="image" src="https://github.com/user-attachments/assets/3fc19831-8734-455c-b9ad-0d988d903f88" />

- Many more utility functions
