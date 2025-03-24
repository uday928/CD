import re
def validate_username(username):
    # Username: 4-16 characters, only letters, digits, and underscores
    pattern = r'^[a-zA-Z0-9_]{4,16}$'
    return bool(re.match(pattern, username))

def validate_password(password):
    # Password: At least 8 characters, at least one uppercase letter, one lowercase letter, one digit, and one special character
    pattern = r'^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[^A-Za-z\d\s])(?=.*[A-Za-z\d\s]).{8,}$'
    return bool(re.match(pattern, password))

# Input and validation
username = input("Enter username: ")
password = input("Enter password: ")

if validate_username(username):
    print("Username is valid.")
else:
    print("Invalid username. It must be 4-16 characters and contain only letters, digits, and underscores.")

if validate_password(password):
    print("Password is valid.")
else:
    print("Invalid password. It must be at least 8 characters long and include an uppercase letter, a lowercase letter, a digit, and a special character.")

# Input:
# For valid:
# User_123
# StrongP@ss1
# For invalid:
# ab
# weakpass
