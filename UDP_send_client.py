import socket

def send_broadcast(message, port=9999):
    # Create a UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    
    # Enable broadcasting mode
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    
    # Set a timeout so the socket does not block indefinitely
    sock.settimeout(0.2)
    
    # Send the broadcast message
    sock.sendto(message.encode('utf-8'), ('255.255.255.255', port))
    print(f"Broadcast message sent: {message}")

# Example usage
send_broadcast("Room1", port=9999)
