#################################################
About Program 1, ptree.c
################################################
It's a kernel modle that automatically store all 
the process in android in an array, in dfs order.


##################################################
About Program2, test.c
################################################
Actually, it's a test code that can evaluate whether 
the system call programed in problem1 can execute 
correctly. As a result, it print out the information 
of all the pocess in Android, using index to differentiate 
the relationships between the process.

##################################################
About Program3, pro3.c
##################################################
In this program, we show the parent process and child process.
At the same time, we use execl to replace the child process and 
execute the program in problem 2.


#########################################################
About Program4, burger.c
#########################################################
It's a problem concerning multi-processing issues.
Input the cook's,cashiers',customers' and racks' number,
the program will automatically simulate the service in
real restaurant. That is, cook make the hamburger untill 
the rack size if full, casheir receive the order from the customer,
and customers come to the restaurant.
In this case, we have to protect the critical data so we use
semaphore.

