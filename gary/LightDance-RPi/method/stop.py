from .baseMethod import BaseMethod


# Stop
class Stop(BaseMethod):
    def method(self, payload=None):
        response = self.socket.send("stop")
        return response
