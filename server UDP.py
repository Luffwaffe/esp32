import socket

DISCOVERY_PORT = 9999
TCP_PORT = 12345
ROOM_NAME = b"Room1"

def run_udp_discovery_server():
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    udp_socket.bind(('', DISCOVERY_PORT))
    print(f"[UDP] Listening for discovery on port {DISCOVERY_PORT}...")

    while True:
        data, addr = udp_socket.recvfrom(1024)
        print(f"[UDP] Received from {addr}: {data}")

        if data == ROOM_NAME:
            udp_socket.sendto(ROOM_NAME, addr)
            print(f"[UDP] Sent response to {addr[0]}")
            break  # Discovery done, exit loop and close socket

    udp_socket.close()
    return addr[0]  # Return IP of client to connect via TCP


def run_tcp_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('', TCP_PORT))
    server_socket.listen(1)
    print(f"[TCP] Server listening on port {TCP_PORT}...")

    conn, addr = server_socket.accept()
    print(f"[TCP] Connected by {addr}")

    with conn:
        while True:
            data = conn.recv(1024)
            if not data:
                break
            msg = data.decode().strip()
            print(f"[TCP] Received: {msg}")

            if msg == "start":
                conn.sendall(b"started")
            elif msg == "end":
                conn.sendall(b"ended")
            elif msg == "getRunningStatus":
                conn.sendall(b"ended")
            else:
                conn.sendall(b"unknown command")

    server_socket.close()
    print("[TCP] Connection closed.")


if __name__ == "__main__":
    try:
        print("[SERVER] Starting UDP discovery...")
        client_ip = run_udp_discovery_server()
        print(f"[SERVER] Discovery complete. Client at {client_ip}")
        run_tcp_server()
    except KeyboardInterrupt:
        print("\n[SERVER] Shutting down.")
