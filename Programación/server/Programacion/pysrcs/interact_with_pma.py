import MySQLdb
import math
import numpy as np
import random
from scipy import integrate
import matplotlib.pyplot as plt
db=MySQLdb.connect("localhost","root","12345678","data_sensors_and_esc")
db_exe=db.cursor()
# Constant Values

db_exe.execute("SELECT pos,speed,acel FROM data_sensors  WHERE ID = 1")
data = db_exe.fetchall()
print(data)
# Getting Data Sensors from local Database
pos = data[0][0]
speed = data[0][1]
acel = data[0][2]

# LQR Design applied to sensor data

# Getting u1,u2,u3,u4
w1 = 192.3*pos
w2 = 200.4*speed
w3 = 23.3*acel
w4 = 43.2
# Converting to w1,w2,w3,w4

def conv2suitrange(n):
    return 0

def sat(v):
    if v>999:
      return 999;
    elif v< 10:
      return 10;
    else:
      return round(v);
v1 = sat(w1)
omega_1 = sat(w1)
omega_2 = sat(w2)
omega_3 = sat(w3)
omega_4 = sat(w4)


# Insert Speed into phpmyadmin DataBase using MySQL 

sqlquery= "UPDATE ESCs SET ESC01  =%s, ESC02 =%s, ESC03 =%s, ESC04 =%s  WHERE ID=1"
values = (omega_1,omega_2,omega_3,omega_4) 
db_exe.execute(sqlquery, values)
db.commit()
db.close()
#db_exe.close() 
