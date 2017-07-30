from flask import Flask, render_template, request, jsonify
from flask_socketio import SocketIO, send, emit

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'

socketio = SocketIO(app)
@app.route("/bohin")
def web1():
	return render_template('bohin.html')

@app.route("/data/<temp>/<humi>")
def getdata(temp,humi):
	print("Temperature:%s Humidity:%s"%(temp,humi))
	#socketio.emit('s2c_temp',temp)
	#socketio.emit('s2c_humi',humi)
	return "OK"

if __name__ == "__main__":
	socketio.run(app)