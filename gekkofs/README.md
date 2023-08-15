# GekkoFS for use with TaskVine 

## Precompiled installation
A precompiled GekkoFS installation is included here in the install\/ directory. This also includes 
a copy of librdmacm.so.1 which is required for GekkoFS to link in at runtime even if RDMA is not being used. The GekkoFS
installation process assumes this library is available to the user, however we had to source it elsewhere in order to run the experiments.

## Manual installation
If the precompiled installation provided is not compatible with your system, follow the installation instructions at https://storage.bsc.es/gitlab/hpc/gekkofs 
to install to this directory. The GekkoFS installation will create its own "install" directory. In order to avoid modification of the experiment scripts, move
the new install directory in the place of the old one, including our copy of librdmacm.so.1 if needed. 

## Running Experiments
Directions for running experiments with GekkoFS and TaskVine will be detailed further in the corresponding experiment directory. Depending on the shared filesystem
being used, the deployment phase of GekkoFS can be precarious. Job submission should be done first before starting the experiment. The hostfile "gekkohost" is to be
created automatically at the root of this repository. Before running the experiment, cat or wc -l the host file to ensure that all scheduled nodes have started
and registered in the hostfile. Occasionally the hostfile will be corrupted by an errant newline or character. If this occurs the job submission must be cancelled and retried.
You may attempt to fix the hostfile in a text editor on the fly, but this will likely result in an IO error at one of the workers. 

Ensure the hostfile does not exist prior to deploying GekkoFS. 
