import os
import sys
dp = [1]*200
s = """tocyjkdzcieoiodfpbgcncsrjbhmugdnojjddhllnofawllbhfiadgdcdjstemphmnjihecoapdjjrprrqnhgccevdarufmliqijgihhfgdcmxvicfauachlifhafpdccfseflcdgjncadfclvfmadvrnaaahahndsikzssoywakgnfjjaihtniptwoulxbaeqkqhfwl"""
for i in range(len(s)):
    for j in range(i):
        if s[i] > s[j]:
            dp[i] += dp[j]
        elif s[i] == s[j]:
            dp[i] -= dp[j]
print(sum(dp))
