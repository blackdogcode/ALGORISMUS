# https://www.acmicpc.net/problem/15874
alphabet = ('a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z')


def caesar_cipher(message, shift_amount):
    encrypted_message = []
    for char in message:
        if char.isalpha():
            curr_pos = alphabet.index(char.lower())
            shifted_pos = (curr_pos + shift_amount) % len(alphabet)
            shifted_char = alphabet[shifted_pos] if char.islower() else alphabet[shifted_pos].upper()
            encrypted_message.append(shifted_char)
        else:
            encrypted_message.append(char)

    return "".join(encrypted_message)


if __name__ == "__main__":
    shift_count, text_length = input().split()
    text = input()
    cipher_text = caesar_cipher(text, int(shift_count))
    print(cipher_text)

"""
if __name__ == "__main__":
    reader = open('test_input.txt', 'r')
    try:
        test_case = int(reader.readline())
        print(test_case)

        for test in range(test_case):
            shift_count, text_length = reader.readline().split()
            text = reader.readline().rstrip()
            cipher_text = caesar_cipher(text, int(shift_count))
            print(cipher_text)
    finally:
        reader.close()
"""