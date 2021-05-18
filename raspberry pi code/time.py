import datetime
import psutil
import requests

data_to_send = {}

x= datetime.datetime.now()
data_to_send["date"] = x.strftime("%X")


print(data_to_send)

r = requests.post("https://hook.integromat.com/yhyjrgmj768l58uubb2rohgdunpql6jl", json = data_to_send)

print(r.status_code)