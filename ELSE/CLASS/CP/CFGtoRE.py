def cfg_to_regex(cfg):
    # 初始化正则表达式字典
    regex_dict = {}

    # 遍历产生式，初始化终结符的正则表达式
    for production in cfg:
        non_terminal, expression = production.split('->')
        regex_dict[non_terminal] = expression.strip()

    # 根据产生式逐步替换非终结符
    for non_terminal in regex_dict:
        for key in regex_dict:
            regex_dict[non_terminal] = regex_dict[non_terminal].replace(key, f'({regex_dict[key]})')

    # 提取最终的正则表达式
    # final_regex = regex_dict['S']

    # return final_regex
    return regex_dict

# 示例文法
cfg_example = [
    'S -> AB | A | B',
    'A -> aAb | a',
    'B -> cBd | d'
]

# 转换为正则表达式
regex_result = cfg_to_regex(cfg_example)

print("正则表达式:", regex_result)
