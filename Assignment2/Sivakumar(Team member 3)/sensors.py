import random
temp = random.randint(1,1000)
hum = random.randint(1,1000)

if temp > 500:
    print(temp,end=" - ")
    print("Alarm is ON")
else:
    print(temp,end=" - ")
    print("Alarm is OFF")