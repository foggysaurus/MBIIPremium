# MBIIPremium
This is a multiplayer bot support mod that I developed in C++ for over 3 years 

**Here you can watch a demo featuring most of the things described below: https://www.youtube.com/watch?v=-_jMBa06cF4**

**The mod features:**

- Tweaked pathfinding algorithms for a complex dynamic 3D environment
  
- Bots intelligently navigate dynamic terrain identifying and chasing targets across vertical and uneven geometry

  _Taking elevators, jumping across gaps, traversing obstacles_

    <p float="left"> <img src="https://github.com/user-attachments/assets/23c87f55-a95d-4e2b-970b-c95d0472095d" width="300"/> <img src="https://github.com/user-attachments/assets/5b1ca60d-6e74-439a-a785-2d8f38e1dca0" width="300"/> <img src="https://github.com/user-attachments/assets/9ccc2e87-bba2-41dc-9d9e-1d6f64881eaf" width="300"/> </p>

- A custom toolset for generating,  editing, and saving a navigation mesh in-game

    <p float="left"> <img src="https://github.com/user-attachments/assets/871f7500-43c3-4656-accb-87727e455f1c" width="300"/> <img src="https://github.com/user-attachments/assets/9802aafb-320b-499d-bf28-9eeeba425a94" width="300"/> </p>

- Custom mesh trigger cells:
  - The "jump" cell, "can only go down/up" cell, "elevator, elevator button (of different types)" cells, "danger" cells to avoid etc.

    <img width="500" height="250" alt="image" src="https://github.com/user-attachments/assets/b7c24408-d19a-4380-aaa4-e5564eff186c" />
- Real-time navmesh adaptation to dynamic world changes:
  - Bridges retracting and extending, doors becoming locked/unlocked, "mover" objects being destroyed/spawned in

    <p float="left"> <img src="https://github.com/user-attachments/assets/1fa47456-9efd-4b14-8513-a977df4a8d97" width="300"/> <img src="https://github.com/user-attachments/assets/bd341c64-3af5-472f-95d4-8c3fc3a2109f" width="300"/> </p>

- Bots calculate and respond to on-screen threats:
  
    Predict and dodge incoming grenades
  
    React to environmental hazards
  
    Detect and shoot mines
 
  <p float="left"> <img src="https://github.com/user-attachments/assets/707bfbc5-9d75-4d9f-b74d-41d4d0a4ed81" width="300"/> <img src="https://github.com/user-attachments/assets/0f7a9169-fa01-4db8-841a-e440d49878c2" width="300"/> <img src="https://github.com/user-attachments/assets/ccb3eb59-2e0f-4dd4-a9d9-2c71759191f8" width="300"/> </p>
  

- Complex state-based bot behavior e.g.:
  - formation system where multiple bots follow their leader in a certain formation to avoid collisions
  - different modes of behavior: seek and destroy, where the bots explore the map autonomously trying to find enemies, or basic mode where a bot follows the leader trying to protect it 
  - bots behaving differently to certain enemy classes based on their own class and tactical situations
  - target priority system, e.g. prioritizing nearby strong melee players first, followed by players actively shooting within a narrow forward angle etc.
  - anti friendly fire system
  - anti melee system
  - predictive target aiming for the bots

    <img width="500" height="250" alt="image" src="https://github.com/user-attachments/assets/8b672e41-7cf1-42f6-82b7-7563b0ce5138" />

- Interprocess communication to enable different game instances interact with one another
- A system of dynamic triggers and conditions to control AI behavior contextually
- A launcher

  <img width="400" height="300" alt="image" src="https://github.com/user-attachments/assets/3fc19831-8734-455c-b9ad-0d988d903f88" />

- Many more utility functions
