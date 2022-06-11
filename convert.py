#!/usr/bin/env python3

import sys

f = open(sys.argv[1], "rb")
data = f.read()
f.close()

o = open("image.c", "w")

width = 640
height = 350

o.write("static unsigned char bmp_image[] = {\n");

offset = 0x36
for y in range(0, height):
  for x in range(0, width):
    b = data[offset+0]
    g = data[offset+1]
    r = data[offset+2]

    new_b = ((b>>6)&3)
    new_g = ((g>>6)&3)
    new_r = ((r>>6)&3)

    color = (new_r<<4)|(new_g<<2)|(new_b<<0)

    o.write('0x%02X' % color)
    o.write(", ")

    offset = offset + 3
  o.write("\n")

o.write("};\n")
o.close()
