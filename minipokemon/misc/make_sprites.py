from PIL import Image, ImageFont, ImageDraw, GifImagePlugin
import string
import os
dirname = os.path.dirname(__file__)

def write_sprite(f, image, offset):
    x,y = offset
    # mask
    f.write("    ")
    for j in range(8):
        f.write("0x{:02x},".format(int("".join("0" if image.getpixel((x+j, y+k))[3] > 0 else "1" for k in range(8)[::-1]),2)))
    for j in range(8):
        f.write("0x{:02x},".format(int("".join("0" if image.getpixel((x+j, y+k))[3] > 0 else "1" for k in range(8,16)[::-1]),2)))
    f.write('\n')
    # draw
    f.write("    ")
    for j in range(8):
        f.write("0x{:02x},".format(int("".join("0" if image.getpixel((x+j, y+k))[0] > 0 else "1" for k in range(8)[::-1]),2)))
    for j in range(8):
        f.write("0x{:02x},".format(int("".join("0" if image.getpixel((x+j, y+k))[0] > 0 else "1" for k in range(8,16)[::-1]),2)))
    f.write('\n')
    # mask
    f.write("    ")
    for j in range(8):
        f.write("0x{:02x},".format(int("".join("0" if image.getpixel((x+j+8, y+k))[3] > 0 else "1" for k in range(8)[::-1]),2)))
    for j in range(8):
        f.write("0x{:02x},".format(int("".join("0" if image.getpixel((x+j+8, y+k))[3] > 0 else "1" for k in range(8,16)[::-1]),2)))
    f.write('\n')
    # draw
    f.write("    ")
    for j in range(8):
        f.write("0x{:02x},".format(int("".join("0" if image.getpixel((x+j+8, y+k))[0] > 0 else "1" for k in range(8)[::-1]),2)))
    for j in range(8):
        f.write("0x{:02x},".format(int("".join("0" if image.getpixel((x+j+8, y+k))[0] > 0 else "1" for k in range(8,16)[::-1]),2)))
    f.write('\n')

chars = "ENTER FLAG" + "CORRECT!"
font = ImageFont.truetype(os.path.join(dirname, 'ThaleahFat.ttf'), 16)
im = Image.new('RGBA', (16*len(chars),16), color=(0,0,0,0))
draw = ImageDraw.Draw(im)
for i in range(len(chars)):
    draw.text((i*16,0), chars[i], font=font, fill=(0,0,0,255))

smoll = Image.open(os.path.join(dirname, 'smoll.png')).convert(mode="RGBA")

with open(os.path.join(dirname, '../src/sprites.h'), 'w') as f:
    f.write('const uint8_t _rom sprites[] _at(0x20000) = {\n')

    for i in range(len(chars)):
        write_sprite(f, im, (16*i, 0))

    for j in range(5*8):
        for k in range(3):
            write_sprite(f, smoll, (j*16, k*16))

    f.write('};\n')
