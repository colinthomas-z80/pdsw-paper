
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
        default=1200,
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

    
    t1 = vine.Task(
        command = "LD_PRELOAD=/tmp/gekkofs_install/install/lib64/libgkfs_intercept.so cp /scratch365/cthoma26/twogig_4 /tmp/gekkomnt/twogig_4",
    )
    task_id = m.submit(t1)
    print("Copying into gekkofs")
    while not m.empty():
        t = m.wait(5)

    for i in range(args.task_count):
        t = vine.Task(
        command = "LD_PRELOAD=/tmp/gekkofs_install/install/lib64/libgkfs_intercept.so cat /tmp/gekkomnt/twogig_4 > /dev/null",
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
                    f"task {t.id} completed with an execution error, exit code {t.exit_code}: {t.std_output}"
                )
            else:
                print(f"task {t.id} failed with status {t.result}")

    print("all tasks complete!")
