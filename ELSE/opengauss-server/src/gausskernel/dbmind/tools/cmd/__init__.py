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
import sys

from .cli import DBMindRun
#To import DBMindRun method from the parent file cli

#function name: main
#description: Get the system command parameters, pass to the DBMindRun and call this function,if an InterruptedError is reported, the program will exit( sys.exit(1)).
#arguments: None
#return value: None
#date: 2022/8/3
#contact: 1865997821
def main() -> None:
    try:
        DBMindRun(sys.argv[1:])
    except InterruptedError:
        sys.exit(1)
