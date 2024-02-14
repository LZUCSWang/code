def get_str(n):
    return chr(n%36-10+ord('a'))
print(get_str(26))