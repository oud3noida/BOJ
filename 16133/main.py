import math
from decimal import Decimal

s = input()
i = 0
cur = s[i]

def accept_it():
    global s, i, cur
    
    i += 1
    if i < len(s):
        cur = s[i]
    else:
        cur = '$'

def accept(c):
    global cur
    
    if cur == c:
        accept_it()
    else:
        raise Exception()

def parse_input():
    global cur
    
    tree = parse_expr()
    
    if cur != '=':
        raise Exception()
    
    return tree
    
def parse_expr():
    global cur
    
    tree = parse_term()
    while cur in "+-":
        op = cur
        accept_it()
        right = parse_term()
        tree = (tree, op, right) # left to right
    return tree
    
def parse_term():
    global cur
    
    tree = parse_factor()
    while cur in "*/":
        op = cur
        accept_it()
        right = parse_factor()
        tree = (tree, op, right) # left to right
    return tree
    
    
def parse_factor():
    global cur
    
    tree = parse_power()
    if cur == '^':
        accept_it()
        right = parse_factor()
        return (tree, '^', right) # right to left
    else:
        return tree
    
def parse_power():
    global cur
    
    if cur == '#':
        accept_it()
        return ('#', parse_power()) # right to left
    else:
        return parse_root()
    
def parse_root():
    global cur
    
    if cur == '(':
        accept_it()
        tree = parse_expr()
        accept(')')
        return tree
    else:
        return parse_num()
    
def parse_num():
    global cur
    
    num = 0
    if cur == '0':
        accept_it()
        return num
    elif '1' <= cur <= '9':
        while '0' <= cur <= '9':
            num = num * 10 + int(cur)
            accept_it()
        return num
    else:
        raise Exception()

def calculate(tree):
    if isinstance(tree, tuple):
        if len(tree) == 2:
            if tree[0] == '#':
                child = calculate(tree[1])
                return math.isqrt(child)
        else:
            left = calculate(tree[0])
            right = calculate(tree[2])
            
            if tree[1] == '+':
                return left + right
            elif tree[1] == '-':
                return left - right
            elif tree[1] == '*':
                return left * right
            elif tree[1] == '/':
                return int(Decimal(left) / Decimal(right))
            elif tree[1] == '^':
                return left ** right
    else:
        return tree

try:
    expr_tree = parse_input()
    print(calculate(expr_tree))
except:
    print("ERROR")
