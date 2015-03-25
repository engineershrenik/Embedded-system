import socket
import win32com.client, time

googleEarth =  win32com.client.Dispatch("GoogleEarth.ApplicationGE")
while not googleEarth.IsInitialized():
    time.sleep(0.5)
    print "waiting for Google Earth to initialize"
	
latitude=41.487942                            # Latitude in degrees. Between -90 and 90.
longitude=0#-81.6865                            # Longitude in degrees. Between -180 and 180. to rotate the earth
altitude=1000  			     # in meters
tilt=0  # looking to the horizon=90, looking to the center of Earth=0
azimuth=370  # looking North=0, East=90, South=180, West=270
speed=0.5  	 # speed transition. must be >= 0, above 5.0 the transition is instantaneous
range=0              # If not=0 camera will move backward from "range meters along the camera axis
altMode=1  #Altitude mode that defines altitude reference origin (1=above ground, 2=absolute)
focusDistance=10000000  #Zoom Value can be changed
	
TCP_IP = '127.0.0.1'
TCP_PORT = 5005
BUFFER_SIZE = 20  # Normally 1024, but we want fast response
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)
conn, addr = s.accept()
print 'Connection address:', addr
while 1:
	
	data = conn.recv(BUFFER_SIZE)
	if not data: break
	#print "received data:", data
	#focusDistance=0
	#data=0
	if data == "DRIGHT":
		print "Right Direction longitude = ", longitude
		if longitude <= 180:
			longitude = longitude-10
		if longitude == -180:
			longitude = 180
		
	elif data == "DLEFT":
		if longitude >= -180:
			longitude = longitude+10
		if longitude == 180:
			longitude = -180
		print "Left Direction longitude = ", longitude
	elif data == "DUP":
		if tilt > 10:
			tilt = tilt - 10 
		if tilt == 0:
			tilt = 90
		print "Up Direction tilt = ", tilt
	elif data == "DDOWN":
		if tilt < 90:
			tilt = tilt + 10 
		if tilt == 90:
			tilt = 0
		
		print "Down Direction tilt = ", tilt
	elif data[0] == 'Z':
		print "Z data Direction"
		data = data[1:6]
		focusDistance = (int(data))
		print 'focus_distance z = ', focusDistance
    #conn.send(data)
	#conn.close()
	googleEarth.SetCameraParams (latitude, longitude, altitude, altMode, focusDistance, tilt, azimuth, speed)
	cam=googleEarth.GetCamera(True)       # returns a ICameraInfoGE  object