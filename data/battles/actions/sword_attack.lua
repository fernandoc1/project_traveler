-- Animation file descriptor
-- This file will describe the frames used to load an animation

animation = {

    -- The file to load the frames from
    --image_filename = "/tmp/test.png",
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
        [0] = { id = 0, duration = 200, rotation = 30 , x = 0.6, y = 0.5},
        [1] = { id = 0, duration = 200, rotation = 45 , x = 0.6, y = 0.5},
        [2] = { id = 0, duration = 200, rotation = 60 , x = 0.6, y = 0.5},
        [3] = { id = 0, duration = 200, rotation = 75 , x = 0.6, y = 0.5},
        [4] = { id = 0, duration = 200, rotation = 90 , x = 0.6, y = 0.5}, 
        [5] = { id = 0, duration = 200, rotation = 105, x = 0.6, y = 0.5}, 
        [6] = { id = 0, duration = 200, rotation = 120, x = 0.6, y = 0.5}, 
        [7] = { id = 0, duration = 200, rotation = 135, x = 0.6, y = 0.5}, 
        [8] = { id = 0, duration = 200, rotation = 150, x = 0.6, y = 0.5}, 
        [9] = { id = 0, duration = 200, rotation = 165, x = 0.6, y = 0.5}, 
        [10] = { id = 0, duration = 0, rotation = 165, x = 0.6, y = 0.5} 
    }
}
