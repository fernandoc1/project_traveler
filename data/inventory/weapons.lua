------------------------------------------------------------------------------[[
-- Filename: weapons.lua
--
-- Description: This file contains the definitions of all weapons.
-- Each weapon has a unique integer identifier that is used
-- as its key in the weapons table below. Weapon IDs are unique not only among
-- each other, but among other inventory game objects as well (items, armor,
-- etc).
--
-- Object IDs 10,001 through 20,000 are reserved for weapons. Do not break this
-- limit, because other value ranges correspond to other types of inventory objects.
--
-- Weapons IDs do -not- need to be sequential. When you make a new weapon, keep it
-- grouped with similar weapon types (swords with swords, etc.) and keep a buffer of
-- space between group types. This way we won't get a mess of random weapons all over
-- this file.
--
-- All weapon entries need the following data to be defined:
-- {name}: Text that defines the name of the weapon.
-- {description}: A brief description about the weapon.
-- {icon}: The filepath to the image icon representing this weapon.
-- {physical_attack}: The amount of physical damage that the weapon causes.
-- {magical_attack}: The amount of magical damage that the weapon causes.
-- {standard_price}: The standard asking price of this weapon from merchants.
-- {usable_by}: A list of characters which may equip this weapon.
-- {slots}: The number of slots available to equip shards on the weapon.
-- {key_item}: Tells whether the item is a key item, preventing it from being consumed or sold.
------------------------------------------------------------------------------]]

-- All weapon definitions are stored in this table
if (weapons == nil) then
   weapons = {}
end


-- -----------------------------------------------------------------------------
-- IDs 10,001 - 10,500 are reserved for swords
-- -----------------------------------------------------------------------------

default_battle_animations = {
    idle =                  "data/battles/actions/idle.lua",
    run =                   "data/battles/actions/run.lua",
    run_after_victory =     "data/battles/actions/run_after_victory.lua", 
    attack =                "data/battles/actions/sword_attack.lua", 
    attack_forward_thrust = "data/battles/actions/attack.lua",
    dodge =                 "data/battles/actions/dodge.lua",
    victory =               "data/battles/actions/victory.lua", 
    hurt =                  "data/battles/actions/hurt.lua", 
    poor =                  "data/battles/actions/kneeling.lua",
    dying =                 "data/battles/actions/kneeling.lua",
    dead =                  "data/battles/actions/dead.lua",
    revive =                "data/battles/actions/kneeling.lua",
    item =                  "data/battles/actions/idle.lua",
    magic_prepare =         "data/battles/actions/magic_prepare.lua",
    magic_cast =            "data/battles/actions/magic_cast.lua", 
    jump_forward =          "data/battles/actions/jump_forward.lua",
    jump_backward =         "data/battles/actions/jump_forward.lua",
    escape_smoke =          "data/battles/actions/idle.lua",
}

-- Wood/earth family
-- -----------------
weapons[10001] = {
    name = vt_system.Translate("Wooden Sword"),
    description = vt_system.Translate("A sword made of wood with a steel hilt, very good for practising."),
    icon = "data/inventory/battle_weapon/sword.png",
    physical_attack = 2,
    magical_attack = 0,
    standard_price = 0,
    usable_by = BRONANN + THANIS + AERITH,
    slots = 0,
    key_item = true,
    ranged_weapon = false,

    battle_animations = {
        [BORGHEN] = default_battle_animations;
        [GOLBEZ] = default_battle_animations;
        [AERITH] = default_battle_animations;
    }
}

weapons[10002] = {
    name = vt_system.Translate("Aerith wand"),
    description = vt_system.Translate("A sword made of wood with a steel hilt, very good for practising."),
    icon = "data/inventory/battle_weapon/wand.png",
    physical_attack = 2,
    magical_attack = 0,
    standard_price = 250,
    usable_by = BRONANN + THANIS + AERITH,
    slots = 0,
    key_item = false,
    ranged_weapon = false,

    trade_conditions = {
        [0] = 35,    -- Drunes
        [3119] = 3,  -- Fine Wood
        [3112] = 1,  -- Silk
        [3101] = 1,  -- Refined Slimy Material
    },

    battle_animations = {
        [BORGHEN] = default_battle_animations;
        [AERITH] = default_battle_animations;
        [GOLBEZ] = default_battle_animations;
    }
}

weapons[10003] = {
    name = vt_system.Translate("Axe"),
    description = vt_system.Translate("A sword made of wood with a steel hilt, very good for practising."),
    icon = "data/inventory/battle_weapon/axe.png",
    physical_attack = 2,
    magical_attack = 0,
    standard_price = 250,
    usable_by = SETZER,
    slots = 0,
    key_item = false,
    ranged_weapon = false,

    trade_conditions = {
        [0] = 35,    -- Drunes
        [3119] = 3,  -- Fine Wood
        [3112] = 1,  -- Silk
        [3101] = 1,  -- Refined Slimy Material
    },

    battle_animations = {
        [BORGHEN] = default_battle_animations;
        [AERITH] = default_battle_animations;
        [SETZER] = default_battle_animations;
    }
}

