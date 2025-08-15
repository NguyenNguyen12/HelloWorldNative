import sys
import re

def replace_word_in_file(filename, original, replacement):
    try:
        # Read file content
        with open(filename, 'r') as file:
            code = file.read()

        # If the original is 'char', handle carefully to avoid replacing 'unsigned char'
        if original == 'char':
            # Avoid replacing 'signed char' or 'unsigned char'
            pattern = r'(?<!signed\s)(?<!unsigned\s)\bchar\b'
        else:
            # Generic whole-word match
            pattern = r'\b' + re.escape(original) + r'\b'

        # Replace
        modified_code = re.sub(pattern, replacement, code)

        # Write back to file
        with open(filename, 'w') as file:
            file.write(modified_code)

        print(f"Replaced '{original}' with '{replacement}' in {filename}")

    except FileNotFoundError:
        print(f"File not found: {filename}")
    except Exception as e:
        print(f"Error: {e}")

# --- Main ---
if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python replace_in_file.py <filename> <original_string> <replacement_string>")
        sys.exit(1)

    filename = sys.argv[1]
    original = sys.argv[2]
    replacement = sys.argv[3]

    replace_word_in_file(filename, original, replacement)
