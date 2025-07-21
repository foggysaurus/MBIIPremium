# MBIIPremium
This is a multiplayer bot support mod that I developed in C++ for over 3 years 

**Here you can watch a demo featuring most of the things described below: https://www.youtube.com/watch?v=-_jMBa06cF4**
**The mod features:**

- Tweaked pathfinding algorithms for a complex dynamic 3D environment

  _Here the bot identifies a target, shoots at it. The target moves on top of the ship, then the bot takes an elevator, jumps the gap onto the ship and shoots the target_

    ![complex_beh](https://github.com/user-attachments/assets/23c87f55-a95d-4e2b-970b-c95d0472095d)

  _Here the bot traverses difficult terrain with gaps_
  
    ![complex_beh2](https://github.com/user-attachments/assets/5b1ca60d-6e74-439a-a785-2d8f38e1dca0)

- A custom toolset for generating,  editing, and saving a navigation mesh in-game

  ![mesh_edit](https://github.com/user-attachments/assets/871f7500-43c3-4656-accb-87727e455f1c)
  
  ![elevator_edit](https://github.com/user-attachments/assets/9802aafb-320b-499d-bf28-9eeeba425a94)

- Custom mesh trigger cells:
  - The "jump" cell, "can only go down/up" cell, "elevator, elevator button (of different types)" cells, "danger" cells to avoid etc.

    <img width="500" height="250" alt="image" src="https://github.com/user-attachments/assets/b7c24408-d19a-4380-aaa4-e5564eff186c" />
- Real-time navmesh adaptation to dynamic world changes:
  - Bridges retracting and extending, doors becoming locked/unlocked, "mover" objects being destroyed/spawned in
 
    <img width="400" height="300" alt="image" src="https://github.com/user-attachments/assets/512d1f01-4b15-497c-b033-16757ca5fca8" /> ![mesh_update](https://github.com/user-attachments/assets/bd341c64-3af5-472f-95d4-8c3fc3a2109f)


- Calculations of dynamic objects on screen
  - bots predicting the trajectories of incoming grenades and calculating the best possible escape plan if in range

  ![gren_throw](https://github.com/user-attachments/assets/707bfbc5-9d75-4d9f-b74d-41d4d0a4ed81)


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
