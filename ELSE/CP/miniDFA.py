'''
Author: WangXianYi
School: LZU
Date: 2023-10-12 16:05:43
Description: 
'''
from automata.fa.dfa import DFA
from automata.fa.nfa import NFA

# DFA which matches all binary strings ending in an odd number of '1's
dfa = DFA(
    states={'q0', 'q1', 'q2', 'q3', 'q4', 'q5', 'q6'},
    input_symbols={'a','b'},
    transitions={
        'q0': {'a': 'q1', 'b': 'q2'},
        'q1': {'a': 'q3', 'b': 'q2'},
        'q2': {'a': 'q1', 'b': 'q4'},
        'q3': {'a': 'q3', 'b': 'q5'},
        'q4': {'a': 'q6', 'b': 'q4'},
        'q5': {'a': 'q6', 'b': 'q4'},
        'q6': {'a': 'q3', 'b': 'q5'}
    },
    initial_state='q0',
    final_states={'q3', 'q4', 'q5', 'q6'}
)
dfa.minify().show_diagram(path='./dfa.png')