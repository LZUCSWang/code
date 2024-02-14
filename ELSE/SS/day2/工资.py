name=input()
hours=float(input())
pervalue=float(input())
shuilv=float(input())
oldlv=float(input())
GP=pervalue*hours
D=GP*shuilv
lao=GP*oldlv
p=GP-D-lao
# print(name,hours,pervalue,GP,D+lao,p)
print("Employee Name: %s"%name)
print()
print("Hours Worked:  %.0f"%hours)
print("Pay Rate: $%.0f"%pervalue)
print("Gross Pay: $%.0f"%GP)
print("Deductions: %.1f"%(D+lao))
print("Net Pay:%.1f"%p)

"""
Employee Name: 于敏

Hours Worked:  8
Pay Rate: $110
Gross Pay: $880
Deductions: 132.0
Net Pay:748.0
"""