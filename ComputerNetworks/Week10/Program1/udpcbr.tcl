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

#set up some nodes 
set n0 [$ns node]
set n1 [$ns node]

#set up links 
$ns duplex-link $n0 $n1 10Mb 10ms DropTail

# set up UDP - connection 
set udp [new Agent/UDP]
$ns attach-agent $n0 $udp 

set null [new Agent/Null] 
$ns attach-agent $n1 $null
$ns connect $udp $null

# set up CBR over CDP 
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packet_size_ 1000
$cbr set rate_ 1Mb
$cbr set random_ false 

$ns at 0.1 "$cbr start"
$ns at 4.5 "$cbr stop"
$ns at 5.0 "finish"

$ns run