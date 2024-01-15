This is based on [Omori's BlåhajDB](https://github.com/BGXBreaker/BGXAddons)
# BGX InterruptDB by Flofian
## What does it do?
This can be used to easily figure out if the enemy is casting a spell I can cancel, and it gives the user control over each spell individually


## How to use it
There are fully working examples at [Flofian - BGXInterruptExamples](https://github.com/Flofian/BGXInterruptExamples)

Include "Interrupt.h" in your champion script
```cpp
#include "Interrupt.h"
```

#### **Initializing the menu**
```cpp
void InterruptDB::InitializeCancelMenu(tab, smallMenu, boolMenuDanger, debugUseAllies);

```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `tab` | `TreeTab*` | **Required**. Pre-Created Tab |
| `smallMenu` | `bool` | **Optional**. This makes the menu less indented |
| `boolMenuDanger` | `int` | **Optional**. Use this to change the menu from sliders to checkboxes (see below) <br> Set this to the minimal danger level you want to have enabled by default |
| `debugUseAllies` | `bool` | **Optional**. Only used for debugging, shows menu for allies instead of enemies |

#### **Getting cast importance of the enemy**
```cpp
int InterruptDB::getCastingImportance(target);
```
| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `target` | `game_object_script` | **Required**. Target to check |
| `return` | `int` | **Returned Value** <br> If using sliders: returns slider value <br> If using Checkboxes: returns 0 or 1 |
#### **Getting cast data of the enemy**
```cpp
interruptableSpell InterruptDB::getInterruptable(target);
```
| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `target` | `game_object_script` | **Required**. Target to check |
| `return` | `interruptableSpell` | **Returned Value** <br> Custom spelldata struct (see below) |

```cpp
struct interruptableSpell {
    float minRemainingTime;
    float maxRemainingTime;
    float expectedRemainingTime;
    int dangerLevel;
};
```
| Parameter | Description                | Example: Pyke Q at cast start | Example: VelKoz R at cast start|
| :-------- | :------------------------- | :---------------------------- |:------------------------------ |
 `minRemainingTime` | How long the target **has to** charge the spell | 0 (could release instantly) | 1 (can only recast after 1s) |
| `maxRemainingTime` | How long the target **could theoretically** charge the spell | 3 (could charge for 3s) | 2.8 (max duration) |
| `expectedRemainingTime` | How long the target **is most likely** to charge the spell | 1 (needs to charge for 1s for full range) | 2.8 (most often used fully) | 
| `dangerLevel` | Same as getCastingImportance | (by default 0, depends on menu) |  (by default 3, depends on menu) |

#### **Misc: Get Display Name**
```cpp
std::string InterruptDB::getCastingImportance(target);
```
| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `target` | `game_object_script` | **Required**. Target to check |
| `return` | `std::string` | **Returned Value** <br> The real name of the champion, since for example Wukong is internally called MonkeyKing |

## Menu Showcase
### `InterruptDB::InitializeCancelMenu(interruptSettingsTab, true, 2)`
![Screenshot (11)](https://github.com/Flofian/BGXInterrupt/assets/56082272/44d4c5ea-5467-4c18-8520-b612282a5825)
---
### `InterruptDB::InitializeCancelMenu(interruptableSpellsTab, true, 2)`
![Screenshot (12)](https://github.com/Flofian/BGXInterrupt/assets/56082272/5576d8f1-0097-430f-bdc8-716f2f2f7a5f)
---
### `InterruptDB::InitializeCancelMenu(interruptableSpellsTab, false, 2)`
![Screenshot (13)](https://github.com/Flofian/BGXInterrupt/assets/56082272/6c67b09b-efbc-41aa-874b-8822cacf8571)
---
### `InterruptDB::InitializeCancelMenu(interruptableSpellsTab, false)`
![Screenshot (14)](https://github.com/Flofian/BGXInterrupt/assets/56082272/e02c4481-f25d-468e-b764-47c1632c8cd7)
---
### `InterruptDB::InitializeCancelMenu(interruptableSpellsTab, true)`
![Screenshot (15)](https://github.com/Flofian/BGXInterrupt/assets/56082272/ca8ce117-dea8-459d-9fb5-5627dec8dc89)

## TODO
- Change structure to make it a class, allowing multiple menus (for example 1 boolMenu for Q, 1 boolMenu for R)
- Allow boolMenu to include multiple Spells (for example on Nami: only use R to interrupt Katarina R, and dont use Q)
- (Maybe) Figure out how many R shots Jhin has left to fix expectedRemainingTime on him
- (Maybe) Figure out the expectedRemainingTime on more spells based on allies/enemies nearby (example: Janna will stop using R when all allies nearby are full hp)
- (Maybe) Figure out a way to fix buffs not being accurate (example Lucian R)
