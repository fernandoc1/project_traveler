-- Animation file descriptor
-- This file will describe the frames used to load an animation

animation = {

    -- The file to load the frames from
    --image_filename = "data/battles/weapons/sword_attack.png",
    image_filename = "data/inventory/battle_weapon/sword.png",
    -- The number of rows and columns of images, will be used to compute
    -- the images width and height, and also the frames number (row x col)
    rows = 1,
    columns = 1,
    -- set the image dimensions on battles (in pixels)
    frame_width = 64.0,
    frame_height = 64.0,
    -- The frames duration in milliseconds
    frames = {
        [0] = { id = 0, duration = 20, rotation = 30},
        [1] = { id = 0, duration = 20, rotation = 45},
        [2] = { id = 0, duration = 20, rotation = 60},
        [3] = { id = 0, duration = 20, rotation = 75},
        [4] = { id = 0, duration = 20, rotation = 90}, 
        [4] = { id = 0, duration = 20, rotation = 105}, 
        [4] = { id = 0, duration = 20, rotation = 120}, 
        [4] = { id = 0, duration = 20, rotation = 135}, 
        [4] = { id = 0, duration = 20, rotation = 150}, 
        [4] = { id = 0, duration = 20, rotation = 165}, 
        [4] = { id = 0, duration = 20, rotation = 180} 
    }
}
