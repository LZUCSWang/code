        elif source[i].isdigit():  # Number
            token = ""
            while i < len_source and len(token) < 9 and source[i].isdigit():
                token += source[i]
                i += 1
            if len(token) <= 8 and (token == '0' or token.startswith('0') or int(token) < 0 or int(token) > 2):
                output.append((token, "invalid constant"))
            else:
                output.append((token, "constant"))