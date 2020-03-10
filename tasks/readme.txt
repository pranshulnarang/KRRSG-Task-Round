.................................................instructions for task1..............................................................
.................................................INSTRUCTIONS TO RUN THE SERVER AND CLIENT....................................
STEP 1:- compile gru.c file using g++ gru.c -o gru -lpthread
STEP 2:- run the gru file using ./gru 8080 where 8080 is a portno. you can put any portno.
STEP 3:- next compile and execute the clientserver.c and send the required array with ,(comma)in between numbers and no spaces and place a ,(comma) in the last also eg 1,2,3,4,5,6,7,8,9,
STEP 4:- connect the required no. of minions as specified as a macro to indicate total no. of minions
STEP 5:- array will be recieved by the minions
STEP 6:- final sum will be recieved by clients


.................................................instructions for task2.................................................................
1.> compile and run the fsm.cpp file and fill out the required information
2.> add 0 0 0 to stop giving input remember to use caps when specifying direction e.g. U and keep spaces between data e.g. 1 U 6
3.> for task2 part2......
4.> first run task2part2.cpp
5.> enter required information
6.> in another terminal open the task2client.cpp
7.> start giving input in the form eg. 1U6
8.>output is displayed in the other terminal where nearest lift approaches and completes the task

.................................................instuctions for task3................................................................
1.> To get the path between final and initial point execute task3.cpp
2.> required path is highlighted change value of EPSILON or radius to get a better path if necessary
3.> to run the path on turtlesim copy TurtlesimPositioncontroller_pkg in catkin_ws/src
4.> run roscore on one terminal
5.> on another terminal run turtlesim using rosrun turtlesim turtlesim_node
6.> in catkin_ws folder use catkin_make and in catkin_ws/src run the TurtlesimPositioncontroller_pkg.cpp file using rosrun TurtlesimPositionControllers_pkg TurtlesimPositionControllers_pkg
7.> remember to correctly specify the path of file which will store the coordinates
8.> a turtle will be spawned which will move on the required path

................................................instructions for task4...................................................................
1-> Train the pendulum using ppo policy as well as the pendulum.py
	to train use
	cd spinningup/spinup/algos/pytorch/ppo
	then use python pendulum.py --env Pendulum-v0
	see the plot using  python -m spinup.run plot /home/pranshul/spinningup/data/ppo/ppo_s0
	run using  python -m spinup.run test_policy /home/pranshul/spinningup/data/ppo/ppo_s0
2-> observer the graph and use it to maximise stability
3.> add an extra factor if necessary
