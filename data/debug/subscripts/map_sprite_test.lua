-- Set the namespace according to the map name.
local ns = {};
setmetatable(ns, {__index = _G});
map_sprite_test = ns;
setfenv(1, ns);

-- The map name, subname and location image
map_name = ""
map_image_filename = ""
map_subname = ""

-- The music file used as default background music on this map.
-- Other musics will have to handled through scripting.
music_filename = "data/sounds/wind.ogg"

-- c++ objects instances
local Map = nil
local DialogueManager = nil
local EventManager = nil
local Script = nil

local bronann = nil
local test_image = nil

-- the main map loading code
function Load(m)
    print("Loading map_sprite_test...");

    Map = m;
    DialogueManager = Map:GetDialogueSupervisor();
    EventManager = Map:GetEventSupervisor();
    Script = Map:GetScriptSupervisor();

    Map:SetUnlimitedStamina(true)
    Map:SetRunningEnabled(false) -- Hide the stamina bar

    -- Adds a sprite
    bronann = CreateSprite(Map, "Borghen", 32, 43, vt_map.MapMode.GROUND_OBJECT);
    bronann:SetDirection(vt_map.MapMode.SOUTH);
    bronann:SetMovementSpeed(vt_map.MapMode.NORMAL_SPEED);

    --_CreateEvents();

    -- Add clouds overlay
    Map:GetEffectSupervisor():EnableAmbientOverlay("data/visuals/ambient/clouds.png", 15.0, -5.0, true);

    -- Set the camera focus on Bronann
    Map:SetCamera(bronann);

    -- A scene map only
    --Map:PushState(vt_map.MapMode.STATE_SCENE);

    EventManager:StartEvent("Bronann looks south", 3000);
end

-- Creates all events and sets up the entire event sequence chain
function _CreateEvents()
    local event = nil
    local text = nil
    local dialogue = nil

    event = vt_map.ChangeDirectionSpriteEvent.Create("Bronann looks south", bronann, vt_map.MapMode.SOUTH);
    event:AddEventLinkAtEnd("Bronann looks west", 2000);
    event = vt_map.ChangeDirectionSpriteEvent.Create("Bronann looks west", bronann, vt_map.MapMode.WEST);
    event:AddEventLinkAtEnd("Bronann looks north", 2000);
    event = vt_map.ChangeDirectionSpriteEvent.Create("Bronann looks north", bronann, vt_map.MapMode.NORTH);
    event:AddEventLinkAtEnd("Bronann looks east", 2000);
    event = vt_map.ChangeDirectionSpriteEvent.Create("Bronann looks east", bronann, vt_map.MapMode.EAST);
    event:AddEventLinkAtEnd("Bronann speaks", 2000);

    dialogue = vt_map.SpriteDialogue.Create();
    text = vt_system.Translate("As you wish. Follow me.");
    dialogue:AddLine(text, bronann);
    event = vt_map.DialogueEvent.Create("Bronann speaks", dialogue);
    event:AddEventLinkAtEnd("Bronann laughs", 2000);

    event = vt_map.ScriptedEvent.Create("Bronann laughs", "bronann_laughs", "");
    event:AddEventLinkAtEnd("Bronann is grayed", 2000);

    event = vt_map.ScriptedEvent.Create("Bronann is grayed", "bronann_gray", "");
    event:AddEventLinkAtEnd("Dump stack state", 2000);

    event = vt_map.ScriptedEvent.Create("Dump stack state", "dump_stack_state", "");
    event:AddEventLinkAtEnd("Random move", 2000);

    event = vt_map.RandomMoveSpriteEvent.Create("Random move", bronann, 1000, 2000);
    event:AddEventLinkAtEnd("Random move", 2000); -- Loop on itself
end

-- Map Custom functions
-- Used through scripted events

map_functions = {
    bronann_laughs = function()
        bronann:SetCustomAnimation("laughing", 700);
    end,

    bronann_gray = function()
        bronann:SetGrayscale(true);
    end,

    dump_stack_state = function()
        ScriptManager:DEBUG_DumpScriptsState()
    end,
}
