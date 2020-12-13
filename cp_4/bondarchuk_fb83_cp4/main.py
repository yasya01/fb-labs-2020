import random


def gorner(a, b, n):
    b = int(str(bin(b))[2:])
    y = 1
    for i in str(b):
        y = pow(y, 2, n)
        y = (y * a ** int(i)) % n
    return y

def gcd_ex(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        d, x, y = gcd_ex(b % a, a)
    return (d, y - (b // a) * x, x)

def mod_reverse(a, m):
    d, x, y = gcd_ex(a, m)
    if d != 1:
        print("no solution")
        return 0
    else:
        x = (x % m + m) % m
        return x

def millera_rabina(n, k):
    if n == 3 or n == 2:
        return True
    if n < 2 or n % 2 == 0:
        return False
    else:
        t = n - 1
        s = 0
        while t % 2 == 0:
            t = t // 2
            s += 1
        for i in range(k):
            a = random.randrange(2, n - 2)
            x = pow(a, t, n)
            if x == 1 or x == n - 1:
                continue
            for i in range(1, s):
                x = pow(x, 2, n)
                if x == 1:
                    return False
                if x == n - 1:
                    break
            if x != n - 1:
                return False
        return True

def GenerateKeyPair():
    p_and_q = []
    k = 10
    res = False
    while res == False:
        p = random.getrandbits(256)
        res = millera_rabina(p, k)
    p_and_q.append(p)
    res = False
    while res == False:
        q = random.getrandbits(256)
        res = millera_rabina(q, k)
    p_and_q.append(q)
    return p_and_q

def Encrypt(message, e, n):
    if len(message) > n - 1:
        print('Long message')
        return 0
    c_message = []
    # text = ''
    for i in message:
        j = pow(int(i), e, n)
        c_message.append(j)
    return c_message

def Decrypt(c_message, d, n):
    d_message = []
    for i in c_message:
        lit = gorner(int(i), d, n)
        d_message.append(lit)
    return d_message

def Sign(message, d, n):
    signature = []
    for i in message:
        s = gorner(int(i), d, n)
        signature.append(s)
    return signature

def Verify(signature, e, n, message):
    m_s_text = ''
    message_t = ''
    m_s = Encrypt(signature, e, n)
    for i in m_s:
        m_s_text += str(i)
    for i in message:
        message_t += str(i)
    if m_s_text == message_t:
        return True
    else:
        return False

def SendKey(e, n1, k): # Аліса відправляє n, e  k == message
    si_text = []
    p_and_q = GenerateKeyPair() #Aліса генерує свою пару
    n = p_and_q[0] * p_and_q[1]
    while n > n1:
        p_and_q = GenerateKeyPair()
        n = p_and_q[0] * p_and_q[1]
    f = (p_and_q[0] - 1) * (p_and_q[1] - 1)
    d = mod_reverse(e, f)
    message = Encrypt(k, e, n1)
    si = Decrypt(k, d, n)
    signature = Sign(si, e, n1)
    return message, signature, n

def ReceiveKey(message, signature, e, n): # Боб отримує повідомлення і розшифровує
    text = Decrypt(message, d1, n1)
    d_signature = Decrypt(signature, d1, n1)
    rs = Verify(d_signature, e, n, text)
    return text, rs


if __name__ == "__main__":

    text = '373'
    e = 2 ** 16 + 1
    p_and_q = GenerateKeyPair()  # Боб генерує свою пару
    f = (p_and_q[0] - 1) * (p_and_q[1] - 1)
    d1 = mod_reverse(e, f)
    n1 = p_and_q[0] * p_and_q[1]

    print('Аліса відправляє зашифрований текст з підписом')
    message, signature, n = SendKey(e, n1, text)
    print(message)
    print('Боб розшифровує та верифікує')
    t, res = ReceiveKey(message, signature, e, n)
    print(t, res)


    #Перевірка на сайті

    print('Key: ')
    #text = random.randint(1, 965)
    k = 79
    k = str(k)
    e = 2 ** 16 + 1
    n1 = (int('A0E773F0BA65E5FE40B8495F94EC0A5231CC838CAE16A30681ED71B11C9CE3F6642F7C169E20B6C7E374D531ED1CF975A0D30858DDC9888BFD9C06082F6B152E801',16))
    mes, sign, n = SendKey(e, n1, k)
    m = ' '
    s1 = ''
    for i in mes:
        m += str(i)
    for i in sign:
        s1 += str(i)
    print(hex(int(m)))
    print(hex(int(s1)))
    print(hex(n))



























