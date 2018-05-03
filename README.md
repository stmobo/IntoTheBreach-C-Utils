# IntoTheBreach-C-Utils
C++ extension module with some functions for Into the Breach modding


Compile in release mode or things will break HORRIBLY.  
Probably should reimplement basic_string and vector instead of casting pointers and hoping that the struct definitions match up.

Using the pilot-related functions on non-Windows systems will probably lead to a game crash.

Side note: this is untested on 32bit systems. It might just work but nasal demons seem more likely.


## Lua-side API

### `GetPawnAddr(pawn)`
 * Get the memory address of a pawn structure.
 * arguments:
    - `pawn`: a Pawn object
 * returns: integer

### `GetWeaponName(pawn, idx)`
 * Get the IDs for a pawn's equipped weapons. Index 1 is the mech's first equipped weapon, index 2 is the mech's second equipped weapon, index 0 will always be `'Move'`.
 * arguments:
    - `pawn`: a Pawn object
    - `idx`: an integer between 0 and 2 (inclusive)
 * returns: string or `nil`

### `SetHealth(pawn, health)`
 * Directly set a pawn's current health.
 * arguments:
    - `pawn`: a Pawn object
    - `health`: an integer health value

### `SetMaxHealth(pawn, max_health)`
 * Directly set a pawn's maximum health value.
 * arguments:
    - `pawn`: a Pawn object
    - `max_health`: an integer health value

### `GetMaxHealth(pawn)`
 * Get a pawn's maximum health value.
 * arguments:
    - `pawn`: a Pawn object
 * returns: integer

### `GetPilotAddr(pawn)`
 * Get a reference to a Mech pawn's pilot structure. This address can then be passed to other functions within this module.
 * arguments:
    - `pawn`: a Pawn object
 * returns: integer

### `GetPilotEXP(pilot_addr)`
 * Get a pilot's accumulated experience count for their current level (i.e. this count resets to 0 on level up)
 * arguments:
    - `pilot_addr`: A reference to a pilot structure.
 * returns: integer

### `SetPilotEXP(pilot_addr, exp)`
 * Set a pilot's experience count.
 * arguments:
    - `pilot_addr`: A reference to a pilot structure.
    - `exp`: an integer experience level

### `GetPilotLevelUpEXP(pilot_addr)`
 * Get the total amount of experience the pilot must accumulate to reach the next level. This will be 0 for level 2 pilots.
 * arguments:
    - `pilot_addr`: A reference to a pilot structure.
 * returns: integer

### `SetPilotLevelUpEXP(pilot_addr, exp)`
 * Set the total amount of experience the pilot must accumulate to reach the next level.
 * arguments:
    - `pilot_addr`: A reference to a pilot structure.
    - `exp`: an integer experience level

### `GetPilotLevel(pilot_addr)`
 * Get a pilot's current level.
 * arguments:
    - `pilot_addr`: A reference to a pilot structure.
 * returns: integer

### `SetPilotLevel(pilot_addr, lvl)`
 * Set a pilot's current level.
 * arguments:
    - `pilot_addr`: A reference to a pilot structure.
    - `exp`: an integer pilot level

### `GetPilotName(pilot_addr)`
 * Get a pilot's full name.
 * arguments:
    - `pilot_addr`: A reference to a pilot structure.
 * returns: string

### `SetPilotName(pilot_addr, new_name)`
 * Set a pilot's full name.
 * arguments:
    - `pilot_addr`: A reference to a pilot structure.
    - `new_name`: The pilot's new name. Must be <= 16 characters long.

### `GetPilotAbility(pilot_addr)`
 * Get a pilot's special ability ID.
 * arguments:
    - `pilot_addr`: A reference to a pilot structure.
 * returns: string

### `SetPilotAbility(pilot_addr, new_ability)`
 * Set a pilot's special ability ID.
 * arguments:
    - `pilot_addr`: A reference to a pilot structure.
    - `new_ability`: The pilot's new ability ID. Must be <= 16 characters long.

### `GetPilotPersonality(pilot_addr)`
 * Get a pilot's special personality ID.
 * arguments:
    - `pilot_addr`: A reference to a pilot structure.
 * returns: string

### `SetPilotPersonality(pilot_addr, new_personality)`
 * Set a pilot's special personality ID.
 * arguments:
    - `pilot_addr`: A reference to a pilot structure.
    - `new_personality`: The pilot's new personality ID. Must be <= 16 characters long.

### `GetPilotID(pilot_addr)`
 * Get a pilot's scripting ID.
 * arguments:
    - `pilot_addr`: A reference to a pilot structure.
 * returns: string

### `SetPilotID(pilot_addr, new_id)`
 * Set a pilot's scripting ID.
 * arguments:
    - `pilot_addr`: A reference to a pilot structure.
    - `new_id`: The pilot's new script ID. Must be <= 16 characters long.
