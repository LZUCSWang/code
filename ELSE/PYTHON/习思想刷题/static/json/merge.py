import os
import json

def merge_json_files(folder_path, output_file):
    with open(output_file, 'w', encoding='utf-8') as outfile:
        all_data = []
        for root, dirs, files in os.walk(folder_path):
            for file in files:
                if file.endswith('.json'):
                    with open(os.path.join(root, file), 'r', encoding='utf-8') as infile:
                        data = json.load(infile)
                        all_data.extend(data)
        json.dump(all_data, outfile, ensure_ascii=False)

merge_json_files('90', 'merge.json')