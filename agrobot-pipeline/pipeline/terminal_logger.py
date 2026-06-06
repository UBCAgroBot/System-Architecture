import sys
import time

class Logger:
    def __init__(self, filepath="outputs/terminal_log.txt"):
        self.terminal = sys.stdout
        self.log_file = open(filepath, 'w')
    
    def write(self, message):
        self.terminal.write(message)
        if message.strip():
            timestamp = time.strftime("%H:%M:%S")
            self.log_file.write(f"[{timestamp}] {message}")
        else:
            self.log_file.write(message)
        self.log_file.flush()

    def flush(self):
        self.terminal.flush()
        self.log_file.flush()

    def close(self):
        self.log_file.close()