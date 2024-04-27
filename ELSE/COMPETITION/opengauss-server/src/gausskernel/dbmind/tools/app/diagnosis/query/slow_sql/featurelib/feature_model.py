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
import csv
#import csv packet
from collections import defaultdict
from typing import List
# To import defaultdict in the parent floder collections and List  in the parent floder typing

import numpy as np
# import numpy packet as the name np

from ..analyzer import _euclid_distance as euclid_distance
from dbmind.common.utils import ExceptionCatch
#To import private function-- _euclid_distance as euclid_distance

#function name: calculate_weight
#description: This function will output feature_weight (= residual_vector / the sum of residual_vector)
#The data used for the calculation is from the features_labels_dict, and the key value pairs of the features_labels_dict are filtered
#arguments: np.ndarray and  np.ndarray
#return value: weight_matrix
#date: 2022/8/2
#contact: 1865997821

def calculate_weight(features: np.ndarray, labels: np.ndarray) -> List:
    normalize_features, normalize_labels = [], []
    features_labels_dict = defaultdict(list)
    for i in range(len(labels)):
        features_labels_dict[labels[i]].append(features[i])
    for key, value in sorted(features_labels_dict.items(), key=lambda x: x[0]):
        normalize_features.append(np.sum(value, axis=0).tolist())
        normalize_labels.append(key)
    n_label = len(normalize_labels)
    dist_matrix = [[0] * n_label for i in range(n_label)]
    weight_matrix = []
    for i in range(n_label):
        for j in range(i, n_label):
            if i == j:
                dist = 0
            else:
                dist = euclid_distance(normalize_features[i], normalize_features[j])
            dist_matrix[i][j] = dist
            dist_matrix[j][i] = dist
    for i in range(n_label):
        n = sum([dist_matrix[i][j] * dist_matrix[i][j] for j in range(n_label) if i != j])
        weight_vector = np.sum(np.array(
            [(1 / (dist_matrix[i][j] * dist_matrix[i][j])) * np.array(normalize_features[j]) for j in range(n_label) if
             i != j]), axis=0) / n
        residual_vector = np.abs(weight_vector - np.array(normalize_features[i]))
        feature_weight = residual_vector / np.sum(residual_vector)
        weight_matrix.append(feature_weight)
    return weight_matrix


# function name: build_model
# description: Create two variables-- features and labels.There are refer to two numpy array(all elements are zero)
# The features array's size is feature_number and dimension is feature_dimension
# This function will read the two arrays and write it as a matrix in a csv file(the save path is './features_new.npz')
# And then it will call the function calculate_weight to calculate the matrix
# arguments: feature_path, feature_number, feature_dimension
# return value: None
# note：A ExceptionCatch function modifier is used
# date: 2022/8/2
#contact: 1865997821
@ExceptionCatch(strategy='exit', name='FEATURE')
def build_model(feature_path: str, feature_number: int, feature_dimension: int,
                save_path: str = './features_new.npz') -> None:
    """
    Build a model based on features
    :param feature_path: path of feature file
    :param feature_number: the number of feature
    :param feature_dimension: the dimension of feature
    :param save_path: path to save feature model
    :return: None
    """
    features, labels = np.zeros((feature_number, feature_dimension)), np.zeros(feature_number)
    with open(feature_path, mode='r') as f:
        csv_reader = csv.reader(f)
        for line in csv_reader:
            line = [int(item) for item in line]
            features[csv_reader.line_num - 1] = line[:-1]
            labels[csv_reader.line_num - 1] = line[-1]
    weight_matrix = calculate_weight(features, labels)
    np.savez(save_path, features=features, labels=labels, weight_matrix=weight_matrix)
