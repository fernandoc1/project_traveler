-- Animation file descriptor
-- This file will describe the frames used to load an animation

animation = {

	-- The number of rows and columns of images, will be used to compute
	-- the images width and height, and also the frames number (row x col)
	rows = 6,
	columns = 8,
	-- set the image dimensions on battles (in pixels)
	frame_width = -64.0,
	frame_height = 72.0,
	-- The frames duration in milliseconds
    frames = {
        [0] = { id = 15, duration = 300 },
    }
}
