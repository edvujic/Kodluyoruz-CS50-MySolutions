from cs50 import get_float
import numpy as np
# get the function
# fonksiyonu al

def get_coins(dollars):
    
    # get quarters
    # yirmi-bes centlik demir paralari bul
    quarters = dollars // 25
    remainder = dollars % 25

    # get dime
    # on centlik demir paralari bul
    dime = remainder // 10
    remainder = remainder % 10

    # get nickle
    # bes centlik demir paralari bul
    nickle = remainder // 5
    remainder = remainder % 5

    # the remainder is the number of pennies
    # kalan (remainder) bir centlik demir paralari ifade ediyor
    return quarters + dime + nickle + remainder


check = False
while check is False:
    dollars = get_float("Change owed: ")
    if dollars > 0:
        check = True
# be sure of proper usage
# dogru kullanimdan emin ol

# round float to two decimal points
# float degiskenini virgulend sonra iki basamaga kadar yuvarla
dollars = np.round(dollars, 3)
# change to cents
# cent'lere cevir
dollars = int(dollars*100)

# print the number of coins
# kullanilan demir para sayisini yazdir
print(get_coins(dollars))
