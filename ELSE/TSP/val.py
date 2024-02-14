from env import Env_tsp
from config import Config, load_pkl, pkl_parser
import torch
cfg = load_pkl('/home/stu_wxy/content/TSP_DRL_PtrNet-master/Pkl/test6.pkl')
env = Env_tsp(cfg)

device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
# Convert the input list or array to a PyTorch tensor
nodes = torch.tensor(city_coordinates, dtype=torch.float32, device=device)
