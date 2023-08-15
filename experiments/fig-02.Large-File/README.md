# Large File Distribution 

This experiment covers the distribution of a two gigabyte data file to be read in at a number of nodes in the cluster.
The TaskVine and PFS experiment uses 100 nodes. The GekkoFS experiment uses 50 nodes.

Ensure you have set up TaskVine and activated your environment at the base of this repository.

To run the TaskVine and PFS experiment, submit the base.submit script to an HTCondor pool. The run either experiment like so:

	condor_submit base.submit

	python vine_distribute_12.py

To run the GekkoFS experiment, some supplemental work is needed to deploy GekkoFS before the workflow runs. First submit the gekko.submit script like so:

	condor_submit gekko.submit

After the jobs are scheduled ensure the hostfile has been created and all nodes have registered:

	wc -l ../../gekkohost
	50

Then run the experiment:

	python gekko_distribute_12.py

Refer to gekkofs/README.md for troubleshooting GekkoFS. 

