import sys
import multiprocessing, subprocess
from datetime import datetime

def handle_with_print(ip, port):
    BINARY = 'client'
    p = subprocess.Popen(['./'+BINARY, ip, port])

def handle_with_no_print(ip, port):
    BINARY = 'client'
    p = subprocess.Popen(['./'+BINARY, ip, port], stdout=subprocess.PIPE)

def handle_with_save(ip, port):
    BINARY = 'client'
    p = subprocess.Popen(['./'+BINARY, ip, port], stdout=subprocess.PIPE)

    out = p.stdout.readlines()

    f = open('log_'+str(datetime.today())+'.txt', 'w')
    f.writelines(out)
    f.close()

def main(ip, port):

    jobs = []
    funcs = (handle_with_print,
             handle_with_save,
             handle_with_no_print,
             handle_with_no_print)

    for i, func in enumerate(funcs):
        p = multiprocessing.Process(target=func, args=(ip, port,))
        jobs.append(p)

    for job in jobs:
        job.start()

if __name__ == '__main__':

    ip = sys.argv[1]
    port = sys.argv[2]

    main(ip, port)
