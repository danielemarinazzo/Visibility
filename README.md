# Visibility
code for visibility grahps, basically  a Matlab version of what is proposed here
http://www.maths.qmul.ac.uk/~lacasa/Software.html


you should compile the cpp file with mex

then the program is called with

[AD K] = Visibility (timeseries, Vis_type)

where the output is
AD = adjacency matrix according to the visibility criterion
K = node degree (this is the quantity that is used to compute mutual information)

and the input is
timeseries = the time series
Vis_type = 1 for Horizontal Visibility and 2 for Natural Visibility
