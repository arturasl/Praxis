#!/usr/bin/python

""" http://programmingpraxis.com/2011/04/26/miscellanea/ """

from math import sqrt

# FizzBuzz

print '########## FizBuzz ##########'


def fizz_buzz(number):
    """ Prints numbers from 1 to n """

    for i in range(1, number + 1):
        if i % 15 == 0:
            print 'FizzBuzz'
        elif i % 3 == 0:
            print 'Fizz'
        elif i % 5 == 0:
            print 'Buzz'
        else:
            print i


fizz_buzz(20)

# Prime Words

print '########## Prime words ##########'


def is_prime(number):
    """ Naive function to check if number is prime """

    if number == 1:
        return False
    if number == 2:
        return True
    if number % 2 == 0:
        return False

    for i in range(3, int(sqrt(number)) + 1, 2):
        print i
        if number % i == 0:
            return False

    return True


# probably cheating
print is_prime(int('PRAXIS', 36))

def hexatridecimal_to_dec(test_str):
    """ converts hexatridecimal string to decimal number """
    test_str = 'PRAXIS'
    pos = len(test_str) - 1
    result = 0

    for character in list(test_str):
        code = ord(character)
        if ord('0') <= code and code <= ord('1'):
            result += (code - ord('0')) * 36 ** pos
        elif ord('A') <= code and code <= ord('Z'):
            result += (code - ord('A') + 10) * 36 ** pos
        else:
            print ('illegal character ', character)

        pos -= 1

    return result


print is_prime(hexatridecimal_to_dec('PRAXIS'))

# Split a list

print '########## Split list ##########'


class SNode:

    """ class which represents single item in linked list """

    def __init__(self, number):
        self.number = number
        self.next_node = None


def split_list(first_node):
    """ splits list into to halves """

    split_at = first_node
    double_next = first_node

    if first_node is None:
        return (None, None)

    while double_next.next_node is not None and double_next.next_node.next_node is not None:
        double_next = double_next.next_node.next_node
        split_at = split_at.next_node

    prev_node = split_at
    split_at = split_at.next_node
    prev_node.next_node = None

    return (first_node, split_at)


def print_list(first_node):
    """ prints from given node """

    while first_node is not None:
        print first_node.number
        first_node = first_node.next_node


def test_split_list():
    """ tests split_list function """

    first_node = SNode(1)
    current_node = first_node

    for i in range(2, 10):
        current_node.next_node = SNode(i)
        current_node = current_node.next_node

    (first_list, second_list) = split_list(first_node)
    print '--'
    print_list(first_list)
    print '--'
    print_list(second_list)
    print '--'


test_split_list()
