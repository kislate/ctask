import subprocess
import platform

def ping(host):
    """
    Ping a host and return True if it responds, False otherwise.
    """
    # Determine the platform to adjust the ping command accordingly
    param = '-n' if platform.system().lower() == 'windows' else '-c'
    
    # Building the command. Ex: "ping -c 1 google.com" or "ping -n 1 google.com"
    command = ['ping', param, '1', host]
    
    # Run the command
    try:
        output = subprocess.check_output(command, stderr=subprocess.STDOUT, universal_newlines=True)
        if "unreachable" in output.lower():
            return False
        else:
            return True
    except subprocess.CalledProcessError:
        return False

if __name__ == "__main__":
    host = input("Enter the host to ping: ")
    if ping(host):
        print(f"{host} is reachable.")
    else:
        print(f"{host} is not reachable.")