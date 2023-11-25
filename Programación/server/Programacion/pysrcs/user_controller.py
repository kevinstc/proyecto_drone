import MySQLdb
import math
import numpy as np
import random
from scipy import integrate
import matplotlib.pyplot as plt
import keyboard  # using module

forward_step = 1;
backward_step = 1;
left_step = 1;
right_step = 1;
up_step = 1;
down_step = 1;


def sat(v):
    if v>999:
      return 999;
    elif v< 1:
      return 0;
    else:
      return v

    
def send_data(v1,v2,v3,v4):
    db=MySQLdb.connect("localhost","root","12345678","data_sensors_and_esc")
    db_exe=db.cursor()
    sqlquery= "UPDATE ESCs SET ESC01  =%s, ESC02 =%s, ESC03 =%s, ESC04 =%s  WHERE ID=1"
    values = (sat(v1),sat(v2),sat(v3),sat(v4)) 
    db_exe.execute(sqlquery, values)
    db.commit()
    db.close()
    return 0
def get_values():
    db=MySQLdb.connect("localhost","root","12345678","data_sensors_and_esc")
    db_exe=db.cursor()
    db_exe.execute("SELECT ESC01,ESC02,ESC03,ESC04 FROM ESCs  WHERE ID = 1")
    data = db_exe.fetchall()
    db.commit()
    db.close()
    return data

while True:  
        if keyboard.is_pressed('w'):   
            sps = get_values()
            print(sps) 
            send_data(sps[0][0]-forward_step,sps[0][1]-forward_step,sps[0][2],sps[0][3])
        elif keyboard.is_pressed('s'):  
             sps = get_values()
             print(sps) 
             send_data(sps[0][0],sps[0][1],sps[0][2]-backward_step,sps[0][3]-backward_step)
        elif keyboard.is_pressed('a'):  
             sps = get_values()
             print(sps) 
             send_data(sps[0][0]-left_step,sps[0][1],sps[0][2]-left_step,sps[0][3])
        elif keyboard.is_pressed('d'):  
             sps = get_values()
             print(sps) 
             send_data(sps[0][0],sps[0][1]-right_step,sps[0][2],sps[0][3]-right_step)
        elif keyboard.is_pressed('U'):  
             sps = get_values()
             print(sps) 
             send_data(sps[0][0]+up_step,sps[0][1]+up_step,sps[0][2]+up_step,sps[0][3]+up_step)
        elif keyboard.is_pressed('J'):  
             sps = get_values()
             print(sps) 
             send_data(sps[0][0]-down_step,sps[0][1]-down_step,sps[0][2]-down_step,sps[0][3]-down_step)    
        elif keyboard.is_pressed('P'):
                break
        
