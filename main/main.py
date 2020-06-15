# This code is based on dethi's original league automated authentication

import serial
import subprocess
import base64, requests, json


UID = '' # fill out the rfid card here

def getLockfile():
    '''Get Riot lockfile - necessary for client-specific info.'''
    raw_output = subprocess.check_output(['wmic', 'PROCESS', 'WHERE', "name='RiotClientUx.exe'", 'GET', 'commandline']).decode('utf-8')
    app_port = raw_output.split('--app-port=')[-1].split(' ')[0]
    auth_token = raw_output.split('--remoting-auth-token=')[-1].split(' ')[0]
    return app_port, auth_token
    
def createConnectionHeader():
    port, password = getLockfile()
    url = "https://127.0.0.1:" + port
    baseString = "riot:" + password
    auth = "Basic " + base64.b64encode(baseString.encode()).decode()
    rqheader = {
        'Authorization': auth,
    }
    return url, rqheader

if __name__ == "__main__":
    
    ser = serial.Serial('COM4', 9600)
    ser.flushInput()
    
    while True:
        try:
            ser_byte = ser.readline()
            if 'Open client'.encode() in ser_byte:
                subprocess.call(['C:\\Riot Games\\League of Legends\\LeagueClient.exe']) # change this directory to the place where you actually run League from
            if 'Card UID:'.encode() in ser_byte:
                auth = ser_byte.split(': '.encode())[1] == UID.encode()
                if auth:
                    url, rqheader = createConnectionHeader()
                    
                    with open('login.json', 'r+') as json_file:
                        obj = json.loads(json_file.read())

                    r = requests.post(url + '/rso-auth/v2/authorizations', headers=rqheader, json=obj['auth'], verify=False)
                    r = requests.put(url + '/rso-auth/v1/session/credentials', headers=rqheader, json=obj['login'], verify=False)

        except KeyboardInterrupt as e:
            print(e)
            break



