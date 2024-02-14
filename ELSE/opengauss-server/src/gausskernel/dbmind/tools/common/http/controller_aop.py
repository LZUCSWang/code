# Copyright (c) 2020 Huawei Technologies Co.,Ltd.
#
# openGauss is licensed under Mulan PSL v2.
# You can use this software according to the terms and conditions of the Mulan PSL v2.
# You may obtain a copy of Mulan PSL v2 at:
#
#          http://license.coscl.org.cn/MulanPSL2
#
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
# EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
# MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
# See the Mulan PSL v2 for more details.


import json
from functools import wraps

skip_filter_paths = ["/metrics", "/favicon.ico"]


def do_before():
    """Nothing"""

def do_after(rt_result):
    """Nothing"""

def do_exception(exception):
    """Nothing"""


#function name: around
#description: Preserve the function properties and prevent an error from terminating the program
#arguments: One or more functions
#return value: none
#note： Decorators are implemented in such a way that the function being decorated is actually another function (the function name and other properties change).
#To avoid this, Python's FuncTools package provides a decorator called wraps to remove such side effects.
#When writing a decorator, it is a good idea to wrap FuncTools before implementing it.
#It preserves the name and properties of the original function
#date: 2022/8/4
#contact: 1865997821
def around(func, *args, **kw):
    @wraps(func)
    def wrapper():
        do_before()
        try:
            rt_result = func(*args, **kw)
            final_rt = do_after(rt_result)
        except BaseException as exception:
            final_rt = do_exception(exception)
        return final_rt

    return wrapper
