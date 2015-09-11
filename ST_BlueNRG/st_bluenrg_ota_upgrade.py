#!/usr/bin/python
# ST BlueNRG OTA upgrade python utility for Linux
# Reference protocol can be found at http://www.st.com/st-web-ui/static/active/cn/resource/technical/document/application_note/DM00115333.pdf
# Copyright (C) 2015 Shrenik Shikhare <engineershrenik@gmail.com>
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
# Note: gatttool must be installed before using this utility

import pexpect
import sys
import time
import os


os.system("sudo hciconfig hci0 down")
os.system("sudo hciconfig hci0 up")
os.system('clear');
print '=========================================================================='
print '============================ST BLE OTA UTILITY============================'
print '=========================================================================='
print '\nScanning BLE devices......'


os.system(" hcitool lescan > scan.txt & sleep 3 ;  pkill --signal SIGINT hcitool")
print 'Scanning is Done.....'
time.sleep(1)
scan = open("scan.txt","r")
readscan = scan.read()
print "Found Following BLE Device = " + readscan[12:29]


bluetooth_adr = readscan[12:29] #sys.argv[1]
tool = pexpect.spawn('gatttool -b ' + bluetooth_adr + ' -I -t random')
#print 'gatttool -b ' + bluetooth_adr + ' -I -t random'
print '\nGatttool is trying to connect to device.. '
tool.expect('\[LE\]>')
print "\nPreparing to connect. wait...:D"
tool.sendline('connect')
# test for success of connect
tool.expect('\[CON\].*>')
print "Connecting COMPUTER -> DEVICE"
tool.sendline('char-read-hnd 0x0012')   #old memory information
tool.expect('descriptor: .*') 
rval = tool.after.split()
rval = rval[1] + rval[2] + rval[3] + rval[4] + rval[5] + rval[6] + rval[7] + rval[8] 
print 'RECEIVED IMAGE INFO -> [0x' + rval+']'
#tool.expect('\[CON\]\[.+\]\[LE\]>')
#tool.expect('\[CON\].*>')

#Send New Image information
print '\nSENDING NEW IMAGE INFO => ' + bluetooth_adr 

#new_image_size = os.path.getsize('./test.bin')
new_image_size = str(hex(os.path.getsize('./test.bin')))
#print '\n NEW IMAGE SIZE = '+new_image_size 
new_image_info = '0x0000' + new_image_size[2:]


new_image_size = new_image_info[8]+new_image_info[9]+ new_image_info[6]+new_image_info[7]+new_image_info[4]+new_image_info[5]+ new_image_info[2]+new_image_info[3]

print 'NEW_IMAGE_SIZE = ' + new_image_size

tool.sendline('char-write-req 0x0014 0x'+ new_image_size+'00660008')



#tool.sendline('char-write-req 0x0014 0xffff010800660008')

print '\n\nGETTING IMAGE INFO <= ' + bluetooth_adr
tool.sendline('char-read-hnd 0x0014')
tool.expect('descriptor: .*') 
rval = tool.after.split()
rvalue = rval[5] + rval[4] + rval[3] + rval[2]
print 'WRITTEN FREE MEMORY => ['+ bluetooth_adr + '] = 0x' + rvalue

if( rvalue == new_image_info[2:] ):
    print '---MATCHED WRITTEN SIZE---'

rvalue = rval[9] + rval[8] + rval[7] + rval[6]
print 'WRITTEN STARTING ADDRESS => ['+ bluetooth_adr + '] = 0x' + rvalue

if( rvalue == '08006600'):
    print '---MATCHED BASE ADDRESS---'
    
    
print '\n\nSENDING BTL EXPECTED IMAGE SEQUENCE CHARACTERISTICS'
tool.sendline('char-write-cmd 0x0019 0100 --listen')
tool.expect('value:.*') 
rval = tool.after.split()
print 'GOT NOTIFIED FROM DEVICE '+bluetooth_adr+' = 0x'+rval[1] +rval[2]+rval[3] +rval[4]
#time.sleep(5)
if (rval[3] == '0f'):
    print 'ERROR FLASH ERASE'
else:
    print 'FLASH ERASED SUCCESSFULLY\n'

#add your file path instead of test.bin
f = open('test.bin','rb')
try:

    fw_image16 = []
        #we loop to upload image in advance and count for size rather than working with openfile and relying on os.path.getsize(filename)
    cnt=0
    imageWord16b = 0
    while 1:
        byte = f.read(1)
        if byte != "":
            imageWord16b += (ord(byte) << ((cnt%16)*8))
            if ((cnt+1)%16 == 0) :
                fw_image16.append(imageWord16b)
                imageWord16b = 0
            cnt+=1
        else:
            if ((cnt%16)!=0) :
                fw_image16.append(imageWord16b)
     
                print "image size is:"
                print cnt
                print "16 byte wise size:"
                print len(fw_image16)

            if ((base_address < flash_LB) or ((base_address+cnt) > flash_UB) or ((base_address%512)!=0)):
                message_reporter("Image above free memory range or base address is not 512 byte aligned")

                #return
            break
except:
        pass

f.close()

    
OTA_ACK_EVERY = 1
characSize = 16
roundedImgSize = (len(fw_image16) * characSize) #os.path.getsize('test.bin')
SeqNum = 0
retriesForChesumError = 0
retriesForSequenceError = 0
retriesForMissedNotification = 0
retriesOnSPI = 0
consecutiveRetries = 0
#fw_image16 =[]
#fw_image16 = f.read()

f = open('test.bin','rb')

a = []
def createStruct1(seq, cs , ack):
        cnt = 0
        for x in range(0,17):
		if(cnt != 16):
                	byte = f.read(1)
		else:
			byte = '\0'
                if(byte != ""):
                        if(cnt%16 == 0): #and cnt != 0):
                                #print ''.join(a)
                                #print str(a)+ c + d
                                packet =  cs + ''.join(a) + ack + seq[2]+ seq[3]+ seq[0]+ seq[1] #seq[1]+seq[0]
                                if (cnt != 0):
                                        print packet
                                	del a[:]
					return packet
                                cnt = 0
                                #print c+'  ' + d
                                #packet = c + a + d
                                #print packet
                                #return a
                                #bleFormat()
                        conv = '{:02x}'.format(ord(byte))
                        a.append(conv)
                        cnt = cnt+1

del a[:]
def createStruct(seq,cs, ack):
        cnt = 0
        for x in range(0,16):
                byte = f.read(1)
                #if(byte != ""):
                if(cnt%16 == 0): #and cnt != 0):
                        #print a
                        #print ''.join(a)
			packet = cs + ''.join(a) + ack + seq[2]+ seq[3]+ seq[0]+ seq[1]
                        return packet
			#print str(a)+ c + d
                                #packet =  ''.join(a) + d + c[0]+c[1]+c[2]+c[3]
                                #if (cnt != 0):
                                #       print packet
                        cnt = 0
                                #print c+'  ' + d
                                #packet = c + a + d
                                #print packet
                                #return a
                                #bleFormat()
                        del a[:]
                conv = '{:02x}'.format(ord(byte))
                a.append(conv)
                cnt = cnt+1




while((SeqNum * characSize) < roundedImgSize):
    checksum = 0
    
    prevSeqNum = SeqNum
    needsACK =  (((SeqNum+1)%(OTA_ACK_EVERY)) == 0) or (((SeqNum+1) * characSize) == roundedImgSize)
    #print hex(fw_image16[SeqNum])
    ImgPayload = (SeqNum<<144) + ((int(needsACK))<<136) + (fw_image16[SeqNum] << 8)
    for k in range(19):
        checksum ^= ((ImgPayload >> (8*(k+1))) & 0xFF)
    #print 'Checksum = '+ hex(checksum)
    CheckedImgPayload = ImgPayload + checksum
    #sendPayload = '%x' % CheckedImgPayload
    #sendPayload = '0x' + sendPayload
    #print hex(ImgPayload)
   # print "***********************************************"
    #print hex(fw_image16[])
    #print "SeqNum:" + hex(SeqNum) + '   needsACK:'+ hex(needsACK) + '   payload: ['+ hex(fw_image16[SeqNum]) +'] checksum:'+ hex(checksum)
    
    payload_SeqNum = '{:04x}'.format(SeqNum)
    payload_needsACK = '{:02x}'.format(needsACK)
    payload_CheckSum = '{:02x}'.format(checksum)
    print 'Seq Number '+payload_SeqNum
    ble_payload = createStruct1(payload_SeqNum, payload_CheckSum, payload_needsACK)
    #tool.sendline('char-write-req 0x0016 b3d8090020652c0008fd2a0008ff2a0008010000') # '+ sendPayload)
    tool.sendline('char-write-req 0x0016 '+ ble_payload) # '+ sendPayload)
    tool.expect('value:.*') 
    rval = tool.after.split()
    print 'GOT NOTIFIED FROM DEVICE '+bluetooth_adr+' = 0x'+rval[1] +rval[2]+rval[3] +rval[4]
    if (rval[3] =='0f'):    #Check if error in notification
        print '*****ERROR IN PACKET'
        break
    
    SeqNum += 1

