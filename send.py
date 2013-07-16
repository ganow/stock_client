import os, sys
import multiprocessing

def handle(ip, port):
    os.system('./client '+ ip + port)

if __name__ == '__main__':

    ip = sys.argv[1]
    port = sys.argv[2]

    jobs = []
    for i in xrange(4):
        p = multiprocessing.Process(target=handle, args=(ip, port,))
        jobs.append(p)

    for job in jobs:
        job.start()