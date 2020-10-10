from cs50 import get_int
# gerekli olan fonksiyon
# needed function

check = False

while check is False:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        check = True
    # input control
    # girdi kontrolu

# get input from user
# kullanicidan girdi alma

definer = 0
# used to align the pyramid
# piramidin terslemesi icin

# printing the pyramid
# piramit yazdiriliyor
for i in range(height):
    definer+=1
    print(" "*(height - definer), end="")
    print("#"*definer)

