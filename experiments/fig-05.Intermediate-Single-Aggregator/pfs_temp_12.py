


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
        default=100,
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
        command = f"cat /scratch365/cthoma26/landmark.tar.gz_1 > /scratch365/cthoma26/outputs/outfile.{i}; sleep 1",
        )
        task_id = m.submit(t)
        i+=1
        print(f"submitted task {t.id}: {t.command}")

    print(f"TaskVine listening for workers on {m.port}")

    print("Waiting for tasks to complete...")
    while not m.empty():
        t = m.wait(5)

    t = vine.Task("cat /scratch365/cthoma26/outputs/outfile.* > /scratch365/cthoma26/outputs/final_output")

    task_id = m.submit(t)
    print(f"final task submitted")

    while not m.empty():
        t = m.wait(5)

        if t:
            print(f"task {t.id} exited {t.std_output}")



    print("all tasks complete!")
