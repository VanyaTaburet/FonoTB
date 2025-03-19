import asyncio
import websockets

connected = set()

async def echo(websocket, path):
    connected.add(websocket)
    try:
        async for message in websocket:
            print(f"Received message: {message}")
            if connected:
                await asyncio.wait([ws.send(message) for ws in connected])
    finally:
        connected.remove(websocket)

start_server = websockets.serve(echo, "localhost", 12345)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()

