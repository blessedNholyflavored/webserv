import cgi
import sys

form = cgi.FieldStorage()

f = open(".tmp", "r")
print("----------------------")
f = f.read()
f = f.split("f_name=", 1)[-1]
f = f.split("&")
s1 = f[0]
s2 = f[1]
s2 = s2.split("s_name=")
s2 = s2[1]


try:
    f_name=s1
except :
    f_name=' First name is blank ' 
	
try:
    s_name=s2
except :

    
    s_name=' Second name is blank ' 

print("<br><b>First Name</b>",f_name)
print("<br><b>Second Name</b>",s_name)

