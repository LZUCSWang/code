'''
Author: WangXianYi
School: LZU
Date: 2023-10-12 09:02:22
Description: 
'''
# print(re.isequal('aa?', 'a|aa'))
# print(re.isequal('aa*', 'a+'))
# print(re.issubset('aa?', 'a*'))

from automata.fa.dfa import DFA
from automata.fa.nfa import NFA

nfa1 = NFA.from_regex('(a|b)*',input_symbols={'a', 'b'})
nfa2 = NFA.from_regex('(a*|b*)*', input_symbols={'a', 'b'})
# nfa2 = NFA.from_regex('aaa*', input_symbols={'a', 'b'})
# print(nfa1)
nfa1.show_diagram(path='./nfa1.png')
nfa2.show_diagram(path='./nfa2.png')
dfa1 = DFA.from_nfa(nfa1).minify(retain_names=True)  # returns an equivalent DFA
dfa2 = DFA.from_nfa(nfa2).minify(retain_names=True)  # returns an equivalent DFA
dfa1.show_diagram(path='./dfa1.png')
dfa2.show_diagram(path='./dfa2.png')