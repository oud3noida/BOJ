import random
import sys
sys.setrecursionlimit(1000000)

def gcd(a, b):
    '''
        Find GCD using the binary GCD algorithm
    '''
    
    if a == b: return a
    
    if a == 0: return b
    if b == 0: return a
    
    if a%2 == 0:
        if b%2 == 0: return 2*gcd(a//2, b//2)
        return gcd(a//2, b)
    else:
        if b%2 == 0: return gcd(a, b//2)
        return gcd(abs(a-b)//2, min(a, b))

def get_miller_rabin_s(n):
    '''
        Find s such that n = (2**s) * d, where d is an odd number
    '''
    s = 0
    while ((n>>s) & 1) == 0: s += 1
    return s
    
def power_mod(a, x, mod):
    '''
        Find (a**x) % mod using binary exponentiation method
    '''
    ret = 1
    a %= mod
    
    while x > 0:
        if x%2 == 1:
            ret = (ret * a) % mod
        a = (a*a) % mod
        x //= 2
    
    return ret

def is_prime(n):
    '''
        Check primality using Miller-Rabin primality test
    '''
    if n == 2 or n == 3:
        return True
    if n == 1 or n%2 == 0:
        return False
    
    s = get_miller_rabin_s(n-1)
    d = (n-1)>>s
    
    for a in (2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37):
        if n == a:
            return True
        
        is_prime_for_current_witness = False
        
        x = power_mod(a, d, n)
        if x == 1 or x == n-1:
            continue
        
        for r in range(s):
            x = power_mod(x, 2, n)
            
            if x == n-1:
                is_prime_for_current_witness = True
                break
            
        if not is_prime_for_current_witness:
            return False
    
    return True

def g(x, n, k):
    '''
        A polynomial modulo used to generate a pseudorandom sequence
        for Pollard's rho algorithm
    '''
    return (x*x + k) % n

def pollard_rho(n):
    '''
        Find a non-trvial prime factor of n, using Pollard's rho algorithm
    '''
    if is_prime(n):
        return n
    
    x = random.randrange(2, n)
    y = x
    k = random.randrange(1, n)
    d = 1
    
    while d == 1:
        x = g(x, n, k)
        y = g(g(y, n, k), n, k)
        d = gcd(abs(x-y), n)
    
    return pollard_rho(d)

def get_prime_factors(n):
    '''
        Get all prime factors of n,
        using Pollard's rho algorithm and Miller-Rabin primality test
    '''
    prime_factors = set()
    
    # Extract all 2's
    s = get_miller_rabin_s(n)
    if s > 0:
        n = n>>s
        prime_factors.add(2)
    
    # Extract the rest of prime factors
    while n > 1:
        factor = pollard_rho(n)
        prime_factors.add(factor)
        n //= factor
    
    # Output prime factors
    return prime_factors

def inverse(x, mod):
    '''
        Find a modular multiplicative inverse of x,
        using extended Euclidean algorithm
    '''
    r0 = x; r1 = mod
    s0 = 1; s1 = 0
    t0 = 0; t1 = 1
    tmp = 0; q = 0
    
    while r1 != 0:
        q = r0 // r1
        
        tmp = r0 - r1*q
        r0 = r1
        r1 = tmp
        
        tmp = s0 - s1*q
        s0 = s1
        s1 = tmp
        
        tmp = t0 - t1*q
        t0 = t1
        t1 = tmp
    
    return (s0 + mod) % mod

# -------------------- Main -------------------- #

MOD = 10**18 + 3

# Input
n = int(input())

# Calculate the value for Euler's totient function
# NOTE: Dividing x is implemented as multiplying the modular inverse of x
ans = n
prime_factors = get_prime_factors(n)
for p in prime_factors:
    ans *= inverse(p, MOD)
    ans %= MOD
    ans *= p - 1
    ans %= MOD

# Output the number of k (1 <= k <= n) such that GCD(n, k) = 1
print(round(ans))
