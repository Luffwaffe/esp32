import socket

# Server settings
HOST = '127.0.0.1'  # localhost
PORT = 1234         # same port the client will connect to

# Create a socket (IPv4, TCP)
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind to address and port
server_socket.bind((HOST, PORT))

# Start listening (max 1 queued connection)
server_socket.listen(1)
print(f"Server listening on {HOST}:{PORT}...")

# Accept a connection
conn, addr = server_socket.accept()
print(f"Connected by {addr}")

with conn:
    while True:
        data = conn.recv(1024)
        if not data:
            break  # client disconnected
        print(f"Received: {data.decode()}")

        # Send response
        if data.decode() == "getRunningStatus\n":
            conn.sendall(b"ended")
        elif data.decode() == "start\n":
            conn.sendall(b"started")
        elif data.decode() == "end\n":
            conn.sendall(b"ended")
        else:
            conn.sendall(b"unknown command")

# Close server socket
server_socket.close()
