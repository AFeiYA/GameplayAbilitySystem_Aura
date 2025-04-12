# GAS Notes

### 3.8 InitAbilityActorInfo 

####
- 能力系统组件有两个变量：
  - Owner Actor和Avatar Actor。
  - Owner Actor是实际拥有该组件的对象，而Avatar Actor是在世界中表示该组件的对象。
- 对于AI角色，这两个通常是同一个对象（即AI角色本身）。
- 对于玩家角色，Owner Actor是Player State，而Avatar Actor是角色本身。
- ![img.png](img.png)
##### Replication: InitAbilityActorInfo
![3.8_replications.png](Images/3.8_replications.png)
![3.8_Mixed_Rep.png](Images/3.8_Mixed_Rep.png)
