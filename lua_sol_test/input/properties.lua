--[[
    properties are given either as standalone lua type:

    type = {
        ...
    }

    or as indexed sequence of types with a naming convention
    for indexed sequences as type_seq:

    type_seq = {
        {...},
        {...}
    }
--]]
window = {
    size = { width = 600, height = 400 }
}

font = {
    ffile = "../fonts/arial.ttf",
    fsize = 24,
    col_rgb = { r = 255, g = 255, b = 255 }
}

circle_seq = {
    {
        name = "CGreen",
        position = { x = 100, y = 100 },
        speed = { sx = -0.03, sy = 0.02 },
        col_rgb = { r = 0, g = 255, b = 0 },
        radius = 50
    },
    {
        name = "CBlue",
        position = { x = 200, y = 200 },
        speed = { sx = 0.02, sy = 0.04 },
        col_rgb = { r = 0, g = 0, b = 255 },
        radius = 100
    }
}

rectangle_seq = {
    {
        name = "RRed",
        position = { x = 200, y = 200 },
        speed = { sx = 0.1, sy = 0.15 },
        col_rgb = { r = 255, g = 0, b = 0 },
        size = { width = 70, height = 25 }
    },
    {
        name = "RGreen",
        position = { x = 200, y = 200 },
        speed = { sx = 0.1, sy = -0.15 },
        col_rgb = { r = 0, g = 255, b = 0 },
        size = { width = 30, height = 45 }
    }
}
