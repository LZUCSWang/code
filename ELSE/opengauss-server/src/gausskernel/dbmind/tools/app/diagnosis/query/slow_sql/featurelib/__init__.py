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
import os

from . import feature_mapping
from . import features
# To import file feature_mapping and features from parent folder

#function name: load_feature_lib
#description: Print the variable FEATURE_LIB in the file-- features
#return value: The value of FEATURE_LIB
#date: 2022/8/2
#contact: 1865997821

def load_feature_lib():
    return features.FEATURE_LIB

#function name: get_feature_mapper
#description: Get the item and value of a dictionary type in the file-- feature_mapping and output it as a generator.
#return value: The item and value in _dict_  variable
#note：Dictionary key-value pairs must start with C then the  item and value will be return.
#date: 2022/8/2
#contact: 1865997821

def get_feature_mapper():
    return {
        item: value
        for item, value in
        feature_mapping.__dict__.items() if item.startswith('C')
    }
