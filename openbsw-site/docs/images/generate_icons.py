from PIL import Image, ImageDraw

# Icon definitions: (filename, draw_function)
# Each draw_function takes (draw, size) and draws the icon

def draw_clock(draw, size):
    # Draw a simple clock
    cx, cy = size//2, size//2
    r = size//2 - 4
    draw.ellipse((cx-r, cy-r, cx+r, cy+r), outline=(102,51,153,255), width=4)  # purple
    draw.line((cx, cy, cx, cy-r+8), fill=(102,51,153,255), width=4)  # hour hand
    draw.line((cx, cy, cx+r-8, cy), fill=(102,51,153,255), width=4)  # minute hand

def draw_shield(draw, size):
    # Draw a simple shield
    w, h = size, size
    points = [(w*0.2, h*0.2), (w*0.8, h*0.2), (w*0.7, h*0.7), (w*0.5, h*0.9), (w*0.3, h*0.7)]
    draw.polygon(points, outline=(102,51,153,255), fill=None, width=4)

def draw_power(draw, size):
    # Draw a power button
    cx, cy = size//2, size//2
    r = size//2 - 8
    draw.arc((cx-r, cy-r, cx+r, cy+r), start=45, end=315, fill=(102,51,153,255), width=4)
    draw.line((cx, cy-18, cx, cy+2), fill=(102,51,153,255), width=4)

def draw_chip(draw, size):
    # Draw a chip
    draw.rectangle((12, 12, 52, 52), outline=(102,51,153,255), width=4)
    for i in range(4):
        draw.line((8, 16+i*12, 12, 16+i*12), fill=(102,51,153,255), width=3)
        draw.line((52, 16+i*12, 56, 16+i*12), fill=(102,51,153,255), width=3)
        draw.line((16+i*12, 8, 16+i*12, 12), fill=(102,51,153,255), width=3)
        draw.line((16+i*12, 52, 16+i*12, 56), fill=(102,51,153,255), width=3)

def draw_puzzle(draw, size):
    # Draw a puzzle piece
    draw.rectangle((16, 16, 48, 48), outline=(102,51,153,255), width=4)
    draw.ellipse((40, 8, 56, 24), outline=(102,51,153,255), width=4)
    draw.ellipse((8, 40, 24, 56), outline=(102,51,153,255), width=4)

def draw_code(draw, size):
    # Draw code brackets
    draw.line((20, 16, 12, 32, 20, 48), fill=(102,51,153,255), width=4)
    draw.line((44, 16, 52, 32, 44, 48), fill=(102,51,153,255), width=4)

def draw_flow(draw, size):
    # Draw a simple pipeline/flowchart
    draw.rectangle((12, 24, 28, 40), outline=(102,51,153,255), width=4)
    draw.rectangle((32, 24, 48, 40), outline=(102,51,153,255), width=4)
    draw.line((28, 32, 32, 32), fill=(102,51,153,255), width=4)

def draw_rust(draw, size):
    # Draw a gear for Rust
    draw.ellipse((12, 12, 52, 52), outline=(102,51,153,255), width=4)
    for i in range(8):
        angle = i * 45
        x1 = 32 + 24 * __import__('math').cos(angle*3.14/180)
        y1 = 32 + 24 * __import__('math').sin(angle*3.14/180)
        x2 = 32 + 28 * __import__('math').cos(angle*3.14/180)
        y2 = 32 + 28 * __import__('math').sin(angle*3.14/180)
        draw.line((x1, y1, x2, y2), fill=(102,51,153,255), width=3)

def draw_cpp(draw, size):
    # Draw C++ symbol
    draw.rectangle((16, 16, 48, 48), outline=(102,51,153,255), width=4)
    draw.text((22, 22), 'C++', fill=(102,51,153,255))

def draw_freertos(draw, size):
    # Draw a simple RTOS block
    draw.rectangle((16, 16, 48, 48), outline=(102,51,153,255), width=4)
    draw.line((16, 32, 48, 32), fill=(102,51,153,255), width=3)
    draw.line((32, 16, 32, 48), fill=(102,51,153,255), width=3)

def draw_zephyr(draw, size):
    # Draw a stylized Z
    draw.line((16, 16, 48, 16, 16, 48, 48, 48), fill=(102,51,153,255), width=4)

# Add more draw functions as needed for the rest of the icon list

icons = [
    ("clock-realtime.png", draw_clock),
    ("shield-safety.png", draw_shield),
    ("power-lowpower.png", draw_power),
    ("chip-mcu.png", draw_chip),
    ("puzzle-modular.png", draw_puzzle),
    ("code-config.png", draw_code),
    ("flow-ci.png", draw_flow),
    ("rust.png", draw_rust),
    ("cpp.png", draw_cpp),
    ("freertos.png", draw_freertos),
    ("zephyr.png", draw_zephyr),
]

size = 64
for filename, draw_fn in icons:
    img = Image.new("RGBA", (size, size), (255, 255, 255, 0))
    draw = ImageDraw.Draw(img)
    draw_fn(draw, size)
    img.save(filename)
