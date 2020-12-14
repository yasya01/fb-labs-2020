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
        #print(hex(n))
        #print('not prime')
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
                    #print(hex(n))
                    #print('miller-robin test failed')
                    return False
                if x == n - 1:
                    break
            if x != n - 1:
                #print(hex(n))
                #print('miller-robin test failed')
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
    si = Sign(k, d, n)
    signature = Encrypt(si, e, n1)
    return message, signature, n

def ReceiveKey(message, signature, e, n): # Боб отримує повідомлення і розшифровує
    text = Decrypt(message, d1, n1)
    d_signature = Decrypt(signature, d1, n1)
    rs = Verify(d_signature, e, n, text)
    return text, rs



def Encrypt_site(message, e, n):
    if message > n - 1:
        print('Long message')
        return 0
    c_message = pow(message,e,n)
    return c_message

def Sign_site(message, d, n):
    signature = pow(message,d,n)
    return signature



def SendKey_site(e1, n1, k): # Аліса відправляє n, e  k == message
    mes = Encrypt_site(k, e1, n1)
    p_and_q = GenerateKeyPair()  # Aліса генерує свою пару
    n = p_and_q[0] * p_and_q[1]
    while n > n1:
        p_and_q = GenerateKeyPair()
        n = p_and_q[0] * p_and_q[1]
    f = (p_and_q[0] - 1) * (p_and_q[1] - 1)

    d = mod_reverse(e, f)
    s = Sign_site(k, d, n)
    sign = Encrypt_site(s, e1, n1)
    return mes, sign, n




if __name__ == "__main__":

#Аліса надсилає Бобу повідомлення яке він має розифрувати
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
    text = ''
    for i in t:
        text += str(i)
    print((text))
    print(res)


 #Перевірка на сайті

    print('Key: ')
    k = random.randint(1, 965)
    e = 2 ** 16 + 3
    e1 = 2 ** 16 + 1
    n1 = (int('B286395B6903065CA7FC81E98FAFFDC430BFD000E5E1133348EC945D86119EFBAE3F6208098D64CABE4262E45E9719266210673BFB727428A538B0619EE7F5B3',16))
    mes, sign, n = SendKey_site(e1,n1,k)
    print(hex(mes))
    print(hex(sign))
    print(hex(n))



























