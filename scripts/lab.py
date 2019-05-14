import os
import shutil

os.system("echo  > ../scripts/out")

root = "../resources"
ac_dir = f"{root}/ac"
tle_dir = f"{root}/tle"

in_root = "/Users/songl/OneDrive/毕业设计/road"

in_files = os.listdir(in_root)

for i in range(len(in_files)):
    in_files[i] = f"{in_root}/{in_files[i]}"


ac_mean = 0.
ac_count = 0
tle_mean = 0.
tle_count = 0


def run(path, name, mode, func, result, input):
    global ac_count, ac_mean, tle_count, tle_mean
    command = f"./run {path} {name} {func} {result} {input} | grep 'number is'"
    os.system(f"echo {command} >> ../scripts/out")
    r = os.popen(command)
    lines = r.readlines()
    if len(lines) == 0:
        return
    store_num = int(lines[0].split(" ")[-1])
    call_num = int(lines[1].split(" ")[-1])
    rate = store_num * 1.0 / call_num
    if mode == "TLE":
        tle_count += 1
        tle_mean += rate
    else:
        ac_count += 1
        ac_mean += rate
    # os.system(
    #     f"echo {path} {name} {mode} store:{store_num} call_num:{call_num} rate:{rate} >> ../scripts/out")


for file_input in in_files:
    ac_count = 0
    ac_mean = 0.
    tle_count = 0
    tle_mean = 0.
    cmd = f"echo {file_input} >> ../scripts/out"
    os.system(cmd)
    for file in os.listdir(ac_dir):
        path = f"{ac_dir}/{file}"
        with open(path) as f:
            line = f.readline()
            func = line.split(" ")[1].strip()
            result = line.split(" ")[2].strip()
            run(ac_dir, file.split('.')[0], "AC", func, result, file_input)
    for file in os.listdir(tle_dir):
        path = f"{tle_dir}/{file}"
        with open(path) as f:
            line = f.readline()
            func = line.split(" ")[1].strip()
            result = line.split(" ")[2].strip()
            run(tle_dir, file.split('.')[0], "AC", func, result, file_input)
    cmd = f"echo tle_mean:{tle_mean / tle_count} ac_mean:{ac_mean / ac_count} >> ../scripts/out"
    os.system(cmd)
