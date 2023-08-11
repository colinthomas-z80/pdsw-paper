


import ndcctools.taskvine as vine
import random
import argparse
import getpass



if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="vine_example_blast.py",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )

    parser.add_argument(
        "--task-count",
        nargs="?",
        type=int,
        help="the number of tasks to generate.",
        default=300,
    )
    parser.add_argument(
        "--name",
        nargs="?",
        type=str,
        help="name to assign to the manager.",
        default=f"vine-blast-{getpass.getuser()}",
    )
    parser.add_argument(
        "--port",
        nargs="?",
        type=int,
        help="port for the manager to listen for connections. If 0, pick any available.",
        default=9123,
    )
    parser.add_argument(
        "--disable-peer-transfers",
        action="store_true",
        help="disable transfers among workers.",
        default=False,
    )
    parser.add_argument(
        "--max-concurrent-transfers",
        nargs="?",
        type=int,
        help="maximum number of concurrent peer transfers",
        default=3,
    )
    args = parser.parse_args()

    m = vine.Manager(port=args.port)
    m.set_name(args.name)

    if args.disable_peer_transfers:
        m.disable_peer_transfers()
    
    i = 0
    for i in range(args.task_count):
        t = vine.Task(
        command = f"cat /scratch365/cthoma26/gigfile_25 > /scratch365/cthoma26/outputs/outfile.{i}; sleep 1",
        )
        task_id = m.submit(t)
        i+=1
        print(f"submitted task {t.id}: {t.command}")

    print(f"TaskVine listening for workers on {m.port}")

    print("Waiting for tasks to complete...")
    while not m.empty():
        t = m.wait(5)

    for i in range(0, args.task_count-2, 2):
        t = vine.Task(f"cat /scratch365/cthoma26/outputs/outfile.{i} >> /scratch365/cthoma26/outputs/outfile.{i+1}; rm /scratch365/cthoma26/outputs/outfile.{i}")
        task_id = m.submit(t)

    while not m.empty():
        t = m.wait(5)
        if t:
            print(f"task {t.id} exited {t.std_output}")

    for i in range(1, args.task_count-2, 2):
        t = vine.Task(f"tar -czvf /scratch365/cthoma26/outputs/mytar.{i} /scratch365/cthoma26/outputs/outfile.{i}; sync; rm /scratch365/cthoma26/outputs/outfie.{i}")
        task_id = m.submit(t)

    while not m.empty():
        t = m.wait(5)
        if t:
            print(f"task {t.id} exited {t.std_output}")
    
    for i in range(1, args.task_count-2, 2):
        t = vine.Task(f"tar -xzvf /scratch365/cthoma26/outputs/mytar.{i}; echo \"myresult\" > /scratch365/cthoma26/outputs/resultfile")
        task_id = m.submit(t)

    while not m.empty():
        t = m.wait(5)
        if t:
            print(f"task {t.id} exited {t.std_output}")
    print("all tasks complete!")
