
all:
	./vine_plot_txn_log vine_results/transactions vine_complex.png --mode tasks  --legend "lower right"
	./vine_plot_txn_log pfs_results/transactions pfs_complex.png --mode tasks --legend none
	dot -Tpng ./vine_results/taskgraph > complex_taskgraph.png 
