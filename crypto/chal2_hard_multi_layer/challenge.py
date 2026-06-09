
from Crypto.Cipher import AES
from hashlib import sha256
import base64

def custom_encode(data):
    return base64.b64encode(data[::-1])

key_seed = b"hidd" + b"en_" + b"seed"
key = sha256(key_seed).digest()[:16]

cipher = AES.new(key, AES.MODE_ECB)

# encrypted output only given
