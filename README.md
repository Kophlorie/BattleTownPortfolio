# BattleTownPrototype

**An Unreal Engine 5.7 C++ gameplay and level-design learning project**

**Status:** Functional prototype · **Engine:** Unreal Engine 5.7 · **Implementation:** C++ and Blueprints · **Mode:** Single-player, switching between two characters

## Overview

BattleTownPrototype is a third-person puzzle prototype set inside a medieval-fantasy fortress. The player alternates control between two characters to navigate a courtyard, activate two pressure plates, open a large gate, and reunite both characters at a destination.

The project was developed through six incremental tutorials, starting with a C++ Unreal project and simple moving Actor, then integrating collision-based interaction, character possession, a connected gameplay puzzle, and cinematic presentation. It is a **learning and portfolio prototype**, not a finished game or a networked co-operative experience.

## Gameplay

1. Explore the fortress and use a moving platform to reach an elevated pressure plate.
2. Switch to the second character using **Tab** and activate a second plate.
3. Keep both plates occupied to lower the main gate; releasing either plate makes it rise again.
4. Move one character to the destination zone.
5. Approach the smaller gate with the other character. It unlocks once the first character has reached the destination.
6. Bring both characters into the destination zone to complete the puzzle.

The moving platform and rooftop pressure plate make vertical traversal part of the puzzle, rather than an isolated demonstration of movement code.

## C++ gameplay systems

The gameplay classes below were created or extended as part of this project. Blueprint-derived Actors and level instances are used to configure meshes, collision volumes, references and gameplay parameters.

| System | Main C++ files | Implementation |
| --- | --- | --- |
| Procedural moving platform | [`MovingPlatform.cpp`](Source/BattleTownPrototype/MovingPlatform.cpp) / [`.h`](Source/BattleTownPrototype/MovingPlatform.h) | `Tick()`-driven, eight-phase movement through vertical and horizontal segments, with configurable speed and movement amplitudes. |
| Character switching | [`BattleTownPlayerController.cpp`](Source/BattleTownPrototype/BattleTownPlayerController.cpp) / [`.h`](Source/BattleTownPrototype/BattleTownPlayerController.h) | Identifies two placed characters by Actor Tags and switches possession with `Possess()` on Tab input. |
| Pressure plates | [`PressurePlate.cpp`](Source/BattleTownPrototype/PressurePlate.cpp) / [`.h`](Source/BattleTownPrototype/PressurePlate.h) | Event-driven collision overlaps update an activation state exposed to other Actors. |
| Reversible main gate | [`ActivationGate.cpp`](Source/BattleTownPrototype/ActivationGate.cpp) / [`.h`](Source/BattleTownPrototype/ActivationGate.h) | Reads two pressure-plate states and interpolates the gate mesh between closed and lowered positions. |
| Conditional secondary gate | [`InteractiveGate.cpp`](Source/BattleTownPrototype/InteractiveGate.cpp) / [`.h`](Source/BattleTownPrototype/InteractiveGate.h) | Checks the destination-zone condition when a character enters its trigger, then raises the gate. |
| Completion condition | [`VictoryZone.cpp`](Source/BattleTownPrototype/VictoryZone.cpp) / [`.h`](Source/BattleTownPrototype/VictoryZone.h) | Independently tracks two tagged characters and announces completion when both are present. |

These mechanics use Unreal's existing Actor, Character, collision, component and input APIs. The project-specific work is the behaviour, interaction rules and integration into a playable level—not the underlying Unreal Engine systems.

## Level and cinematic work

The principal portfolio level is [`L_CourtyardPortfolio.umap`](Content/BattleTown/Maps/L_CourtyardPortfolio.umap). Its fortress blockout includes walls and towers, interconnected courtyards, elevated walkways, rooftop and ground-level pressure plates, moving platforms, gates, lighting and gameplay indicators.

The project also explores material instances, atmospheric composition, Sequencer camera cuts and Take Recorder gameplay capture. The locally developed cinematic sequences and recorded takes are **not included in the public repository**, because Unreal embedded machine-specific author metadata into the files. Their removal from this source snapshot does not affect the gameplay C++ examples, but the original cinematic sequences cannot be opened from a fresh clone.

The visual environment is deliberately **prototype/blockout quality**. It should not be interpreted as a finished asset-production or character-animation showcase.

## Development milestones

| Tutorial | Focus | Outcome |
| --- | --- | --- |
| 1 | C++ project setup and blockout | Initial third-person courtyard |
| 2 | Actor movement | Configurable C++ moving platform |
| 3 | Collision-trigger interaction | Interactive gate prototype |
| 4 | Player possession | Tab-based switching between characters |
| 5 | Integrated puzzle | Two plates, reversible gate, conditional gate, completion zone |
| 6 | Presentation | Expanded fortress layout, lighting and cinematic sequence assembly |

Selected engineering challenges included correcting PlayerController inheritance to preserve existing input handling, debugging overlap events, making gate movement reversible, and recording component-relative movement correctly in Take Recorder.

## Opening the project

**Requirements:** Unreal Engine **5.7** and a compatible Windows C++ development toolchain (for example Visual Studio with Unreal/C++ support).

1. Clone this repository.
2. Open `BattleTownPrototype.uproject` with Unreal Engine 5.7; generate project files/build the C++ module if prompted.
3. In the Unreal Content Browser, open **`Content/BattleTown/Maps/L_CourtyardPortfolio`** for the integrated puzzle. The project configuration may initially open `L_CourtyardPrototype` instead.
4. Press **Play** in the editor. Use the existing third-person movement controls and press **Tab** to switch characters.

**Important dependencies and omissions:** The portfolio map references a third-party Fab fog package under `/Game/Fab/FogArea/`. That package is deliberately **not included** in this repository. A fresh clone may report missing references or display different fog/atmosphere. Only add the package from a copy you are authorised to use; do not redistribute its source files through this repository. Saved cinematic Level Sequences and Take Recorder assets are also excluded for privacy; a fresh clone does not contain the recorded cinematic presentation.

A standalone packaged build has not been verified or provided.

## Source attribution and boundaries

This is an incremental learning project built on Epic Games' Third Person C++ template and other Unreal-provided sample functionality. Character frameworks, base movement/camera systems, starter assets, standard engine APIs and built-in cinematic tools were **not developed from scratch** here. The repository retains some template variants and sample content alongside the project-specific source and levels.

The principal portfolio contributions are the project-specific C++ Actors and their interaction rules, two-character switching, integration into a coherent puzzle, fortress level assembly and cinematic setup. Code and level work were developed through tutorials and iterative experimentation, including use of coding assistance.

Third-party assets, engine samples and any separately licensed materials remain subject to their respective terms. No blanket licence to redistribute every asset in this repository is implied.

## Known limitations and next steps

- Blockout meshes, placeholder decorations and basic visual feedback are still in use.
- Pressure-plate activation is a Boolean for the intended one-character-per-plate puzzle and does not count multiple occupants robustly.
- Puzzle completion currently uses an on-screen debug message, not a final user interface.
- The excluded Fab fog package affects the reproducibility of the exact scene appearance.
- Cinematic Level Sequences and recorded takes are intentionally omitted from this repository to avoid exposing local editor-author metadata; cinematic work is described as part of the development process only.
- Automated tests, a packaged standalone release, performance benchmarks and a final exported video have not been verified.
- Future work may include clearer UI, improved art and animation, generalised plate logic, stronger component validation, further puzzles and reproducible packaging.

**This repository documents a working prototype and the technical learning process behind it—not a complete commercial game.**
