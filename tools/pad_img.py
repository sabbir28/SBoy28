import sys
import os

def pad_file(filename, min_size):
    try:
        if not os.path.exists(filename):
            print(f"File not found: {filename}")
            sys.exit(1)
            
        file_size = os.path.getsize(filename)
        if file_size < min_size:
            with open(filename, "ab") as f:
                f.write(b'\x00' * (min_size - file_size))
            print(f"Successfully padded {filename} to {min_size} bytes")
        else:
            print(f"{filename} is already {file_size} bytes (min {min_size})")
    except Exception as e:
        print(f"Failed to pad {filename}: {e}")
        sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python pad_img.py <filename> <min_size>")
        sys.exit(1)
    
    filename = sys.argv[1]
    try:
        min_size = int(sys.argv[2])
    except ValueError:
        print("min_size must be an integer")
        sys.exit(1)
        
    pad_file(filename, min_size)
