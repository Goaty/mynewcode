 
import hmac
import hashlib
import array
import time
import unittest
import json
import requests
import httplib, urllib
#import http.client
def HOTP(K, C, digits=6):
    
    C_bytes = _long_to_byte_array(C)
    hmac_sha1 = hmac.new(key=K, msg=C_bytes,
                         digestmod=hashlib.sha1).hexdigest()
    return Truncate(hmac_sha1)[-digits:]
 
 
def TOTP(K, digits=6, window=30):
 
    C = long(time.time() / window)
    return HOTP(K, C, digits=digits)
 
 
def Truncate(hmac_sha1):
    
    offset = int(hmac_sha1[-1], 16)
    binary = int(hmac_sha1[(offset * 2):((offset * 2) + 8)], 16) & 0x7fffffff
    return str(binary)
 
 
def _long_to_byte_array(long_num):
    
    byte_array = array.array('B')
    for i in reversed(range(0, 8)):
        byte_array.insert(0, long_num & 0xff)
        long_num >>= 8
    return byte_array
from otpauth import OtpAuth
import base64
import httplib, urllib
#auth = OtpAuth('HDECHALLENGE001')  # a secret string
#password = auth.totp()
password=TOTP('HDECHALLENGE001')
authorize=base64.b64encode('duchuy1992@kaist.ac.kr'+':'+str(password));
authorize_header='Basic '+authorize
#print authorize
host = "hdegip.appspot.com"
jstring={'github_url': 'https://github.com/Goaty/mynewcode','contact_email':'duchuy1992@kaist.ac.kr'}
params=json.dumps(jstring);
print params
headers = { 
'Authorization': authorize_header,
'Host': 'hdegip.appspot.com',
'Accept': '*/*',
'Content-Type': 'application/json',
'Content-Length': 95
}
url = '/challenge/001/endpoint'

# POST the request
conn = httplib.HTTPConnection(host)
conn.request('POST',url,params,headers)

#r=requests.post(url,data=params,headers=headers)
#t = requests.get('http://hdegip.appspot.com/challenge/001/endpoint')
#print t.status_code
response = conn.getresponse()
data = response.read()
#print data
#data = json.dumps({'name':'test', 'description':'some test repo'})
print data
conn.close()
