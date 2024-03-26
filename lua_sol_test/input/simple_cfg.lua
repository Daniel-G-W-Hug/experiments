name = "Asus"
width = 1920
height = 1080

config = {
    fullscreen = false,
    resolution = { x = 1024, y = 768 }
}

vec = { 11, 12, 13, 14, 15 }

pr = require 'pl.pretty' -- use penlight for pretty printing
pr.dump(vec)
