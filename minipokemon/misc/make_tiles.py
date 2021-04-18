from PIL import Image
import string
import os
dirname = os.path.dirname(__file__)

alphabet = string.ascii_uppercase + string.ascii_lowercase + string.digits + "\x00\x01"

alphabet = list(range(33,33+26)) # uppercase
alphabet += list(range(65,65+26)) # lowercase
alphabet += list(range(16,16+10)) # digits
alphabet += [91, 93] # braces
alphabet += [0, 1] # arrows
alphabet += [14] # dot

im = Image.open(os.path.join(dirname, 'tiles.png'))

with open(os.path.join(dirname, '../src/tiles.h'), 'w') as f:
    f.write('const uint8_t tile_count = 192;\n')
    f.write('const uint8_t _rom tiles[] _at(0x10000) = {\n')

    for i in alphabet:
        x = 8*(i%16)
        y = 8*(i//16)
        f.write("    ")
        for j in range(8):
            f.write("0x{:02x},".format(int("".join("0" if im.getpixel((x+j, y+k))[0] == 255 else "1" for k in range(8)[::-1]),2)))
        f.write('\n')

    for i in range(192-len(alphabet)):
        f.write("    "+"0x00,"*8+'\n')

    f.write('};\n')
