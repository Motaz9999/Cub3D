import os
import re

libft_dir = "libft"

for file in os.listdir(libft_dir):
    if not file.endswith(".c"): continue
    path = os.path.join(libft_dir, file)
    with open(path, "r") as f:
        content = f.read()

    # The 42 header is typically 11 lines.
    # We can isolate the 42 header and then clean the rest of the body.
    lines = content.split('\n')
    header = '\n'.join(lines[:12])
    body = '\n'.join(lines[12:])
    
    # 1. Remove all C-style block comments /* ... */ from the body
    body = re.sub(r'/\*.*?\*/', '', body, flags=re.DOTALL)
    
    # 2. Remove all unclosed C-style block comments specifically at the end of the file
    body = re.sub(r'/\*.*', '', body, flags=re.DOTALL)
    
    # 3. Remove all single-line C++ style comments // ...
    body = re.sub(r'//.*', '', body)

    # 4. Remove consecutive empty lines
    body = re.sub(r'\n{3,}', '\n\n', body)
    
    # 5. Ensure file ends with exactly one newline
    body = body.rstrip() + '\n'

    with open(path, "w") as f:
        f.write(header + '\n' + body)

print("Formatting applied.")
