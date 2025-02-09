-- Animation file descriptor
-- This file will describe the frames used to load an animation

animation = {

    -- The file to load the frames from
    --image_filename = "/tmp/test.png",
    --image_filename = "data/inventory/battle_weapon/sword.png",
    -- The number of rows and columns of images, will be used to compute
    -- the images width and height, and also the frames number (row x col)
    rows = 1,
    columns = 1,
    -- set the image dimensions on battles (in pixels)
    frame_width = 64.0,
    frame_height = 64.0,
    -- The frames duration in milliseconds
    frames = {
        [0] = { id = 0, duration = 90, rotation = -60, x = 0.50, y = 0.30},
        [1] = { id = 0, duration = 15, rotation = -60, x = 0.60, y = 0.30},
        [2] = { id = 0, duration = 15, rotation = -60, x = 0.70, y = 0.30},
        [3] = { id = 0, duration = 15, rotation = -60, x = 0.80, y = 0.30},
        [4] = { id = 0, duration = 15, rotation = -30, x = 0.80, y = 0.30},
        [5] = { id = 0, duration = 15, rotation = -15, x = 0.80, y = 0.30},
        [6] = { id = 0, duration = 15, rotation =   0, x = 0.80, y = 0.30},
        [7] = { id = 0, duration = 15, rotation =  15, x = 0.80, y = 0.30},
        [8] = { id = 0, duration = 15, rotation =  30, x = 0.80, y = 0.30},
        [9] = { id = 0, duration =  0, rotation =  45, x = 0.80, y = 0.30}
    }
}
