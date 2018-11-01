set ns [new Simulator] 

set nt [open simulate.nam w]
$ns namtrace-all $nt

set tr [open simulate.tr w]
$ns trace-all $tr

#close before finishing 
proc finish {} {
	global ns nt tr
	$ns flush-trace
	close $nt
	close $tr
	exec nam simulate.nam &
	exit 0
}

$ns color 1 green
$ns color 2 Red

#set up some nodes 
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

$ns duplex-link $n1 $n2 2Mb 20ms DropTail
$ns duplex-link $n1 $n3 1Mb 5ms DropTail
$ns duplex-link $n3 $n4 1Mb 10ms DropTail

$ns duplex-link-op $n1 $n2 orient right
$ns duplex-link-op $n1 $n3 orient right-down
$ns duplex-link-op $n4 $n3 orient right-up
#set up TCP Connections 
set tcp1 [new Agent/TCP]
$ns attach-agent $n1 $tcp1
set tcp2 [new Agent/TCP]
$ns attach-agent $n3 $tcp2

set sink1 [new Agent/TCPSink]
$ns attach-agent $n2 $sink1 
$ns connect $tcp1 $sink1
$tcp1 set fid_ 1
set sink2 [new Agent/TCPSink]
$ns attach-agent $n4 $sink2
$ns connect $tcp2 $sink2
$tcp2 set fid_ 2

# set up Application layer protocol
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp1 set type_ FTP
set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$ftp2 set type_ FTP

$ns at 0.1 "$ftp1 start"
$ns at 0.5 "$ftp2 start"
$ns at 4.1 "$ftp1 stop"
$ns at 4.5 "$ftp2 stop"

$ns at 5.0 "finish"
$ns run