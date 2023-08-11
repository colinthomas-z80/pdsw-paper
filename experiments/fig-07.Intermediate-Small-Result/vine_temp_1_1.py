

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

    
    m.tune("worker-source-max-transfers", 3)
    m.tune("file-source-max-transfers", 10)

    landmark = m.declare_url("file:///scratch365/cthoma26/gigfile_13", cache="always")

    if args.disable_peer_transfers:
        m.disable_peer_transfers()

    list_outputs = []
    for i in range(args.task_count):
        outfile = m.declare_temp()
        list_outputs.append(outfile)
        t = vine.Task(
        command = "cat landmark.tar.gz > outfile; sleep 1",
        inputs = { landmark : {"remote_name":"landmark.tar.gz"} },
        outputs = {outfile : {"remote_name": "outfile"}},
        )
        task_id = m.submit(t)
        print(f"submitted task {t.id}: {t.command}")

    print(f"TaskVine listening for workers on {m.port}")

    print("Waiting for tasks to complete...")
    while not m.empty():
        t = m.wait(5)
        if t:
            if t.successful():
                print(f"task {t.id} result: {t.std_output}")
            elif t.completed():
                print(
                    f"task {t.id} completed with an executin error, exit code {t.exit_code}"
                )
            else:
                print(f"task {t.id} failed with status {t.result}")
   
    for o in list_outputs:
        t = vine.Task("cat infile > /dev/null")
        t.add_input(o, "infile", strict_input=True)
        tid = m.submit(t)
        print(f"submitted final task {t.id}: {t.command}")

    while not m.empty():
        t = m.wait(5)
        if t:
            if t.successful():
                print(f"task {t.id} result: {t.std_output}")
            elif t.completed():
                print(f"task {t.id} completed with an execution error, exit code {t.exit_code}")
            else:
                print(f"task {t.id} failed with status {t.result}")

    print("all tasks complete!")
