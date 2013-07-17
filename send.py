import sys
import multiprocessing, subprocess
from datetime import datetime

def handle_with_print(ip, port, bin):
    p = subprocess.Popen([bin, ip, port])

def handle_with_no_print(ip, port, bin):
    p = subprocess.Popen([bin, ip, port], stdout=subprocess.PIPE)

def handle_with_save(ip, port, bin):
    p = subprocess.Popen([bin, ip, port], stdout=subprocess.PIPE)

    out = p.stdout.readlines()

    f = open('./logs/log_'+str(datetime.today())+'.txt', 'w')
    f.writelines(out)
    f.close()

def main(ip, port, bin='./client'):

    jobs = []
    funcs = (handle_with_print,
             handle_with_save,
             handle_with_no_print,
             handle_with_no_print)

    for i, func in enumerate(funcs):
        p = multiprocessing.Process(target=func, args=(ip, port, bin,))
        jobs.append(p)

    for job in jobs:
        job.start()

if __name__ == '__main__':

    ip = sys.argv[1]
    port = sys.argv[2]

    if len(sys.argv) >= 4:
        bin = sys.argv[3]
    else:
        bin = './client'

    main(ip, port, bin)
